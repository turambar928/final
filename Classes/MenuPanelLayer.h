#ifndef __CarrotFantasy__MenuPanelLayer__ //如果没有定义__CarrotFantasy__MenuPanelLayer__宏，防止头文件重复包含
#define __CarrotFantasy__MenuPanelLayer__ //定义__CarrotFantasy__MenuPanelLayer__宏

#include "PublicDefine.h" //包含公共定义的头文件

class PageViewLayer; //声明一个类，表示分页视图层

class MenuPanelLayer :public Layer //定义一个类，继承自Layer类，用于显示菜单面板
{
public:

    CREATE_FUNC(MenuPanelLayer); //使用宏定义一个创建函数，用于创建对象

    virtual void setPageTurnFunc(const std::function<void(const bool&)>& rFuncPageTurn); //定义一个虚函数，用于设置翻页的函数，参数为一个函数对象的引用，表示翻页的函数

protected:

    virtual bool init(); //定义一个虚函数，用于初始化对象，返回一个布尔值

    virtual void createItemPanel(); //定义一个虚函数，用于创建项目面板，显示菜单项

private:

    std::function<void(const bool&)> _funcPageTurn; //定义一个函数对象类型的成员变量，用于存储翻页的函数

};


#endif /* defined(__CarrotFantasy__MenuPanelLayer__) */ //结束条件编译
