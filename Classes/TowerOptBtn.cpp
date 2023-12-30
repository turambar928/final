#include "TowerOptBtn.h"
#include "PublicSourceDefine.h"
#include "MapUtil.h"
#include "TowerFactory.h"
#include "LevelConfigUtil.h"
#include "ScoreAndControlLayer.h"
#include "TowerBase.h"
#include "SoundUtil.h"

/**
 * @brief TowerOptBtn��Ĺ��캯��
 */
TowerOptBtn::TowerOptBtn() {
}

/**
 * @brief TowerOptBtn�����������
 */
TowerOptBtn::~TowerOptBtn() {
	// �ͷŴ��������������Ĳ˵�����������ڴ�
	CC_SAFE_DELETE(_pCreateTowerItemSpVec);
	CC_SAFE_DELETE(_pGradeTowerItemSpVec);
}

/**
 * @brief ��ʼ��TowerOptBtn����
 * @return ��ʼ���Ƿ�ɹ�
 */
bool TowerOptBtn::init() {
	bool bRet = false;
	do {
		// �������������������Ĳ˵��������
		_pCreateTowerItemSpVec = new Vector<MenuItemSprite*>();
		_pGradeTowerItemSpVec = new Vector<MenuItemSprite*>();

		// �����˵��Ͳ˵�������ö�ʱ������
		createMenuAndItems();
		this->schedule(CC_SCHEDULE_SELECTOR(TowerOptBtn::ChangingItem));

		bRet = true;
	} while (0);
	return bRet;
}

/**
 * @brief ������������ť�ķ���
 */
void TowerOptBtn::hideTowerOpt() {
	// ���ùؼ����鲻�ɼ�
	_bKeySpVisible = false;
	_pKeySp->setVisible(_bKeySpVisible);

	// �������Χ������ڣ������ò��ɼ�
	if (_pTowerRangeSp != nullptr)
		_pTowerRangeSp->setVisible(false);

	// ���ô����������˵����ɼ�
	_pCreateMenu1->setVisible(false);
	_pCreateMenu2->setVisible(false);
}


/**
 * @brief ��ʾ��������ť�ķ���
 */
void TowerOptBtn::showTowerOpt() {
	// ���ùؼ�����ɼ�
	_bKeySpVisible = true;
	_pKeySp->setVisible(_bKeySpVisible);
}

/**
 * @brief �����˵��Ͳ˵���ķ���
 */
void TowerOptBtn::createMenuAndItems() {
	// �����ؼ����顢�����˵�1�������˵�2�Լ������˵��������ó�ʼ�ɼ���
	_pKeySp = Sprite::create();
	_pKeySp->setVisible(false);
	_pCreateMenu1 = Menu::create();
	_pCreateMenu1->setVisible(false);
	_pCreateMenu2 = Menu::create();
	_pCreateMenu2->setVisible(false);
	_pGradeMenu = Menu::create();

	// �������˵������ö���Ч��������ӵ��ؼ�������
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

	// ��������Χ���鲢���ó�ʼ���ɼ�����ӵ��ؼ�������
	_pTowerRangeSp = Sprite::create();
	_pTowerRangeSp->setPosition(40, 40);
	_pTowerRangeSp->setVisible(false);
	_pKeySp->addChild(_pTowerRangeSp);
}


/**
 * @brief �������˵��ķ���
 */
void TowerOptBtn::createTowerMenu() {
	int i = 1;
	for (auto& iterTower : LevelConfigUtil::getInstance()->getCurLevelTowersInfo()) {

		// ��ȡ����ID������������
		int _TowerId = CsvUtil::getInstance()->findValueInWithLine(iterTower, 1, TOWERCSVFILE);
		std::stringstream StoI;
		std::string _sUpgradeCost = CsvUtil::getInstance()->getText(_TowerId, en_CreateCost, TOWERCSVFILE);
		StoI << _sUpgradeCost;
		int _upGradeMoney;
		StoI >> _upGradeMoney;

		// ������������
		if (iterTower == "Sun1") iterTower = "Sun";
		if (iterTower == "PPlane1") iterTower = "Plane";

		// ��������ľ���
		auto _TowerItemSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(iterTower + "01" + PHOTOPOSTFIX));

		// ��������Ĳ˵�������ûص�����
		auto _Toweritem = MenuItemSprite::create(_TowerItemSp, _TowerItemSp, [=](Ref* r) {
			TowerType _towerType;
			this->setTag(0);
			hideTowerOpt();

			// ����Ƿ����㹻�������
			if (_upGradeMoney > _funcCheckMoney()) {
				return;
			}

			// ������IDѡ����Ӧ��������
			switch (_TowerId) {
			case 1: _towerType = en_GreenTower; break;
			case 4: _towerType = en_CloverTower; break;
			case 7: _towerType = en_ShitTower; break;
			case 10: _towerType = en_BallTower; break;
			case 13: _towerType = en_StarTower; break;
			default: break;
			}

			// �����������Ž�����Ч
			TowerFactory::createTower(_towerType, this->getPosition());
			SoundUtil::getInstance()->playEffect(BUILDTOWER);

			// �۳����������ң������ͽ�ұ仯֪ͨ
			int createMoney = -CsvUtil::getInstance()->getInt(_TowerId, en_CreateCost, TOWERCSVFILE);
			NOTIFY->postNotification("moneyChange", (Ref*)(&createMoney));
			});

		_Toweritem->setTag(_upGradeMoney);
		_Toweritem->setName(iterTower);
		_pCreateTowerItemSpVec->pushBack(_Toweritem);

		// ���ݼ�����������������뵽�˵�1���ǲ˵�2
		i < 5 ? _pCreateMenu1->addChild(_Toweritem) : _pCreateMenu2->addChild(_Toweritem);
		i++;
	}

	// ���ò˵�1��ˮƽ���룬����������������4��ʱ���ò˵�2��ˮƽ����
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
 * @brief �������˵������ۣ����ݽ��������ʾ��ͬ״̬
 * @param dt ʱ����
 */
void TowerOptBtn::ChangingItem(float dt) {
	// ���´������Ĳ˵������
	for (auto itemCreateSp = _pCreateTowerItemSpVec->begin(); itemCreateSp != _pCreateTowerItemSpVec->end(); itemCreateSp++) {
		auto _pCreateItemSp = (*itemCreateSp);

		// �жϽ���Ƿ��㹻��ѡ��ͬ�ľ�����ʾ
		if (_pCreateItemSp->getTag() > _funcCheckMoney()) {
			_pCreateItemSp->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_pCreateItemSp->getName() + "00" + PHOTOPOSTFIX)));
		}
		else {
			_pCreateItemSp->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_pCreateItemSp->getName() + "01" + PHOTOPOSTFIX)));
		}
	}

	// �����������Ĳ˵������
	for (auto itemGradeSp = _pGradeTowerItemSpVec->begin(); itemGradeSp != _pGradeTowerItemSpVec->end(); itemGradeSp++) {
		auto _pGradeItemSp = (*itemGradeSp);

		// �ж��Ƿ�������ҽ���Ƿ��㹻��ѡ��ͬ�ľ�����ʾ
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
 * @brief ��ʾ�����˵������ݰ�ťλ�ú����˵������������˵�����
 */
void TowerOptBtn::showCreateMenu() {
	// ��������˵����ӽڵ�
	_pGradeMenu->removeAllChildrenWithCleanup(true);

	// ���ô����˵�1�Ͳ˵�2�ɼ�
	_pCreateMenu1->setVisible(true);
	_pCreateMenu2->setVisible(true);

	// ���ݰ�ťλ�õ����˵�1�ĳ�ʼλ��
	if (this->getPositionY() < 320) {
		_pCreateMenu1->setPosition(40, 120);
		// �����˵�����������4�������˵�2��λ��
		if (_pCreateTowerItemSpVec->size() > 4) {
			_pCreateMenu2->setPosition(_pCreateMenu1->getPosition());
			_pCreateMenu1->setPosition(40, 200);
		}
	}
	else {
		_pCreateMenu1->setPosition(40, -50);
		// �����˵�����������4�������˵�2��λ��
		if (_pCreateTowerItemSpVec->size() > 4) _pCreateMenu2->setPosition(_pCreateMenu1->getPosition() - Vec2(0, 80));
	}

	int x1 = 120;
	int x2 = 120;

	// �������˵������������˵�1�Ͳ˵�2��ˮƽλ��
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

	// ���ݰ�ťλ�õ����˵�1�Ͳ˵�2��ˮƽλ��
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