

#include "OptLayer.h"
#include "MapUtil.h"
#include "TowerManager.h"
#include "TowerBase.h"
#include "BarrierBase.h"
#include "BarrierManager.h"
#include "TowerOptBtn.h"
#include "TowerBase.h"
#include "MonsterManager.h"
#include "MonsterBase.h"
#include "SoundUtil.h"
#include "Carrot.h"
#include "GameScene.h"
// ��ʼ������������һ������ֵ��ʾ�Ƿ�ɹ���ʼ��
bool OptLayer::init()
{
	bool bRet = false; // ����һ������ֵ��������ʼΪfalse
	do
	{
		CC_BREAK_IF(!Layer::init()); // �������Layer�ĳ�ʼ��ʧ�ܣ�������ѭ��
		towerOptBtn = TowerOptBtn::create(); // ����һ��TowerOptBtn����������ʾ����ѡ��˵�
		towerOptBtn->setName("towerOptBtn"); // ���ö��������
		towerOptBtn->setTag(0); // ���ö���ı�ǩ�������ж��Ƿ���ʾ�˵�
		_pforbiddenSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("forbidden.png")); // ����һ���������������ʾ��ֹͼ��
		_pforbiddenSp->setVisible(false); // ���þ������Ϊ���ɼ�
		addChild(_pforbiddenSp); // ������������Ϊ�ӽڵ�
		addChild(towerOptBtn); // ��TowerOptBtn�������Ϊ�ӽڵ�
		listener(); // ����listener��������Ӵ����¼�����
		bRet = true; // ���÷���ֵΪtrue
	} while (0); // ѭ������Ϊ0��ִֻ��һ��
	return bRet; // ����bRet
}
// ��Ӵ����¼������������޷���ֵ
void OptLayer::listener()
{
	auto listen = EventListenerTouchOneByOne::create();// ����һ�����㴥���¼���������
	listen->onTouchBegan = [=](Touch* t, Event* e){// ���崥����ʼʱ�Ļص�����
        auto tPos = t->getLocation();// ��ȡ������λ��
        
        if(tPos.y > 590) return true;// ���������λ������Ļ�Ϸ����ͷ���true�������κδ���
		if (towerOptBtn->getTag()){// ���TowerOptBtn����ı�ǩΪ��0����ʾ��ǰ��ʾ�˲˵�
			towerOptBtn->setTag(0);// ����TowerOptBtn����ı�ǩΪ0
			towerOptBtn->hideTowerOpt();// ����TowerOptBtn����ķ��������ز˵�
		}else{// ���TowerOptBtn����ı�ǩΪ0����ʾ��ǰû����ʾ�˵�
			Carrot* carrot = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene())->getCarrot();// ��ȡ��ǰ�����е�Carrot�������ڱ�ʾ��ҵ�����ֵ
			if (carrot->getBoundingBox().containsPoint(t->getLocation())){// ���������λ����Carrot����İ�Χ����
				return true;
			}
			for (auto & toweritem : TowerManager::getInstance()->getTowerVec()){// ����TowerManager����������������
				if (toweritem->getBoundingBox().containsPoint(t->getLocation())){// ���������λ����ĳ�����İ�Χ����
					towerOptBtn->setTag(1);// ����TowerOptBtn����ı�ǩΪ1
					towerOptBtn->setPosition(toweritem->getPosition()); // ����TowerOptBtn�����λ��Ϊ����λ��
					towerOptBtn->showTowerOpt();// ����TowerOptBtn����ķ�������ʾ�˵�
					towerOptBtn->gradeTowerMenu(toweritem);// ����TowerOptBtn����ķ����������������ͺ͵ȼ���ʾ��������۵�ѡ��
					return true;
				}
			}
			for (auto & blankitem : MapUtil::getInstance()->getEffectTowerPoses()){// ����MapUtil�������Ŀɷ�������λ�õ�����
				if (blankitem.containsPoint(t->getLocation())){// ���������λ����ĳ��λ�õľ�����
					towerOptBtn->setTag(1);// ����TowerOptBtn����ı�ǩΪ1
					towerOptBtn->setPosition(blankitem.origin + blankitem.size/2);// ����TowerOptBtn�����λ��Ϊ���ε����ĵ�
					towerOptBtn->showTowerOpt();// ����TowerOptBtn����ķ�������ʾ�˵�
					towerOptBtn->showCreateMenu();// ����TowerOptBtn����ķ�������ʾ��������ѡ��
                    return true;
				}
                
			}
			auto tMonsterVec = MonsterManager::getInstance()->getMonsterVec();// ��ȡMonsterManager�������Ĺ��������
			for (auto & monsterIter : tMonsterVec)// �������������
			{
				if (monsterIter->getBoundingBox().containsPoint(t->getLocation()))// ���������λ����ĳ������İ�Χ����
				{
					auto tMonsterLockFlag = monsterIter->getAtkTarget();// ��ȡ����Ĺ���Ŀ��ı�־����ʾ�Ƿ�������
					BarrierManager::getInstance()->clearBeAtkLockState();// ����BarrierManager����ķ�������������ϰ���Ĺ���Ŀ��ı�־
					MonsterManager::getInstance()->clearBeAtkLockState();// ����MonsterManager����ķ�����������й���Ĺ���Ŀ��ı�־
					monsterIter->setAtkTarget(!tMonsterLockFlag);// ���ù���Ĺ���Ŀ��ı�־Ϊ�෴ֵ����ʾ�л�����״̬
					return true;
				}
			}
			auto tBarrierVec = BarrierManager::getInstance()->getBarrierVec(); // ��ȡBarrierManager���������ϰ��������
			for (auto & barrierItem : tBarrierVec)// �����ϰ��������
			{
				if (barrierItem->getBoundingBox().containsPoint(t->getLocation()))// ���������λ����ĳ���ϰ���İ�Χ����
				{
					auto tBarrierLockFlag = barrierItem->getAtkTarget();// ��ȡ�ϰ���Ĺ���Ŀ��ı�־����ʾ�Ƿ�������
					MonsterManager::getInstance()->clearBeAtkLockState();// ����MonsterManager����ķ�����������й���Ĺ���Ŀ��ı�־
					BarrierManager::getInstance()->clearBeAtkLockState();// ����BarrierManager����ķ�������������ϰ���Ĺ���Ŀ��ı�־
					barrierItem->setAtkTarget(!tBarrierLockFlag);// �����ϰ���Ĺ���Ŀ��ı�־Ϊ�෴ֵ����ʾ�л�����״̬
					return true;
				}
			}
            SoundUtil::getInstance()->playEffect(SELECTFAULT);// ����SoundUtil����ķ���������ѡ��ʧ�ܵ���Ч
			_pforbiddenSp->setVisible(true);// ���ý�ֹ����Ϊ�ɼ�
			_pforbiddenSp->runAction(Sequence::create(FadeIn::create(0.1), FadeOut::create(1), NULL));// �ý�ֹ����ִ��һ�����뽥���Ķ���
			_pforbiddenSp->setPosition(t->getLocation());// ���ý�ֹ�����λ��Ϊ������λ��
		}
		
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, this);// �������¼�����������ӵ��¼��ַ����У�����Ϊ�������ȼ�
}
