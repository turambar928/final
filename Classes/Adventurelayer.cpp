#include"Adventurelayer.h"
#include"level1.h"
#include"SysMenu.h"
#include"2d/CCMenu.h"
#include "AudioEngine.h"

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
	//显示波数
	Sprite* adv_wave15 = Sprite::create("picture/adv_wave15.png");
	adv_wave15->setPosition(Vec2(winSize.width / 2 + 180, winSize.height - 130));
	adv_wave15->setScale(2);
	this->addChild(adv_wave15, 1);

	//添加开始按钮
	Sprite* adv_sta_nor = Sprite::create("picture/adv_sta_nor.png");
	Sprite* adv_sta_sel = Sprite::create("picture/adv_sta_sel.png");

	MenuItemSprite* adv_sta_cho = MenuItemSprite::create(adv_sta_nor, adv_sta_sel, CC_CALLBACK_1(Adventure_layer::onStart,this));
	adv_sta_cho->setScale(2);
	Menu*menu1 = Menu::create(adv_sta_cho, NULL);
	menu1->setPosition(Vec2(winSize.width / 2, 150));
	this->addChild(menu1, 1);

	//第一关场景图
	Sprite* adv_level1 = Sprite::create("picture/adv_level1.png");
	adv_level1->setScale(3.2);
	adv_level1->setPosition(Vec2(winSize.width / 2, winSize.height / 2+45));
	this->addChild(adv_level1, 1);


	return true;
}

void Adventure_layer::onBackCallback(Ref* pSender)
{
	onButtonEffect();
	Scene* scene = SysMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFlipAngular::create(1.2, scene));
}

void Adventure_layer::onButtonEffect() {
	//此处可以加一个if语句，来控制什么时候让声音输出。
	auto effect_audio = AudioEngine::play2d("music/Select.mp3");
}

void Adventure_layer::onStart(Ref* pSender) {
	onButtonEffect();
	//onEnter();
	Scene* scene = level1::scene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.2, scene));
}

void Adventure_layer::onEnter() {//这个函数在进入窗口的时候就会执行
	Layer::onEnter();
	int judgemusic=0;
	// 检查是否正在播放背景音乐
	if (AudioEngine::getState(judgemusic) == AudioEngine::AudioState::PLAYING)
	{
		// 获取当前播放的音乐文件名
		//std::string currentMusic;

		// 检查当前播放的音乐是否是你需要的音乐
		//if (currentMusic == "BGMusic.mp3")
		//{
			// 如果不是你需要的音乐，那么停止
			//AudioEngine::stop(judgemusic);
		//}
	}

	else {
		auto effect_audio1 = AudioEngine::play2d("music/BGMusic.mp3", 1);
	}
}



