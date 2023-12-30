#ifndef __CarrotFantasy__TowerBase__
#define __CarrotFantasy__TowerBase__

#include "Entity.h"

class VictimEntityBase;


class TowerBase:public Entity
{
public:
    
	static TowerBase* create(const int &rId);

	virtual void doRocation(float dt);

    virtual ~TowerBase();
	
	virtual int getTowerGradeCost();

	virtual void setAtkTarget(VictimEntityBase *pVictimEntity);

	virtual void showGradeMark();

	virtual void hideGradeMark();


	virtual bool isInAtkRange(const Vec2 &rPos);

	virtual void upGrade();
protected:

    virtual void deadAction(const std::string &rSDeadImageFile = "")override;

    virtual void checkAtkTarget(float dt);

    virtual void chooseAtkTarget();

    virtual void checkTargetIsOutOfRange();

    virtual void missAtkTarget();

	virtual void fire(float dt);

	virtual void initTower();
    
    virtual bool init(const int &rId);

	virtual void fireAction();

    CC_SYNTHESIZE_PASS_BY_REF(int, _iBulletId, IBulletId);

    CC_SYNTHESIZE_PASS_BY_REF(int, _iAtkRange, IAtkRange);

    CC_SYNTHESIZE_PASS_BY_REF(double, _iAtkSpace, IAtkSpace);

    CC_SYNTHESIZE_PASS_BY_REF(std::string, _sUpgradeCost, SUpgradeCose);

    CC_SYNTHESIZE_PASS_BY_REF(int, _iUpgradeCount, IUpgradeCount);

    CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsRotation, BIsRotation);

	CC_SYNTHESIZE_PASS_BY_REF(int, _iCreateCost, ICreateCost);
    
    CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsHaveAtkTarget, IsHaveAtkTarget);
	
protected:
	Sprite* _pGradeMark = nullptr;

	Sprite *_pTowerPanel = nullptr;

    VictimEntityBase *_pAtkTarget = nullptr;
};

#endif /* defined(__CarrotFantasy__TowerBase__) */
