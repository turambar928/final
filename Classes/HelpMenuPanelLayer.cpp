
#include "HelpMenuPanelLayer.h"
#include "HelpLayer.h"
#include "MonsterHelpLayer.h"
#include "TowerHelpLayer.h"
#include "SceneManager.h"

bool HelpMenuPanelLayer::init()
{
	bool bRet = false;  // 布尔变量，用于判断初始化是否成功

	do
	{
		CC_BREAK_IF(!Layer::init());  // 如果Layer初始化失败，跳出循环

		// 创建一个LayerMultiplex对象，用于切换不同的帮助图层
		_pLayers = LayerMultiplex::create(HelpLayer::create(), MonsterHelpLayer::create(), TowerHelpLayer::create(), nullptr);
		addChild(_pLayers);  // 将LayerMultiplex添加到当前Layer中

		// 创建并添加帮助背景精灵
		auto pBg = Sprite::createWithSpriteFrameName("help_bg.png");
		pBg->setPosition(VisibleRect::center());
		addChild(pBg);

		// 创建菜单面板
		createMenuPanel();

		bRet = true;  // 初始化成功

	} while (0);

	return bRet;  // 返回初始化结果
}

void HelpMenuPanelLayer::createMenuPanel()
{
	// 创建返回主页按钮
	auto pHomeBtn = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("help_home_normal.png"),
		Sprite::createWithSpriteFrameName("help_home_pressed.png"),
		[](Ref* pSender)
		{
			// 切换到欢迎场景
			auto enWelcomeScene = std::make_tuple(en_WelcomeScene, 0);
			NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enWelcomeScene));
		});
	pHomeBtn->setPosition(pHomeBtn->getContentSize().width / 2, 640 - pHomeBtn->getContentSize().height / 2 + 5);

	// 创建普通菜单项（未按下状态），用于展示帮助信息
	auto pNormalItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("tips_normal_CN.png"), nullptr);

	// 创建帮助层，并设置名称为"helpLayer"
	auto helpLayer = HelpLayer::create();
	helpLayer->setName("helpLayer");

	// 将帮助层添加到当前场景中
	addChild(helpLayer);
	// 创建帮助按钮的选中状态菜单项
	auto pSelectedItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("tips_selected_CN.png"), nullptr);

	// 创建帮助按钮，使用 MenuItemToggle 以处理切换状态
	pHelpBtn = MenuItemToggle::createWithCallback([=](Ref* pSender) {
		// 重置其他按钮的选中状态
		pMonsterHelpBtn->setSelectedIndex(0);
		pTowerHelpBtn->setSelectedIndex(0);

		// 移除可能存在的其他帮助层
		this->removeChildByName("helpLayer");
		this->removeChildByName("monsterHelpLayer");
		this->removeChildByName("towerHelpLayer");

		// 如果帮助按钮当前被选中，则创建并添加帮助层
		if (pHelpBtn->getSelectedIndex() == 1)
		{
			auto helpLayer = HelpLayer::create();
			helpLayer->setName("helpLayer");
			addChild(helpLayer);
		}

		}, pNormalItem, pSelectedItem, NULL);

	// 设置帮助按钮初始状态为选中
	pHelpBtn->setSelectedIndex(1);

	// 创建怪物按钮的正常状态菜单项
	pNormalItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("monster_normal_CN.png"), nullptr);

	// 创建怪物按钮的选中状态菜单项
	pSelectedItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("monster_selected_CN.png"), nullptr);

	// 创建怪物按钮，使用 MenuItemToggle 处理切换状态
	pMonsterHelpBtn = MenuItemToggle::createWithCallback([=](Ref* pSender) {
		// 重置其他按钮的选中状态
		pHelpBtn->setSelectedIndex(0);
		pTowerHelpBtn->setSelectedIndex(0);

		// 移除可能存在的其他帮助层
		this->removeChildByName("helpLayer");
		this->removeChildByName("monsterHelpLayer");
		this->removeChildByName("towerHelpLayer");

		// 如果怪物按钮当前被选中，则创建并添加怪物帮助层
		if (pMonsterHelpBtn->getSelectedIndex() == 1)
		{
			auto monsterHelpLayer = MonsterHelpLayer::create();
			monsterHelpLayer->setName("monsterHelpLayer");
			addChild(monsterHelpLayer);
		}

		}, pNormalItem, pSelectedItem, NULL);

	// 创建防御塔按钮的正常状态菜单项
	pNormalItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("tower_normal_CN.png"), nullptr);

	// 创建防御塔按钮的选中状态菜单项
	pSelectedItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("tower_selected_CN.png"), nullptr);

	// 创建防御塔按钮，使用 MenuItemToggle 处理切换状态
	pTowerHelpBtn = MenuItemToggle::createWithCallback([=](Ref* pSender) {
		// 重置其他按钮的选中状态
		pHelpBtn->setSelectedIndex(0);
		pMonsterHelpBtn->setSelectedIndex(0);

		// 移除可能存在的其他帮助层
		this->removeChildByName("helpLayer");
		this->removeChildByName("monsterHelpLayer");
		this->removeChildByName("towerHelpLayer");

		// 如果防御塔按钮当前被选中，则创建并添加防御塔帮助层
		if (pTowerHelpBtn->getSelectedIndex() == 1)
		{
			auto towerHelpLayer = TowerHelpLayer::create();
			towerHelpLayer->setName("towerHelpLayer");
			addChild(towerHelpLayer);
		}
		}, pNormalItem, pSelectedItem, nullptr);

	// 创建菜单面板，包括主页按钮、帮助按钮、怪物帮助按钮和防御塔帮助按钮
	auto pMenuPanel = Menu::create(pHomeBtn, pHelpBtn, pMonsterHelpBtn, pTowerHelpBtn, NULL);

	// 设置按钮在屏幕上的位置
	pHelpBtn->setPosition(320, 590);
	pMonsterHelpBtn->setPosition(480, 590);
	pTowerHelpBtn->setPosition(640, 590);

	// 将菜单面板添加到当前场景中
	addChild(pMenuPanel, 2);

}


