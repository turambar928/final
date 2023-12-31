// 防止头文件重复包含
#ifndef __CarrotFantasy__MonsterFactory__
#define __CarrotFantasy__MonsterFactory__

// 包含公共定义的头文件
#include "PublicDefine.h"

// 定义一个怪物工厂类
class MonsterFactory
{
public:

    // 定义一个静态函数，根据传入的怪物类型参数，创建并返回一个对应类型的怪物对象
    static MonsterBase* createMonster(const MonsterType& rMonsterType);
};

// 结束头文件的定义
#endif /* defined(__CarrotFantasy__MonsterFactory__) */
