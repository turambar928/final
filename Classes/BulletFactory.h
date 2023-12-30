#ifndef __CarrotFantasy__BulletFactory__
#define __CarrotFantasy__BulletFactory__

#include "PublicDefine.h"

class VictimEntityBase;

class BulletFactory
{
public:
    
	static BulletBase *createBullet(const int &rBulletId, TowerBase* rTower, VictimEntityBase *rVictimEntity);
};

#endif 
