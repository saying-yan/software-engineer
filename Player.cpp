#define _CRT_SECURE_NO_WARNINGS
#include "Player.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

Player::Player(uint8_t index, int _fund)
{
    char s[4] = {'Q', 'A', 'S', 'J'};
    name = s[index];
    fund = _fund;
    credit = 0;
    location = 0;
    tool = new Tool;
    // tool->bomb = 0;
    tool->barrier = 0;
    tool->robot = 0;
    god_days = 0;
    bankrupt = 0;
    // hos_days = 0;
    // pri_days = 0;
    color = Color::Red;

    switch (index)
    {
    case 0:
        color = Color::Red;
        break;
    case 1:
        color = Color::Green;
        break;
    case 2:
        color = Color::Yellow;
        break;
    case 3:
        color = Color::Blue;
        break;
    }
}

bool Player::isBankrupt()
{
    return this->bankrupt;
}

void Player::colorfulPrintf(char c)
{
    if (this->color == Color::Red)
    {
        printf("\033[31m");
        putchar(c);
        printf("\033[0m");
    }
    else if (this->color == Color::Green)
    {
        printf("\033[32m");
        putchar(c);
        printf("\033[0m");
    }
    else if (this->color == Color::Yellow)
    {
        printf("\033[33m");
        putchar(c);
        printf("\033[0m");
    }
    else if (this->color == Color::Blue)
    {
        printf("\033[34m");
        putchar(c);
        printf("\033[0m");
    }
}

void Player::Roll()
{
    int step = rand() % 6 + 1; //����Ϊ1~6�������
    for (int i = 0; i < step; ++i)
    {
        //���õ�·;�е��ߵ��жϣ���ʱ����
        this->location = (this->location + 1) % 70;
    }
}

void Player::colorfulPrintf(string s)
{
    if (this->color == Color::Red)
    {
        printf("\033[31m");
        cout << s;
        printf("\033[0m");
    }
    else if (this->color == Color::Green)
    {
        printf("\033[32m");
        cout << s;
        printf("\033[0m");
    }
    else if (this->color == Color::Yellow)
    {
        printf("\033[33m");
        cout << s;
        printf("\033[0m");
    }
    else if (this->color == Color::Blue)
    {
        printf("\033[34m");
        cout << s;
        printf("\033[0m");
    }
}

void Player::CheckStatus()
{
    //printf("fund: %d\ncredit: %d\ntool--bomb: %d\ntool--barrier: %d\ntool--robot: %d\n", fund, credit, tool->bomb, tool->barrier, tool->robot);
    cout << "fund: " << this->fund << endl;
    cout << "credit: " << this->credit << endl;
    cout << "tool: " << endl <<
        "\tbarrier: " << (this->tool->barrier + '0') << endl <<
        "\trobot: " << (this->tool->robot + '0') << endl;
}

void Player::Mine(int c) {
    this->credit += c;
    return;
}

void Player::SellBuliding(Land& _land)
{
    if (_land.owner != name || _land.type != Land_Empty)			//����Ĳ����Լ��ĵز�
    {
        printf("������������ĵز�\n");
    }
    fund = fund + _land.origin_price * (_land.level + 1) * 2;     //������ʽ𣬽��Ϊ��Ͷ������
    _land.owner = 0;												//�������������
    _land.level = 0;												//���صȼ���Ϊ�յ�
}

void Player::BuyLand(Land& _land)     //��յ�
{
    char str[30];
    int i = 0;
    printf("�������Ƿ�Ҫ�������յأ�������yes/no\n");
    scanf("%s", str);
    if (fund < _land.origin_price)		//��Ҳ���
    {
        printf("��Ľ�Ҳ���\n");
        return;
    }
    while (true)
    {
        if (!strcmp(str, "yes"))					//���
        {
            fund = fund - _land.origin_price;      //������˻���Ǯ
            _land.owner = name;						//��������������
            //�����ͼ
            break;
        }
        else if (!strcmp(str, "no"))			//�����
        {
            break;
        }
        else
        {
            printf("ע������淶\n");			//���벻�淶����������
            printf("�������Ƿ�Ҫ�������յأ�������yes/no\n");
            scanf("%s", str);
        }
    }
}

void Player::UpdateBuliding(Land& _land)			//��������
{
    char str[30];
    int i = 0;
    if (_land.level == 3)
    {
        printf("��ķ����Ѿ���Ħ��¥��\n");      //������Ħ��¥��ֱ���˳�����
        return;
    }
    printf("�������Ƿ�����Ҫ���������������yes/no\n");
    scanf("%s", str);
    if (fund < _land.origin_price)				//��Ҳ���
    {
        printf("��Ľ�Ҳ���\n");
        return;
    }
    while (true)
    {
        if (!strcmp(str, "yes"))					//����
        {
            fund = fund - _land.origin_price;      //������˻���Ǯ
            _land.level++;
            //�����ͼ
            break;
        }
        else if (!strcmp(str, "no"))			//�����
        {
            break;
        }
        else
        {
            printf("ע������淶\n");			//���벻�淶����������
            printf("�������Ƿ�����Ҫ���������������yes/no\n");
            scanf("%s", str);
        }
    }
}

void Player::PayRent(Land& _land, Player& _owner)					//player֧�����
{
    int rent;
    if (god_days > 0)      //�����ڼ���ҽԺ������в��������
    {
        printf("�����\n");
        return;
    }
    rent = 0.5 * _land.origin_price * (_land.level + 1);
    if (rent > fund)													//��Ҳ��㣬����Ʋ���owner��������н��
    {
        _owner.fund = _owner.fund + fund;
        //player �Ʋ�����
        return;
    }
    else															//����㹻֧�����
    {
        fund = fund - rent;
        _owner.fund = _owner.fund + rent;
        return;
    }
}

void Player::GiftHouse() {
    printf("��ӭ������Ʒ�ݣ���ѡ��һ����ϲ��������\n");
    printf("���1��\t����2000Ԫ\n");
    printf("���2��\t��������200��\n");
    printf("���3��\t����·����ҵز���������ѣ�5����Ч\n");
    printf("��Ҫѡ���ţ���������֮������Ϊ�˳���Ʒ�ݣ�\n");
    char num[32] = { 0 };
    while (1) {
        fgets(num, 31, stdin);
        num[31] = '\0';
        if (strcmp(num, "1") == 0) {
            this->fund += 2000;
            break;
        }
        else if (strcmp(num, "2") == 1) {
            this->credit += 200;
            break;
        }
        else if (strcmp(num, "3") == 2) {
            this->god_days = 5;
            break;
        }
    }
}