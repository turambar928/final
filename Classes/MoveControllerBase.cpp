
#include "MoveControllerBase.h"
#include "MapUtil.h"
#define STEP 10.0
// 定义移动控制器基类的初始化函数，参数是一个指向怪物基类的指针
bool MoveControllerBase::init(MonsterBase* pMomster)
{
	// 定义一个布尔类型的返回值，初始为false
	if (!Node::init()) {
		// 如果父类的初始化函数失败，就返回false
		return false;
	}

	// 调用成员函数，设置成员变量为参数指向的怪物对象
	setMonster(pMomster);
	// 从怪物对象中获取速度，赋值给成员变量
	_iMonsterSpeed = _pMonster->getISpeed();
	// 将当前对象添加为怪物对象的子节点
	_pMonster->addChild(this);

	// 调用地图工具的单例函数，获取移动路径的点的向量，赋值给一个自动类型的变量
	auto Points = MapUtil::getInstance()->getMovePoses();

	// 创建一个新的二维向量的向量，赋值给成员变量
	_pMapPonits = new std::vector<Vec2>();

	// 使用for循环，遍历移动路径的点的向量
	for (int i = 0; i < Points.size(); i++) {
		// 定义一个二维向量的变量，用来存放调整后的点的坐标
		Vec2 t_point;
		// 根据怪物对象的等级，对点的x坐标进行不同的偏移，使怪物对象能够在不同的轨道上移动
		if (_pMonster->getILevel() == 1) t_point.x = Points.at(i).x + _pMonster->getContentSize().width / 2 - 15;
		if (_pMonster->getILevel() == 2) t_point.x = Points.at(i).x + 30;
		if (_pMonster->getILevel() == 3) t_point.x = Points.at(i).x + 40;
		// 对点的y坐标进行一定的偏移，使怪物对象能够在地面上移动
		t_point.y = Points.at(i).y - 5;
		// 将调整后的点的坐标添加到成员变量的向量中
		_pMapPonits->push_back(t_point);
	}
	// 设置怪物对象的位置为成员变量的向量的第一个元素，即移动路径的起点
	_pMonster->setPosition(*_pMapPonits->begin());

	// 调用成员函数，监听怪物对象的移动事件，参数是一个常量除以怪物对象的速度，表示移动的时间间隔
	listenerMonster(STEP / _pMonster->getISpeed());

	// 返回true，表示初始化成功
	return true;
}
// 定义移动控制器基类的创建函数，参数是一个指向怪物基类的指针，返回一个指向移动控制器基类的指针
MoveControllerBase* MoveControllerBase::create(MonsterBase* pMomster) {
	// 创建一个新的移动控制器基类的对象，赋值给一个自动类型的变量
	auto cMonster = new MoveControllerBase();
	// 如果对象不为空，并且调用初始化函数成功
	if (cMonster && cMonster->init(pMomster)) {
		// 调用对象的自动释放函数，防止内存泄漏
		cMonster->autorelease();
		// 返回对象的指针
		return cMonster;
	}
	// 使用CC_SAFE_DELETE宏安全地删除对象，释放内存
	CC_SAFE_DELETE(cMonster);
	// 返回空指针
	return nullptr;
}

// 定义移动控制器基类的设置怪物对象的函数，参数是一个指向怪物基类的指针，无返回值
void MoveControllerBase::setMonster(MonsterBase* pMonster)
{
	// 将参数赋值给成员变量，表示关联的怪物对象
	_pMonster = pMonster;
}

// 定义移动控制器基类的监听怪物对象的函数，参数是一个浮点类型的变量，表示移动的时间间隔
void MoveControllerBase::listenerMonster(float t)
{
	// 如果怪物对象的生命值小于等于0，或者怪物对象已经死亡，就直接返回
	if (_pMonster->getIHp() <= 0 || _pMonster->getIsDead())return;
	// 调用成员函数，删除移动路径的第一个点
	erasePoint();
	// 定义一个二维向量的变量，赋值为成员变量的向量的第一个元素，表示移动路径的下一个点
	Vec2 pot = *_pMapPonits->begin();
	// 如果下一个点的x坐标小于怪物对象的x坐标，就将怪物对象的朝向设置为左
	if (pot.x < _pMonster->getPositionX()) {
		_pMonster->setIsLeft(true);
	}
	// 否则，将怪物对象的朝向设置为右
	else {
		_pMonster->setIsLeft(false);
	}
	// 定义一个指向移动动作的指针，用来存放移动的步骤
	MoveBy* pStep;
	// 如果怪物对象的x坐标等于下一个点的x坐标，表示怪物对象需要沿着y轴移动
	if (_pMonster->getPositionX() == pot.x) {
		// 如果怪物对象的y坐标小于等于下一个点的y坐标，就创建一个向上移动一定距离的动作，赋值给指针
		if (_pMonster->getPositionY() <= pot.y) {
			pStep = MoveBy::create(t, Vec2(0, STEP));
		}
		// 否则，创建一个向下移动一定距离的动作，赋值给指针
		else {
			pStep = MoveBy::create(t, Vec2(0, -STEP));
		}
	}
	// 否则，表示怪物对象需要沿着x轴移动
	else {
		// 如果怪物对象的x坐标小于等于下一个点的x坐标，就创建一个向右移动一定距离的动作，赋值给指针
		if (_pMonster->getPositionX() <= pot.x) {
			pStep = MoveBy::create(t, Vec2(STEP, 0));
		}
		// 否则，创建一个向左移动一定距离的动作，赋值给指针
		else {
			pStep = MoveBy::create(t, Vec2(-STEP, 0));
		}
	}
	// 创建一个回调函数对象，用来在移动完成后再次调用监听怪物对象的函数，传递相同的时间间隔参数
	auto pMoveCall = CallFuncN::create([=](Node* pSender) {
		this->listenerMonster(STEP / _pMonster->getISpeed());
		});
	// 创建一个序列动作对象，包括移动的步骤和回调函数
	Sequence* seq = Sequence::create(pStep, pMoveCall, NULL);
	// 如果怪物对象的朝向不是左，就将怪物对象的精灵的y轴旋转角度设置为0，表示正面朝向
	if (!_pMonster->getIsLeft()) {
		_pMonster->getSprite()->setRotationSkewY(0);
	}
	// 否则，将怪物对象的精灵的y轴旋转角度设置为180，表示反面朝向
	else {
		_pMonster->getSprite()->setRotationSkewY(180);
	}

	// 定义一个整数类型的变量，赋值为怪物对象的状态
	int MonsterState = _pMonster->getIState();
	// 定义三个整数类型的变量，分别表示怪物对象的减速、停止和中毒的状态，用位运算符和相应的掩码进行判断
	int State_Slow = MonsterState & 2;
	int State_Stop = MonsterState & 4;
	int State_Poison = MonsterState & 8;
	// 如果怪物对象处于减速状态，并且减速持续时间大于0
	if (State_Slow && _pMonster->getFSlowDuration() > 0)
	{
		// 将怪物对象的速度设置为成员变量的速度除以3，表示减速效果
		_pMonster->setISpeed(_iMonsterSpeed / 3);
		// 定义一个浮点类型的变量，赋值为怪物对象的减速持续时间减去移动的时间间隔，表示剩余的减速时间
		float StateTime = _pMonster->getFSlowDuration() - t;
		// 如果剩余的减速时间小于0，就将其设置为0
		if (StateTime < 0) StateTime = 0;
		// 将怪物对象的减速持续时间设置为剩余的减速时间
		_pMonster->setFSlowDuration(StateTime);
		// 创建一个精灵对象，用来显示减速的动画效果
		Sprite* pTemp = Sprite::create();
		// 设置精灵对象的位置，根据怪物对象的大小和位置进行偏移
		pTemp->setPosition(_pMonster->getContentSize().width / 2, 40);
		// 将精灵对象添加为怪物对象的精灵的子节点
		_pMonster->getSprite()->addChild(pTemp);
		// 调用成员函数，根据怪物对象的子弹状态类型和移动的时间间隔，创建一个动画对象，赋值给一个自动类型的变量
		Animation* pAnimation = AnimationMaker(_pMonster->getIBulletStateType(), t);
		// 创建一个回调函数对象，用来在动画播放完成后执行一些操作
		auto pCallFunc = CallFunc::create([=]() {
			// 将精灵对象从父节点中移除并清理
			pTemp->removeFromParentAndCleanup(true);
		// 如果怪物对象的减速持续时间小于等于0，表示减速效果结束
		if (_pMonster->getFSlowDuration() <= 0)
		{
			// 将怪物对象的速度恢复为成员变量的速度
			_pMonster->setISpeed(_iMonsterSpeed);
			// 将怪物对象的状态用位运算符和相应的掩码进行修改，表示取消减速状态
			_pMonster->setIState(_pMonster->getIState() & 13);
		}
			});
		// 创建一个序列动作对象，包括动画和回调函数
		Sequence* pSequence = Sequence::create(Animate::create(pAnimation), pCallFunc, NULL);
		// 让精灵对象执行序列动作
		pTemp->runAction(pSequence);
	}
	// 如果怪物对象处于中毒状态，并且中毒持续时间大于0
	if (State_Poison && _pMonster->getfPoisonDuration() > 0)
	{
		// 定义一个浮点类型的变量，赋值为怪物对象的中毒持续时间减去移动的时间间隔，表示剩余的中毒时间
		float StateTime = _pMonster->getfPoisonDuration() - t;
		// 如果剩余的中毒时间小于0，就将其设置为0
		if (StateTime < 0) StateTime = 0;
		// 将怪物对象的中毒持续时间设置为剩余的中毒时间
		_pMonster->setfPoisonDuration(StateTime);
		// 定义一个攻击属性的变量，赋值为一个结构体，表示中毒的伤害效果
		AtkProperty atk;
		// 设置攻击属性的状态为1，表示普通攻击
		atk._enAtkState = 1;
		// 设置攻击属性的攻击力为2，表示每次中毒造成的伤害
		atk._iAtk = 2;
		// 设置攻击属性的持续时间为0，表示无持续效果
		atk._iDuration = 0;

		// 创建一个精灵对象，用来显示中毒的动画效果
		Sprite* pTemp = Sprite::create();
		// 设置精灵对象的位置，根据怪物对象的大小和位置进行偏移
		pTemp->setPosition(_pMonster->getContentSize().width / 2, 40);
		// 将精灵对象添加为怪物对象的精灵的子节点
		_pMonster->getSprite()->addChild(pTemp);
		// 调用成员函数，根据怪物对象的子弹状态类型和移动的时间间隔，创建一个动画对象，赋值给一个自动类型的变量
		Animation* pAnimation = AnimationMaker(6, t);
		// 创建一个回调函数对象，用来在动画播放完成后执行一些操作
		auto pCallFunc = CallFunc::create([=]() {
			// 如果怪物对象没有死亡，就调用怪物对象的受伤函数，传递攻击属性的变量，表示造成中毒伤害
			if (!_pMonster->getIsDead()) _pMonster->beHurt(atk);
		// 如果怪物对象的中毒持续时间小于等于0，表示中毒效果结束
		if (_pMonster->getfPoisonDuration() <= 0)
		{
			// 将怪物对象的状态用位运算符和相应的掩码进行修改，表示取消中毒状态
			_pMonster->setIState(_pMonster->getIState() & 7);
		}
		// 将精灵对象从父节点中移除并清理
		pTemp->removeFromParentAndCleanup(true);
			});
		// 让精灵对象执行一个序列动作，包括动画和回调函数
		pTemp->runAction(Sequence::create(Animate::create(pAnimation), pCallFunc, NULL));
	}
	// 如果怪物对象处于停止状态，并且停止持续时间大于0
	if (State_Stop && _pMonster->getfStopDuration() > 0)
	{
		// 定义一个浮点类型的变量，赋值为怪物对象的停止持续时间减去移动的时间间隔，表示剩余的停止时间
		float StateTime = _pMonster->getfStopDuration() - t;
		// 如果剩余的停止时间小于0，就将其设置为0
		if (StateTime < 0) StateTime = 0;
		// 将怪物对象的停止持续时间设置为剩余的停止时间
		_pMonster->setfStopDuration(StateTime);
		// 创建一个精灵对象，用来显示停止的动画效果
		Sprite* pTemp = Sprite::create();
		// 设置精灵对象的位置，根据怪物对象的大小和位置进行偏移
		pTemp->setPosition(_pMonster->getContentSize().width / 2, 40);
		// 将精灵对象添加为怪物对象的精灵的子节点
		_pMonster->getSprite()->addChild(pTemp);
		// 调用成员函数，根据怪物对象的子弹状态类型和移动的时间间隔，创建一个动画对象，赋值给一个自动类型的变量
		Animation* pAnimation = AnimationMaker(_pMonster->getIBulletStateType(), t);
		// 创建一个回调函数对象，用来在动画播放完成后执行一些操作
		auto pCallFunc = CallFunc::create([=]() {
			// 如果怪物对象的停止持续时间小于等于0，表示停止效果结束
			if (_pMonster->getfStopDuration() <= 0)
			{
				// 将怪物对象的状态用位运算符和相应的掩码进行修改，表示取消停止状态
				_pMonster->setIState(_pMonster->getIState() & 11);
			}
		// 再次调用监听怪物对象的函数，传递相同的时间间隔参数，表示恢复移动
		this->listenerMonster(STEP / _pMonster->getISpeed());
		// 将精灵对象从父节点中移除并清理
		pTemp->removeFromParentAndCleanup(true);
			});
		// 让精灵对象执行一个序列动作，包括动画和回调函数
		pTemp->runAction(Sequence::create(Animate::create(pAnimation), pCallFunc, NULL));
		// 直接返回，不执行后面的移动动作
		return;
	}
	// 让怪物对象执行移动的序列动作
	_pMonster->runAction(seq);
}

// 定义移动控制器基类的删除点的函数，无参数，无返回值
void MoveControllerBase::erasePoint() {
	// 如果成员变量的向量的大小等于1，表示只剩下一个点，就直接返回
	if (_pMapPonits->size() == 1) {
		return;
	}
	// 如果怪物对象的位置等于成员变量的向量的第一个元素，表示到达了一个点
	if (_pMonster->getPosition() == *_pMapPonits->begin()) {
		// 就从成员变量的向量中删除第一个元素
		_pMapPonits->erase(_pMapPonits->begin());
		// 如果成员变量的向量的大小等于1，表示到达了最后一个点
		if (_pMapPonits->size() == 1)
		{
			// 就发送一个通知，表示胡萝卜受到伤害，参数是怪物对象的指针
			NOTIFY->postNotification("CarrotHurt", _pMonster);
			// 就发送一个通知，表示怪物对象死亡，参数是怪物对象的指针
			NOTIFY->postNotification("MonsterDead", _pMonster);
			// 将怪物对象的死亡状态设置为真
			_pMonster->setIsDead(true);
			// 将怪物对象从父节点中移除并清理
			_pMonster->removeFromParentAndCleanup(true);
		}
	}
}

// 定义移动控制器基类的析构函数，释放内存
MoveControllerBase::~MoveControllerBase()
{
	// 删除成员变量的向量，释放内存
	delete(_pMapPonits);
}

// 定义移动控制器基类的动画制作函数，参数是一个整数类型的变量，表示子弹的类型，和一个浮点类型的变量，表示动画的时间间隔，返回一个指向动画对象的指针
Animation* MoveControllerBase::AnimationMaker(int iBulletType, float t)
{
	// 创建一个新的动画对象，赋值给一个自动类型的变量
	Animation* pAnimation = Animation::create();
	// 如果子弹的类型等于1，表示是屎
	if (iBulletType == 1)
	{
		// 就从精灵帧缓存中获取两个屎的精灵帧，添加到动画对象中
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PShit-11.png"));
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PShit-12.png"));
		// 设置动画对象的每帧延时为时间间隔除以2
		pAnimation->setDelayPerUnit(t / 2);
	}
	// 如果子弹的类型等于5，表示是星星
	else if (iBulletType == 5)
	{
		// 就从精灵帧缓存中获取一个星星的精灵帧，添加到动画对象中
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PBStar-21.png"));
		// 设置动画对象的每帧延时为时间间隔
		pAnimation->setDelayPerUnit(t);
	}
	// 如果子弹的类型等于15或30或45，表示是雪花
	else if (iBulletType == 15 || iBulletType == 30 || iBulletType == 45)
	{
		// 就从精灵帧缓存中获取两个雪花的精灵帧，添加到动画对象中
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PSnow01.png"));
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PSnow02.png"));
		// 设置动画对象的每帧延时为时间间隔除以2
		pAnimation->setDelayPerUnit(t / 2);
	}
	// 如果子弹的类型等于6，表示是针
	else if (iBulletType == 6)
	{
		// 就从精灵帧缓存中获取四个针的精灵帧，添加到动画对象中
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PPin01.png"));
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PPin02.png"));
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PPin03.png"));
		pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PPin04.png"));
		// 设置动画对象的每帧延时为时间间隔除以4
		pAnimation->setDelayPerUnit(t / 4);
	}
	// 设置动画对象的循环次数为1，表示只播放一次
	pAnimation->setLoops(1);
	// 返回动画对象的指针
	return pAnimation;
}
