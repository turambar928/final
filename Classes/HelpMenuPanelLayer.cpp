
#include "HelpMenuPanelLayer.h"
#include "HelpLayer.h"
#include "MonsterHelpLayer.h"
#include "TowerHelpLayer.h"
#include "SceneManager.h"

bool HelpMenuPanelLayer::init()
{
	bool bRet = false;  // ���������������жϳ�ʼ���Ƿ�ɹ�

	do
	{
		CC_BREAK_IF(!Layer::init());  // ���Layer��ʼ��ʧ�ܣ�����ѭ��

		// ����һ��LayerMultiplex���������л���ͬ�İ���ͼ��
		_pLayers = LayerMultiplex::create(HelpLayer::create(), MonsterHelpLayer::create(), TowerHelpLayer::create(), nullptr);
		addChild(_pLayers);  // ��LayerMultiplex��ӵ���ǰLayer��

		// ��������Ӱ�����������
		auto pBg = Sprite::createWithSpriteFrameName("help_bg.png");
		pBg->setPosition(VisibleRect::center());
		addChild(pBg);

		// �����˵����
		createMenuPanel();

		bRet = true;  // ��ʼ���ɹ�

	} while (0);

	return bRet;  // ���س�ʼ�����
}

void HelpMenuPanelLayer::createMenuPanel()
{
	// ����������ҳ��ť
	auto pHomeBtn = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("help_home_normal.png"),
		Sprite::createWithSpriteFrameName("help_home_pressed.png"),
		[](Ref* pSender)
		{
			// �л�����ӭ����
			auto enWelcomeScene = std::make_tuple(en_WelcomeScene, 0);
			NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enWelcomeScene));
		});
	pHomeBtn->setPosition(pHomeBtn->getContentSize().width / 2, 640 - pHomeBtn->getContentSize().height / 2 + 5);

	// ������ͨ�˵��δ����״̬��������չʾ������Ϣ
	auto pNormalItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("tips_normal_CN.png"), nullptr);

	// ���������㣬����������Ϊ"helpLayer"
	auto helpLayer = HelpLayer::create();
	helpLayer->setName("helpLayer");

	// ����������ӵ���ǰ������
	addChild(helpLayer);
	// ����������ť��ѡ��״̬�˵���
	auto pSelectedItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("tips_selected_CN.png"), nullptr);

	// ����������ť��ʹ�� MenuItemToggle �Դ����л�״̬
	pHelpBtn = MenuItemToggle::createWithCallback([=](Ref* pSender) {
		// ����������ť��ѡ��״̬
		pMonsterHelpBtn->setSelectedIndex(0);
		pTowerHelpBtn->setSelectedIndex(0);

		// �Ƴ����ܴ��ڵ�����������
		this->removeChildByName("helpLayer");
		this->removeChildByName("monsterHelpLayer");
		this->removeChildByName("towerHelpLayer");

		// ���������ť��ǰ��ѡ�У��򴴽�����Ӱ�����
		if (pHelpBtn->getSelectedIndex() == 1)
		{
			auto helpLayer = HelpLayer::create();
			helpLayer->setName("helpLayer");
			addChild(helpLayer);
		}

		}, pNormalItem, pSelectedItem, NULL);

	// ���ð�����ť��ʼ״̬Ϊѡ��
	pHelpBtn->setSelectedIndex(1);

	// �������ﰴť������״̬�˵���
	pNormalItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("monster_normal_CN.png"), nullptr);

	// �������ﰴť��ѡ��״̬�˵���
	pSelectedItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("monster_selected_CN.png"), nullptr);

	// �������ﰴť��ʹ�� MenuItemToggle �����л�״̬
	pMonsterHelpBtn = MenuItemToggle::createWithCallback([=](Ref* pSender) {
		// ����������ť��ѡ��״̬
		pHelpBtn->setSelectedIndex(0);
		pTowerHelpBtn->setSelectedIndex(0);

		// �Ƴ����ܴ��ڵ�����������
		this->removeChildByName("helpLayer");
		this->removeChildByName("monsterHelpLayer");
		this->removeChildByName("towerHelpLayer");

		// ������ﰴť��ǰ��ѡ�У��򴴽�����ӹ��������
		if (pMonsterHelpBtn->getSelectedIndex() == 1)
		{
			auto monsterHelpLayer = MonsterHelpLayer::create();
			monsterHelpLayer->setName("monsterHelpLayer");
			addChild(monsterHelpLayer);
		}

		}, pNormalItem, pSelectedItem, NULL);

	// ������������ť������״̬�˵���
	pNormalItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("tower_normal_CN.png"), nullptr);

	// ������������ť��ѡ��״̬�˵���
	pSelectedItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("tower_selected_CN.png"), nullptr);

	// ������������ť��ʹ�� MenuItemToggle �����л�״̬
	pTowerHelpBtn = MenuItemToggle::createWithCallback([=](Ref* pSender) {
		// ����������ť��ѡ��״̬
		pHelpBtn->setSelectedIndex(0);
		pMonsterHelpBtn->setSelectedIndex(0);

		// �Ƴ����ܴ��ڵ�����������
		this->removeChildByName("helpLayer");
		this->removeChildByName("monsterHelpLayer");
		this->removeChildByName("towerHelpLayer");

		// �����������ť��ǰ��ѡ�У��򴴽�����ӷ�����������
		if (pTowerHelpBtn->getSelectedIndex() == 1)
		{
			auto towerHelpLayer = TowerHelpLayer::create();
			towerHelpLayer->setName("towerHelpLayer");
			addChild(towerHelpLayer);
		}
		}, pNormalItem, pSelectedItem, nullptr);

	// �����˵���壬������ҳ��ť��������ť�����������ť�ͷ�����������ť
	auto pMenuPanel = Menu::create(pHomeBtn, pHelpBtn, pMonsterHelpBtn, pTowerHelpBtn, NULL);

	// ���ð�ť����Ļ�ϵ�λ��
	pHelpBtn->setPosition(320, 590);
	pMonsterHelpBtn->setPosition(480, 590);
	pTowerHelpBtn->setPosition(640, 590);

	// ���˵������ӵ���ǰ������
	addChild(pMenuPanel, 2);

}


