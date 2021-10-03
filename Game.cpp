#include "Game.hpp"

Game::Game(uint8_t _player_total_num, uint8_t _order[], int init_fund)
{
    player_total_num = _player_total_num;
    player_current_num = player_total_num;

    for (int i = 0; i < _player_total_num; i++) //玩家顺序
    {
        player_index[i] = _order[i];
    }

    Map_Init();             //生成地图
    Player_Init(init_fund); //生成玩家
}

void Game::Map_Init()
{
    land[0] = Land(Land_Origin, 0);
    for (int i = 1; i < 29; i++)
    {
        land[i] = Land(Land_Empty, 200);
    }
    for (int i = 29; i < 35; i++)
    {
        land[i] = Land(Land_Empty, 500);
    }
    for (int i = 35; i < 64; i++)
    {
        land[i] = Land(Land_Empty, 300);
    }
    for (int i = 64; i < 70; i++)
    {
        land[i] = Land(Land_Mine, 0);
    }
}

void Game::Player_Init(int init_fund)
{
    for (int i = 0; i < this->player_current_num; i++)
    {
        player[player_index[i]] = Player(player_index[i], init_fund);
    }
}