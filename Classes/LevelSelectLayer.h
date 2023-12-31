#ifndef __newCardDefence__LevelSelectLayer__ //如果没有定义__newCardDefence__LevelSelectLayer__宏，防止头文件重复包含
#define __newCardDefence__LevelSelectLayer__ //定义__newCardDefence__LevelSelectLayer__宏

#include "PublicDefine.h" //包含公共定义的头文件

class LevelSelectLayer : public Layer //定义一个类，继承自Layer类，用于显示关卡选择界面
{
public:

    CREATE_FUNC(LevelSelectLayer); //使用宏定义一个创建函数，用于创建对象

    virtual ~LevelSelectLayer(); //定义一个虚的析构函数，用于销毁对象，释放资源

protected:

    virtual bool init(); //定义一个虚函数，用于初始化对象，返回一个布尔值

    virtual void loadSource(); //定义一个虚函数，用于加载资源，从精灵帧缓存中获取图片

    virtual void loadLevel(); //定义一个虚函数，用于加载关卡，从本地数据中获取关卡数据

    virtual void loadMenuItem(); //定义一个虚函数，用于加载菜单项，创建并添加菜单项

    virtual std::tuple<int, bool> checkLevelIsLockAndBarrierIsClean(const int& rILevelIndex); //定义一个常量虚函数，用于检查关卡是否被锁定和障碍物是否被清除，参数为一个整数类型的引用，表示关卡索引，返回一个元组，包含一个整数和一个布尔值

    virtual void changeToGameScene(); //定义一个虚函数，用于切换到游戏场景，开始游戏

    virtual void loadData(); //定义一个虚函数，用于加载数据，从CSV文件中读取数据

private:

    int _iPageIndex = 0; //定义一个整数类型的成员变量，用于存储当前页面索引，初始值为0

    int _iCurLevelIndex = 0; //定义一个整数类型的成员变量，用于存储当前关卡索引，初始值为0

    ValueMap _DataValueMap; //定义一个值映射类型的成员变量，用于存储关卡数据

private:

    Sprite* _pLockSprite = nullptr; //定义一个指向精灵的指针，用于存储锁定精灵，初始值为nullptr

    MenuItemSprite* _pStartBtn = nullptr; //定义一个指向菜单项精灵的指针，用于存储开始按钮，初始值为nullptr
};

#endif /* defined(__newCardDefence__LevelSelectLayer__) */ //结束条件编译
