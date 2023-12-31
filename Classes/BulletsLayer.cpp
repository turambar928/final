#include "BulletsLayer.h"
#include "BulletManager.h"

bool BulletsLayer::init()
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!EntityLayerBase::init());

        scheduleUpdate();

        bRet = true;
    }
    while (0);
    
    return bRet;
}

void BulletsLayer::update(float dt)
{
    BulletManager::getInstance()->checkBulletIsDead();
}