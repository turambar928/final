#ifndef __CarrotFantasy__BulletsLayer__
#define __CarrotFantasy__BulletsLayer__

#include "EntityLayerBase.h"

/**
 *  BulletsLayer use to show Bullet
 */

class BulletsLayer:public EntityLayerBase
{
public:
    
    CREATE_FUNC(BulletsLayer);
    
protected:
    
    virtual bool init();
    
    virtual void update(float dt);
};

#endif
