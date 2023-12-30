#ifndef __CarrotFantasy__BarrierManager__
#define __CarrotFantasy__BarrierManager__

#include "PublicDefine.h"

class Entity;

class BarrierManager: public Ref
{
public:

    CREATE_INSTANCE_FUNC(BarrierManager);//自定义的宏，声明一个静态成员函数，创建一个 BarrierManager 对象的单例
    
    DESTROY_INSTANCE_FUNC();//这自定义的宏，声明一个静态成员函数，用于销毁 BarrierManager 对象的单例，并释放内存空间。
    
    BarrierVec &getBarrierVec();//获取一个 BarrierVec 类型的引用
    
    virtual void setFuncAddBarrierToLayer(const std::function<void (Entity*)> &rFuncAddBarrierToLayer);//将障碍物对象添加到游戏层中
    
    virtual void clearBeAtkLockState();//清除所有障碍物的被攻击锁定状态，防止障碍物被多次攻击。
    
    virtual void clearManager();//清除管理器中的所有障碍物对象
protected:
    
    friend class BarrierBase;
    
    virtual void addBarrier(BarrierBase *pBarrier);//添加障碍物对象
    
    virtual bool init();//初始化
    
    virtual void registerBarrierDeadEvent();//死亡时间
    
    virtual void removeBarrierFromManager(Ref *pBarrier);//从管理器中移除
    
private:
    
    BarrierVec *_pBarrierVec = nullptr;
    
    std::function<void (Entity*)> _funcAddBarrierToLayer;//将障碍物对象添加到游戏层中
    
private:
    
    BarrierManager();
    
    virtual ~BarrierManager();
    
    BarrierManager(const BarrierManager &) = delete;
    //拷贝构造函数，用于创建一个 BarrierManager 对象的副本，它接受一个 BarrierManager 类型的引用作为参数，它被删除，表示不能被使用，这是为了防止出现多个 BarrierManager 对象的情况。
    
    BarrierManager &operator=(const BarrierManager &) = delete;
    //这是一个赋值运算符，用于将一个 BarrierManager 对象的值赋给另一个 BarrierManager 对象，它接受一个 BarrierManager 类型的引用作为参数，
    //它返回一个 BarrierManager 类型的引用，表示赋值后的对象，它被删除，表示不能被使用，这是为了防止出现多个 BarrierManager 对象的情况。
};

#endif 
