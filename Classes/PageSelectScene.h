// 防止头文件重复包含
#ifndef __newCardDefence__PageSelectScene__
#define __newCardDefence__PageSelectScene__

// 引入PublicDefine头文件，包含一些公共的宏和类型定义
#include "PublicDefine.h"

// 定义一个PageSelectScene类，继承自Scene类，用于显示和选择关卡的场景
class PageSelectScene : public Scene
{
public:

    // 定义一个宏，用于创建PageSelectScene对象
    CREATE_FUNC(PageSelectScene);

    // 声明一个虚析构函数，用于释放内存
    virtual ~PageSelectScene();

protected:

    // 声明一个虚函数，用于初始化PageSelectScene对象，返回一个布尔值
    virtual bool init();

    // 声明一个虚函数，用于进入场景时的操作，无返回值
    virtual void onEnter()override;

private:

    // 声明一个Layer类型的指针，用于指向显示关卡的滑动视图的层
    Layer* _pPageViewLayer = nullptr;

    // 声明一个Layer类型的指针，用于指向显示菜单栏的层
    Layer* _pMenuPanelLayer = nullptr;

    // 声明一个Layer类型的指针，用于指向显示翻页按钮的层
    Layer* _pPageTurningLayer = nullptr;

};

// 结束头文件的定义
#endif /* defined(__newCardDefence__LevelSelectScene__) */
