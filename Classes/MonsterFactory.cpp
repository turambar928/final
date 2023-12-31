// 包含怪物工厂的头文件
#include "MonsterFactory.h"
// 包含怪物基类的头文件
#include "MonsterBase.h"

// 定义一个怪物工厂的函数，根据传入的怪物类型参数，创建并返回一个对应类型的怪物对象
MonsterBase* MonsterFactory::createMonster(const MonsterType& rMonsterType)
{
    // 声明一个指向怪物基类的指针，用来存放创建的怪物对象，初始为nullptr
    MonsterBase* pMonster = nullptr;

    // 声明一个整型变量，用来存放怪物的编号，初始为0
    int iMosterId = 0;
    // 使用switch语句，根据怪物类型参数的不同，给怪物编号赋不同的值
    switch (rMonsterType) {
        // 如果怪物类型是en_Land_Pink，就把怪物编号设为2
    case en_Land_Pink:iMosterId = 2;
        break;
        // 如果怪物类型是en_Land_Star，就把怪物编号设为1
    case en_Land_Star:iMosterId = 1;
        break;
        // 如果怪物类型是en_Land_Nima，就把怪物编号设为3
    case en_Land_Nima:iMosterId = 3;
        break;
        // 如果怪物类型是en_Fly_Yellow，就把怪物编号设为7
    case en_Fly_Yellow:iMosterId = 7;
        break;
        // 如果怪物类型是en_Fly_Blue，就把怪物编号设为8
    case en_Fly_Blue:iMosterId = 8;
        break;
        // 如果怪物类型是en_Fat_Green，就把怪物编号设为11
    case en_Fat_Green:iMosterId = 11;
        break;
        // 如果怪物类型是en_Land_Boss_Pink，就把怪物编号设为5
    case en_Land_Boss_Pink:iMosterId = 5;
        break;
        // 如果怪物类型是en_Land_Boss_Star，就把怪物编号设为4
    case en_Land_Boss_Star:iMosterId = 4;
        break;
        // 如果怪物类型是en_Land_Boss_Nima，就把怪物编号设为6
    case en_Land_Boss_Nima:iMosterId = 6;
        break;
        // 如果怪物类型是en_Fly_Boss_Yellow，就把怪物编号设为9
    case en_Fly_Boss_Yellow:iMosterId = 9;
        break;
        // 如果怪物类型是en_Fly_Boss_Blue，就把怪物编号设为10
    case en_Fly_Boss_Blue:iMosterId = 10;
        break;
        // 如果怪物类型是en_Fat_Boss_Green，就把怪物编号设为12
    case en_Fat_Boss_Green:iMosterId = 12;
        break;
        // 如果怪物类型是en_Big_Oldboss，就把怪物编号设为14
    case en_Big_Oldboss:iMosterId = 14;
        break;
        // 如果怪物类型是en_Fat_Oldboss，就把怪物编号设为15
    case en_Fat_Oldboss:iMosterId = 15;
        break;
        // 如果怪物类型是en_Fly_Oldboss，就把怪物编号设为16
    case en_Fly_Oldboss:iMosterId = 16;
        break;
        // 如果怪物类型是en_Land_Oldboss，就把怪物编号设为17
    case en_Land_Oldboss:iMosterId = 17;
        break;
        // 如果怪物类型是en_Boss_Big，就把怪物编号设为13
    case en_Boss_Big:iMosterId = 13;
        break;
        // 如果怪物类型是其他值，就不做任何操作
    default:
        break;
    }
    // 调用怪物基类的静态函数，根据怪物编号创建一个怪物对象，赋值给指针
    pMonster = MonsterBase::create(iMosterId);

    // 返回创建的怪物对象的指针
    return pMonster;
}
