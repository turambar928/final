// 防止头文件重复包含
#ifndef __CarrotFantasy__PageViewLayer__
#define __CarrotFantasy__PageViewLayer__

// 引入PublicDefine头文件，包含一些公共的宏和类型定义
#include "PublicDefine.h"
// 引入ui/UIPageView头文件，包含PageView类的定义
#include "ui/UIPageView.h"
// 使用ui命名空间，方便访问PageView类
using namespace ui;

// 定义一个PageViewLayer类，继承自Layer类，用于显示关卡的滑动视图的层
class PageViewLayer : public Layer
{
public:

    // 声明一个虚析构函数，用于释放内存
    virtual ~PageViewLayer();

    // 定义一个宏，用于创建PageViewLayer对象
    CREATE_FUNC(PageViewLayer);

    // 声明一个虚函数，用于翻页操作，参数为一个布尔值，表示向左或向右翻页
    virtual void pageTurn(const bool& rBLeft);

protected:

    // 声明一个虚函数，用于初始化PageViewLayer对象，返回一个布尔值
    virtual bool init();

    // 声明一个虚函数，用于设置页面标志的状态，参数为一个整型值，表示页面的索引
    virtual void setPageFlag(const int& rIIndex);

    // 声明一个虚函数，用于创建关卡的滑动视图
    virtual void createThemePageView();

    // 声明一个虚函数，用于创建页面标志的按钮
    virtual void createThemeFlags();

    // 声明一个虚函数，用于加载背景图片和标题
    virtual void loadBg();

private:

    // 声明一个PageView类型的指针，用于指向显示关卡的滑动视图的对象
    PageView* _pPageView = nullptr;

    // 声明一个整型变量，用于记录当前页面的索引
    int _iPageIndex = 0;

    // 声明一个Vector<MenuItemSprite*>类型的指针，用于指向存储页面标志的精灵菜单项的向量
    Vector<MenuItemSprite*>* _pPageFlagVec = nullptr;
};

// 结束头文件的定义
#endif /* defined(__CarrotFantasy__PageViewLayer__) */
