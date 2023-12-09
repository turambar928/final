#include "setting.h"
#include "Sysmenu.h" 
#include"2d/CCMenu.h"
USING_NS_CC;
Scene* setting_layer::scene()
{
	Scene* scene = Scene::create();
	setting_layer* setting = setting_layer::create();
	scene->addChild(setting);
	return scene;
}


bool setting_layer::init() {
	if (!Layer::init()) {
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();
	Sprite* adv_back = Sprite::create("picture/adventure_back.png");
	adv_back->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT); //左下角对齐
	adv_back->setScale(2.2);
	this->addChild(adv_back, 0);
	
	//两个按钮：返回和求助
	Sprite* adv_back_nor = Sprite::create("picture/adv_back_nor.png");
	Sprite* adv_que_nor = Sprite::create("picture/adv_que_nor.png");
	
	Sprite* adv_back_sel = Sprite::create("picture/adv_back_sel.png");
	Sprite* adv_que_sel = Sprite::create("picture/adv_que_sel.png");

	MenuItemSprite* adv_back_cho = MenuItemSprite::create(adv_back_nor, adv_back_sel, CC_CALLBACK_1(setting_layer::onBackCallback, this));
	MenuItemSprite* adv_que_cho = MenuItemSprite::create(adv_que_nor, adv_que_sel, CC_CALLBACK_1(setting_layer::onBackCallback, this));
	adv_back_cho->setScale(1.5);
	adv_que_cho->setScale(1.5);

	Menu* menu = Menu::create(adv_back_cho, adv_que_cho, NULL);
	menu->alignItemsHorizontallyWithPadding(winSize.width - 180);
	menu->setPosition(Vec2(670, winSize.height - 30));
	this->addChild(menu, 1);

	
	// 创建两个新的按钮
	Sprite* mute_nor = Sprite::create("picture/mute.png");
	Sprite* mute_sel = Sprite::create("picture/mute.png");

	Sprite* unmute_nor = Sprite::create("picture/unmute.png");
	Sprite* unmute_sel = Sprite::create("picture/unmute.png");

	// 创建按钮选项
	MenuItemSprite* mute_cho = MenuItemSprite::create(mute_nor, mute_sel, CC_CALLBACK_1(setting_layer::onBackCallback, this));
	MenuItemSprite* unmute_cho = MenuItemSprite::create(unmute_nor, unmute_sel, CC_CALLBACK_1(setting_layer::onBackCallback, this));

	// 设置按钮大小
	mute_cho->setScale(0.45);
	unmute_cho->setScale(1.0);

	// 创建菜单并添加按钮选项
	menu = Menu::create( mute_cho, unmute_cho, NULL);
	menu->alignItemsVerticallyWithPadding(30);  // 调整10为你想要的按钮间距

	Size menuSize = menu->getContentSize();
	float xPos = winSize.width * 0.5f;
	float yPos = winSize.height * 0.5f;

	menu->setPosition(Vec2(xPos, yPos));
	this->addChild(menu, 1);



	return true;
}

void setting_layer::onBackCallback(Ref* pSender)
{
	Scene* scene = SysMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.2, scene));
}

void mute(Ref* pSender) {
	// 静音
	
}


void unmute(Ref* pSender) {
	//解除静音
	
}

