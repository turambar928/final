// �������﹤����ͷ�ļ�
#include "MonsterFactory.h"
// ������������ͷ�ļ�
#include "MonsterBase.h"

// ����һ�����﹤���ĺ��������ݴ���Ĺ������Ͳ���������������һ����Ӧ���͵Ĺ������
MonsterBase* MonsterFactory::createMonster(const MonsterType& rMonsterType)
{
    // ����һ��ָ���������ָ�룬������Ŵ����Ĺ�����󣬳�ʼΪnullptr
    MonsterBase* pMonster = nullptr;

    // ����һ�����ͱ�����������Ź���ı�ţ���ʼΪ0
    int iMosterId = 0;
    // ʹ��switch��䣬���ݹ������Ͳ����Ĳ�ͬ���������Ÿ���ͬ��ֵ
    switch (rMonsterType) {
        // �������������en_Land_Pink���Ͱѹ�������Ϊ2
    case en_Land_Pink:iMosterId = 2;
        break;
        // �������������en_Land_Star���Ͱѹ�������Ϊ1
    case en_Land_Star:iMosterId = 1;
        break;
        // �������������en_Land_Nima���Ͱѹ�������Ϊ3
    case en_Land_Nima:iMosterId = 3;
        break;
        // �������������en_Fly_Yellow���Ͱѹ�������Ϊ7
    case en_Fly_Yellow:iMosterId = 7;
        break;
        // �������������en_Fly_Blue���Ͱѹ�������Ϊ8
    case en_Fly_Blue:iMosterId = 8;
        break;
        // �������������en_Fat_Green���Ͱѹ�������Ϊ11
    case en_Fat_Green:iMosterId = 11;
        break;
        // �������������en_Land_Boss_Pink���Ͱѹ�������Ϊ5
    case en_Land_Boss_Pink:iMosterId = 5;
        break;
        // �������������en_Land_Boss_Star���Ͱѹ�������Ϊ4
    case en_Land_Boss_Star:iMosterId = 4;
        break;
        // �������������en_Land_Boss_Nima���Ͱѹ�������Ϊ6
    case en_Land_Boss_Nima:iMosterId = 6;
        break;
        // �������������en_Fly_Boss_Yellow���Ͱѹ�������Ϊ9
    case en_Fly_Boss_Yellow:iMosterId = 9;
        break;
        // �������������en_Fly_Boss_Blue���Ͱѹ�������Ϊ10
    case en_Fly_Boss_Blue:iMosterId = 10;
        break;
        // �������������en_Fat_Boss_Green���Ͱѹ�������Ϊ12
    case en_Fat_Boss_Green:iMosterId = 12;
        break;
        // �������������en_Big_Oldboss���Ͱѹ�������Ϊ14
    case en_Big_Oldboss:iMosterId = 14;
        break;
        // �������������en_Fat_Oldboss���Ͱѹ�������Ϊ15
    case en_Fat_Oldboss:iMosterId = 15;
        break;
        // �������������en_Fly_Oldboss���Ͱѹ�������Ϊ16
    case en_Fly_Oldboss:iMosterId = 16;
        break;
        // �������������en_Land_Oldboss���Ͱѹ�������Ϊ17
    case en_Land_Oldboss:iMosterId = 17;
        break;
        // �������������en_Boss_Big���Ͱѹ�������Ϊ13
    case en_Boss_Big:iMosterId = 13;
        break;
        // �����������������ֵ���Ͳ����κβ���
    default:
        break;
    }
    // ���ù������ľ�̬���������ݹ����Ŵ���һ��������󣬸�ֵ��ָ��
    pMonster = MonsterBase::create(iMosterId);

    // ���ش����Ĺ�������ָ��
    return pMonster;
}
