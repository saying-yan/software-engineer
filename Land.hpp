#pragma once

#include <cstdint>

const uint8_t LOC_START = 0;      //起点位置
const uint8_t LOC_HOSPITAL = 14;  //医院位置
const uint8_t LOC_TOOLHOUSE = 28; //道具屋位置
const uint8_t LOC_GIFTHOUSE = 35; //礼品屋位置
const uint8_t LOC_PRISON = 49;    //监狱位置
const uint8_t LOC_MAGICHOUSE = 63;//魔法屋位置
const uint8_t LOC_MINE_START = 64;//矿地开始位置

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
    uint8_t owner;    //隶属玩家 0,1,2,3,4
    uint8_t level;    //地产 level
    uint8_t tool;     //道具类型
    int origin_price; //地段售价

    Land(LandType _type=Land_Empty, int _origin_price=0); //初始化
    int Sell_price();                        //获取售价
};