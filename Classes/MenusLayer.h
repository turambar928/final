// 防止头文件重复包含
#ifndef __CarrotFantasy__MenusLayer__
#define __CarrotFantasy__MenusLayer__

// 包含公共定义的头文件
#include "PublicDefine.h"

// 定义一个菜单层的类，继承自Layer类
class MenusLayer :public Layer
{
public:

    // 使用宏定义创建一个静态的创建函数
    CREATE_FUNC(MenusLayer);

protected:

    // 重写初始化函数
    virtual bool init();

    // 创建菜单项的函数
    virtual void createMenuItems();
};

// 结束头文件的定义
#endif /* defined(__CarrotFantasy__MenusLayer__) */
