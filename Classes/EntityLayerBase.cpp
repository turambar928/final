#include "EntityLayerBase.h"
#include "Entity.h"

void EntityLayerBase::addEntity(Entity *pEntity)
{
    addChild(pEntity);
}