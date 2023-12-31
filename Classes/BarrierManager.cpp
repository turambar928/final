#include "BarrierManager.h"
#include "BarrierBase.h"
#include "SceneManager.h"

BarrierManager *BarrierManager::_gInstance;

BarrierManager::BarrierManager()
{
}

BarrierManager::~BarrierManager()
{
    CC_SAFE_DELETE(_pBarrierVec);//ɾ��ָ���ͷ��ڴ�
}


bool BarrierManager::init()
{
    bool bRet = false;
    
    _pBarrierVec = new Vector<BarrierBase*>();  //��ʼ��
    registerBarrierDeadEvent();//�Ǽ������¼�
    bRet = true;
    
    return bRet;
}

Vector<BarrierBase*> &BarrierManager::getBarrierVec()
{
    return *_pBarrierVec;
}

void BarrierManager::addBarrier(BarrierBase *pBarrier)
{
    if(_pBarrierVec) _pBarrierVec->pushBack(pBarrier);//����ϰ���
    _funcAddBarrierToLayer(pBarrier);
}

void BarrierManager::setFuncAddBarrierToLayer(const std::function<void (Entity *)> &rFuncAddBarrierToLayer)
{
    _funcAddBarrierToLayer = rFuncAddBarrierToLayer;
}

void BarrierManager::registerBarrierDeadEvent()
{
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(BarrierManager::removeBarrierFromManager), "BarrierDead", nullptr);
    //addObserver ��һ�������� ��ʾ��ǰ�� BarrierManager ������Ϊ�۲��ߡ�
    //addObserver �ڶ��������� ��ʾ���յ�֪ͨʱ��Ҫ���õĻص�����
    //addObserver ������������ ��ʾҪ���յ�֪ͨ������
    //addObserver ���ĸ������� ��ʾ��ָ��֪ͨ�ķ����ߣ��������κη����߷��͵� ��BarrierDead�� ֪ͨ��
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
    //����ϰ���ı���������״̬
    for(auto &iterBarrier : *_pBarrierVec)
        iterBarrier->setAtkTarget(false);
}



