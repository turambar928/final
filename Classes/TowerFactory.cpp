// TowerFactory.cpp

#include "TowerFactory.h"
#include "TowerBase.h"
#include "TowerStar.h"

// 根据指定类型创建塔对象
TowerBase* TowerFactory::createTower(const TowerType& rTowerType, Vec2 tposition) {
    // 初始化塔指针为nullptr
    TowerBase* pTower = nullptr;

    // 初始化塔的ID
    int towerId = 0;

    // 根据塔的类型选择相应的ID
    switch (rTowerType) {
    case en_GreenTower: towerId = 1; break;
    case en_CloverTower: towerId = 4; break;
    case en_ShitTower: towerId = 7; break;
    case en_StarTower: towerId = 13; pTower = TowerStar::create(); break;
    default: break;
    }

    // 如果塔的ID小于8，创建普通的TowerBase对象
    if (towerId < 8) {
        pTower = TowerBase::create(towerId);
    }

    // 设置塔的位置
    pTower->setPosition(tposition);

    // 返回创建的塔对象
    return pTower;
}
