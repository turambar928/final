#include "BulletManager.h"
#include "BulletBase.h"

BulletManager *BulletManager::_gInstance;

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
    CC_SAFE_DELETE(_pBulletVec);
}

bool BulletManager::init()
{
    bool bRet = false;
    _pBulletVec = new Vector<BulletBase*>();

    bRet = true;
    
    return bRet;
}

Vector<BulletBase*> &BulletManager::getBulletVec()
{
    return *_pBulletVec;
}

void BulletManager::addBullet(BulletBase *pBullet)
{//����ӵ�
    if(_pBulletVec) _pBulletVec->pushBack(pBullet);
    _funcAddBulletLayer(pBullet);
}

void BulletManager::setFuncAddBulletLayer(const std::function<void (Entity *)> &rFuncAddBulletLayer)
{//��������ӵ���
    _funcAddBulletLayer = rFuncAddBulletLayer;
}

void BulletManager::checkBulletIsDead()
{//����ӵ���������
    for(auto iterBullet = _pBulletVec->begin(); iterBullet != _pBulletVec->end();)
    {
        if((*iterBullet)->getIsDead()) iterBullet = _pBulletVec->erase(iterBullet);
        else ++iterBullet;
    }
}


void BulletManager::clearManager()
{
    _pBulletVec->clear();
}



