#pragma once

#include <cstdint>
#include "Land.hpp"
#include "Player.hpp"

const int MAX_PLAYER_NUM = 4; //��������
const int LAND_NUM = 70;      //��ͼ����

class Game
{
public:
    uint8_t player_total_num;             //�������
    uint8_t player_current_num;           //ʣ���������
    uint8_t player_index[MAX_PLAYER_NUM]; //�ڳ����˳������
    Player player[MAX_PLAYER_NUM];        //��Ҷ�����
    Land land[LAND_NUM];                  //��ͼ������

    Player *current_player;                   //��ǰ���
    uint8_t current_player_i;                 //��ǰ�������
    uint8_t Get_cur_player_index(char _name); //�������ַ�����Ҷ�Ӧ����
    string Get_charactor_name(char _name);    //����������ַ��ض�Ӧ����

    void Game_Start(); //��ʼ��Ϸ����������������ִ�ж�Ӧ����

    Game(){};
    Game(uint8_t total_num, uint8_t _order[], int init_fund); //��ʼ��
    void Map_Init();                                          //��ʼ����ͼ
    void Player_Init(int init_fund);                          //��ʼ�����
    void Turn_to_next_Player();                               //�л�����һ�����

    void Lay_Block(int loc);        //ʹ���ϰ�
    void Lay_Robot();               //ʹ�û�����
    void Map_Display();             //��ӡ��ͼ
    void display_loc(uint8_t loc);  // ��ӡ��ͼ����λ�õ��ַ�
    void Player_Bankrupt(Player p); //���������ʲ��Ƿ��Ʋ�
    void Roll(Player p);            //��ɫ�ӣ���λ
    void Help();                    //������Ϣ
    void Roll();                    //��ɫ��
    void MagicHouse();              //ħ����

    //���Թ���
    bool Set_Cur_Player(uint8_t cur_player);                        //���õ�ǰ���
    bool Set_Player_Location(uint8_t player, int loc, int delay);   //�������λ��
    bool Set_Land(uint8_t player, int loc, int level);              //���� Land���������ݵȼ�
    bool Set_Player_Status(uint8_t player, int _fund, int _credit); //�������Ǯ�͵���
    void Set_Player_Tool(uint8_t player, int tool_type, int num);   //������ҵ�����
    bool Set_Barrier(int tool_type, int location);                  //���õ���
};