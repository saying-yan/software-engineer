#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "Game.hpp"

int main()
{
    srand((unsigned)time(NULL));

    //人数选择
    int user, user_c;
    int user_num = 0;
    printf("请选择2~4个角色：1.钱夫人 2.阿土伯 3.孙小美 4.金贝贝，可自由排序\n");
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

    //开局资金选择
    int i_fund;
    printf("请输入启动资金，范围：1000~50000 （输入其他默认10000）\n");
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

    //开启游戏
    Game *g = new Game(user_num, charactor, i_fund);
    g->Game_Start();

    return 0;
}