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
    LandType type;       //�յء���㡢�����ݡ���Ʒ�ݡ�ħ���ݡ���԰�����
    uint8_t owner;       //������� 0,1,2,3,4
    uint8_t level;       //�ز� level
    uint8_t isblock;     //�����ϰ�
    uint8_t mine_credit; //��ص���----------------------------------------------------------------------
    int origin_price;    //�ض��ۼ�

    Land(LandType _type = Land_Empty, int _origin_price = 0); //��ʼ��
    int Sell_price();                                         //��ȡ�ۼ�
};