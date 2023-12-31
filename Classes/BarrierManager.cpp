#include "BarrierManager.h"
#include "BarrierBase.h"
#include "SceneManager.h"

BarrierManager *BarrierManager::_gInstance;

BarrierManager::BarrierManager()
{
}

BarrierManager::~BarrierManager()
{
    CC_SAFE_DELETE(_pBarrierVec);//删除指针释放内存
}


bool BarrierManager::init()
{
    bool bRet = false;
    
    _pBarrierVec = new Vector<BarrierBase*>();  //初始化
    registerBarrierDeadEvent();//登记死亡事件
    bRet = true;
    
    return bRet;
}

Vector<BarrierBase*> &BarrierManager::getBarrierVec()
{
    return *_pBarrierVec;
}

void BarrierManager::addBarrier(BarrierBase *pBarrier)
{
    if(_pBarrierVec) _pBarrierVec->pushBack(pBarrier);//添加障碍物
    _funcAddBarrierToLayer(pBarrier);
}

void BarrierManager::setFuncAddBarrierToLayer(const std::function<void (Entity *)> &rFuncAddBarrierToLayer)
{
    _funcAddBarrierToLayer = rFuncAddBarrierToLayer;
}

void BarrierManager::registerBarrierDeadEvent()
{
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(BarrierManager::removeBarrierFromManager), "BarrierDead", nullptr);
    //addObserver 第一个参数是 表示当前的 BarrierManager 对象作为观察者。
    //addObserver 第二个参数是 表示当收到通知时，要调用的回调函数
    //addObserver 第三个参数是 表示要接收的通知的名字
    //addObserver 第四个参数是 表示不指定通知的发送者，即接收任何发送者发送的 “BarrierDead” 通知。
}

void BarrierManager::removeBarrierFromManager(Ref *pBarrier)
{
    if(!(_pBarrierVec && _pBarrierVec->size())) return;
    _pBarrierVec->eraseObject(reinterpret_cast<BarrierBase*>(pBarrier));
    
    if(!_pBarrierVec->size())
    {
        auto tThemeIndex = SceneManager::getInstance()->getCurPageIndex() + 1;
        auto tLevelIndex = SceneManager::getInstance()->getCurLevelIndex() + 1;
        auto tLevelData = std::make_tuple(1, 1, tThemeIndex, tLevelIndex);
        NOTIFY->postNotification(LEVELDATACHANGE, reinterpret_cast<Ref*>(&tLevelData));
    }
}

void BarrierManager::clearManager()
{
    _pBarrierVec->clear();
}

void BarrierManager::clearBeAtkLockState()
{
    //清除障碍物的被攻击锁定状态
    for(auto &iterBarrier : *_pBarrierVec)
        iterBarrier->setAtkTarget(false);
}



