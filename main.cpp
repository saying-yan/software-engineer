#include <stdio.h>
#include "Game.hpp"
#include "CmdlineParse.hpp"

int main()
{
    uint8_t _order[2] = {2, 0};
    Game g = Game(2, _order, 10000);
    g.Map_Display();

    return 0;
}