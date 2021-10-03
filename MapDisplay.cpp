#include <cstdio>
#include "Game.hpp"

void Game::display_loc(uint8_t loc) {
    for (int i = 0; i < this->player_total_num; ++i) {
        if (!this->player[i].isBankrupt() && this->player[i].location == loc) {
            this->player[i].colorfulPrintf(this->player[i].name);
            return;
        }
    }
    if (this->land[loc].type == Land_Origin) {
        putchar('S');
    }
    else if (this->land[loc].type == Land_Hospitol) {
        putchar('H');
    }
    else if (this->land[loc].type == Land_ToolHouse) {
        putchar('T');
    }
    else if (this->land[loc].type == Land_GiftHouse) {
        putchar('G');
    }
    else if (this->land[loc].type == Land_Prison) {
        putchar('P');
    }
    else if (this->land[loc].type == Land_MagicHouse) {
        putchar('M');
    }
    else if (this->land[loc].type == Land_Mine) {
        putchar('$');
    }
    else if (this->land[loc].type == Land_Empty) {
        if (this->land[loc].owner == 0) {
            putchar(this->land[loc].level);
        } else {
            uint8_t owner = this->land[loc].owner;
            this->player[owner].colorfulPrintf(this->land[loc].level);
        }
    }
    else {
        printf("[Error] invalid LandType\n");
    }
    return;
}

void Game::Map_Display() {
    for (int i = 0; i < 29; ++i) {
        this->display_loc(i);
    }
    putchar('\n');
    for (int i = 0; i < 6; ++i) {
        this->display_loc(69-i);
        for (int j = 0; j < 27; ++j) putchar(' ');
        this->display_loc(29+i);
        putchar('\n');
    }
    for (int i = 63; i >= 35; --i) {
        this->display_loc(i);
    }
    putchar('\n');
}