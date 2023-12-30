#include "BarrierBase.h"
#include "BarrierManager.h"
#include "MapUtil.h"

bool BarrierBase::init(const int &rId)
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!VictimEntityBase::init(rId, BARRIERCSVFILE));//判断是否初始化成功 BARRIERCSVFILE是CSV文件名
        BarrierManager::getInstance()->addBarrier(this);//当前的 BarrierBase 对象添加到一个管理障碍物的容器中
        bRet = true;
    }
    while (0);
    
    return bRet;
}

BarrierBase * BarrierBase::create(const int &rId){
    
    BarrierBase * pBarriers = new BarrierBase();
    
    if (pBarriers && pBarriers->init(rId))
    {
        pBarriers->autorelease();//将其添加到自动释放池中
        return pBarriers;
    }
    CC_SAFE_DELETE(pBarriers);//自定义宏
    return nullptr;
}

void BarrierBase::deadAction(const std::string &rSDeadImageFile)
{
    NOTIFY->postNotification("BarrierDead", this);//障碍物死了
    MapUtil::getInstance()->removeBarrierRect(getPosition());//从地图上清除障碍物
	VictimEntityBase::deadAction();
}

void BarrierBase::behurtAction()
{

}

