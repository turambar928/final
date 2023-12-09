#include"level1.h"
#include"Adventurelayer.h"
#include"AudioEngine.h"
#include"2d/CCMenu.h"

USING_NS_CC;

Scene* level1::scene()
{
	Scene* scene = Scene::create();
	level1* level = level1::create();
	scene->addChild(level);
	return scene;
}

bool level1::init() {
	if (!Layer::init()) {
		return false;
	}
	//背景
	Sprite* level1back = Sprite::create("picture/level1back.png");
	level1back->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	level1back->setScale(2.15);
	this->addChild(level1back, 0);
	//地形
	Sprite* level1_terrain = Sprite::create("picture/level1_terrain.png");
	level1_terrain->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	level1_terrain->setScale(2.15);
	this->addChild(level1_terrain, 1);
	//鼠标监听事件
	auto listener = EventListenerTouchOneByOne::create();
	//listener->onTouchBegan = CC_CALLBACK_2(level1::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(level1::onTouchMoved, this);
	//listener->onTouchEnded = CC_CALLBACK_2(level1::onTouchEnded, this);
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//注册事件监听器到主事件循环中。这样，当用户在屏幕上触摸屏幕时，就会触发相应的回调函数，并执行其中的逻辑。






	return true;
}


void level1::onEnter() {//这个函数在进入窗口的时候就会执行
	Layer::onEnter();
	int judgemusic = 0;
	// 检查是否正在播放背景音乐
	if (AudioEngine::getState(judgemusic) == AudioEngine::AudioState::PLAYING)
	{
		// 获取当前播放的音乐文件名
		//std::string currentMusic;

		// 检查当前播放的音乐是否是你需要的音乐
		//if (currentMusic == "BGMusic.mp3")
		//{
			// 如果不是你需要的音乐，那么停止
		AudioEngine::stop(judgemusic);
		//}
	}

}