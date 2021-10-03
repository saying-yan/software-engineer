#pragma once

#include <cstdint>
#include "Land.hpp"
#include "Player.hpp"

#define MAX_PLAYER_NUM 4 //最大玩家数
#define LAND_NUM 70      //地图格数

class Game
{
public:
    uint8_t player_total_num;             //玩家总量
    uint8_t player_current_num;           //剩余玩家数量
    uint8_t player_index[MAX_PLAYER_NUM]; //在场玩家顺序索引
    Player player[MAX_PLAYER_NUM];        //玩家对象组
    Land land[LAND_NUM];                  //地图对象组

    Game();
    Game(uint8_t total_num, uint8_t _order[], int init_fund); //初始化
    void Map_Init();                                          //初始化地图
    void Player_Init(int init_fund);                          //初始化玩家

    bool Set_Cur_Player(uint8_t cur_player);                        //设置当前玩家
    int Get_Cur_Player(void);                                       //获得当前玩家
    bool Set_Player_Location(uint8_t player, int loc, int delay);   //设置玩家位置
    bool Set_Land(uint8_t player, int loc, int level);              //设置 Land所属及房屋等级
    bool Set_Player_Status(uint8_t player, int _fund, int _credit); //设置玩家钱和点数
    void Set_Player_Tool(uint8_t player, int tool_type, int num);   //设置玩家道具数
    bool Set_Barrier(int tool_type, int location);                  //放道具

    void Map_Display();             //打印地图
    void Player_Bankrupt(Player p); //清算人物资产是否破产
    void Roll(Player p);            //掷色子，移位
};

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
    for (int i = 35; i < 54; i++)
    {
        land[i] = Land(Land_Empty, 300);
    }
    for (int i = 54; i < 70; i++)
    {
        land[i] = Land(Land_Mine, 0);
    }
}

void Game::Player_Init(int init_fund)
{
    for (int i; i < player_current_num; i++)
    {
        player[i] = Player(player_index[i], init_fund);
    }
}

Game::Game(uint8_t _player_total_num, uint8_t _order[], int init_fund)
{
    player_total_num = _player_total_num;
    player_current_num = player_total_num;

    for (int i = 0; i < _player_total_num; i++) //在场玩家顺序索引
        player_index[i] = _order[i];

    Map_Init();             //生成地图
    Player_Init(init_fund); //生成玩家
}
