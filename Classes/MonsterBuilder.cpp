#include "MonsterBuilder.h"
#include "MapUtil.h"
#include "MonsterFactory.h"
// 包含怪物建造者的头文件
#include "MonsterBuilder.h"
// 包含地图工具的头文件
#include "MapUtil.h"
// 包含怪物工厂的头文件
#include "MonsterFactory.h"
// 包含怪物管理器的头文件
#include "MonsterManager.h"
// 包含关卡配置工具的头文件
#include "LevelConfigUtil.h"
// 包含怪物基类的头文件
#include "MonsterBase.h"
// 包含游戏管理器的头文件
#include "GameManager.h"
// 包含声音工具的头文件
#include "SoundUtil.h"

// 初始化怪物建造者对象的函数
bool MonsterBuilder::init()
{
	// 定义一个返回值，初始为false
	bool bRet = false;
	do
	{
		// 如果节点的初始化失败，就跳出循环
		CC_BREAK_IF(!Node::init());
		// 设置每批次创建的怪物数量为10
		_iBuildNumber = 10;
		// 设置创建怪物的延迟时间为常量
		_fDelayTime = _iConstDelayTime;
		// 设置当前批次的怪物计数为0
		_MonsterCount = 0;
		// 设置总共创建的怪物计数为0
		_MonsterBuilderNumber = 0;
		// 设置延迟标志为true
		_bDelay = true;
		// 设置每批次的怪物编号为0
		_iNumber = 0;
		// 设置当前的批次为0
		_iBatch = 0;
		// 调用游戏管理器的函数，设置怪物的批次为0
		GameManager::getInstance()->setIMonsterBatch(0);

		// 创建一个动画对象，用来显示创建怪物的效果
		_createMonsterAnimation = Animation::create();
		// 向动画对象添加两个精灵帧，从精灵帧缓存中获取
		_createMonsterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mcm01.png"));
		_createMonsterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mcm02.png"));
		// 设置动画对象的每帧延迟时间为0.15秒
		_createMonsterAnimation->setDelayPerUnit(0.15);
		// 设置动画对象的循环次数为1
		_createMonsterAnimation->setLoops(1);
		// 将动画对象的引用计数加一，防止被自动释放
		_createMonsterAnimation->retain();

		// 调用关卡配置工具的函数，获取当前关卡的怪物批次数量
		_iReadFileMonsterCount = LevelConfigUtil::getInstance()->getCurLevelMonsterBatchCount();

		// 设置怪物建造者对象的位置，根据地图工具的函数获取移动路径的第一个点，并做一些偏移
		this->setPosition(MapUtil::getInstance()->getMovePoses().at(0) + Vec2(40, -15));

		// 设置返回值为true，表示初始化成功
		bRet = true;
		// 如果循环条件为0，就结束循环
	} while (0);
	// 返回初始化结果
	return bRet;
}

// 当怪物建造者对象进入场景时的函数
void MonsterBuilder::onEnter()
{
	// 调用节点的进入场景函数
	Node::onEnter();
	// 安排一个定时器，每隔1.5秒调用一次创建怪物的更新函数，最多调用20001次，开始前延迟3秒
	schedule(CC_SCHEDULE_SELECTOR(MonsterBuilder::createMonsterUpdate), 1.5, 20001, 3);
}

// 创建怪物的更新函数，参数是时间间隔
void MonsterBuilder::createMonsterUpdate(float t)
{
	// 如果总共创建的怪物计数等于每批次创建的怪物数量乘以当前关卡的怪物批次数量
	if (_MonsterBuilderNumber == 10 * _iReadFileMonsterCount)
	{
		// 调用声音工具的函数，播放最后一波怪物的音效
		SoundUtil::getInstance()->playEffect(FINALWAVE);
		// 取消定时器，停止调用创建怪物的更新函数
		this->unschedule(CC_SCHEDULE_SELECTOR(MonsterBuilder::createMonsterUpdate));
		// 发送一个通知，告诉其他对象可以检查游戏是否结束
		NOTIFY->postNotification("openCheckGameEnd");
	}
	// 如果创建怪物的延迟时间小于常量，且怪物管理器中的怪物向量的大小为0，表示没有怪物存活
	if (_fDelayTime < _iConstDelayTime && MonsterManager::getInstance()->getMonsterVec().size() == 0)
	{
		// 将创建怪物的延迟时间加上时间间隔
		_fDelayTime += t;
	}
	// 如果创建怪物的延迟时间大于等于常量，表示可以创建下一批次的怪物
	else if (_fDelayTime >= _iConstDelayTime)
	{
		// 计算当前的批次，等于总共创建的怪物计数除以每批次创建的怪物数量，再加一
		_iBatch = _MonsterBuilderNumber / 10 + 1;
		// 调用游戏管理器的函数，设置怪物的批次
		GameManager::getInstance()->setIMonsterBatch(_iBatch);
		// 发送一个通知，告诉其他对象怪物的批次发生了变化，参数是当前的批次
		NOTIFY->postNotification("monsterBatchChange", (Ref*)&_iBatch);
		// 调用怪物工厂控制器的函数，创建一个怪物对象
		MonsterFactoryController();
		// 将当前批次的怪物计数加一
		_MonsterCount++;
		// 将总共创建的怪物计数加一
		_MonsterBuilderNumber++;
		// 如果当前批次的怪物计数等于10，表示这一批次的怪物创建完毕
		if (_MonsterCount == 10)
		{
			// 将创建怪物的延迟时间重置为0
			_fDelayTime = 0;
			// 将当前批次的怪物计数重置为0
			_MonsterCount = 0;
		}
	}
}

// 定义怪物工厂控制器的函数，用来根据不同的批次和编号创建不同类型的怪物
void MonsterBuilder::MonsterFactoryController()
{
	// 调用声音工具的函数，播放创建怪物的音效
	SoundUtil::getInstance()->playEffect(BUILDMONSTER);
	// 如果每批次的怪物编号等于10，就重置为0
	if (_iNumber == 10)_iNumber = 0;
	// 计算每批次创建的陆地怪物的数量，等于10减去当前批次减一再乘以2
	int number = 10 - (_iBatch - 1) * 2;
	// 声明一个指向怪物基类的指针，用来存放创建的怪物对象
	MonsterBase* pMonster;
	// 如果当前批次等于关卡的怪物批次数量，且当前编号等于5，表示要创建大Boss
	if (_iBatch == _iReadFileMonsterCount && _iNumber == 5)
	{
		// 调用怪物工厂的函数，创建一个大Boss类型的怪物对象，赋值给指针
		pMonster = MonsterFactory::createMonster(en_Boss_Big);
	}
	// 否则，根据当前批次和编号的不同，创建不同类型的怪物对象
	else
	{
		// 如果当前编号小于陆地怪物的数量
		if (_iNumber < number)
		{
			// 调用怪物工厂的函数，创建一个陆地怪物类型的怪物对象，类型根据当前批次的不同而变化，赋值给指针
			pMonster = MonsterFactory::createMonster(MonsterType(1 + int(_iBatch / 5)));
		}
		// 否则，表示要创建飞行怪物
		else
		{
			// 调用怪物工厂的函数，创建一个飞行怪物类型的怪物对象，类型根据当前批次的不同而变化，赋值给指针
			pMonster = MonsterFactory::createMonster(MonsterType(4 + int(_iBatch / 5)));
		}
	}
	// 调用怪物对象的函数，设置怪物的生命值，根据当前批次的不同而增加
	pMonster->setIHp(pMonster->getIHp() + (_iBatch - 1) / 5 * pMonster->getIHp());
	// 调用怪物对象的函数，设置怪物的最大速度，根据当前批次的不同而增加
	pMonster->setMaxSpeed(pMonster->getISpeed() + int(_iBatch / 5) * 10);
	// 获取怪物对象的精灵对象，让它执行创建怪物的动画对象的动作
	pMonster->getSprite()->runAction(Animate::create(_createMonsterAnimation));
	// 将当前编号加一，准备创建下一个怪物对象
	_iNumber++;
}

// 获取当前批次的函数，返回当前批次的值
int MonsterBuilder::getBatch()
{
	return _iBatch;
}

// 怪物建造者对象的析构函数
MonsterBuilder::~MonsterBuilder()
{
	// 使用CC_SAFE_RELEASE_NULL宏安全地释放创建怪物的动画对象，减少引用计数
	CC_SAFE_RELEASE_NULL(_createMonsterAnimation);
}
