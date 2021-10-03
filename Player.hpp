#pragma once

#include <cstdio>
#include <cstdint>
#include <string>
#include "Land.hpp"

using namespace std;

struct Tool
{
    // uint8_t bomb;
    uint8_t barrier;
    uint8_t robot;
};

enum class Color
{
    Red,
    Green,
    Yellow,
    Blue,
};

class Player
{
public:
    char name;         //人物名
    int fund;          //金币数
    int credit;        //点数
    uint8_t location;  //位置
    struct Tool *tool; //道具
    uint8_t god_days;  //财神剩余天数
    // uint8_t hos_days;  //住院剩余天数
    // uint8_t pri_days; //坐牢剩余天数
    uint8_t magic_days; //魔法剩余天数
    bool bankrupt;      //是否破产
    bool is_sell;       //本轮是否出售过了房产

    Color color; // 颜色

    Player(uint8_t _name = 0, int _fund = 0); //初始化

    bool isBankrupt();     //查询是否破产
    void CheckStatus();    //查询状态
    void Check_Bankrupt(); //清算资产

    void UpdateBuliding(Land &_land); //升级建筑
    void SellBuliding();              //卖建筑
    void Roll();                      //掷色子

    uint8_t CheckLand();       //检测进入的地形
    void MagicWork();          //魔法生效
    void ToolWork();           //进入道具位置，道具生效
    void BuyLand(Land &_land); //进入空地，买空地
    void PayRent();            //进入他人房产，付租金
    void ToolHouse();          //进入工具屋
    void MagicHouse();         //进入魔法屋
    void GiftHouse();          //进入礼物屋
    void Hospital();           //进入医院
    void Prison();             //进入监狱
    void Mine();               //到达矿地

    void colorfulPrintf(char c);   // 带颜色输出
    void colorfulPrintf(string s); //带颜色输出
};
