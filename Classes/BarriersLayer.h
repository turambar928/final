#ifndef __CarrotFantasy__BarriersLayer__
#define __CarrotFantasy__BarriersLayer__

#include "EntityLayerBase.h"


class BarriersLayer: public EntityLayerBase
{
    
public:
    
    CREATE_FUNC(BarriersLayer);
    
protected:
    
    virtual bool init();
    
};

#endif 
