
#include "MoveControllerBase.h"
#include "MapUtil.h"
#define STEP 10.0
// �����ƶ�����������ĳ�ʼ��������������һ��ָ���������ָ��
bool MoveControllerBase::init(MonsterBase* pMomster)
{
	// ����һ���������͵ķ���ֵ����ʼΪfalse
	if (!Node::init()) {
		// �������ĳ�ʼ������ʧ�ܣ��ͷ���false
		return false;
	}

	// ���ó�Ա���������ó�Ա����Ϊ����ָ��Ĺ������
	setMonster(pMomster);
	// �ӹ�������л�ȡ�ٶȣ���ֵ����Ա����
	_iMonsterSpeed = _pMonster->getISpeed();
	// ����ǰ�������Ϊ���������ӽڵ�
	_pMonster->addChild(this);

	// ���õ�ͼ���ߵĵ�����������ȡ�ƶ�·���ĵ����������ֵ��һ���Զ����͵ı���
	auto Points = MapUtil::getInstance()->getMovePoses();

	// ����һ���µĶ�ά��������������ֵ����Ա����
	_pMapPonits = new std::vector<Vec2>();

	// ʹ��forѭ���������ƶ�·���ĵ������
	for (int i = 0; i < Points.size(); i++) {
		// ����һ����ά�����ı�����������ŵ�����ĵ������
		Vec2 t_point;
		// ���ݹ������ĵȼ����Ե��x������в�ͬ��ƫ�ƣ�ʹ��������ܹ��ڲ�ͬ�Ĺ�����ƶ�
		if (_pMonster->getILevel() == 1) t_point.x = Points.at(i).x + _pMonster->getContentSize().width / 2 - 15;
		if (_pMonster->getILevel() == 2) t_point.x = Points.at(i).x + 30;
		if (_pMonster->getILevel() == 3) t_point.x = Points.at(i).x + 40;
		// �Ե��y�������һ����ƫ�ƣ�ʹ��������ܹ��ڵ������ƶ�
		t_point.y = Points.at(i).y - 5;
		// ��������ĵ��������ӵ���Ա������������
		_pMapPonits->push_back(t_point);
	}
	// ���ù�������λ��Ϊ��Ա�����������ĵ�һ��Ԫ�أ����ƶ�·�������
	_pMonster->setPosition(*_pMapPonits->begin());

	// ���ó�Ա�������������������ƶ��¼���������һ���������Թ��������ٶȣ���ʾ�ƶ���ʱ����
	listenerMonster(STEP / _pMonster->getISpeed());

	// ����true����ʾ��ʼ���ɹ�
	return true;
}
// �����ƶ�����������Ĵ���������������һ��ָ���������ָ�룬����һ��ָ���ƶ������������ָ��
MoveControllerBase* MoveControllerBase::create(MonsterBase* pMomster) {
	// ����һ���µ��ƶ�����������Ķ��󣬸�ֵ��һ���Զ����͵ı���
	auto cMonster = new MoveControllerBase();
	// �������Ϊ�գ����ҵ��ó�ʼ�������ɹ�
	if (cMonster && cMonster->init(pMomster)) {
		// ���ö�����Զ��ͷź�������ֹ�ڴ�й©
		cMonster->autorelease();
		// ���ض����ָ��
		return cMonster;
	}
	// ʹ��CC_SAFE_DELETE�갲ȫ��ɾ�������ͷ��ڴ�
	CC_SAFE_DELETE(cMonster);
	// ���ؿ�ָ��
	return nullptr;
}

// �����ƶ���������������ù������ĺ�����������һ��ָ���������ָ�룬�޷���ֵ
void MoveControllerBase::setMonster(MonsterBase* pMonster)
{
	// ��������ֵ����Ա��������ʾ�����Ĺ������
	_pMonster = pMonster;
}

// �����ƶ�����������ļ����������ĺ�����������һ���������͵ı�������ʾ�ƶ���ʱ����
void MoveControllerBase::listenerMonster(float t)
{
	// ���������������ֵС�ڵ���0�����߹�������Ѿ���������ֱ�ӷ���
	if (_pMonster->getIHp() <= 0 || _pMonster->getIsDead())return;
	// ���ó�Ա������ɾ���ƶ�·���ĵ�һ����
	erasePoint();
	// ����һ����ά�����ı�������ֵΪ��Ա�����������ĵ�һ��Ԫ�أ���ʾ�ƶ�·������һ����
	Vec2 pot = *_pMapPonits->begin();
	// �����һ�����x����С�ڹ�������x���꣬�ͽ��������ĳ�������Ϊ��
	if (pot.x < _pMonster->getPositionX()) {
		_pMonster->setIsLeft(true);
	}
	// ���򣬽��������ĳ�������Ϊ��
	else {
		_pMonster->setIsLeft(false);
	}
	// ����һ��ָ���ƶ�������ָ�룬��������ƶ��Ĳ���
	MoveBy* pStep;
	// �����������x���������һ�����x���꣬��ʾ���������Ҫ����y���ƶ�
	if (_pMonster->getPositionX() == pot.x) {
		// �����������y����С�ڵ�����һ�����y���꣬�ʹ���һ�������ƶ�һ������Ķ�������ֵ��ָ��
		if (_pMonster->getPositionY() <= pot.y) {
			pStep = MoveBy::create(t, Vec2(0, STEP));
		}
		// ���򣬴���һ�������ƶ�һ������Ķ�������ֵ��ָ��
		else {
			pStep = MoveBy::create(t, Vec2(0, -STEP));
		}
	}
	// ���򣬱�ʾ���������Ҫ����x���ƶ�
	else {
		// �����������x����С�ڵ�����һ�����x���꣬�ʹ���һ�������ƶ�һ������Ķ�������ֵ��ָ��
		if (_pMonster->getPositionX() <= pot.x) {
			pStep = MoveBy::create(t, Vec2(STEP, 0));
		}
		// ���򣬴���һ�������ƶ�һ������Ķ�������ֵ��ָ��
		else {
			pStep = MoveBy::create(t, Vec2(-STEP, 0));
		}
	}
	// ����һ���ص����������������ƶ���ɺ��ٴε��ü����������ĺ�����������ͬ��ʱ��������
	auto pMoveCall = CallFuncN::create([=](Node* pSender) {
		this->listenerMonster(STEP / _pMonster->getISpeed());
		});
	// ����һ�����ж������󣬰����ƶ��Ĳ���ͻص�����
	Sequence* seq = Sequence::create(pStep, pMoveCall, NULL);
	// ����������ĳ������󣬾ͽ��������ľ����y����ת�Ƕ�����Ϊ0����ʾ���泯��
	if (!_pMonster->getIsLeft()) {
		_pMonster->getSprite()->setRotationSkewY(0);
	}
	// ���򣬽��������ľ����y����ת�Ƕ�����Ϊ180����ʾ���泯��
	else {
		_pMonster->getSprite()->setRotationSkewY(180);
	}

	// ����һ���������͵ı�������ֵΪ��������״̬
	int MonsterState = _pMonster->getIState();
	// ���������������͵ı������ֱ��ʾ�������ļ��١�ֹͣ���ж���״̬����λ���������Ӧ����������ж�
	int State_Slow = MonsterState & 2;
	int State_Stop = MonsterState & 4;
	int State_Poison = MonsterState & 8;
	// �����������ڼ���״̬�����Ҽ��ٳ���ʱ�����0
	if (State_Slow && _pMonster->getFSlowDuration() > 0)
	{
		// �����������ٶ�����Ϊ��Ա�������ٶȳ���3����ʾ����Ч��
		_pMonster->setISpeed(_iMonsterSpeed / 3);
		// ����һ���������͵ı�������ֵΪ�������ļ��ٳ���ʱ���ȥ�ƶ���ʱ��������ʾʣ��ļ���ʱ��
		float StateTime = _pMonster->getFSlowDuration() - t;
		// ���ʣ��ļ���ʱ��С��0���ͽ�������Ϊ0
		if (StateTime < 0) StateTime = 0;
		// ���������ļ��ٳ���ʱ������Ϊʣ��ļ���ʱ��
		_pMonster->setFSlowDuration(StateTime);
		// ����һ���������������ʾ���ٵĶ���Ч��
		Sprite* pTemp = Sprite::create();
		// ���þ�������λ�ã����ݹ������Ĵ�С��λ�ý���ƫ��
		pTemp->setPosition(_pMonster->getContentSize().width / 2, 40);
		// ������������Ϊ�������ľ�����ӽڵ�
		_pMonster->getSprite()->addChild(pTemp);
		// ���ó�Ա���������ݹ��������ӵ�״̬���ͺ��ƶ���ʱ����������һ���������󣬸�ֵ��һ���Զ����͵ı���
		Animation* pAnimation = AnimationMaker(_pMonster->getIBulletStateType(), t);
		// ����һ���ص��������������ڶ���������ɺ�ִ��һЩ����
		auto pCallFunc = CallFunc::create([=]() {
			// ���������Ӹ��ڵ����Ƴ�������
			pTemp->removeFromParentAndCleanup(true);
		// ����������ļ��ٳ���ʱ��С�ڵ���0����ʾ����Ч������
		if (_pMonster->getFSlowDuration() <= 0)
		{
			// �����������ٶȻָ�Ϊ��Ա�������ٶ�
			_pMonster->setISpeed(_iMonsterSpeed);
			// ����������״̬��λ���������Ӧ����������޸ģ���ʾȡ������״̬
			_pMonster->setIState(_pMonster->getIState() & 13);
		}
			});
		// ����һ�����ж������󣬰��������ͻص�����
		Sequence* pSequence = Sequence::create(Animate::create(pAnimation), pCallFunc, NULL);
		// �þ������ִ�����ж���
		pTemp->runAction(pSequence);
	}
	// �������������ж�״̬�������ж�����ʱ�����0
	if (State_Poison && _pMonster->getfPoisonDuration() > 0)
	{
		// ����һ���������͵ı�������ֵΪ���������ж�����ʱ���ȥ�ƶ���ʱ��������ʾʣ����ж�ʱ��
		float StateTime = _pMonster->getfPoisonDuration() - t;
		// ���ʣ����ж�ʱ��С��0���ͽ�������Ϊ0
		if (StateTime < 0) StateTime = 0;
		// �����������ж�����ʱ������Ϊʣ����ж�ʱ��
		_pMonster->setfPoisonDuration(StateTime);
		// ����һ���������Եı�������ֵΪһ���ṹ�壬��ʾ�ж����˺�Ч��
		AtkProperty atk;
		// ���ù������Ե�״̬Ϊ1����ʾ��ͨ����
		atk._enAtkState = 1;
		// ���ù������ԵĹ�����Ϊ2����ʾÿ���ж���ɵ��˺�
		atk._iAtk = 2;
		// ���ù������Եĳ���ʱ��Ϊ0����ʾ�޳���Ч��
		atk._iDuration = 0;

		// ����һ���������������ʾ�ж��Ķ���Ч��
		Sprite* pTemp = Sprite::create();
		// ���þ�������λ�ã����ݹ������Ĵ�С��λ�ý���ƫ��
		pTemp->setPosition(_pMonster->getContentSize().width / 2, 40);
		// ������������Ϊ�������ľ�����ӽڵ�
		_pMonster->getSprite()->addChild(pTemp);
		// ���ó�Ա���������ݹ��������ӵ�״̬���ͺ��ƶ���ʱ����������һ���������󣬸�ֵ��һ���Զ����͵ı���
		Animation* pAnimation = AnimationMaker(6, t);
		// ����һ���ص��������������ڶ���������ɺ�ִ��һЩ����
		auto pCallFunc = CallFunc::create([=]() {
			// ����������û���������͵��ù����������˺��������ݹ������Եı�������ʾ����ж��˺�
			if (!_pMonster->getIsDead()) _pMonster->beHurt(atk);
		// ������������ж�����ʱ��С�ڵ���0����ʾ�ж�Ч������
		if (_pMonster->getfPoisonDuration() <= 0)
		{
			// ����������״̬��λ���������Ӧ����������޸ģ���ʾȡ���ж�״̬
			_pMonster->setIState(_pMonster->getIState() & 7);
		}
		// ���������Ӹ��ڵ����Ƴ�������
		pTemp->removeFromParentAndCleanup(true);
			});
		// �þ������ִ��һ�����ж��������������ͻص�����
		pTemp->runAction(Sequence::create(Animate::create(pAnimation), pCallFunc, NULL));
	}
	// ������������ֹͣ״̬������ֹͣ����ʱ�����0
	if (State_Stop && _pMonster->getfStopDuration() > 0)
	{
		// ����һ���������͵ı�������ֵΪ��������ֹͣ����ʱ���ȥ�ƶ���ʱ��������ʾʣ���ֹͣʱ��
		float StateTime = _pMonster->getfStopDuration() - t;
		// ���ʣ���ֹͣʱ��С��0���ͽ�������Ϊ0
		if (StateTime < 0) StateTime = 0;
		// ����������ֹͣ����ʱ������Ϊʣ���ֹͣʱ��
		_pMonster->setfStopDuration(StateTime);
		// ����һ���������������ʾֹͣ�Ķ���Ч��
		Sprite* pTemp = Sprite::create();
		// ���þ�������λ�ã����ݹ������Ĵ�С��λ�ý���ƫ��
		pTemp->setPosition(_pMonster->getContentSize().width / 2, 40);
		// ������������Ϊ�������ľ�����ӽڵ�
		_pMonster->getSprite()->addChild(pTemp);
		// ���ó�Ա���������ݹ��������ӵ�״̬���ͺ��ƶ���ʱ����������һ���������󣬸�ֵ��һ���Զ����͵ı���
		Animation* pAnimation = AnimationMaker(_pMonster->getIBulletStateType(), t);
		// ����һ���ص��������������ڶ���������ɺ�ִ��һЩ����
		auto pCallFunc = CallFunc::create([=]() {
			// �����������ֹͣ����ʱ��С�ڵ���0����ʾֹͣЧ������
			if (_pMonster->getfStopDuration() <= 0)
			{
				// ����������״̬��λ���������Ӧ����������޸ģ���ʾȡ��ֹͣ״̬
				_pMonster->setIState(_pMonster->getIState() & 11);
			}
		// �ٴε��ü����������ĺ�����������ͬ��ʱ������������ʾ�ָ��ƶ�
		this->listenerMonster(STEP / _pMonster->getISpeed());
		// ���������Ӹ��ڵ����Ƴ�������
		pTemp->removeFromParentAndCleanup(true);
			});
		// �þ������ִ��һ�����ж��������������ͻص�����
		pTemp->runAction(Sequence::create(Animate::create(pAnimation), pCallFunc, NULL));
		// ֱ�ӷ��أ���ִ�к�����ƶ�����
		return;
	}
	// �ù������ִ���ƶ������ж���
	_pMonster->runAction(seq);
}

// �����ƶ������������ɾ����ĺ������޲������޷���ֵ
void MoveControllerBase::erasePoint() {
	// �����Ա�����������Ĵ�С����1����ʾֻʣ��һ���㣬��ֱ�ӷ���
	if (_pMapPonits->size() == 1) {
		return;
	}
	// �����������λ�õ��ڳ�Ա�����������ĵ�һ��Ԫ�أ���ʾ������һ����
	if (_pMonster->getPosition() == *_pMapPonits->begin()) {
		// �ʹӳ�Ա������������ɾ����һ��Ԫ��
		_pMapPonits->erase(_pMapPonits->begin());
		// �����Ա�����������Ĵ�С����1����ʾ���������һ����
		if (_pMapPonits->size() == 1)
		{
			// �ͷ���һ��֪ͨ����ʾ���ܲ��ܵ��˺��������ǹ�������ָ��
			NOTIFY->postNotification("CarrotHurt", _pMonster);
			// �ͷ���һ��֪ͨ����ʾ������������������ǹ�������ָ��
			NOTIFY->postNotification("MonsterDead", _pMonster);
			// ��������������״̬����Ϊ��
			_pMonster->setIsDead(true);
			// ���������Ӹ��ڵ����Ƴ�������
			_pMonster->removeFromParentAndCleanup(true);
		}
	}
}

// �����ƶ�����������������������ͷ��ڴ�
MoveControllerBase::~MoveControllerBase()
{
	// ɾ����Ա�������������ͷ��ڴ�
	delete(_pMapPonits);
}

// �����ƶ�����������Ķ�������������������һ���������͵ı�������ʾ�ӵ������ͣ���һ���������͵ı�������ʾ������ʱ����������һ��ָ�򶯻������ָ��
Animation* MoveControllerBase::AnimationMaker(int iBulletType, float t)
{
	// ����һ���µĶ������󣬸�ֵ��һ���Զ����͵ı���
	Animation* pAnimation = Animation::create();
	// ����ӵ������͵���1����ʾ��ʺ
	if (iBulletType == 1)
	{
		// �ʹӾ���֡�����л�ȡ����ʺ�ľ���֡����ӵ�����������
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PShit-11.png"));
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PShit-12.png"));
		// ���ö��������ÿ֡��ʱΪʱ��������2
		pAnimation->setDelayPerUnit(t / 2);
	}
	// ����ӵ������͵���5����ʾ������
	else if (iBulletType == 5)
	{
		// �ʹӾ���֡�����л�ȡһ�����ǵľ���֡����ӵ�����������
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PBStar-21.png"));
		// ���ö��������ÿ֡��ʱΪʱ����
		pAnimation->setDelayPerUnit(t);
	}
	// ����ӵ������͵���15��30��45����ʾ��ѩ��
	else if (iBulletType == 15 || iBulletType == 30 || iBulletType == 45)
	{
		// �ʹӾ���֡�����л�ȡ����ѩ���ľ���֡����ӵ�����������
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PSnow01.png"));
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PSnow02.png"));
		// ���ö��������ÿ֡��ʱΪʱ��������2
		pAnimation->setDelayPerUnit(t / 2);
	}
	// ����ӵ������͵���6����ʾ����
	else if (iBulletType == 6)
	{
		// �ʹӾ���֡�����л�ȡ�ĸ���ľ���֡����ӵ�����������
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PPin01.png"));
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PPin02.png"));
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PPin03.png"));
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PPin04.png"));
		// ���ö��������ÿ֡��ʱΪʱ��������4
		pAnimation->setDelayPerUnit(t / 4);
	}
	// ���ö��������ѭ������Ϊ1����ʾֻ����һ��
	pAnimation->setLoops(1);
	// ���ض��������ָ��
	return pAnimation;
}
