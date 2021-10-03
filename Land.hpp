#pragma once

#include <cstdint>

//const uint8_t LOC_START = 0;       //ï¿½ï¿½ï¿½Î»ï¿½ï¿?
//const uint8_t LOC_HOSPITAL = 14;   //Ò½ÔºÎ»ï¿½ï¿½
//const uint8_t LOC_TOOLHOUSE = 28;  //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Î»ï¿½ï¿½
//const uint8_t LOC_GIFTHOUSE = 35;  //ï¿½ï¿½Æ·ï¿½ï¿½Î»ï¿½ï¿½
//const uint8_t LOC_PRISON = 49;     //ï¿½ï¿½ï¿½ï¿½Î»ï¿½ï¿½
//const uint8_t LOC_MAGICHOUSE = 63; //Ä§ï¿½ï¿½ï¿½ï¿½Î»ï¿½ï¿½
//const uint8_t LOC_MINE_START = 64; //ï¿½ï¿½Ø¿ï¿½Ê¼Î»ï¿½ï¿?

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
    LandType type;    //¿ÕµØ¡¢Æðµã¡¢µÀ¾ßÎÝ¡¢ÀñÆ·ÎÝ¡¢Ä§·¨ÎÝ¡¢Ò½Ôº¡¢¼àÓü¡¢¿óµØ
    uint8_t owner;    //Á¥ÊôÍæ¼Ò 0,1,2,3,4
    uint8_t level;    //µØ²ú level
    uint8_t tool;     //µÀ¾ßÀàÐÍ
    int origin_price; //µØ¶ÎÊÛ¼Û

    Land(LandType _type = Land_Empty, int _origin_price = 0); //³õÊ¼»¯
    int Sell_price();                                         //»ñÈ¡ÊÛ¼Û
};