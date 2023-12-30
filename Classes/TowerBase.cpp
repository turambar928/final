#include "TowerBase.h"
#include "TowerManager.h"
#include "VictimEntityBase.h"
#include "CsvUtil.h"
#include "BulletBase.h"
#include "BulletFactory.h"
#include "VictimEntityBase.h"
#include "MonsterManager.h"
#include "MonsterBase.h"
#include "SoundUtil.h"

TowerBase::~TowerBase() {
	// 释放攻击目标和塔楼面板对象
	CC_SAFE_RELEASE_NULL(_pAtkTarget);
	CC_SAFE_RELEASE_NULL(_pTowerPanel);
}

bool TowerBase::init(const int& rId) {
	bool bRet = false;

	do {
		// 调用基类的初始化方法
		CC_BREAK_IF(!Entity::init(rId, TOWERCSVFILE));

		// 初始化塔楼
		initTower();

		// 将塔楼添加到塔楼管理器中
		TowerManager::getInstance()->addTower(this);

		// 定时调度攻击目标检查方法，间隔为0.1秒
		schedule(CC_SCHEDULE_SELECTOR(TowerBase::checkAtkTarget), 0.1f);

		// 定时调度攻击方法，间隔为攻击间隔时间
		schedule(CC_SCHEDULE_SELECTOR(TowerBase::fire), _iAtkSpace);

		// 定时调度旋转方法，间隔为0.1秒
		schedule(CC_SCHEDULE_SELECTOR(TowerBase::doRocation), 0.1f);

		// 初始化成功
		bRet = true;
	} while (0);

	return  bRet;
}

void TowerBase::deadAction(const std::string& rSDeadImageFile) {
	// 发送塔楼死亡通知
	NOTIFY->postNotification("TowerDead", this);

	// 调用基类的死亡动作方法
	Entity::deadAction();
}

void TowerBase::checkAtkTarget(float dt) {
	// 如果没有攻击目标，选择一个
	if (!_pAtkTarget) chooseAtkTarget();
	else {
		// 如果攻击目标死亡或者攻击目标不具有攻击目标并且塔楼有攻击目标
		if (_pAtkTarget->getIsDead() || (!_pAtkTarget->getAtkTarget() && _bIsHaveAtkTarget)) {
			// 丢失攻击目标
			missAtkTarget();
			setIsHaveAtkTarget(false);
			return;
		}

		// 检查目标是否超出攻击范围
		checkTargetIsOutOfRange();
	}
}

/**
 * @brief 选择攻击目标的方法
 */
void TowerBase::chooseAtkTarget() {
	// 获取怪物管理器的怪物向量
	auto tMonsterVec = MonsterManager::getInstance()->getMonsterVec();

	// 遍历怪物向量
	for (auto& iterMonster : tMonsterVec) {
		// 如果怪物在攻击范围内
		if (isInAtkRange(iterMonster->getPosition())) {
			// 设置攻击目标并结束循环
			setAtkTarget(iterMonster);
			break;
		}
	}
}

/**
 * @brief 判断某个位置是否在塔楼的攻击范围内
 * @param rPos 要判断的位置
 * @return 如果在范围内返回true，否则返回false
 */
bool TowerBase::isInAtkRange(const cocos2d::Vec2& rPos) {
	bool bRet = false;

	do {
		// 计算塔楼与目标位置的距离
		auto tDistance = getPosition().distance(rPos);

		// 创建攻击范围精灵
		auto RangeSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("range_%d", _iAtkRange) + PHOTOPOSTFIX));

		// 如果距离小于攻击范围的一半加上30（一个额外的安全距离），则在攻击范围内
		CC_BREAK_IF(!(tDistance < RangeSp->getContentSize().width / 2 + 30));

		// 在攻击范围内
		bRet = true;
	} while (0);

	return bRet;
}


/**
 * @brief 发射子弹的方法
 * @param dt 时间步长
 */
void TowerBase::fire(float dt) {
	// 如果没有攻击目标或者攻击目标已经死亡，则返回
	if (!_pAtkTarget || _pAtkTarget->getIsDead()) return;

	// 执行发射动作
	fireAction();

	// 创建子弹的回调函数
	auto createBulletCF = CallFunc::create([=]() {
		// 如果没有攻击目标，则返回
		if (!_pAtkTarget) return;

		// 创建子弹
		BulletFactory::createBullet(_iBulletId, this, _pAtkTarget);
		});

	// 延时0.15秒后执行创建子弹的回调函数
	this->runAction(Sequence::create(DelayTime::create(0.15), createBulletCF, NULL));
}

/**
 * @brief 检查攻击目标是否超出攻击范围的方法
 */
void TowerBase::checkTargetIsOutOfRange() {
	// 如果存在攻击目标
	if (_pAtkTarget) {
		// 如果攻击目标不在攻击范围内，则执行丢失攻击目标的方法
		if (!isInAtkRange(_pAtkTarget->getPosition())) missAtkTarget();
	}
}

/**
 * @brief 丢失攻击目标的方法
 */
void TowerBase::missAtkTarget() {
	// 释放攻击目标，并置为空指针
	CC_SAFE_RELEASE_NULL(_pAtkTarget);
}

/**
 * @brief 设置攻击目标的方法
 * @param pVictimEntity 攻击目标
 */
void TowerBase::setAtkTarget(VictimEntityBase* pVictimEntity) {
	// 释放之前的攻击目标
	CC_SAFE_RELEASE_NULL(_pAtkTarget);

	// 设置新的攻击目标，并保持引用计数
	_pAtkTarget = pVictimEntity;
	CC_SAFE_RETAIN(_pAtkTarget);
}

/**
 * @brief 创建塔楼对象的静态方法
 * @param rId 塔楼的唯一标识符
 * @return 创建的塔楼对象，如果创建失败返回nullptr
 */
TowerBase* TowerBase::create(const int& rId) {
	auto t = new TowerBase();

	// 如果初始化成功，则自动释放并返回塔楼对象
	if (t && t->init(rId)) {
		t->autorelease();
		return t;
	}

	// 初始化失败时释放塔楼对象并返回nullptr
	CC_SAFE_DELETE(t);
	return nullptr;
}


/**
 * @brief 执行旋转的方法
 * @param dt 时间步长
 */
void TowerBase::doRocation(float dt) {
	// 如果没有攻击目标，则返回
	if (!_pAtkTarget) return;

	// 如果允许旋转，执行旋转动作
	if (_bIsRotation)
		getSprite()->runAction(RotateTo::create(0.1, 90 - 180 * (_pAtkTarget->getPosition() - this->getPosition()).getAngle() / M_PI));
}

/**
 * @brief 执行发射动作的方法
 */
void TowerBase::fireAction() {
	// 获取音效名称
	std::string soundName = _sName;

	// 如果音效名称为"BStar"，则使用"PStar"代替
	if (soundName == "BStar") soundName = "PStar";

	// 播放音效
	SoundUtil::getInstance()->playEffect(StringUtils::format("Music/Towers/%s.mp3", soundName.c_str()));

	// 创建动画对象
	auto pAnimation = Animation::create();
	auto pSpriteFrameCache = SpriteFrameCache::getInstance();

	// 添加精灵帧到动画中
	for (int i = 1; i <= this->getAnimationFrameCount(); i++)
		pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(_sModelName + StringUtils::format("%d", i) + PHOTOPOSTFIX));

	// 添加额外的精灵帧，用于过渡
	pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(_sModelName + "1" + PHOTOPOSTFIX));

	// 设置动画播放速度和循环次数
	pAnimation->setDelayPerUnit(0.05);
	pAnimation->setLoops(1);

	// 创建动画动作并执行
	auto pAnimate = Animate::create(pAnimation);
	this->getSprite()->runAction(pAnimate);
}


/**
 * @brief 升级当前塔的方法
 */
void TowerBase::upGrade() {
	// 将升级花费从字符串转换为整数
	std::stringstream StoI;
	StoI << _sUpgradeCost;
	int upGradeMoney;
	StoI >> upGradeMoney;
	upGradeMoney = -upGradeMoney;

	// 发送金币变化通知
	NOTIFY->postNotification("moneyChange", (Ref*)(&upGradeMoney));

	// 保存当前升级次数
	auto upGradeCounts = this->getIUpgradeCount();

	// 移除升级标志和塔的精灵
	_pGradeMark->removeFromParentAndCleanup(true);
	getSprite()->removeFromParentAndCleanup(true);

	// 通过增加ID初始化塔的属性
	Entity::initProperty(this->getIId() + 1, TOWERCSVFILE);

	// 重新初始化塔
	initTower();

	// 恢复升级次数
	this->_iUpgradeCount = upGradeCounts;
}

/**
 * @brief 初始化塔的属性
 */
void TowerBase::initTower() {
	// 如果塔的面板存在，则移除
	if (_pTowerPanel)
		removeChild(_pTowerPanel);

	// 释放塔的面板
	CC_SAFE_RELEASE_NULL(_pTowerPanel);

	// 获取CSV工具实例
	auto pCsvUtil = CsvUtil::getInstance();

	// 从CSV文件中获取塔的属性值
	_iBulletId = pCsvUtil->getInt(_iId, en_BulletId, TOWERCSVFILE);
	_iAtkRange = pCsvUtil->getInt(_iId, en_Range, TOWERCSVFILE);
	_iAtkSpace = pCsvUtil->getDouble(_iId, en_Space, TOWERCSVFILE);
	_sUpgradeCost = pCsvUtil->getText(_iId, en_UpGradeCost, TOWERCSVFILE);
	_bIsRotation = pCsvUtil->getInt(_iId, en_IsRotation, TOWERCSVFILE);
	_iUpgradeCount = 0;
	_iCreateCost = pCsvUtil->getInt(_iId, en_CreateCost, TOWERCSVFILE);
	_bIsHaveAtkTarget = false;

	// 创建并初始化升级标志动画
	_pGradeMark = Sprite::create();
	_pGradeMark->setVisible(false);
	auto aniGradeMark = Animation::create();
	for (int i = 1; i <= 2; i++) {
		aniGradeMark->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("showupgrade0%d.png", i)));
	}
	aniGradeMark->setDelayPerUnit(0.5);
	aniGradeMark->setLoops(-1);
	_pGradeMark->setLocalZOrder(3);
	_pGradeMark->runAction(Animate::create(aniGradeMark));
	_pGradeMark->setPosition(0, 50);
	addChild(_pGradeMark);

	// 创建并初始化塔的面板
	_pTowerPanel = Sprite::createWithSpriteFrameName(pCsvUtil->getText(_iId, en_TowerBase, TOWERCSVFILE));
	_pTowerPanel->retain();
	_pTowerPanel->setLocalZOrder(1);
	addChild(_pTowerPanel);

	// 设置塔的精灵的渲染层次
	getSprite()->setLocalZOrder(2);
}


/**
 * @brief 获取升级当前塔所需的金币成本
 * @return 金币成本
 */
int TowerBase::getTowerGradeCost() {
	// 将升级花费从字符串转换为整数
	std::stringstream StoI;
	StoI << _sUpgradeCost;
	int upGradeMoney;
	StoI >> upGradeMoney;
	return upGradeMoney;
}

/**
 * @brief 显示升级标志
 */
void TowerBase::showGradeMark() {
	_pGradeMark->setVisible(true);
}

/**
 * @brief 隐藏升级标志
 */
void TowerBase::hideGradeMark() {
	_pGradeMark->setVisible(false);
}
