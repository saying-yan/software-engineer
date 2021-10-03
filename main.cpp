#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "Game.hpp"

int main()
{
    srand((unsigned)time(NULL));

    int s, s_c;
    int s_length = 0;

    //����ѡ��
    printf("��ѡ��2~4����ɫ��1.Ǯ���� 2.������ 3.��С�� 4.�𱴱�������������\n");
    cin >> s;
    s_c = s;
    while (s_c)
    {
        s_c /= 10;
        s_length++;
    }

    uint8_t* charactor = new uint8_t[s_length];
    if (s_length < 2 || s_length > 4)
        exit(0);
    else
    {
        for (int i = 0; i < s_length; i++)
        {
            charactor[i] = (s / (int)(pow(10, (s_length - i - 1)))) % 10 - 1;
        }
    }

    //������Ϸ
    Game *g = new Game(s_length, charactor, 10000);
    g->Game_Start();

    return 0;
}