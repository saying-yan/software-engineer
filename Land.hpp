#pragma once

#include <cstdint>

const uint8_t LOC_START = 0;
const uint8_t LOC_HOSPITAL = 14;
const uint8_t LOC_TOOLHOUSE = 28;
const uint8_t LOC_GIFTHOUSE = 35;
const uint8_t LOC_PRISON = 49;
const uint8_t LOC_MAGICHOUSE = 63;
const uint8_t LOC_MINE_START = 64;

enum LandType
{
    Land_Empty,
    Land_Origin,
    Land_ToolHouse,
    Land_GiftHouse,
    Land_MagicHouse,
    Land_Hospitol,
    Land_Prison,
    Land_Mine,
};

class Land
{
public:
    LandType type;    //空地、起点、道具屋、礼品屋、魔法屋、医院、监狱、矿地
    uint8_t owner;    //隶属玩家
    uint8_t level;    //地产 level
    uint8_t tool;     //道具类型
    int origin_price; //地段售价

    Land(LandType _type = Land_Empty, int _origin_price = 0); //初始化
    int Sell_price();                                         //获取售价
};