#ifndef __newCardDefence__LevelSelectScene__ //如果没有定义__newCardDefence__LevelSelectScene__宏，防止头文件重复包含
#define __newCardDefence__LevelSelectScene__ //定义__newCardDefence__LevelSelectScene__宏

#include "SceneBase.h" //包含场景基类的头文件

class LevelSelectScene : public SceneBase //定义一个类，继承自SceneBase类，用于显示关卡选择场景
{
public:

    CREATE_FUNC(LevelSelectScene); //使用宏定义一个创建函数，用于创建对象

    virtual ~LevelSelectScene(); //定义一个虚的析构函数，用于销毁对象，释放资源

protected:

    virtual bool init(); //定义一个虚函数，用于初始化对象，返回一个布尔值

    virtual void onEnter()override; //定义一个虚函数，用于在场景进入时执行，覆盖父类的同名函数

private:

    int _iThemeIndex = 0; //定义一个整数类型的成员变量，用于存储当前主题索引，初始值为0

    Layer* _pLevelSelectLayer = nullptr; //定义一个指向层的指针，用于存储关卡选择层，初始值为nullptr
};

#endif /* defined(__newCardDefence__LevelSelectScene__) */ //结束条件编译
