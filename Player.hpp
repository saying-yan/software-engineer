#pragma once

#include <cstdint>

struct Tool
{
    uint8_t bomb;
    uint8_t barrier;
    uint8_t robot;
};

class Player
{
public:
    uint8_t name;      //人物名
    int fund;          //金币数
    int credit;        //点数
    uint8_t location;  //位置
    struct Tool *tool; //道具
    uint8_t god_days;  //财神剩余天数
    uint8_t hos_days;  //住院剩余天数
    uint8_t pri_days;  //坐牢剩余天数
    bool bankrupt;     //是否破产
    bool is_sell;      //本轮是否出售过了房产
    //int m_inMagic;     //停止剩余轮数

    Player();
    Player(uint8_t _name, int _fund); //初始化

    bool isBankrupt();  //查询是否破产
    void CheckStatus(); //查询状态

    void LayTool();        //放道具
    void UpdateBuliding(); //升级建筑
    void SellBuliding();   //卖建筑
    void Roll();           //掷色子

    void MagicWork();  //魔法生效
    void ToolWork();   //进入道具位置，道具生效
    void BuyLand();    //进入空地，买空地
    void PayRent();    //进入他人房产，付租金
    void ToolHouse();  //进入工具屋
    void MagicHouse(); //进入魔法屋
    void GiftHouse();  //进入礼物屋
    void Hospital();   //进入医院
    void Prison();     //进入监狱
    void Mine();       //到达矿地
};

Player::Player()
{
}

Player::Player(uint8_t _name, int _fund)
{
    name = _name;
    fund = _fund;
    credit = 0;
    location = Land_Origin;
    tool->bomb = 0;
    tool->barrier = 0;
    tool->robot = 0;
    god_days = 0;
    bankrupt = 0;
    hos_days = 0;
    pri_days = 0;
}