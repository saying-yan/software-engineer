#pragma once

#include <cstdio>
#include <cstdint>
#include "Land.hpp"

struct Tool
{
    uint8_t bomb;
    uint8_t barrier;
    uint8_t robot;
};

enum Color
{
    Red,
    Green,
    Yellow,
    Blue
};

class Player
{
public:
    char name;         //������
    int fund;          //�����
    int credit;        //����
    uint8_t location;  //λ��
    struct Tool *tool; //����
    uint8_t god_days;  //����ʣ������
    uint8_t hos_days;  //סԺʣ������
    uint8_t pri_days;  //����ʣ������
    bool bankrupt;     //�Ƿ��Ʋ�
    bool is_sell;      //�����Ƿ���۹��˷���
    //int m_inMagic;     //ֹͣʣ������

    uint8_t color; // ��ɫ

    Player(uint8_t _name = 0, int _fund = 0); //��ʼ��

    bool isBankrupt();  //��ѯ�Ƿ��Ʋ�
    void CheckStatus(); //��ѯ״̬

    void LayTool();        //�ŵ���
    void UpdateBuliding(); //��������
    void SellBuliding();   //������
    void Roll();           //��ɫ��

    void MagicWork();  //ħ����Ч
    void ToolWork();   //�������λ�ã�������Ч
    void BuyLand();    //����յأ���յ�
    void PayRent();    //�������˷����������
    void ToolHouse();  //���빤����
    void MagicHouse(); //����ħ����
    void GiftHouse();  //����������
    void Hospital();   //����ҽԺ
    void Prison();     //�������
    void Mine();       //������

    void colorfulPrintf(char c); // ����ɫ���
};
