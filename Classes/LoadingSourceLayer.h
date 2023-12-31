#ifndef __CarrotFantasy__LoadingSourceLayer__ //如果没有定义__CarrotFantasy__LoadingSourceLayer__宏，防止头文件重复包含
#define __CarrotFantasy__LoadingSourceLayer__ //定义__CarrotFantasy__LoadingSourceLayer__宏

#include "PublicDefine.h" //包含公共定义的头文件

class LoadingSourceLayer : public Layer //定义一个类，继承自Layer类，用于显示加载资源的层
{
public:

    CREATE_FUNC(LoadingSourceLayer); //使用宏定义一个创建函数，用于创建对象

    virtual void setFuncShowMenuPanel(const std::function<void()>& rFuncShowMenuPanel); //定义一个虚函数，用于设置显示菜单面板的函数，参数为一个函数对象的引用

protected:

    virtual void onEnter()override; //定义一个虚函数，用于在层进入时执行，覆盖父类的同名函数

    virtual bool init(); //定义一个虚函数，用于初始化对象，返回一个布尔值

    virtual void loadSource(); //定义一个虚函数，用于加载资源，从精灵帧缓存中获取图片

protected:

    std::function<void()> _funShowMenuPanel; //定义一个函数对象类型的成员变量，用于存储显示菜单面板的函数

    Label* _pLoadingTitle = nullptr; //定义一个指向标签的指针，用于存储加载标题，初始值为nullptr
};

#endif /* defined(__CarrotFantasy__LoadingSourceLayer__) */ //结束条件编译
