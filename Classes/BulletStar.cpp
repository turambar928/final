#include "BulletStar.h"
#include "VictimEntityBase.h"
#include "MonsterManager.h"
#include "MonsterBase.h"
#include "BarrierManager.h"
#include "BarrierBase.h"

bool BulletStar::init(const int & rId,VictimEntityBase *rVictimEntity)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!BulletBase::init(rId,rVictimEntity));

		bRet = true;
	} while (0);
	return bRet;
}

BulletStar * BulletStar::create(const int & rId,VictimEntityBase *rVictimEntity)
{
	//建立
	BulletStar * pBullet = new BulletStar();
	if (pBullet && pBullet->init(rId,rVictimEntity))
	{
		pBullet->autorelease();
		return pBullet;
	}
	CC_SAFE_DELETE(pBullet);
	return nullptr;
}

void BulletStar::doAction()
{
	//执行动作
	getSprite()->runAction(RepeatForever::create(RotateBy::create(0.7, 360)));//旋转
}

void BulletStar::doMove(){
	if (_pAtkTarget->getIsDead())//判断
	{
		removeFromParent();
		setIsDead(true);
		return;
	}
	doAction();

	Animation * pAnimation = Animation::create();//存储动画帧
	for (int i = 1;i < 7;i++)
	{
		std::string SpriteFrameName = StringUtils::format("PStar-1%d.png",i);
		SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteFrameName);
		pAnimation->addSpriteFrame(spriteFrame);//形成动画序列
	}
	pAnimation->setDelayPerUnit(0.05);
	pAnimation->setLoops(1);

	auto deadActionCF = CallFunc::create([=]()//动画播放结束后执行一个回调函数
	{

		Rect rect = Rect(_pAtkTarget->getPositionX() - 100, _pAtkTarget->getPositionY() - 100, 200, 200);
		if (_pAtkTarget->getAnimationFrameCount() != 0)
		{
			Vector<MonsterBase*>  MonsterDel;
			Vector<MonsterBase *>  MonsterVector = Vector<MonsterBase *>(MonsterManager::getInstance()->getMonsterVec());
			for (auto mIter = MonsterVector.begin(); mIter != MonsterVector.end();)
			{
				MonsterBase * pMonster = (MonsterBase *)(*mIter);
				if (rect.intersectsRect(pMonster->getBoundingBox()))
				{//受伤
					pMonster->beHurt(getAtkPro());
				}
				if (pMonster->getIHp() <= 0 || pMonster->getIsDead())
				{//是否死亡
					MonsterDel.pushBack(pMonster);
				}				
			
				++mIter;
				
			}

			for (auto mIter = MonsterDel.begin(); mIter != MonsterDel.end(); ++mIter)
			{//清除
				MonsterBase* pMonster = (MonsterBase*)(*mIter);
				MonsterVector.eraseObject(pMonster);
			}

		}
		else
		{
			Vector<BarrierBase*>  BarrierDel;
			Vector<BarrierBase *>  BarrierVector = Vector<BarrierBase *>(BarrierManager::getInstance()->getBarrierVec());
			for (auto bIter = BarrierVector.begin(); bIter != BarrierVector.end();)
			{
				BarrierBase * pBarrier = (BarrierBase *)(*bIter);
				if (rect.intersectsRect(pBarrier->getBoundingBox()))
				{
					pBarrier->beHurt(getAtkPro());
				}
				if (pBarrier->getIHp() <= 0 || pBarrier->getIsDead())
				{
					BarrierDel.pushBack(pBarrier);
				}				
				++bIter;
				
			}
			for (auto bIter = BarrierDel.begin(); bIter != BarrierDel.end(); ++bIter)
			{
				BarrierBase* pBarrier = (BarrierBase*)(*bIter);
				BarrierDel.eraseObject(pBarrier);
			}
		}
		deadAction(_sName);
	});

	Vec2 MovetoPosition = _pAtkTarget->getPosition() - this->getPosition();
	float MoveDistance = this->getPosition().distance(_pAtkTarget->getPosition());
	getSprite()->runAction(Sequence::create(MoveBy::create(MoveDistance / _iSpeed, MovetoPosition),Animate::create(pAnimation),deadActionCF, NULL));
}

