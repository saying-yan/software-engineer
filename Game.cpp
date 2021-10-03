#include "Game.hpp"
#include <iostream>
#include <cstring>
#include <windows.h>

using namespace std;
const string s_Roll = string("Roll");
const string s_Query = string("Query");
const string s_Quit = string("Quit");
const string s_Sell = string("Sell");
const string s_Block = string("Block");
// const string s_Bomb = string("Bomb");
const string s_Robot = string("Robot");
const string s_Help = string("Help");
const string s_Step = string("Step");

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

void Game::Lay_Block(int loc)
{
    uint8_t p_location = this->current_player->location;
    if (p_location >= 0)
    {
        p_location = (p_location + loc) % 70;
    }
    else
    {
        p_location += 70;
    }
    this->land[p_location].isblock = 1;
}

void Game::Lay_Robot()
{
    uint8_t p_location = this->current_player->location;
    for (int i = 0; i < 10; i++)
    {
        land[(p_location + i) % 70].isblock = 0;
    }
}

void Game::Game_Start()
{
    string s;
    while (true)
    {
        system("cls");
        this->Map_Display();
        while (true)
        {
            string name;
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

            cin >> s; //读取命令行指令

            if (s_Roll == s)
            {
                this->current_player->Roll();
                uint8_t loc = this->current_player->location;
                int num;
                switch (this->land[loc].type)
                {
                case Land_Empty:

                    break;
                case Land_ToolHouse:

                    break;
                case Land_GiftHouse:

                    break;
                case Land_MagicHouse:

                    break;
                case Land_Mine:
                    num = this->land[this->current_player->location].credit;
                    this->current_player->Mine(num);
                    break;
                default:
                    break;
                }

                break; // break退出此人循环
            }
            else if (s_Quit == s)
            {
                exit(0);
            }
            else if (s_Query == s)
            {
                this->current_player->CheckStatus();
            }
            else if (s_Sell == s)
            {
                //this->current_player->;
                printf("Sell not finished!\n");
            }
            else if (s_Block == s)
            {
                //this->current_player->;
                printf("Block not finished!\n");
            }
            // else if (s_Bomb == s)
            // {
            //     //this->current_player->;
            //     printf("Bomb not finished!\n");
            // }
            else if (s_Robot == s)
            {
                //this->current_player->;
                printf("Robot not finished!\n");
            }
            else if (s_Help == s)
            {
                //this->current_player->;
                printf("Help not finished!\n");
            }
            else if (s_Step == s)
            {
                //this->current_player->;
                printf("Step not finished!\n");
            }
        }
        this->Turn_to_next_Player();
    }
}
