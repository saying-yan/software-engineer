#define _CRT_SECURE_NO_WARNINGS
#include "Player.hpp"
#include "Game.hpp"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

Player::Player(uint8_t index, int _fund)
{
    char s[4] = {'Q', 'A', 'S', 'J'};
    name = s[index];
    fund = _fund;
    credit = 0;
    location = 0;
    tool = new Tool;
    // tool->bomb = 0;
    tool->barrier = 0;
    tool->robot = 0;
    god_days = 0;
    bankrupt = 0;
    // hos_days = 0;
    // pri_days = 0;
    color = Color::Red;

    switch (index)
    {
    case 0:
        color = Color::Red;
        break;
    case 1:
        color = Color::Green;
        break;
    case 2:
        color = Color::Yellow;
        break;
    case 3:
        color = Color::Blue;
        break;
    }
}

bool Player::isBankrupt()
{
    return this->bankrupt;
}

void Player::colorfulPrintf(char c)
{
    if (this->color == Color::Red)
    {
        printf("\033[31m");
        putchar(c);
        printf("\033[0m");
    }
    else if (this->color == Color::Green)
    {
        printf("\033[32m");
        putchar(c);
        printf("\033[0m");
    }
    else if (this->color == Color::Yellow)
    {
        printf("\033[33m");
        putchar(c);
        printf("\033[0m");
    }
    else if (this->color == Color::Blue)
    {
        printf("\033[34m");
        putchar(c);
        printf("\033[0m");
    }
}

void Player::Step(int n)
{
    int step = n;
    for (int i = 0; i < step; ++i)
    {
        //会用到路途中道具的判断，暂时留空
        this->location = (this->location + 1) % 70;
    }
}

void Player::colorfulPrintf(string s)
{
    if (this->color == Color::Red)
    {
        printf("\033[31m");
        cout << s;
        printf("\033[0m");
    }
    else if (this->color == Color::Green)
    {
        printf("\033[32m");
        cout << s;
        printf("\033[0m");
    }
    else if (this->color == Color::Yellow)
    {
        printf("\033[33m");
        cout << s;
        printf("\033[0m");
    }
    else if (this->color == Color::Blue)
    {
        printf("\033[34m");
        cout << s;
        printf("\033[0m");
    }
}

void Player::CheckStatus()
{
    //printf("fund: %d\ncredit: %d\ntool--bomb: %d\ntool--barrier: %d\ntool--robot: %d\n", fund, credit, tool->bomb, tool->barrier, tool->robot);
    cout << "fund: " << this->fund << endl;
    cout << "credit: " << this->credit << endl;
    cout << "tool: " << endl
         << "  -- barrier: " << (this->tool->barrier + 0) << endl
         << "  -- robot: " << (this->tool->robot + 0) << endl;
}

void Player::Mine(Land _land)
{
    this->credit += _land.credit;
    return;
}

void Player::SellBuliding(Land &_land)
{
    if (_land.owner != name || _land.type != Land_Empty) //输入的不是自己的地产
    {
        printf("这不是你的地产!\n");
        return;
    }

    printf("确认要卖出%d号位置的地产吗？yes/no\n");
    string s;
    cin >> s;
    if (s == string("yes"))
    {
        printf("你卖出了此房产，获得收入：%d\n", _land.Sell_price());
        fund += _land.Sell_price(); //获得卖房收益
        _land.owner = 0;            //土地所有者清除
        _land.level = 0;            //土地等级归为空地
    }
}

void Player::BuyLand(Land &_land) //买空地
{
    char str[30];
    int i = 0;
    printf("你走到了一片无主空地，价格：%d，请问您是否要购买？请输入yes/no\n", _land.origin_price);
    scanf("%s", str);
    while (true)
    {
        if (!strcmp(str, "yes")) //买地
        {
            if (fund < _land.origin_price) //金币不足
            {
                printf("你的资金不足\n");
                return;
            }

            fund = fund - _land.origin_price; //从玩家账户扣钱
            _land.owner = name;               //更改土地所有者
            printf("现在这块地是你的地产了，租金：%d\n", _land.Sell_price() / 4);
            break;
        }
        else if (!strcmp(str, "no")) //不买地
        {
            break;
        }
        else
        {
            printf("注意输入规范\n"); //输入不规范，重新输入
            printf("请问您是否要购买这块空地？请输入yes/no\n");
            scanf("%s", str);
        }
    }
}

void Player::UpdateBuliding(Land &_land) //升级房产
{
    if (_land.level == 3)
    {
        printf("你来到了你的房产，它已经是摩天楼了，不能再升级！\n"); //房产是摩天楼，直接退出升级
        return;
    }

    printf("你来到了你的房产，请问是否升级它？请输入yes/no：\n");
    string s;
    cin >> s;
    while (true)
    {
        if (s == string("yes")) //升级
        {
            if (fund < _land.origin_price) //资金不足
            {
                printf("你的资金不足！\n");
                return;
            }

            fund -= _land.origin_price; //从玩家账户扣钱
            _land.level++;

            string s;
            switch (_land.level)
            {
            case 1:
                s = "茅屋";
                break;
            case 2:
                s = "洋房";
                break;
            case 3:
                s = "摩天楼";
                break;
            }
            printf("你把此处房产升级成为了%s，售价：%d  租金：%d\n", s.c_str(), _land.Sell_price(), (int)_land.Sell_price() / 4);
            break;
        }
        else if (s == string("no")) //不升级
        {
            break;
        }
        else
        {
            printf("注意输入规范，请重新输入yes/no：\n"); //输入不规范，重新输入
        }
    }
}

void Player::PayRent(Land &_land, Player &_owner) //支付租金
{
    int rent;
    if (god_days > 0) //玩家有财神，免租金
    {
        printf("财神降临，免地租！\n");
        return;
    }
    rent = 0.5 * _land.origin_price * (_land.level + 1);

    //打印提示语句
    string name;
    switch (_owner.name)
    {
    case 'Q':
        name = "钱夫人";
        break;
    case 'A':
        name = "阿土伯";
        break;
    case 'S':
        name = "孙小美";
        break;
    case 'J':
        name = "金贝贝";
        break;
    }
    printf("你来到了%s的地产，\n", name.c_str());

    //支付租金
    if (rent > fund) //金币不足，玩家破产，owner获得其所有金币
    {
        _owner.fund = _owner.fund + fund;
        fund = -1;
        printf("仅剩的钱全交了，你破产了\n", fund);
        return;
    }
    else //金币足够支付租金
    {
        _owner.fund = _owner.fund + rent;
        fund = fund - rent;
        printf("缴纳租金: %d    剩余：%d\n", rent, this->fund);
        return;
    }
}

void Player::GiftHouse()
{
    printf("你来到了礼品屋，请选择一份您喜欢的礼物\n");
    printf("编号1：\t奖金：2000元\n");
    printf("编号2：\t点数卡：200点\n");
    printf("编号3：\t财神：路过玩家地产，均可免费，5轮有效\n");
    printf("您要选择编号：（输入编号之外则认为退出礼品屋）\n");
    int s;
    cin >> s;
    switch (s)
    {
    case 1:
        this->fund += 2000;
        break;
    case 2:
        this->credit += 200;
        break;
    case 3:
        this->god_days = 6;
        break;
    default:
        break;
    }
}

void Player::ToolHouse(void)
{
    char k;
    printf("欢迎来到道具屋，请通过输入编号选择所需道具：\n");
    printf("编号        名称        价格        显示方式\n");
    printf("1           路障         50            # \n");
    printf("2         机器娃娃       30            无\n");
    printf("按F退出\n");
    cin >> k;
    switch (k)
    {
    case '1': //键入1
        this->Buy_Tool(1);
        break;
    case '2': //键入2
        this->Buy_Tool(2);
        break;
    case 'f': //键入F
        return;
    case 'F': //键入F
        return;
    default:
        printf("非法输入！自动退出。\n");
        return;
    }
}
void Player::Buy_Tool(int tool_type) //玩家买道具
{
    if (tool_type == 1)
    {
        if (this->credit >= 50)
        {
            this->tool->barrier++;
            this->credit -= 50;
        }
        else
            printf("没有足够点数\n");
    }
    else if (tool_type == 2)
    {
        if (this->credit >= 30)
        {
            this->tool->robot++;
            this->credit -= 30;
        }
        else
            printf("没有足够点数\n");
    }
}
