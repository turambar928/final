#include "TowerOptBtn.h"
#include "PublicSourceDefine.h"
#include "MapUtil.h"
#include "TowerFactory.h"
#include "LevelConfigUtil.h"
#include "ScoreAndControlLayer.h"
#include "TowerBase.h"
#include "SoundUtil.h"

/**
 * @brief TowerOptBtn类的构造函数
 */
TowerOptBtn::TowerOptBtn() {
}

/**
 * @brief TowerOptBtn类的析构函数
 */
TowerOptBtn::~TowerOptBtn() {
	// 释放创建塔和升级塔的菜单项精灵向量的内存
	CC_SAFE_DELETE(_pCreateTowerItemSpVec);
	CC_SAFE_DELETE(_pGradeTowerItemSpVec);
}

/**
 * @brief 初始化TowerOptBtn对象
 * @return 初始化是否成功
 */
bool TowerOptBtn::init() {
	bool bRet = false;
	do {
		// 创建创建塔和升级塔的菜单项精灵向量
		_pCreateTowerItemSpVec = new Vector<MenuItemSprite*>();
		_pGradeTowerItemSpVec = new Vector<MenuItemSprite*>();

		// 创建菜单和菜单项，并调用定时器方法
		createMenuAndItems();
		this->schedule(CC_SCHEDULE_SELECTOR(TowerOptBtn::ChangingItem));

		bRet = true;
	} while (0);
	return bRet;
}

/**
 * @brief 隐藏塔操作按钮的方法
 */
void TowerOptBtn::hideTowerOpt() {
	// 设置关键精灵不可见
	_bKeySpVisible = false;
	_pKeySp->setVisible(_bKeySpVisible);

	// 如果塔范围精灵存在，则设置不可见
	if (_pTowerRangeSp != nullptr)
		_pTowerRangeSp->setVisible(false);

	// 设置创建和升级菜单不可见
	_pCreateMenu1->setVisible(false);
	_pCreateMenu2->setVisible(false);
}


/**
 * @brief 显示塔操作按钮的方法
 */
void TowerOptBtn::showTowerOpt() {
	// 设置关键精灵可见
	_bKeySpVisible = true;
	_pKeySp->setVisible(_bKeySpVisible);
}

/**
 * @brief 创建菜单和菜单项的方法
 */
void TowerOptBtn::createMenuAndItems() {
	// 创建关键精灵、创建菜单1、创建菜单2以及升级菜单，并设置初始可见性
	_pKeySp = Sprite::create();
	_pKeySp->setVisible(false);
	_pCreateMenu1 = Menu::create();
	_pCreateMenu1->setVisible(false);
	_pCreateMenu2 = Menu::create();
	_pCreateMenu2->setVisible(false);
	_pGradeMenu = Menu::create();

	// 创建塔菜单，设置动画效果，并添加到关键精灵中
	createTowerMenu();
	auto MenuAnimation = Animation::create();
	auto _pSpriteFrameCache = SpriteFrameCache::getInstance();
	for (int i = 1; i <= 4; ++i)
		MenuAnimation->addSpriteFrame(_pSpriteFrameCache->getSpriteFrameByName(StringUtils::format("select_0%d", i) + PHOTOPOSTFIX));
	MenuAnimation->setDelayPerUnit(0.1);
	MenuAnimation->setLoops(-1);

	_pKeySp->runAction(Animate::create(MenuAnimation));
	_pKeySp->addChild(_pCreateMenu1);
	_pKeySp->addChild(_pCreateMenu2);
	_pKeySp->addChild(_pGradeMenu);
	addChild(_pKeySp);

	// 创建塔范围精灵并设置初始不可见，添加到关键精灵中
	_pTowerRangeSp = Sprite::create();
	_pTowerRangeSp->setPosition(40, 40);
	_pTowerRangeSp->setVisible(false);
	_pKeySp->addChild(_pTowerRangeSp);
}


/**
 * @brief 创建塔菜单的方法
 */
void TowerOptBtn::createTowerMenu() {
	int i = 1;
	for (auto& iterTower : LevelConfigUtil::getInstance()->getCurLevelTowersInfo()) {

		// 获取塔的ID及升级所需金币
		int _TowerId = CsvUtil::getInstance()->findValueInWithLine(iterTower, 1, TOWERCSVFILE);
		std::stringstream StoI;
		std::string _sUpgradeCost = CsvUtil::getInstance()->getText(_TowerId, en_CreateCost, TOWERCSVFILE);
		StoI << _sUpgradeCost;
		int _upGradeMoney;
		StoI >> _upGradeMoney;

		// 处理特殊塔名
		if (iterTower == "Sun1") iterTower = "Sun";
		if (iterTower == "PPlane1") iterTower = "Plane";

		// 创建塔项的精灵
		auto _TowerItemSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(iterTower + "01" + PHOTOPOSTFIX));

		// 创建塔项的菜单项，并设置回调函数
		auto _Toweritem = MenuItemSprite::create(_TowerItemSp, _TowerItemSp, [=](Ref* r) {
			TowerType _towerType;
			this->setTag(0);
			hideTowerOpt();

			// 检查是否有足够金币升级
			if (_upGradeMoney > _funcCheckMoney()) {
				return;
			}

			// 根据塔ID选择相应的塔类型
			switch (_TowerId) {
			case 1: _towerType = en_GreenTower; break;
			case 4: _towerType = en_CloverTower; break;
			case 7: _towerType = en_ShitTower; break;
			case 10: _towerType = en_BallTower; break;
			case 13: _towerType = en_StarTower; break;
			default: break;
			}

			// 创建塔并播放建塔音效
			TowerFactory::createTower(_towerType, this->getPosition());
			SoundUtil::getInstance()->playEffect(BUILDTOWER);

			// 扣除建塔所需金币，并发送金币变化通知
			int createMoney = -CsvUtil::getInstance()->getInt(_TowerId, en_CreateCost, TOWERCSVFILE);
			NOTIFY->postNotification("moneyChange", (Ref*)(&createMoney));
			});

		_Toweritem->setTag(_upGradeMoney);
		_Toweritem->setName(iterTower);
		_pCreateTowerItemSpVec->pushBack(_Toweritem);

		// 根据计数器决定将塔项加入到菜单1还是菜单2
		i < 5 ? _pCreateMenu1->addChild(_Toweritem) : _pCreateMenu2->addChild(_Toweritem);
		i++;
	}

	// 设置菜单1的水平对齐，并在塔项数量超过4个时设置菜单2的水平对齐
	_pCreateMenu1->alignItemsHorizontallyWithPadding(1);
	if (_pCreateTowerItemSpVec->size() > 4) _pCreateMenu2->alignItemsHorizontallyWithPadding(1);
}


void TowerOptBtn::gradeTowerMenu(TowerBase* touchTower){
	_pGradeMenu->removeAllChildrenWithCleanup(true);
	auto _pSpriteFrameCache = SpriteFrameCache::getInstance();
	_pTowerRangeSp->setSpriteFrame(_pSpriteFrameCache->getSpriteFrameByName("range_" + StringUtils::format("%d", touchTower->getIAtkRange()) + PHOTOPOSTFIX));
	_pTowerRangeSp->setVisible(true);
	auto _pAtkRange = Sprite::createWithSpriteFrame(_pSpriteFrameCache->getSpriteFrameByName(StringUtils::format("range_%d", touchTower->getIAtkRange()) + PHOTOPOSTFIX));
	auto UpgradeSp = Sprite::createWithSpriteFrame(_pSpriteFrameCache->getSpriteFrameByName("upgrade_" + touchTower->getSUpgradeCose() + PHOTOPOSTFIX));
	auto UpgradeItem = MenuItemSprite::create(UpgradeSp, UpgradeSp, [=](Ref* r){
		this->setTag(0);
		hideTowerOpt();
		if (touchTower->getIUpgradeCount() > 1) return;
		if (touchTower->getTowerGradeCost() > _funcCheckMoney()) return;
		touchTower->upGrade();
        SoundUtil::getInstance()->playEffect(UPGRADETOWER);
		touchTower->setIUpgradeCount(touchTower->getIUpgradeCount() + 1);
	});
	auto SellSp = Sprite::createWithSpriteFrame(_pSpriteFrameCache->getSpriteFrameByName(StringUtils::format("sell_%d", touchTower->getIValue()) + PHOTOPOSTFIX));
	auto SellItem = MenuItemSprite::create(SellSp, SellSp, [=](Ref* r){
		this->setTag(0);
		hideTowerOpt();
		SoundUtil::getInstance()->playEffect(SELLTOWER);
		touchTower->doDead();
	});

	UpgradeItem->setName("upgrade_");
	UpgradeItem->setTag(touchTower->getTowerGradeCost());
	_pGradeTowerItemSpVec->pushBack(UpgradeItem);
	_pGradeMenu->addChild(UpgradeItem);
	_pGradeMenu->addChild(SellItem);
	if (this->getPositionY() >= 480){
		if (this->getPositionX() < 80) UpgradeItem->setPosition(Vec2(80, 0));
		else UpgradeItem->setPosition(Vec2(-80, 0));
		SellItem->setPosition(Vec2(0, -80));
	}
	else if (this->getPositionY() < 80){
		if (this->getPositionX() < 80) SellItem->setPosition(Vec2(80, 0));
		else SellItem->setPosition(Vec2(-80, 0));
		UpgradeItem->setPosition(Vec2(0, 80));
	}
	else _pGradeMenu->alignItemsVerticallyWithPadding(100);
	_pGradeMenu->setPosition(40, 40);
}

/**
 * @brief 更新塔菜单项的外观，根据金币数量显示不同状态
 * @param dt 时间间隔
 */
void TowerOptBtn::ChangingItem(float dt) {
	// 更新创建塔的菜单项外观
	for (auto itemCreateSp = _pCreateTowerItemSpVec->begin(); itemCreateSp != _pCreateTowerItemSpVec->end(); itemCreateSp++) {
		auto _pCreateItemSp = (*itemCreateSp);

		// 判断金币是否足够，选择不同的精灵显示
		if (_pCreateItemSp->getTag() > _funcCheckMoney()) {
			_pCreateItemSp->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_pCreateItemSp->getName() + "00" + PHOTOPOSTFIX)));
		}
		else {
			_pCreateItemSp->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_pCreateItemSp->getName() + "01" + PHOTOPOSTFIX)));
		}
	}

	// 更新升级塔的菜单项外观
	for (auto itemGradeSp = _pGradeTowerItemSpVec->begin(); itemGradeSp != _pGradeTowerItemSpVec->end(); itemGradeSp++) {
		auto _pGradeItemSp = (*itemGradeSp);

		// 判断是否可升级且金币是否足够，选择不同的精灵显示
		if (_pGradeItemSp->getTag() != 0) {
			if (_pGradeItemSp->getTag() > _funcCheckMoney()) {
				_pGradeItemSp->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_pGradeItemSp->getName() + StringUtils::format("%d", -_pGradeItemSp->getTag()) + PHOTOPOSTFIX)));
			}
			else {
				_pGradeItemSp->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_pGradeItemSp->getName() + StringUtils::format("%d", _pGradeItemSp->getTag()) + PHOTOPOSTFIX)));
			}
		}
	}
}


void TowerOptBtn::setFuncCheckMoney(const std::function<int()> &rFuncCheckMoney){
	_funcCheckMoney = rFuncCheckMoney;
}



/**
 * @brief 显示创建菜单，根据按钮位置和塔菜单项数量调整菜单布局
 */
void TowerOptBtn::showCreateMenu() {
	// 清空升级菜单的子节点
	_pGradeMenu->removeAllChildrenWithCleanup(true);

	// 设置创建菜单1和菜单2可见
	_pCreateMenu1->setVisible(true);
	_pCreateMenu2->setVisible(true);

	// 根据按钮位置调整菜单1的初始位置
	if (this->getPositionY() < 320) {
		_pCreateMenu1->setPosition(40, 120);
		// 若塔菜单项数量大于4，调整菜单2的位置
		if (_pCreateTowerItemSpVec->size() > 4) {
			_pCreateMenu2->setPosition(_pCreateMenu1->getPosition());
			_pCreateMenu1->setPosition(40, 200);
		}
	}
	else {
		_pCreateMenu1->setPosition(40, -50);
		// 若塔菜单项数量大于4，调整菜单2的位置
		if (_pCreateTowerItemSpVec->size() > 4) _pCreateMenu2->setPosition(_pCreateMenu1->getPosition() - Vec2(0, 80));
	}

	int x1 = 120;
	int x2 = 120;

	// 根据塔菜单项数量调整菜单1和菜单2的水平位置
	switch (_pCreateTowerItemSpVec->size())
	{
	case 1: x1 = 0; break;
	case 2: x1 = 40; break;
	case 3: x1 = 80; break;
	case 4: x1 = 120; break;
	default: break;
	}

	switch (_pCreateTowerItemSpVec->size() - 4)
	{
	case 1: x2 = 0; break;
	case 2: x2 = 40; break;
	case 3: x2 = 80; break;
	case 4: x2 = 120; break;
	default: break;
	}

	// 根据按钮位置调整菜单1和菜单2的水平位置
	if (this->getPositionX() <= 120) {
		_pCreateMenu1->setPosition(_pCreateMenu1->getPosition() + Vec2(x1, 0));
		_pCreateMenu2->setPosition(_pCreateMenu2->getPosition() + Vec2(x2, 0));
	}
	if (this->getPositionX() >= 840) {
		_pCreateMenu1->setPosition(_pCreateMenu1->getPosition() + Vec2(-x1, 0));
		_pCreateMenu2->setPosition(_pCreateMenu2->getPosition() + Vec2(-x2, 0));
	}
}


void TowerOptBtn::hideCreateMenu(){
	_pCreateMenu1->setVisible(false);
	_pCreateMenu2->setVisible(false);
}