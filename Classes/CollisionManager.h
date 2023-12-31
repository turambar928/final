#ifndef __CarrotFantasy__CollisionManager__
#define __CarrotFantasy__CollisionManager__

#include "PublicDefine.h"

class CollisionManager
{
public:
    
    static void collision(Vector<BarrierBase *> &rBarrierVec, Vector<MonsterBase *> &rMonsterVec, Vector<BulletBase*> &rBulletVec);
	
protected:

	static void MonsterAndBullet(BulletBase * pBullet, Vector<MonsterBase *> &rMonsterVec);

	static void BarrierAndBullet(BulletBase * pBullet,Vector<BarrierBase *> &rBarrierVec);

	static Animation * AnimationMaker(std::string BulletName,int SpriteFrameCount);
    
};

#endif 
