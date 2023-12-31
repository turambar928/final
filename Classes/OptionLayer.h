// 防止头文件重复包含
#ifndef __CarrotFantasy__OptionLayer__
#define __CarrotFantasy__OptionLayer__

// 引入cocos2d头文件
#include "cocos2d.h"
// 使用cocos2d命名空间
using namespace cocos2d;

// 定义一个OptionLayer类，继承自Layer类
class OptionLayer :public Layer
{

public:

    // 定义一个宏，用于创建OptionLayer对象
    CREATE_FUNC(OptionLayer);

protected:

    // 声明一个虚函数，用于初始化OptionLayer对象，返回一个布尔值
    virtual bool init();

    // 声明一个虚函数，用于加载资源
    virtual void loadSource();
};

// 结束头文件的定义
#endif /* defined(__CarrotFantasy__OptionLayer__) */
