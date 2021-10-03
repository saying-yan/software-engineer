#pragma once

#include <cstdint>
#include "Land.hpp"
#include "Player.hpp"

const int MAX_PLAYER_NUM=4; //最大玩家数
const int LAND_NUM=70;      //地图格数

class Game
{
public:
    uint8_t player_total_num;      //玩家总量
    uint8_t player_current_num;    //剩余玩家数量
    uint8_t order[MAX_PLAYER_NUM]; //玩家顺序
    Player player[MAX_PLAYER_NUM]; //玩家对象组
    Land land[LAND_NUM];           //地图对象组

    Game();
    Game(uint8_t total_num, uint8_t _order[]); //初始化

    bool Set_Cur_Player(uint8_t cur_player);                        //设置当前玩家
    int Get_Cur_Player(void);                                       //获得当前玩家
    bool Set_Player_Location(uint8_t player, int loc, int delay);   //设置玩家位置
    bool Set_Land(uint8_t player, int loc, int level);              //设置 Land所属及房屋等级
    bool Set_Player_Status(uint8_t player, int _fund, int _credit); //设置玩家钱和点数
    void Set_Player_Tool(uint8_t player, int tool_type, int num);   //设置玩家道具数
    bool Set_Barrier(int tool_type, int location);                  //放道具

    void Map_Display(); //打印地图
private:
    void display_loc(uint8_t loc); // 打印地图具体位置的字符
};

Game::Game(uint8_t total_num, uint8_t _order[])
{
    player_total_num = total_num;
    player_current_num = player_total_num;

    for (int i = 0; i < total_num; i++)
        order[i] = _order[i];

    Land_Init();
    Player_Init();
}