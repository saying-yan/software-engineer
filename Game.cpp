#include "Game.hpp"
#include <iostream>
#include <cstring>
#include <windows.h>
#include <algorithm>

using namespace std;

const string s_Roll = string("roll");
const string s_Query = string("query");
const string s_Quit = string("quit");
const string s_Sell = string("sell");
const string s_Block = string("block");
// const string s_Bomb = string("Bomb");
const string s_Robot = string("robot");
const string s_Help = string("help");
const string s_Step = string("step");

Game::Game(uint8_t _player_total_num, uint8_t _order[], int init_fund)
{
    player_total_num = _player_total_num;
    player_current_num = player_total_num;

    for (int i = 0; i < _player_total_num; i++)
    {
        player_index[i] = _order[i];
    }

    current_player_i = 0;
    current_player = &(player[player_index[current_player_i]]);

    Map_Init();
    Player_Init(init_fund);
    Map_Display();
}

void Game::Map_Init()
{
    for (int i = 1; i < 29; i++)
    {
        land[i] = Land(Land_Empty, 200);
    }
    for (int i = 29; i < 35; i++)
    {
        land[i] = Land(Land_Empty, 500);
    }
    for (int i = 35; i < 64; i++)
    {
        land[i] = Land(Land_Empty, 300);
    }
    for (int i = 64; i < 70; i++)
    {
        land[i] = Land(Land_Mine, 0);
    }

    land[0] = Land(Land_Origin, 0);
    // land[14] = Land(Land_Hospitol, 0);
    land[14] = Land(Land_Park, 0);
    land[28] = Land(Land_ToolHouse, 0);
    land[35] = Land(Land_GiftHouse, 0);
    // land[49] = Land(Land_Prison, 0);
    land[49] = Land(Land_Park, 0);
    land[63] = Land(Land_MagicHouse, 0);
    land[64].credit = 60;
    land[65].credit = 80;
    land[66].credit = 40;
    land[67].credit = 100;
    land[68].credit = 80;
    land[69].credit = 20;
}

void Game::Player_Init(int init_fund)
{
    for (int i = 0; i < this->player_current_num; i++)
    {
        player[player_index[i]] = Player(player_index[i], init_fund);
    }
}

void Game::Turn_to_next_Player()
{
    current_player_i = (current_player_i + 1) % player_current_num;
    current_player = &(player[player_index[current_player_i]]);
}

uint8_t Game::Get_cur_player_index(char _name)
{
    for (int i = 0; i < this->player_current_num; i++)
    {
        if (this->player[this->player_index[i]].name == _name)
        {
            return this->player_index[i];
        }
    }
    printf("Get_cur_player_index wrong!\n");
    exit(0);
}

void Game::Player_Bankrupt(Player p)
{
    if (p.fund < 0)
    {
        //标记破产
        p.bankrupt = 1;

        //玩家顺序表更新
        int i;
        for (i = 0; i < player_current_num; i++)
        {
            if (player[player_index[i]].name == p.name)
                break;
        }
        for (; i < player_current_num - 1; i++)
        {
            player_index[i] = player_index[i + 1];
        }

        //玩家数量减一
        player_current_num--;

        //地产归公
        for (i = 0; i < LAND_NUM; i++)
        {
            if (land[i].owner == p.name)
            {
                land[i].owner = 0;
                land[i].level = 0;
            }
        }

        //因为破产玩家是当前玩家，所以其退出后后面玩家排序向前移 1，防止在Turn_to_next_Player()里溢出
        current_player_i--;
    }
}

void Game::Lay_Block(int loc)
{
    if (this->current_player->tool->barrier <= 0)
    {
        printf("你没有路障！\n");
        return;
    }

    if (loc > 10 || loc < -10)
    {
        printf("距离指定错误！\n");
        return;
    }

    uint8_t p_location = this->current_player->location + loc;
    if (p_location >= 0)
    {
        p_location %= 70;
    }
    else
    {
        p_location += 70;
    }

    if (this->land[p_location].isblock == 1)
    {
        printf("指定地点已经有路障了，无法再放！\n");
        return;
    }

    this->land[p_location].isblock = 1;
    this->current_player->tool->barrier--;
    printf("你用了一个路障，还剩%d个\n", this->current_player->tool->barrier);
}

void Game::Lay_Robot()
{
    if (this->current_player->tool->robot <= 0)
    {
        printf("你没有机器人！\n");
        return;
    }

    uint8_t p_location = this->current_player->location;
    uint8_t count = 0;
    for (int i = 0; i < 10; i++)
    {
        if (land[(p_location + i) % 70].isblock == 1)
        {
            count++;
        }
        land[(p_location + i) % 70].isblock = 0;
    }
    this->current_player->tool->robot--;
    printf("你用了一个机器人，还剩%d个，清扫了前方%d个路障\n", this->current_player->tool->robot, count);
}

void Game::Roll()
{
    int step = rand() % 6 + 1; //步数为1~6的随机数
    printf("前进%d步\n", step);
    for (int i = 0; i < step; ++i)
    {
        this->current_player->location = (this->current_player->location + 1) % 70;
        if (this->land[this->current_player->location].isblock)
        {
            this->land[this->current_player->location].isblock = 0;
            printf("你撞到了路障，走了%d步就停了\n", i + 1);
            return;
        }
    }
}

string Game::Get_charactor_name(char _name)
{
    string s;
    switch (_name)
    {
    case 'Q':
        s = "钱夫人";
        break;
    case 'A':
        s = "阿土伯";
        break;
    case 'S':
        s = "孙小美";
        break;
    case 'J':
        s = "金贝贝";
        break;
    }
    return s;
}

void Game::MagicHouse()
{
    printf("请输入要陷害的玩家：");
    for (int i = 0; i < player_current_num; i++)
    {
        printf("%c——%s ", player[player_index[i]].name, Get_charactor_name(player[player_index[i]].name).c_str());
    }
    printf("（其他输入表示放弃）\n ");

    char c;
    cin >> c;
    uint8_t flag = 0;
    for (int i = 0; i < player_current_num; i++)
    {
        if (c == player[player_index[i]].name)
            flag++;
    }
    if (flag == 1)
    {
        this->player[Get_cur_player_index(c)].magic_days += 2;

        printf("%s被魔法陷害，轮空轮数加2，共需轮空%d轮\n", Get_charactor_name(this->player[Get_cur_player_index(c)].name).c_str(), this->player[Get_cur_player_index(c)].magic_days);
        return;
    }

    printf("输入无效！\n");
}

void Game::Help()
{
    printf("命令帮助：\n");
    printf("命令                       功能说明                        参数说明\n");
    printf("Roll            掷骰子命令，行走1`6步，步数随机产生 。         无\n");
    printf("Sell n          轮到玩家时，可出售自己的任意房产，出售    n为房产的绝对位置\n");
    printf("                价格为投资总成本的2倍\n");
    printf("Block n         玩家可将路障放置到当前位置前后10部的任     n为前后相对距离\n");
    printf("                何位置，任一玩家经过将被拦截，一次有效       负数表示后方\n");
    printf("Robot           使用该道具将清除前方10步内任何其他道具\n");
    printf("Query           显示自家资产\n");
    printf("Help            查看命令帮助\n");
    printf("Quit            强制退出\n");
}

void Game::Game_Start()
{
    while (true)
    {
        // system("cls");
        this->Map_Display();

        string name;
        while (true)
        {
            if (this->current_player->isBankrupt())
                break;

            if (this->current_player->magic_days > 0)
            {
                this->current_player->magic_days--;
                printf("魔法生效中，%s本轮轮空，还剩%d轮魔法消失！\n", Get_charactor_name(this->current_player->name).c_str(), this->current_player->magic_days);

                if (this->land[this->current_player->location].owner != this->current_player->name && this->land[this->current_player->location].owner != 0)
                {
                    //交租
                    this->current_player->PayRent(this->land[this->current_player->location], this->player[Get_cur_player_index(this->land[this->current_player->location].owner)]);
                    //破产清算
                    Player_Bankrupt(*this->current_player);
                }

                break;
            }

            switch (this->current_player->name)
            {
            case 'Q':
                name = "钱夫人>";
                break;
            case 'A':
                name = "阿土伯>";
                break;
            case 'S':
                name = "孙小美>";
                break;
            case 'J':
                name = "金贝贝>";
                break;
            }
            this->current_player->colorfulPrintf(name);

            string s;
            cin >> s; //读取命令行指令
            transform(s.begin(), s.end(), s.begin(), ::tolower);
            if (s_Roll == s || s_Step == s) //前进：摇色子、指定步数
            {
                if (s_Roll == s)
                {
                    this->Roll();
                }
                else
                {
                    int n;
                    cin >> n;
                    this->current_player->Step(n);
                }

                switch (this->land[this->current_player->location].type)
                {
                case Land_Empty:
                    if (this->land[this->current_player->location].owner == 0)
                    {
                        this->current_player->BuyLand(this->land[this->current_player->location]);
                    }
                    else if (this->land[this->current_player->location].owner == this->current_player->name)
                    {
                        this->current_player->UpdateBuliding(this->land[this->current_player->location]);
                    }
                    else
                    {
                        this->current_player->PayRent(this->land[this->current_player->location], this->player[Get_cur_player_index(this->land[this->current_player->location].owner)]);

                        //破产清算
                        Player_Bankrupt(*this->current_player);
                    }
                    break;
                case Land_ToolHouse:
                    this->current_player->ToolHouse();
                    break;
                case Land_GiftHouse:
                    this->current_player->GiftHouse();
                    break;
                case Land_MagicHouse:
                    this->MagicHouse();
                    break;
                case Land_Mine:
                    this->current_player->Mine(this->land[this->current_player->location]);
                    break;
                default:
                    break;
                }

                if (this->current_player->god_days > 0)
                {
                    this->current_player->god_days--;
                }
                break; // break退出此人循环
            }
            else if (s_Quit == s) //终止游戏
            {
                exit(0);
            }
            else if (s_Query == s) //查看玩家状态
            {
                this->current_player->CheckStatus();
            }
            else if (s_Sell == s) //出售地产
            {
                int n;
                cin >> n;
                this->current_player->SellBuliding(this->land[n]);
            }
            else if (s_Block == s) //使用障碍
            {
                int n;
                cin >> n;
                this->Lay_Block(n);
            }
            else if (s_Robot == s) //使用机器人
            {
                this->Lay_Robot();
            }
            else if (s_Help == s) //显示帮助信息
            {
                this->Help();
            }
        }

        if (player_current_num == 1)
        {
            break;
        }

        this->Turn_to_next_Player();
    }

    this->Turn_to_next_Player();
    printf("%s获得胜利！\n", Get_charactor_name(this->current_player->name).c_str());
    return;
}
