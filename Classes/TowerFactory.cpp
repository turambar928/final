// TowerFactory.cpp

#include "TowerFactory.h"
#include "TowerBase.h"
#include "TowerStar.h"

// ����ָ�����ʹ���������
TowerBase* TowerFactory::createTower(const TowerType& rTowerType, Vec2 tposition) {
    // ��ʼ����ָ��Ϊnullptr
    TowerBase* pTower = nullptr;

    // ��ʼ������ID
    int towerId = 0;

    // ������������ѡ����Ӧ��ID
    switch (rTowerType) {
    case en_GreenTower: towerId = 1; break;
    case en_CloverTower: towerId = 4; break;
    case en_ShitTower: towerId = 7; break;
    case en_StarTower: towerId = 13; pTower = TowerStar::create(); break;
    default: break;
    }

    // �������IDС��8��������ͨ��TowerBase����
    if (towerId < 8) {
        pTower = TowerBase::create(towerId);
    }

    // ��������λ��
    pTower->setPosition(tposition);

    // ���ش�����������
    return pTower;
}
