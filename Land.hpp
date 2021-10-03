#pragma once

#include <cstdint>

enum LandType
{
    Land_Empty,
    Land_Origin,
    Land_ToolHouse,
    Land_GiftHouse,
    Land_MagicHouse,
    Land_Park,
    //Land_Hospitol,
    //Land_Prison,
    Land_Mine,
};

class Land
{
public:
    LandType type;       //空地、起点、道具屋、礼品屋、魔法屋、公园、矿地
    uint8_t owner;       //隶属玩家 0,1,2,3,4
    uint8_t level;       //地产 level
    uint8_t isblock;     //有无障碍
    uint8_t mine_credit; //矿地点数----------------------------------------------------------------------
    int origin_price;    //地段售价

    Land(LandType _type = Land_Empty, int _origin_price = 0); //初始化
    int Sell_price();                                         //获取售价
};