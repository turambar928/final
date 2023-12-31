#ifndef __CarrotFantasy__BarrierFactory__
#define __CarrotFantasy__BarrierFactory__

#include "PublicDefine.h"

class BarrierBase;

class BarrierFactory
{
public:
    static BarrierBase *createBarrier(const BarrierType &rBarrierType);
};

#endif 
