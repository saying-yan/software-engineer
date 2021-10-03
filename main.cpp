#include <stdio.h>
#include "Game.hpp"
#include "CmdlineParse.hpp"

int main()
{
    uint8_t _order[2] = {2, 3};
    Game game = Game(2, _order, 10000);
    printf("player_total_num：%d\n", game.player_total_num);
    printf("player_current_num：%d\n", game.player_current_num);
    printf("player_index[0]：%d\n", game.player_index[0]);
    printf("player_index[1]：%d\n", game.player_index[1]);

    return 0;
}