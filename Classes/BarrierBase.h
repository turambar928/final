#ifndef __CarrotFantasy__BarrierBase__
#define __CarrotFantasy__BarrierBase__


#include "VictimEntityBase.h"

class BarrierBase:public VictimEntityBase
{

public:
    
    static BarrierBase * create(const int &rId);//���ڴ���һ�� BarrierBase ���󣬲������ϰ���ı��
    
    friend class BarrierFactory;
    
protected:

    virtual bool init(const int &rId);//��ʼ��
    
    virtual void deadAction(const std::string &rSDeadImageFile = "");//��������
    
    virtual void behurtAction();//���˶���
    
};

#endif 
