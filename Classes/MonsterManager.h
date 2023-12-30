
#ifndef __CarrotFantasy__MonsterManager__
#define __CarrotFantasy__MonsterManager__

// 包含公共定义的头文件
#include "PublicDefine.h"

// 前置声明实体类
class Entity;

// 定义一个怪物管理器类，继承自引用类
class MonsterManager : public Ref
{
public:

    // 使用宏定义创建一个怪物管理器对象的静态函数，实现单例模式
    CREATE_INSTANCE_FUNC(MonsterManager);

    // 使用宏定义销毁一个怪物管理器对象的静态函数，释放内存
    DESTROY_INSTANCE_FUNC();

    // 定义一个虚函数，返回一个怪物对象的向量的引用，用来存放所有的怪物对象
    virtual MonsterVec& getMonsterVec();

    // 定义一个虚函数，设置一个成员函数指针，参数是一个函数对象，接受一个指向实体类的指针，无返回值，用来将怪物对象添加到层中
    virtual void setFuncAddMonsterToLayer(const std::function<void(Entity*)>& rFuncAddMonsterToLayer);

    // 定义一个虚函数，清除管理器中的所有怪物对象
    virtual void clearManager();

    // 定义一个虚函数，清除所有怪物对象的被攻击锁定状态
    virtual void clearBeAtkLockState();

protected:

    // 声明怪物基类为友元类，可以访问管理器类的私有成员
    friend class MonsterBase;

    // 定义一个虚函数，开启检查游戏结束的标志，参数是一个指向引用类型的指针
    virtual void openCheckGameEnd(Ref* pSender);

    // 定义一个虚函数，添加一个怪物对象到管理器中，参数是一个指向怪物基类的指针
    virtual void addMonster(MonsterBase* pBullet);

    // 定义一个虚函数，初始化管理器对象
    virtual bool init();

    // 定义一个虚函数，注册怪物死亡事件，当收到通知时，调用相应的函数
    virtual void registerDeadEvent();

    // 定义一个虚函数，从管理器中移除一个怪物对象，参数是一个指向引用类型的指针
    virtual void removeMonsterFromManager(Ref* pMonster);

private:

    // 定义一个指向怪物对象的向量的指针，初始为nullptr，用来存放所有的怪物对象
    MonsterVec* _pMonsterVec = nullptr;

    // 定义一个成员函数指针，参数是一个指向实体类的指针，无返回值，用来将怪物对象添加到层中
    std::function<void(Entity*)> _funcAddMonsterToLayer;

    // 定义一个布尔类型的成员变量，表示是否开启检查游戏结束的标志，初始为false
    bool _bIsOpenCheckGameEnd = false;

private:

    // 定义管理器类的构造函数
    MonsterManager();

    // 定义管理器类的析构函数
    virtual ~MonsterManager();

    // 删除管理器类的拷贝构造函数，防止对象被复制
    MonsterManager(const MonsterManager&) = delete;

    // 删除管理器类的赋值运算符重载函数，防止对象被赋值
    MonsterManager& operator=(const MonsterManager&) = delete;

};


#endif /* defined(__CarrotFantasy__MonsterManager__) */
