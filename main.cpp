#include <stdio.h>
#include "Game.hpp"
#include "CmdlineParse.hpp"

int main()
{
    uint8_t _order[2] = {2, 3};
    Game g = Game(2, _order, 10000);

    printf("player_total_num��%d\n", g.player_total_num);
    printf("player_current_num��%d\n", g.player_current_num);
    printf("player_index[0]��%d\n", g.player_index[0]);
    printf("player_index[1]��%d\n", g.player_index[1]);
    for (int i = 0; i < g.player_current_num; i++)
    {
        printf("player[%d].name��%d\n", g.player_index[i], g.player[g.player_index[i]].name);
        printf("player[%d].fund��%d\n", g.player_index[i], g.player[g.player_index[i]].fund);
        printf("player[%d].credit��%d\n", g.player_index[i], g.player[g.player_index[i]].credit);
        printf("player[%d].location��%d\n", g.player_index[i], g.player[g.player_index[i]].location);
    }
    return 0;
}