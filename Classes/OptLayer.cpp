

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
// 初始化函数，返回一个布尔值表示是否成功初始化
bool OptLayer::init()
{
	bool bRet = false; // 定义一个返回值变量，初始为false
	do
	{
		CC_BREAK_IF(!Layer::init()); // 如果父类Layer的初始化失败，就跳出循环
		towerOptBtn = TowerOptBtn::create(); // 创建一个TowerOptBtn对象，用于显示塔的选项菜单
		towerOptBtn->setName("towerOptBtn"); // 设置对象的名字
		towerOptBtn->setTag(0); // 设置对象的标签，用于判断是否显示菜单
		_pforbiddenSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("forbidden.png")); // 创建一个精灵对象，用于显示禁止图标
		_pforbiddenSp->setVisible(false); // 设置精灵对象为不可见
		addChild(_pforbiddenSp); // 将精灵对象添加为子节点
		addChild(towerOptBtn); // 将TowerOptBtn对象添加为子节点
		listener(); // 调用listener函数，添加触摸事件监听
		bRet = true; // 设置返回值为true
	} while (0); // 循环条件为0，只执行一次
	return bRet; // 返回bRet
}
// 添加触摸事件监听函数，无返回值
void OptLayer::listener()
{
	auto listen = EventListenerTouchOneByOne::create();// 创建一个单点触摸事件监听对象
	listen->onTouchBegan = [=](Touch* t, Event* e){// 定义触摸开始时的回调函数
        auto tPos = t->getLocation();// 获取触摸的位置
        
        if(tPos.y > 590) return true;// 如果触摸的位置在屏幕上方，就返回true，不做任何处理
		if (towerOptBtn->getTag()){// 如果TowerOptBtn对象的标签为非0，表示当前显示了菜单
			towerOptBtn->setTag(0);// 设置TowerOptBtn对象的标签为0
			towerOptBtn->hideTowerOpt();// 调用TowerOptBtn对象的方法，隐藏菜单
		}else{// 如果TowerOptBtn对象的标签为0，表示当前没有显示菜单
			Carrot* carrot = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene())->getCarrot();// 获取当前场景中的Carrot对象，用于表示玩家的生命值
			if (carrot->getBoundingBox().containsPoint(t->getLocation())){// 如果触摸的位置在Carrot对象的包围盒内
				return true;
			}
			for (auto & toweritem : TowerManager::getInstance()->getTowerVec()){// 遍历TowerManager对象管理的塔的向量
				if (toweritem->getBoundingBox().containsPoint(t->getLocation())){// 如果触摸的位置在某个塔的包围盒内
					towerOptBtn->setTag(1);// 设置TowerOptBtn对象的标签为1
					towerOptBtn->setPosition(toweritem->getPosition()); // 设置TowerOptBtn对象的位置为塔的位置
					towerOptBtn->showTowerOpt();// 调用TowerOptBtn对象的方法，显示菜单
					towerOptBtn->gradeTowerMenu(toweritem);// 调用TowerOptBtn对象的方法，根据塔的类型和等级显示升级或出售的选项
					return true;
				}
			}
			for (auto & blankitem : MapUtil::getInstance()->getEffectTowerPoses()){// 遍历MapUtil对象管理的可放置塔的位置的向量
				if (blankitem.containsPoint(t->getLocation())){// 如果触摸的位置在某个位置的矩形内
					towerOptBtn->setTag(1);// 设置TowerOptBtn对象的标签为1
					towerOptBtn->setPosition(blankitem.origin + blankitem.size/2);// 设置TowerOptBtn对象的位置为矩形的中心点
					towerOptBtn->showTowerOpt();// 调用TowerOptBtn对象的方法，显示菜单
					towerOptBtn->showCreateMenu();// 调用TowerOptBtn对象的方法，显示创建塔的选项
                    return true;
				}
                
			}
			auto tMonsterVec = MonsterManager::getInstance()->getMonsterVec();// 获取MonsterManager对象管理的怪物的向量
			for (auto & monsterIter : tMonsterVec)// 遍历怪物的向量
			{
				if (monsterIter->getBoundingBox().containsPoint(t->getLocation()))// 如果触摸的位置在某个怪物的包围盒内
				{
					auto tMonsterLockFlag = monsterIter->getAtkTarget();// 获取怪物的攻击目标的标志，表示是否被塔锁定
					BarrierManager::getInstance()->clearBeAtkLockState();// 调用BarrierManager对象的方法，清除所有障碍物的攻击目标的标志
					MonsterManager::getInstance()->clearBeAtkLockState();// 调用MonsterManager对象的方法，清除所有怪物的攻击目标的标志
					monsterIter->setAtkTarget(!tMonsterLockFlag);// 设置怪物的攻击目标的标志为相反值，表示切换锁定状态
					return true;
				}
			}
			auto tBarrierVec = BarrierManager::getInstance()->getBarrierVec(); // 获取BarrierManager对象管理的障碍物的向量
			for (auto & barrierItem : tBarrierVec)// 遍历障碍物的向量
			{
				if (barrierItem->getBoundingBox().containsPoint(t->getLocation()))// 如果触摸的位置在某个障碍物的包围盒内
				{
					auto tBarrierLockFlag = barrierItem->getAtkTarget();// 获取障碍物的攻击目标的标志，表示是否被塔锁定
					MonsterManager::getInstance()->clearBeAtkLockState();// 调用MonsterManager对象的方法，清除所有怪物的攻击目标的标志
					BarrierManager::getInstance()->clearBeAtkLockState();// 调用BarrierManager对象的方法，清除所有障碍物的攻击目标的标志
					barrierItem->setAtkTarget(!tBarrierLockFlag);// 设置障碍物的攻击目标的标志为相反值，表示切换锁定状态
					return true;
				}
			}
            SoundUtil::getInstance()->playEffect(SELECTFAULT);// 调用SoundUtil对象的方法，播放选择失败的音效
			_pforbiddenSp->setVisible(true);// 设置禁止精灵为可见
			_pforbiddenSp->runAction(Sequence::create(FadeIn::create(0.1), FadeOut::create(1), NULL));// 让禁止精灵执行一个渐入渐出的动作
			_pforbiddenSp->setPosition(t->getLocation());// 设置禁止精灵的位置为触摸的位置
		}
		
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, this);// 将触摸事件监听对象添加到事件分发器中，设置为场景优先级
}
