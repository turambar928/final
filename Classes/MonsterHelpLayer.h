
#ifndef __CarrotFantasy__MonsterHelpLayer__
#define __CarrotFantasy__MonsterHelpLayer__

// 包含公共定义的头文件
#include "PublicDefine.h"

// 定义一个怪物帮助层类，继承自层类
class MonsterHelpLayer :public Layer
{
public:

    // 使用宏定义创建一个怪物帮助层对象的静态函数
    CREATE_FUNC(MonsterHelpLayer);

protected:

    // 重写层类的初始化函数
    virtual bool init()override;
};

#endif /* defined(__CarrotFantasy__MonsterHelpLayer__) */
