
#ifndef __CarrotFantasy__MonsterLayer__
#define __CarrotFantasy__MonsterLayer__

// 包含实体层基类的头文件
#include "EntityLayerBase.h"

// 前置声明怪物基类
class MonsterBase;


// 定义一个怪物层类，继承自实体层基类
class MonsterLayer :public EntityLayerBase
{
public:

    // 使用宏定义创建一个怪物层对象的静态函数
    CREATE_FUNC(MonsterLayer);

protected:

    // 重写实体层基类的初始化函数
    virtual bool init();

    // 定义一个注册怪物死亡事件的函数
    virtual void registerMonsterDeadEvent();

    // 定义一个怪物死亡的函数，参数是一个指向引用类型的指针
    virtual void monsterDead(Ref* pData);

    // 重写实体层基类的退出场景函数
    virtual void onExit()override;

};


#endif /* defined(__CarrotFantasy__MonsterLayer__) */
