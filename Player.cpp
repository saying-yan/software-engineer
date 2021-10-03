#include "Player.hpp"
#include <stdio.h>
#include <string.h>

Player::Player(uint8_t index, int _fund)
{
    char s[4] = {'Q', 'A', 'S', 'J'};
    name = s[index];
    fund = _fund;
    credit = 0;
    location = 0;
    tool = new Tool;
    tool->bomb = 0;
    tool->barrier = 0;
    tool->robot = 0;
    god_days = 0;
    bankrupt = 0;
    hos_days = 0;
    pri_days = 0;

    color = index;
}

bool Player::isBankrupt()
{
    return this->bankrupt;
}

void Player::colorfulPrintf(char c)
{
    if (this->color == Red)
    {
        printf("\033[31;0m");
        putchar(c);
        printf("\033[0m");
    }
    else if (this->color == Green)
    {
        printf("\033[32;0m");
        putchar(c);
        printf("\033[0m");
    }
}

void Player::BuyLand(Land &_land)
{
    char str[30];
    int i = 0;
    printf("请问您是否要购买这块空地？请输入yes/no\n");
    scanf("%s", str);
    if (fund < _land.origin_price) //金币不足
    {
        printf("你的金币不足\n");
        return;
    }
    while (i == 0)
    {
        if (!strcmp(str, "yes")) //买地
        {
            fund = fund - _land.origin_price; //从玩家账户扣钱
            _land.owner = name;               //更改土地所有者
            //输出地图
            i = 1; //跳出循环
        }
        else if (!strcmp(str, "no")) //不买地
        {
            i = 1; //跳出循环
        }
        else
        {
            printf("注意输入规范\n"); //输入不规范，重新输入
            printf("请问您是否要购买这块空地？请输入yes/no\n");
            scanf("%s", str);
        }
    }
}

void Player::UpdateBuliding(Land &_land)
{
    char str[30];
    int i = 0;
    if (_land.level == 3)
    {
        printf("你的房产已经是摩天楼了\n"); //房产是摩天楼，直接退出升级
        return;
    }
    printf("请问您是否升级要这个房产？请输入yes/no\n");
    scanf("%s", str);
    if (fund < _land.origin_price) //金币不足
    {
        printf("你的金币不足\n");
        return;
    }
    while (i == 0)
    {
        if (!strcmp(str, "yes")) //升级
        {
            fund = fund - _land.origin_price; //从玩家账户扣钱
            _land.level++;
            //输出地图
            i = 1; //跳出循环
        }
        else if (!strcmp(str, "no")) //不买地
        {
            i = 1; //跳出循环
        }
        else
        {
            printf("注意输入规范\n"); //输入不规范，重新输入
            printf("请问您是否升级要这个房产？请输入yes/no\n");
            scanf("%s", str);
        }
    }
}