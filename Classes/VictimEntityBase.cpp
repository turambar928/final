#include "VictimEntityBase.h"
#include "HpSlot.h"
#include "TowerManager.h"
#include "TowerBase.h"
#include "SoundUtil.h"


/**
 * @brief VictimEntityBase析构函数
 * @details 释放对象的资源
 */
VictimEntityBase::~VictimEntityBase()
{
    CC_SAFE_RELEASE_NULL(_pLockAtkTarget); // 释放攻击目标锁定对象
    CC_SAFE_RELEASE_NULL(_pHpSlot); // 释放生命槽对象
    CC_SAFE_RELEASE_NULL(_pLockFlagAnimate); // 释放锁定标志动画对象
}

/**
 * @brief VictimEntityBase初始化函数
 */
bool VictimEntityBase::init(const int& rIId, const std::string& rSCsvFileName)
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Entity::init(rIId, rSCsvFileName)); // 如果Entity初始化失败则中断

        _iHp = CsvUtil::getInstance()->getInt(_iId, en_Hp, rSCsvFileName); // 从CSV中获取生命值
        _iState = en_Normal; // 设置状态为正常
        _fSlowDuration = 0; // 初始化减速效果持续时间为0
        _fStopDuration = 0; // 初始化停止效果持续时间为0
        _fPoisonDuration = 0; // 初始化中毒效果持续时间为0
        _Pos = getPosition(); // 获取实体位置
        _Size = getContentSize(); // 获取实体大小

        this->schedule(CC_SCHEDULE_SELECTOR(VictimEntityBase::checkAtkTarget)); // 定时调度攻击目标检测函数

        bRet = true; // 初始化成功
    } while (0);

    return bRet;
}


/**
 * @brief 受伤处理函数
 * @param tBeHurtValue 攻击属性
 * @details 处理受到伤害的逻辑，更新状态、减血、执行相关动作等
 */
void VictimEntityBase::beHurt(const AtkProperty tBeHurtValue)
{
    // 如果实体已经死亡，则不进行处理
    if (this->getIsDead()) return;

    // 更新实体状态和子弹状态类型
    _iState |= tBeHurtValue._enAtkState;
    _iBulletStateType = tBeHurtValue._iButtltType;

    // 根据攻击状态类型执行相应操作
    switch (tBeHurtValue._enAtkState)
    {
    case en_Slow: _fSlowDuration = tBeHurtValue._iDuration; break; // 减速效果
    case en_Stop: _fStopDuration = tBeHurtValue._iDuration; break; // 停止效果
    case en_Poison: _fPoisonDuration = tBeHurtValue._iDuration; break; // 中毒效果
    default: break;
    }

    // 计算减血后的生命值
    auto tIHp = getIHp() - tBeHurtValue._iAtk;

    // 如果生命值仍然大于0，则更新相关状态
    if (tIHp > 0)
    {
        // 取消之前的关闭生命槽调度器
        unschedule(CC_SCHEDULE_SELECTOR(VictimEntityBase::closeHpSlot));

        // 如果生命槽不存在，则设置可见并开启相应调度器
        if (!_bHpSlotExsit)
        {
            hpSlotVisible(!_bHpSlotExsit);
            _bHpSlotExsit = true;
        }

        // 设置生命槽可见并开启关闭生命槽的调度器
        _pHpSlot->setVisible(true);
        schedule(CC_SCHEDULE_SELECTOR(VictimEntityBase::closeHpSlot), _iHpCloseTime);

        // 更新生命值并设置生命槽显示的生命值
        setIHp(tIHp);
        _pHpSlot->setHp(getIHp());

        // 执行受伤动作
        behurtAction();
    }
    // 如果生命值小于等于0，则执行死亡处理
    else if (tIHp <= 0)
    {
        doDead();
    }
}

/**
 * @brief 关闭生命槽
 * @param dt 间隔时间
 * @details 关闭生命槽的调度器回调函数
 */
void VictimEntityBase::closeHpSlot(float dt)
{
    _pHpSlot->setVisible(false);
}

/**
 * @brief 死亡动作
 * @param rSDeadImageFile 死亡图像文件名
 * @details 执行实体死亡时的动作，包括发布死亡金币通知、移除生命槽和攻击目标锁定
 */
void VictimEntityBase::deadAction(const std::string& rSDeadImageFile)
{
    // 发布死亡金币通知
    auto tValue = std::make_tuple(getPosition(), _iValue);
    NOTIFY->postNotification("monsterDeadMoney", reinterpret_cast<Ref*>(&tValue));

    // 移除生命槽和攻击目标锁定
    if (_pHpSlot) _pHpSlot->removeFromParent();
    if (_pLockAtkTarget) _pLockAtkTarget->removeFromParent();

    // 执行父类的死亡动作
    Entity::deadAction();
}


void VictimEntityBase::createHpSlotSprite()
{
    _pHpSlot = HpSlot::create(this);
    _pHpSlot->retain();
    auto tPos = getPosition();
    auto tSpriteSize = getContentSize();
    auto tSlotSize = _pHpSlot->getContentSize();
    _pHpSlot->setPosition(Vec2(-tSlotSize.width / 2 - 3, tSpriteSize.height / 2 - 12));
    addChild(_pHpSlot);
}

void VictimEntityBase::createLockAtkSprite()
{
	createLockFlagAnimate();
	_pLockAtkTarget = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("point01.png"));
    CC_SAFE_RETAIN(_pLockAtkTarget);
	_pLockAtkTarget->setPosition(Vec2(0, _Pos.y + _Size.height / 2 + 12));
	addChild(_pLockAtkTarget, 2);
}

void VictimEntityBase::createLockFlagAnimate()
{
    auto pAnimation = Animation::create();
    auto pSpriteFrameCache = SpriteFrameCache::getInstance();
    for(int i = 1; i <= 3; ++i)
        pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(StringUtils::format("point0%d.png", i)));
    pAnimation->setLoops(-1);
    pAnimation->setDelayPerUnit(0.1f);
    _pLockFlagAnimate = Animate::create(pAnimation);
    _pLockFlagAnimate->retain();
}

void VictimEntityBase::setAtkTarget(const bool &rBisAtkTarget)
{
    _bIsAtkTarget = rBisAtkTarget;
    if(_bIsAtkTarget)
    {
		if (!_pLockAtkTarget) createLockAtkSprite();
        _pLockAtkTarget->runAction(_pLockFlagAnimate);
        _pLockAtkTarget->setVisible(_bIsAtkTarget);
		SoundUtil::getInstance()->playEffect(SELECTVICTIMENTITYBASE);
    }
    else
    {
        if(!_pLockAtkTarget) return;
        _pLockAtkTarget->stopAllActions();
        _pLockAtkTarget->setVisible(_bIsAtkTarget);
    }
}

void VictimEntityBase::hpSlotVisible(const bool &rBIsVisible)
{
    if(rBIsVisible) createHpSlotSprite();
    else _pHpSlot->setVisible(rBIsVisible);
}

void VictimEntityBase::checkAtkTarget(float dt){
    auto tTowerVec = TowerManager::getInstance()->getTowerVec();
	if (_bIsAtkTarget){
		for (auto & towerItem : tTowerVec)
        {
			if (towerItem->isInAtkRange(this->getPosition())){
				towerItem->setAtkTarget(this);
                towerItem->setIsHaveAtkTarget(true);
			}
		}
	}
}



