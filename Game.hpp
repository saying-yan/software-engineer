#pragma once

#include <cstdint>
#include "Land.hpp"
#include "Player.hpp"

const int MAX_PLAYER_NUM = 4; //最大玩家数
const int LAND_NUM = 70;      //地图格数

class Game
{
public:
    uint8_t player_total_num;             //玩家总量
    uint8_t player_current_num;           //剩余玩家数量
    uint8_t player_index[MAX_PLAYER_NUM]; //在场玩家顺序索引
    Player player[MAX_PLAYER_NUM];        //玩家对象组
    Land land[LAND_NUM];                  //地图对象组

    Player *current_player;                   //当前玩家
    uint8_t current_player_i;                 //当前玩家索引
    uint8_t Get_cur_player_index(char _name); //根据名字返回玩家对应索引
    string Get_charactor_name(char _name);    //根据玩家名字返回对应人名

    void Game_Start(); //开始游戏，解析命令行输入执行对应操作

    Game(){};
    Game(uint8_t total_num, uint8_t _order[], int init_fund); //初始化
    void Map_Init();                                          //初始化地图
    void Player_Init(int init_fund);                          //初始化玩家
    void Turn_to_next_Player();                               //切换到下一个玩家

    void Lay_Block(int loc);        //使用障碍
    void Lay_Robot();               //使用机器人
    void Map_Display();             //打印地图
    void display_loc(uint8_t loc);  // 打印地图具体位置的字符
    void Player_Bankrupt(Player p); //清算人物资产是否破产
    void Roll(Player p);            //掷色子，移位
    void Help();                    //帮助信息
    void Roll();                    //掷色子
    void MagicHouse();              //魔法屋

    //测试功能
    bool Set_Cur_Player(uint8_t cur_player);                        //设置当前玩家
    bool Set_Player_Location(uint8_t player, int loc, int delay);   //设置玩家位置
    bool Set_Land(uint8_t player, int loc, int level);              //设置 Land所属及房屋等级
    bool Set_Player_Status(uint8_t player, int _fund, int _credit); //设置玩家钱和点数
    void Set_Player_Tool(uint8_t player, int tool_type, int num);   //设置玩家道具数
    bool Set_Barrier(int tool_type, int location);                  //放置道具
};