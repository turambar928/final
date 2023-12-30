#ifndef __CarrotFantasy__TowersLayer__
#define __CarrotFantasy__TowersLayer__

#include "EntityLayerBase.h"

class TowersLayer:public EntityLayerBase
{
public:
    
    CREATE_FUNC(TowersLayer);
    
protected:
	virtual void checkTowerGrade(float dt);
    virtual bool init();
    
    
};

#endif /* defined(__CarrotFantasy__TowersLayer__) */
