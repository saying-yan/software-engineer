#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "Game.hpp"

int main()
{
    srand((unsigned)time(NULL));

    //����ѡ��
    int user, user_c;
    int user_num = 0;
    printf("��ѡ��2~4����ɫ��1.Ǯ���� 2.������ 3.��С�� 4.�𱴱�������������\n");
    cin >> user;
    user_c = user;
    while (user_c)
    {
        user_c /= 10;
        user_num++;
    }
    uint8_t *charactor = new uint8_t[user_num];
    if (user_num < 2 || user_num > 4)
        exit(0);
    else
    {
        for (int i = 0; i < user_num; i++)
        {
            charactor[i] = (user / (int)(pow(10, (user_num - i - 1)))) % 10 - 1;
        }
    }

    //�����ʽ�ѡ��
    int i_fund;
    printf("�����������ʽ𣬷�Χ��1000~50000 ����������Ĭ��10000��\n");
    cin >> i_fund;
    // printf("%d\n", i_fund);
    if (i_fund > 50000 || i_fund < 1000)
    {
        i_fund = 10000;
    }
    if (cin.rdstate())
    {
        cin.clear();
        cin.ignore(65535, '\n');
    }

    //������Ϸ
    Game *g = new Game(user_num, charactor, i_fund);
    g->Game_Start();

    return 0;
}