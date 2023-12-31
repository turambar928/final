#ifndef __CarrotFantasy__LoadingScene__ //如果没有定义__CarrotFantasy__LoadingScene__宏，防止头文件重复包含
#define __CarrotFantasy__LoadingScene__ //定义__CarrotFantasy__LoadingScene__宏

#include "cocos2d.h" //包含cocos2d框架的头文件
using namespace cocos2d; //使用cocos2d命名空间

class GameScene; //声明一个类，表示游戏场景

class LoadingScene :public Scene //定义一个类，继承自Scene类，用于显示加载场景
{
public:

    CREATE_FUNC(LoadingScene); //使用宏定义一个创建函数，用于创建对象

protected:

    virtual bool init()override; //定义一个虚函数，用于初始化对象，返回一个布尔值，覆盖父类的同名函数

    virtual void onEnter()override; //定义一个虚函数，用于在场景进入时执行，覆盖父类的同名函数

    virtual void onExit()override; //定义一个虚函数，用于在场景退出时执行，覆盖父类的同名函数

    virtual void sourceLoadCallBack(Ref* pData); //定义一个虚函数，用于在资源加载完成时执行，参数为一个引用类型的指针

protected:

    GameScene* _pGameScene = nullptr; //定义一个指向游戏场景的指针，用于存储游戏场景对象，初始值为nullptr

};

#endif /* defined(__CarrotFantasy__LoadingScene__) */ //结束条件编译
