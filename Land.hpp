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
    LandType type;    //�յء���㡢�����ݡ���Ʒ�ݡ�ħ���ݡ�ҽԺ�����������
    uint8_t owner;    //�������
    uint8_t level;    //�ز� level
    uint8_t tool;     //��������
    int origin_price; //�ض��ۼ�

    Land(LandType _type = Land_Empty, int _origin_price = 0); //��ʼ��
    int Sell_price();                                         //��ȡ�ۼ�
};