#include "MonsterBuilder.h"
#include "MapUtil.h"
#include "MonsterFactory.h"
// �������ｨ���ߵ�ͷ�ļ�
#include "MonsterBuilder.h"
// ������ͼ���ߵ�ͷ�ļ�
#include "MapUtil.h"
// �������﹤����ͷ�ļ�
#include "MonsterFactory.h"
// ���������������ͷ�ļ�
#include "MonsterManager.h"
// �����ؿ����ù��ߵ�ͷ�ļ�
#include "LevelConfigUtil.h"
// ������������ͷ�ļ�
#include "MonsterBase.h"
// ������Ϸ��������ͷ�ļ�
#include "GameManager.h"
// �����������ߵ�ͷ�ļ�
#include "SoundUtil.h"

// ��ʼ�����ｨ���߶���ĺ���
bool MonsterBuilder::init()
{
	// ����һ������ֵ����ʼΪfalse
	bool bRet = false;
	do
	{
		// ����ڵ�ĳ�ʼ��ʧ�ܣ�������ѭ��
		CC_BREAK_IF(!Node::init());
		// ����ÿ���δ����Ĺ�������Ϊ10
		_iBuildNumber = 10;
		// ���ô���������ӳ�ʱ��Ϊ����
		_fDelayTime = _iConstDelayTime;
		// ���õ�ǰ���εĹ������Ϊ0
		_MonsterCount = 0;
		// �����ܹ������Ĺ������Ϊ0
		_MonsterBuilderNumber = 0;
		// �����ӳٱ�־Ϊtrue
		_bDelay = true;
		// ����ÿ���εĹ�����Ϊ0
		_iNumber = 0;
		// ���õ�ǰ������Ϊ0
		_iBatch = 0;
		// ������Ϸ�������ĺ��������ù��������Ϊ0
		GameManager::getInstance()->setIMonsterBatch(0);

		// ����һ����������������ʾ���������Ч��
		_createMonsterAnimation = Animation::create();
		// �򶯻����������������֡���Ӿ���֡�����л�ȡ
		_createMonsterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mcm01.png"));
		_createMonsterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mcm02.png"));
		// ���ö��������ÿ֡�ӳ�ʱ��Ϊ0.15��
		_createMonsterAnimation->setDelayPerUnit(0.15);
		// ���ö��������ѭ������Ϊ1
		_createMonsterAnimation->setLoops(1);
		// ��������������ü�����һ����ֹ���Զ��ͷ�
		_createMonsterAnimation->retain();

		// ���ùؿ����ù��ߵĺ�������ȡ��ǰ�ؿ��Ĺ�����������
		_iReadFileMonsterCount = LevelConfigUtil::getInstance()->getCurLevelMonsterBatchCount();

		// ���ù��ｨ���߶����λ�ã����ݵ�ͼ���ߵĺ�����ȡ�ƶ�·���ĵ�һ���㣬����һЩƫ��
		this->setPosition(MapUtil::getInstance()->getMovePoses().at(0) + Vec2(40, -15));

		// ���÷���ֵΪtrue����ʾ��ʼ���ɹ�
		bRet = true;
		// ���ѭ������Ϊ0���ͽ���ѭ��
	} while (0);
	// ���س�ʼ�����
	return bRet;
}

// �����ｨ���߶�����볡��ʱ�ĺ���
void MonsterBuilder::onEnter()
{
	// ���ýڵ�Ľ��볡������
	Node::onEnter();
	// ����һ����ʱ����ÿ��1.5�����һ�δ�������ĸ��º�����������20001�Σ���ʼǰ�ӳ�3��
	schedule(CC_SCHEDULE_SELECTOR(MonsterBuilder::createMonsterUpdate), 1.5, 20001, 3);
}

// ��������ĸ��º�����������ʱ����
void MonsterBuilder::createMonsterUpdate(float t)
{
	// ����ܹ������Ĺ����������ÿ���δ����Ĺ����������Ե�ǰ�ؿ��Ĺ�����������
	if (_MonsterBuilderNumber == 10 * _iReadFileMonsterCount)
	{
		// �����������ߵĺ������������һ���������Ч
		SoundUtil::getInstance()->playEffect(FINALWAVE);
		// ȡ����ʱ����ֹͣ���ô�������ĸ��º���
		this->unschedule(CC_SCHEDULE_SELECTOR(MonsterBuilder::createMonsterUpdate));
		// ����һ��֪ͨ����������������Լ����Ϸ�Ƿ����
		NOTIFY->postNotification("openCheckGameEnd");
	}
	// �������������ӳ�ʱ��С�ڳ������ҹ���������еĹ��������Ĵ�СΪ0����ʾû�й�����
	if (_fDelayTime < _iConstDelayTime && MonsterManager::getInstance()->getMonsterVec().size() == 0)
	{
		// ������������ӳ�ʱ�����ʱ����
		_fDelayTime += t;
	}
	// �������������ӳ�ʱ����ڵ��ڳ�������ʾ���Դ�����һ���εĹ���
	else if (_fDelayTime >= _iConstDelayTime)
	{
		// ���㵱ǰ�����Σ������ܹ������Ĺ����������ÿ���δ����Ĺ����������ټ�һ
		_iBatch = _MonsterBuilderNumber / 10 + 1;
		// ������Ϸ�������ĺ��������ù��������
		GameManager::getInstance()->setIMonsterBatch(_iBatch);
		// ����һ��֪ͨ���������������������η����˱仯�������ǵ�ǰ������
		NOTIFY->postNotification("monsterBatchChange", (Ref*)&_iBatch);
		// ���ù��﹤���������ĺ���������һ���������
		MonsterFactoryController();
		// ����ǰ���εĹ��������һ
		_MonsterCount++;
		// ���ܹ������Ĺ��������һ
		_MonsterBuilderNumber++;
		// �����ǰ���εĹ����������10����ʾ��һ���εĹ��ﴴ�����
		if (_MonsterCount == 10)
		{
			// ������������ӳ�ʱ������Ϊ0
			_fDelayTime = 0;
			// ����ǰ���εĹ����������Ϊ0
			_MonsterCount = 0;
		}
	}
}

// ������﹤���������ĺ������������ݲ�ͬ�����κͱ�Ŵ�����ͬ���͵Ĺ���
void MonsterBuilder::MonsterFactoryController()
{
	// �����������ߵĺ��������Ŵ����������Ч
	SoundUtil::getInstance()->playEffect(BUILDMONSTER);
	// ���ÿ���εĹ����ŵ���10��������Ϊ0
	if (_iNumber == 10)_iNumber = 0;
	// ����ÿ���δ�����½�ع��������������10��ȥ��ǰ���μ�һ�ٳ���2
	int number = 10 - (_iBatch - 1) * 2;
	// ����һ��ָ���������ָ�룬������Ŵ����Ĺ������
	MonsterBase* pMonster;
	// �����ǰ���ε��ڹؿ��Ĺ��������������ҵ�ǰ��ŵ���5����ʾҪ������Boss
	if (_iBatch == _iReadFileMonsterCount && _iNumber == 5)
	{
		// ���ù��﹤���ĺ���������һ����Boss���͵Ĺ�����󣬸�ֵ��ָ��
		pMonster = MonsterFactory::createMonster(en_Boss_Big);
	}
	// ���򣬸��ݵ�ǰ���κͱ�ŵĲ�ͬ��������ͬ���͵Ĺ������
	else
	{
		// �����ǰ���С��½�ع��������
		if (_iNumber < number)
		{
			// ���ù��﹤���ĺ���������һ��½�ع������͵Ĺ���������͸��ݵ�ǰ���εĲ�ͬ���仯����ֵ��ָ��
			pMonster = MonsterFactory::createMonster(MonsterType(1 + int(_iBatch / 5)));
		}
		// ���򣬱�ʾҪ�������й���
		else
		{
			// ���ù��﹤���ĺ���������һ�����й������͵Ĺ���������͸��ݵ�ǰ���εĲ�ͬ���仯����ֵ��ָ��
			pMonster = MonsterFactory::createMonster(MonsterType(4 + int(_iBatch / 5)));
		}
	}
	// ���ù������ĺ��������ù��������ֵ�����ݵ�ǰ���εĲ�ͬ������
	pMonster->setIHp(pMonster->getIHp() + (_iBatch - 1) / 5 * pMonster->getIHp());
	// ���ù������ĺ��������ù��������ٶȣ����ݵ�ǰ���εĲ�ͬ������
	pMonster->setMaxSpeed(pMonster->getISpeed() + int(_iBatch / 5) * 10);
	// ��ȡ�������ľ����������ִ�д�������Ķ�������Ķ���
	pMonster->getSprite()->runAction(Animate::create(_createMonsterAnimation));
	// ����ǰ��ż�һ��׼��������һ���������
	_iNumber++;
}

// ��ȡ��ǰ���εĺ��������ص�ǰ���ε�ֵ
int MonsterBuilder::getBatch()
{
	return _iBatch;
}

// ���ｨ���߶������������
MonsterBuilder::~MonsterBuilder()
{
	// ʹ��CC_SAFE_RELEASE_NULL�갲ȫ���ͷŴ�������Ķ������󣬼������ü���
	CC_SAFE_RELEASE_NULL(_createMonsterAnimation);
}
