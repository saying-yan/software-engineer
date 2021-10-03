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
    printf("fund: %d\ncredit: %d\ntool--barrier: %d\ntool--robot: %d\n", fund, credit, tool->barrier, tool->robot);
}