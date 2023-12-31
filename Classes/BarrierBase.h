#ifndef __CarrotFantasy__BarrierBase__
#define __CarrotFantasy__BarrierBase__


#include "VictimEntityBase.h"

class BarrierBase:public VictimEntityBase
{

public:
    
    static BarrierBase * create(const int &rId);//用于创建一个 BarrierBase 对象，参数是障碍物的编号
    
    friend class BarrierFactory;
    
protected:

    virtual bool init(const int &rId);//初始化
    
    virtual void deadAction(const std::string &rSDeadImageFile = "");//死亡动作
    
    virtual void behurtAction();//受伤动作
    
};

#endif 
