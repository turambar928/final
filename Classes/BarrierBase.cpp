#include "BarrierBase.h"
#include "BarrierManager.h"
#include "MapUtil.h"

bool BarrierBase::init(const int &rId)
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!VictimEntityBase::init(rId, BARRIERCSVFILE));//�ж��Ƿ��ʼ���ɹ� BARRIERCSVFILE��CSV�ļ���
        BarrierManager::getInstance()->addBarrier(this);//��ǰ�� BarrierBase ������ӵ�һ�������ϰ����������
        bRet = true;
    }
    while (0);
    
    return bRet;
}

BarrierBase * BarrierBase::create(const int &rId){
    
    BarrierBase * pBarriers = new BarrierBase();
    
    if (pBarriers && pBarriers->init(rId))
    {
        pBarriers->autorelease();//������ӵ��Զ��ͷų���
        return pBarriers;
    }
    CC_SAFE_DELETE(pBarriers);//�Զ����
    return nullptr;
}

void BarrierBase::deadAction(const std::string &rSDeadImageFile)
{
    NOTIFY->postNotification("BarrierDead", this);//�ϰ�������
    MapUtil::getInstance()->removeBarrierRect(getPosition());//�ӵ�ͼ������ϰ���
	VictimEntityBase::deadAction();
}

void BarrierBase::behurtAction()
{

}

