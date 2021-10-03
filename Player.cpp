#define _CRT_SECURE_NO_WARNINGS
#include "Player.hpp"
#include <iostream>
#include <stdlib.h>
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

void Player::Roll()
{
    int step = rand() % 6 + 1; //步数为1~6的随机数
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
    cout << "tool: " << endl <<
        "\tbarrier: " << (this->tool->barrier + '0') << endl <<
        "\trobot: " << (this->tool->robot + '0') << endl;
}

void Player::Mine(int c) {
    this->credit += c;
    return;
}

void Player::SellBuliding(Land& _land)
{
    if (_land.owner != name || _land.type != Land_Empty)			//输入的不是自己的地产
    {
        printf("请输入属于你的地产\n");
    }
    fund = fund + _land.origin_price * (_land.level + 1) * 2;     //获得买房资金，金额为总投资两倍
    _land.owner = 0;												//土地所有者清除
    _land.level = 0;												//土地等级归为空地
}

void Player::BuyLand(Land& _land)     //买空地
{
    char str[30];
    int i = 0;
    printf("请问您是否要购买这块空地？请输入yes/no\n");
    scanf("%s", str);
    if (fund < _land.origin_price)		//金币不足
    {
        printf("你的金币不足\n");
        return;
    }
    while (true)
    {
        if (!strcmp(str, "yes"))					//买地
        {
            fund = fund - _land.origin_price;      //从玩家账户扣钱
            _land.owner = name;						//更改土地所有者
            //输出地图
            break;
        }
        else if (!strcmp(str, "no"))			//不买地
        {
            break;
        }
        else
        {
            printf("注意输入规范\n");			//输入不规范，重新输入
            printf("请问您是否要购买这块空地？请输入yes/no\n");
            scanf("%s", str);
        }
    }
}

void Player::UpdateBuliding(Land& _land)			//升级房产
{
    char str[30];
    int i = 0;
    if (_land.level == 3)
    {
        printf("你的房产已经是摩天楼了\n");      //房产是摩天楼，直接退出升级
        return;
    }
    printf("请问您是否升级要这个房产？请输入yes/no\n");
    scanf("%s", str);
    if (fund < _land.origin_price)				//金币不足
    {
        printf("你的金币不足\n");
        return;
    }
    while (true)
    {
        if (!strcmp(str, "yes"))					//升级
        {
            fund = fund - _land.origin_price;      //从玩家账户扣钱
            _land.level++;
            //输出地图
            break;
        }
        else if (!strcmp(str, "no"))			//不买地
        {
            break;
        }
        else
        {
            printf("注意输入规范\n");			//输入不规范，重新输入
            printf("请问您是否升级要这个房产？请输入yes/no\n");
            scanf("%s", str);
        }
    }
}

void Player::PayRent(Land& _land, Player& _owner)					//player支付租金
{
    int rent;
    if (god_days > 0)      //房主在监狱医院或玩家有财神，免租金
    {
        printf("免地租\n");
        return;
    }
    rent = 0.5 * _land.origin_price * (_land.level + 1);
    if (rent > fund)													//金币不足，玩家破产，owner获得其所有金币
    {
        _owner.fund = _owner.fund + fund;
        //player 破产函数
        return;
    }
    else															//金币足够支付租金
    {
        fund = fund - rent;
        _owner.fund = _owner.fund + rent;
        return;
    }
}

void Player::GiftHouse() {
    printf("欢迎光临礼品屋，请选择一份您喜欢的礼物\n");
    printf("编号1：\t奖金：2000元\n");
    printf("编号2：\t点数卡：200点\n");
    printf("编号3：\t财神：路过玩家地产，均可免费，5轮有效\n");
    printf("您要选择编号：（输入编号之外则认为退出礼品屋）\n");
    char num[32] = { 0 };
    while (1) {
        fgets(num, 31, stdin);
        num[31] = '\0';
        if (strcmp(num, "1") == 0) {
            this->fund += 2000;
            break;
        }
        else if (strcmp(num, "2") == 1) {
            this->credit += 200;
            break;
        }
        else if (strcmp(num, "3") == 2) {
            this->god_days = 5;
            break;
        }
    }
}