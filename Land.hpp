#pragma once

#include <cstdint>

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

    Land();
    Land(LandType _type, uint8_t _origin_price); //初始化
    int Sell_price();                            //获取售价
};

Land::Land(LandType _type, uint8_t _origin_price)
{
    type = _type;
    owner = 0;
    level = 0;
    tool = 0;
    origin_price = _origin_price;
}

int Land::Sell_price()
{
    if (type == Land_Empty && owner != 0)
        return origin_price * (level + 1);
    else
        return 0;
}

void Land_Init();