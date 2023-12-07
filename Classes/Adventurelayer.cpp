#include"Adventurelayer.h"
#include"SysMenu.h"
#include"2d/CCMenu.h"
USING_NS_CC;
Scene* Adventure_layer::scene()
{
	Scene* scene = Scene::create();
	Adventure_layer* adventure = Adventure_layer::create();
	scene->addChild(adventure);
	return scene;
}

bool Adventure_layer::init() {
	if (!Layer::init()) {
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();
	//创建背景
	Sprite* adv_back = Sprite::create("picture/adventure_back.png");
	adv_back->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT); //左下角对齐
	adv_back->setScale(2.2);
	this->addChild(adv_back, 0);

	//“选择关卡”
	Sprite* adv_cho = Sprite::create("picture/adv_cho.png");
	adv_cho->setPosition(Vec2(winSize.width / 2, winSize.height - adv_cho->getContentSize().height));
	adv_cho->setScale(2.2);
	this->addChild(adv_cho, 1);

	//两个按钮：返回和求助
    Sprite* adv_back_nor = Sprite::create("picture/adv_back_nor.png");
    Sprite* adv_que_nor = Sprite::create("picture/adv_que_nor.png");

    Sprite* adv_back_sel = Sprite::create("picture/adv_back_sel.png");
    Sprite* adv_que_sel = Sprite::create("picture/adv_que_sel.png");

    MenuItemSprite* adv_back_cho = MenuItemSprite::create(adv_back_nor, adv_back_sel, CC_CALLBACK_1(Adventure_layer::onBackCallback, this));
    MenuItemSprite* adv_que_cho = MenuItemSprite::create(adv_que_nor, adv_que_sel, CC_CALLBACK_1(Adventure_layer::onBackCallback, this));
    adv_back_cho->setScale(1.5);
    adv_que_cho->setScale(1.5);
    
	Menu* menu = Menu::create(adv_back_cho, adv_que_cho, NULL);
	menu->alignItemsHorizontallyWithPadding(winSize.width-180);
	menu->setPosition(Vec2(670, winSize.height-30 ));
	this->addChild(menu, 1);
	return true;
}

void Adventure_layer::onBackCallback(Ref* pSender)
{
	Scene* scene = SysMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.2, scene));
}
