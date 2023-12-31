//²»¶®£¡

#include "BarrierFactory.h"
#include "BarrierBase.h"


BarrierBase *BarrierFactory::createBarrier(const BarrierType &rBarrierType)
{
    BarrierBase *pBarrier = nullptr;
    
    switch (rBarrierType) {
        case en_BalloonType:
            break;
		case en_CloudType:
            break;
        case en_StoneType:
            break;
        case en_TreeType:
            break;
        default:
            break;
    }
    return pBarrier;
}