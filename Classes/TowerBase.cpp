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
	// �ͷŹ���Ŀ�����¥������
	CC_SAFE_RELEASE_NULL(_pAtkTarget);
	CC_SAFE_RELEASE_NULL(_pTowerPanel);
}

bool TowerBase::init(const int& rId) {
	bool bRet = false;

	do {
		// ���û���ĳ�ʼ������
		CC_BREAK_IF(!Entity::init(rId, TOWERCSVFILE));

		// ��ʼ����¥
		initTower();

		// ����¥��ӵ���¥��������
		TowerManager::getInstance()->addTower(this);

		// ��ʱ���ȹ���Ŀ���鷽�������Ϊ0.1��
		schedule(CC_SCHEDULE_SELECTOR(TowerBase::checkAtkTarget), 0.1f);

		// ��ʱ���ȹ������������Ϊ�������ʱ��
		schedule(CC_SCHEDULE_SELECTOR(TowerBase::fire), _iAtkSpace);

		// ��ʱ������ת���������Ϊ0.1��
		schedule(CC_SCHEDULE_SELECTOR(TowerBase::doRocation), 0.1f);

		// ��ʼ���ɹ�
		bRet = true;
	} while (0);

	return  bRet;
}

void TowerBase::deadAction(const std::string& rSDeadImageFile) {
	// ������¥����֪ͨ
	NOTIFY->postNotification("TowerDead", this);

	// ���û����������������
	Entity::deadAction();
}

void TowerBase::checkAtkTarget(float dt) {
	// ���û�й���Ŀ�꣬ѡ��һ��
	if (!_pAtkTarget) chooseAtkTarget();
	else {
		// �������Ŀ���������߹���Ŀ�겻���й���Ŀ�겢����¥�й���Ŀ��
		if (_pAtkTarget->getIsDead() || (!_pAtkTarget->getAtkTarget() && _bIsHaveAtkTarget)) {
			// ��ʧ����Ŀ��
			missAtkTarget();
			setIsHaveAtkTarget(false);
			return;
		}

		// ���Ŀ���Ƿ񳬳�������Χ
		checkTargetIsOutOfRange();
	}
}

/**
 * @brief ѡ�񹥻�Ŀ��ķ���
 */
void TowerBase::chooseAtkTarget() {
	// ��ȡ����������Ĺ�������
	auto tMonsterVec = MonsterManager::getInstance()->getMonsterVec();

	// ������������
	for (auto& iterMonster : tMonsterVec) {
		// ��������ڹ�����Χ��
		if (isInAtkRange(iterMonster->getPosition())) {
			// ���ù���Ŀ�겢����ѭ��
			setAtkTarget(iterMonster);
			break;
		}
	}
}

/**
 * @brief �ж�ĳ��λ���Ƿ�����¥�Ĺ�����Χ��
 * @param rPos Ҫ�жϵ�λ��
 * @return ����ڷ�Χ�ڷ���true�����򷵻�false
 */
bool TowerBase::isInAtkRange(const cocos2d::Vec2& rPos) {
	bool bRet = false;

	do {
		// ������¥��Ŀ��λ�õľ���
		auto tDistance = getPosition().distance(rPos);

		// ����������Χ����
		auto RangeSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("range_%d", _iAtkRange) + PHOTOPOSTFIX));

		// �������С�ڹ�����Χ��һ�����30��һ������İ�ȫ���룩�����ڹ�����Χ��
		CC_BREAK_IF(!(tDistance < RangeSp->getContentSize().width / 2 + 30));

		// �ڹ�����Χ��
		bRet = true;
	} while (0);

	return bRet;
}


/**
 * @brief �����ӵ��ķ���
 * @param dt ʱ�䲽��
 */
void TowerBase::fire(float dt) {
	// ���û�й���Ŀ����߹���Ŀ���Ѿ��������򷵻�
	if (!_pAtkTarget || _pAtkTarget->getIsDead()) return;

	// ִ�з��䶯��
	fireAction();

	// �����ӵ��Ļص�����
	auto createBulletCF = CallFunc::create([=]() {
		// ���û�й���Ŀ�꣬�򷵻�
		if (!_pAtkTarget) return;

		// �����ӵ�
		BulletFactory::createBullet(_iBulletId, this, _pAtkTarget);
		});

	// ��ʱ0.15���ִ�д����ӵ��Ļص�����
	this->runAction(Sequence::create(DelayTime::create(0.15), createBulletCF, NULL));
}

/**
 * @brief ��鹥��Ŀ���Ƿ񳬳�������Χ�ķ���
 */
void TowerBase::checkTargetIsOutOfRange() {
	// ������ڹ���Ŀ��
	if (_pAtkTarget) {
		// �������Ŀ�겻�ڹ�����Χ�ڣ���ִ�ж�ʧ����Ŀ��ķ���
		if (!isInAtkRange(_pAtkTarget->getPosition())) missAtkTarget();
	}
}

/**
 * @brief ��ʧ����Ŀ��ķ���
 */
void TowerBase::missAtkTarget() {
	// �ͷŹ���Ŀ�꣬����Ϊ��ָ��
	CC_SAFE_RELEASE_NULL(_pAtkTarget);
}

/**
 * @brief ���ù���Ŀ��ķ���
 * @param pVictimEntity ����Ŀ��
 */
void TowerBase::setAtkTarget(VictimEntityBase* pVictimEntity) {
	// �ͷ�֮ǰ�Ĺ���Ŀ��
	CC_SAFE_RELEASE_NULL(_pAtkTarget);

	// �����µĹ���Ŀ�꣬���������ü���
	_pAtkTarget = pVictimEntity;
	CC_SAFE_RETAIN(_pAtkTarget);
}

/**
 * @brief ������¥����ľ�̬����
 * @param rId ��¥��Ψһ��ʶ��
 * @return ��������¥�����������ʧ�ܷ���nullptr
 */
TowerBase* TowerBase::create(const int& rId) {
	auto t = new TowerBase();

	// �����ʼ���ɹ������Զ��ͷŲ�������¥����
	if (t && t->init(rId)) {
		t->autorelease();
		return t;
	}

	// ��ʼ��ʧ��ʱ�ͷ���¥���󲢷���nullptr
	CC_SAFE_DELETE(t);
	return nullptr;
}


/**
 * @brief ִ����ת�ķ���
 * @param dt ʱ�䲽��
 */
void TowerBase::doRocation(float dt) {
	// ���û�й���Ŀ�꣬�򷵻�
	if (!_pAtkTarget) return;

	// ���������ת��ִ����ת����
	if (_bIsRotation)
		getSprite()->runAction(RotateTo::create(0.1, 90 - 180 * (_pAtkTarget->getPosition() - this->getPosition()).getAngle() / M_PI));
}

/**
 * @brief ִ�з��䶯���ķ���
 */
void TowerBase::fireAction() {
	// ��ȡ��Ч����
	std::string soundName = _sName;

	// �����Ч����Ϊ"BStar"����ʹ��"PStar"����
	if (soundName == "BStar") soundName = "PStar";

	// ������Ч
	SoundUtil::getInstance()->playEffect(StringUtils::format("Music/Towers/%s.mp3", soundName.c_str()));

	// ������������
	auto pAnimation = Animation::create();
	auto pSpriteFrameCache = SpriteFrameCache::getInstance();

	// ��Ӿ���֡��������
	for (int i = 1; i <= this->getAnimationFrameCount(); i++)
		pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(_sModelName + StringUtils::format("%d", i) + PHOTOPOSTFIX));

	// ��Ӷ���ľ���֡�����ڹ���
	pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(_sModelName + "1" + PHOTOPOSTFIX));

	// ���ö��������ٶȺ�ѭ������
	pAnimation->setDelayPerUnit(0.05);
	pAnimation->setLoops(1);

	// ��������������ִ��
	auto pAnimate = Animate::create(pAnimation);
	this->getSprite()->runAction(pAnimate);
}


/**
 * @brief ������ǰ���ķ���
 */
void TowerBase::upGrade() {
	// ���������Ѵ��ַ���ת��Ϊ����
	std::stringstream StoI;
	StoI << _sUpgradeCost;
	int upGradeMoney;
	StoI >> upGradeMoney;
	upGradeMoney = -upGradeMoney;

	// ���ͽ�ұ仯֪ͨ
	NOTIFY->postNotification("moneyChange", (Ref*)(&upGradeMoney));

	// ���浱ǰ��������
	auto upGradeCounts = this->getIUpgradeCount();

	// �Ƴ�������־�����ľ���
	_pGradeMark->removeFromParentAndCleanup(true);
	getSprite()->removeFromParentAndCleanup(true);

	// ͨ������ID��ʼ����������
	Entity::initProperty(this->getIId() + 1, TOWERCSVFILE);

	// ���³�ʼ����
	initTower();

	// �ָ���������
	this->_iUpgradeCount = upGradeCounts;
}

/**
 * @brief ��ʼ����������
 */
void TowerBase::initTower() {
	// ������������ڣ����Ƴ�
	if (_pTowerPanel)
		removeChild(_pTowerPanel);

	// �ͷ��������
	CC_SAFE_RELEASE_NULL(_pTowerPanel);

	// ��ȡCSV����ʵ��
	auto pCsvUtil = CsvUtil::getInstance();

	// ��CSV�ļ��л�ȡ��������ֵ
	_iBulletId = pCsvUtil->getInt(_iId, en_BulletId, TOWERCSVFILE);
	_iAtkRange = pCsvUtil->getInt(_iId, en_Range, TOWERCSVFILE);
	_iAtkSpace = pCsvUtil->getDouble(_iId, en_Space, TOWERCSVFILE);
	_sUpgradeCost = pCsvUtil->getText(_iId, en_UpGradeCost, TOWERCSVFILE);
	_bIsRotation = pCsvUtil->getInt(_iId, en_IsRotation, TOWERCSVFILE);
	_iUpgradeCount = 0;
	_iCreateCost = pCsvUtil->getInt(_iId, en_CreateCost, TOWERCSVFILE);
	_bIsHaveAtkTarget = false;

	// ��������ʼ��������־����
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

	// ��������ʼ���������
	_pTowerPanel = Sprite::createWithSpriteFrameName(pCsvUtil->getText(_iId, en_TowerBase, TOWERCSVFILE));
	_pTowerPanel->retain();
	_pTowerPanel->setLocalZOrder(1);
	addChild(_pTowerPanel);

	// �������ľ������Ⱦ���
	getSprite()->setLocalZOrder(2);
}


/**
 * @brief ��ȡ������ǰ������Ľ�ҳɱ�
 * @return ��ҳɱ�
 */
int TowerBase::getTowerGradeCost() {
	// ���������Ѵ��ַ���ת��Ϊ����
	std::stringstream StoI;
	StoI << _sUpgradeCost;
	int upGradeMoney;
	StoI >> upGradeMoney;
	return upGradeMoney;
}

/**
 * @brief ��ʾ������־
 */
void TowerBase::showGradeMark() {
	_pGradeMark->setVisible(true);
}

/**
 * @brief ����������־
 */
void TowerBase::hideGradeMark() {
	_pGradeMark->setVisible(false);
}
