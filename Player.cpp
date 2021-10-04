#define _CRT_SECURE_NO_WARNINGS
#include "Player.hpp"
#include "Game.hpp"
#include <iostream>
#include <stdlib.h>
#include <string.h>
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

void Player::Step(int n)
{
    int step = n;
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
    cout << "tool: " << endl
         << "  -- barrier: " << (this->tool->barrier + 0) << endl
         << "  -- robot: " << (this->tool->robot + 0) << endl;
}

void Player::Mine(Land _land)
{
    this->credit += _land.credit;
    return;
}

void Player::SellBuliding(Land &_land)
{
    if (_land.owner != name || _land.type != Land_Empty) //����Ĳ����Լ��ĵز�
    {
        printf("�ⲻ����ĵز�!\n");
        return;
    }

    printf("ȷ��Ҫ����%d��λ�õĵز���yes/no\n");
    string s;
    cin >> s;
    if (s == string("yes"))
    {
        printf("�������˴˷�����������룺%d\n", _land.Sell_price());
        fund += _land.Sell_price(); //�����������
        _land.owner = 0;            //�������������
        _land.level = 0;            //���صȼ���Ϊ�յ�
    }
}

void Player::BuyLand(Land &_land) //��յ�
{
    char str[30];
    int i = 0;
    printf("���ߵ���һƬ�����յأ��۸�%d���������Ƿ�Ҫ����������yes/no\n", _land.origin_price);
    scanf("%s", str);
    while (true)
    {
        if (!strcmp(str, "yes")) //���
        {
            if (fund < _land.origin_price) //��Ҳ���
            {
                printf("����ʽ���\n");
                return;
            }

            fund = fund - _land.origin_price; //������˻���Ǯ
            _land.owner = name;               //��������������
            printf("������������ĵز��ˣ����%d\n", _land.Sell_price() / 4);
            break;
        }
        else if (!strcmp(str, "no")) //�����
        {
            break;
        }
        else
        {
            printf("ע������淶\n"); //���벻�淶����������
            printf("�������Ƿ�Ҫ�������յأ�������yes/no\n");
            scanf("%s", str);
        }
    }
}

void Player::UpdateBuliding(Land &_land) //��������
{
    if (_land.level == 3)
    {
        printf("����������ķ��������Ѿ���Ħ��¥�ˣ�������������\n"); //������Ħ��¥��ֱ���˳�����
        return;
    }

    printf("����������ķ����������Ƿ���������������yes/no��\n");
    string s;
    cin >> s;
    while (true)
    {
        if (s == string("yes")) //����
        {
            if (fund < _land.origin_price) //�ʽ���
            {
                printf("����ʽ��㣡\n");
                return;
            }

            fund -= _land.origin_price; //������˻���Ǯ
            _land.level++;

            string s;
            switch (_land.level)
            {
            case 1:
                s = "é��";
                break;
            case 2:
                s = "��";
                break;
            case 3:
                s = "Ħ��¥";
                break;
            }
            printf("��Ѵ˴�����������Ϊ��%s���ۼۣ�%d  ���%d\n", s.c_str(), _land.Sell_price(), (int)_land.Sell_price() / 4);
            break;
        }
        else if (s == string("no")) //������
        {
            break;
        }
        else
        {
            printf("ע������淶������������yes/no��\n"); //���벻�淶����������
        }
    }
}

void Player::PayRent(Land &_land, Player &_owner) //֧�����
{
    int rent;
    if (god_days > 0) //����в��������
    {
        printf("�����٣�����⣡\n");
        return;
    }
    rent = 0.5 * _land.origin_price * (_land.level + 1);

    //��ӡ��ʾ���
    string name;
    switch (_owner.name)
    {
    case 'Q':
        name = "Ǯ����";
        break;
    case 'A':
        name = "������";
        break;
    case 'S':
        name = "��С��";
        break;
    case 'J':
        name = "�𱴱�";
        break;
    }
    printf("��������%s�ĵز���\n", name.c_str());

    //֧�����
    if (rent > fund) //��Ҳ��㣬����Ʋ���owner��������н��
    {
        _owner.fund = _owner.fund + fund;
        fund = -1;
        printf("��ʣ��Ǯȫ���ˣ����Ʋ���\n", fund);
        return;
    }
    else //����㹻֧�����
    {
        _owner.fund = _owner.fund + rent;
        fund = fund - rent;
        printf("�������: %d    ʣ�ࣺ%d\n", rent, this->fund);
        return;
    }
}

void Player::GiftHouse()
{
    printf("����������Ʒ�ݣ���ѡ��һ����ϲ��������\n");
    printf("���1��\t����2000Ԫ\n");
    printf("���2��\t��������200��\n");
    printf("���3��\t����·����ҵز���������ѣ�5����Ч\n");
    printf("��Ҫѡ���ţ���������֮������Ϊ�˳���Ʒ�ݣ�\n");
    int s;
    cin >> s;
    switch (s)
    {
    case 1:
        this->fund += 2000;
        break;
    case 2:
        this->credit += 200;
        break;
    case 3:
        this->god_days = 6;
        break;
    default:
        break;
    }
}

void Player::ToolHouse(void)
{
    char k;
    printf("��ӭ���������ݣ���ͨ��������ѡ��������ߣ�\n");
    printf("���        ����        �۸�        ��ʾ��ʽ\n");
    printf("1           ·��         50            # \n");
    printf("2         ��������       30            ��\n");
    printf("��F�˳�\n");
    cin >> k;
    switch (k)
    {
    case '1': //����1
        this->Buy_Tool(1);
        break;
    case '2': //����2
        this->Buy_Tool(2);
        break;
    case 'f': //����F
        return;
    case 'F': //����F
        return;
    default:
        printf("�Ƿ����룡�Զ��˳���\n");
        return;
    }
}
void Player::Buy_Tool(int tool_type) //��������
{
    if (tool_type == 1)
    {
        if (this->credit >= 50)
        {
            this->tool->barrier++;
            this->credit -= 50;
        }
        else
            printf("û���㹻����\n");
    }
    else if (tool_type == 2)
    {
        if (this->credit >= 30)
        {
            this->tool->robot++;
            this->credit -= 30;
        }
        else
            printf("û���㹻����\n");
    }
}
