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
    printf("�������Ƿ�Ҫ�������յأ�������yes/no\n");
    scanf("%s", str);
    if (fund < _land.origin_price) //��Ҳ���
    {
        printf("��Ľ�Ҳ���\n");
        return;
    }
    while (i == 0)
    {
        if (!strcmp(str, "yes")) //���
        {
            fund = fund - _land.origin_price; //������˻���Ǯ
            _land.owner = name;               //��������������
            //�����ͼ
            i = 1; //����ѭ��
        }
        else if (!strcmp(str, "no")) //�����
        {
            i = 1; //����ѭ��
        }
        else
        {
            printf("ע������淶\n"); //���벻�淶����������
            printf("�������Ƿ�Ҫ�������յأ�������yes/no\n");
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
        printf("��ķ����Ѿ���Ħ��¥��\n"); //������Ħ��¥��ֱ���˳�����
        return;
    }
    printf("�������Ƿ�����Ҫ���������������yes/no\n");
    scanf("%s", str);
    if (fund < _land.origin_price) //��Ҳ���
    {
        printf("��Ľ�Ҳ���\n");
        return;
    }
    while (i == 0)
    {
        if (!strcmp(str, "yes")) //����
        {
            fund = fund - _land.origin_price; //������˻���Ǯ
            _land.level++;
            //�����ͼ
            i = 1; //����ѭ��
        }
        else if (!strcmp(str, "no")) //�����
        {
            i = 1; //����ѭ��
        }
        else
        {
            printf("ע������淶\n"); //���벻�淶����������
            printf("�������Ƿ�����Ҫ���������������yes/no\n");
            scanf("%s", str);
        }
    }
}