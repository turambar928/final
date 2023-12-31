#include "BulletBase.h"
#include "BulletManager.h"
#include "VictimEntityBase.h"

BulletBase *BulletBase::create(const int &rIId, VictimEntityBase *rVictimEntity)
{
    //创建对象
    auto pBullet = new BulletBase();
	if (pBullet && pBullet->init(rIId, rVictimEntity)) pBullet->autorelease();
    else CC_SAFE_DELETE(pBullet);
    return pBullet;
}

bool BulletBase::init(const int &rId, VictimEntityBase *rVictimEntity)
{
    bool bRet = false;
    
    do
    {
        //初始化，并判断
		CC_BREAK_IF(!Entity::init(rId, BULLETCSVFILE));
		CC_BREAK_IF(!DynamicPropertyInterFace::init(rId, BULLETCSVFILE));
        
		_iAtkState = CsvUtil::getInstance()->getInt(_iId, en_AtkState, BULLETCSVFILE);
		_iBulletType = CsvUtil::getInstance()->getInt(_iId, en_BulletType, BULLETCSVFILE);
		_iDeadActCount = CsvUtil::getInstance()->getInt(_iId, en_DeadActCount, BULLETCSVFILE);
        CC_SAFE_RETAIN(rVictimEntity);
		_pAtkTarget = rVictimEntity;
		_IdMap = new std::set<int>();

        BulletManager::getInstance()->addBullet(this);
    
        bRet = true;
    }
    while (0);
    
    return  bRet;
}

void BulletBase::doAction(const float &rDt)
{
	switch (_iBulletType)
    {
		case en_NormalBullet:
        case en_GunBullet:
            {
                std::vector<std::string> tAnimationFiles;
                for (int i = 1; i <= _IAnimationFrameCount; ++i)
                    tAnimationFiles.push_back(_sModelName + StringUtils::format("%d", i) + PHOTOPOSTFIX);
                
                createDynamicEntityAnimation(tAnimationFiles);//创建一个动态实体动画
                _pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_sModelName + "1" + PHOTOPOSTFIX));
                _pAnimation->setDelayPerUnit(rDt);//延迟
                getSprite()->runAction(Animate::create(_pAnimation));//移动
                break;
            }
        case en_NoDisspper:
            {
                getSprite()->runAction(RepeatForever::create(RotateBy::create(0.7, 360)));
                break;
            }
        default:
            break;
	}
}

void BulletBase::doMove(){
    if(_pAtkTarget->getIsDead())//判断死亡
    {
        removeFromParent();
        setIsDead(true);
        return ;
    }
    doAction(0.2f);

	auto deadActionCF = CallFunc::create([=]()//回调函数，子弹到达目标后执行
    {
		if (_iBulletType == en_NormalBullet || _iBulletType == en_GunBullet || _iBulletType == en_StarBullet){
			if (_pAtkTarget != nullptr && !_pAtkTarget->getIsDead())
			_pAtkTarget->beHurt(getAtkPro());//受伤
			this->setPosition(_pAtkTarget->getPosition());//设置位置
		}
		deadAction(_sName);
	});

	Vec2 MovetoPosition;
	float MoveDistance;
	switch (_iBulletType)
    {
        case en_NormalBullet:
        case en_GunBullet:
            MovetoPosition = _pAtkTarget->getPosition() - this->getPosition();
            MoveDistance = this->getPosition().distance(_pAtkTarget->getPosition());//获得位置
            break;
        case en_NoDisspper:
        {
            float Hypotenuse = Vec2::ZERO.distance(Director::getInstance()->getVisibleSize());
            MovetoPosition = Vec2(Hypotenuse * sin(this->getRotation() * M_PI / 180), Hypotenuse * cos(this->getRotation() * M_PI / 180));
            MoveDistance = MovetoPosition.distance(this->getPosition());
            break;
        }
        default:
            break;
	}
	this->runAction(Sequence::create(MoveBy::create(MoveDistance / _iSpeed, MovetoPosition), deadActionCF, NULL));//移动函数
}

AtkProperty BulletBase::getAtkPro()
{
    //获取信息
    AtkProperty tAtkProperty;
    tAtkProperty._enAtkState = _iAtkState;
    tAtkProperty._iAtk = getIAtk();
    tAtkProperty._iDuration = CsvUtil::getInstance()->getInt(_iId, en_Duration, BULLETCSVFILE);
	tAtkProperty._iButtltType = _iBulletType;
    return tAtkProperty;
}

void BulletBase::deadAction(const std::string &rSDeadImageFile)
{
	delete(_IdMap);//删除子弹
    Entity::deadAction(rSDeadImageFile);
}

std::set<int>& BulletBase::getIdMap()
{
	return *_IdMap;
}