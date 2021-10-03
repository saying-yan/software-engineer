#include "Player.hpp"

Player::Player(uint8_t index, int _fund)
{
    char s[4] = {'Q', 'A', 'S', 'J'};
    name = s[index];
    fund = _fund;
    credit = 0;
    location = Land_Origin;
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

void Player_Init();

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