#include "BarriersLayer.h"

bool BarriersLayer::init()
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!EntityLayerBase::init());
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}




