#ifndef __CarrotFantasy__EntityLayerBase__
#define __CarrotFantasy__EntityLayerBase__

#include "cocos2d.h"
using namespace cocos2d;

class Entity;

class EntityLayerBase:public Layer
{
    
public:
    
    virtual void addEntity(Entity *pEntity);
};

#endif 
