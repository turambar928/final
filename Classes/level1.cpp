#include"level1.h"
#include"Adventurelayer.h"
#include"AudioEngine.h"
#include"2d/CCMenu.h"
#include"Mon1.h"
#include"monsterbase.h"
#include"myresource.h"
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
	winSize = Director::getInstance()->getVisibleSize();
	Size piece;
	piece.width = winSize.width / 12;
	piece.height = winSize.height / 8;
	mypath.push_back(Vec2(1.5*piece.width,5.5*piece.height));
	mypathjudge.push_back(0);
	mypath.push_back(Vec2(1.5 * piece.width, 2.5 * piece.height));
	mypathjudge.push_back(0);
	mypath.push_back(Vec2(4.5 * piece.width, 2.5 * piece.height));
	mypathjudge.push_back(0);
	mypath.push_back(Vec2(4.5 * piece.width, 3.5 * piece.height));
	mypathjudge.push_back(0);
	mypath.push_back(Vec2(7.5 * piece.width, 3.5 * piece.height));
	mypathjudge.push_back(0);
	mypath.push_back(Vec2(7.5 * piece.width, 2.5 * piece.height));
	mypathjudge.push_back(0);
	mypath.push_back(Vec2(10.5 * piece.width, 2.5 * piece.height));
	mypathjudge.push_back(0);
	mypath.push_back(Vec2(10.5 * piece.width, 5.5 * piece.height));
	mypathjudge.push_back(0);
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
	
    Mon* temp_mon = new Mon1();//初始化is_dead的初始化似乎有问题
	temp_mon->sprite_init(Vec2(mypath[0].x, mypath[0].y));
	//temp_mon->run_mon_move_animation(1);
	my_mon.push_back(temp_mon);
	this->addChild(temp_mon->sprite, 3);
	/*if (temp_mon->is_move == false) {
		auto sprite_leftleaf = Sprite::create("picture/leaf1.png");


		sprite_leftleaf->setPosition(Vec2(winSize.width / 2 - 60,
			winSize.height - 3 * sprite_leftleaf->getContentSize().height + 10));
		sprite_leftleaf->setScale(1.9);
		// add the sprite as a child to this layer
		this->addChild(sprite_leftleaf, 3);
	}*/
	
	/*
	// 创建Mon1对象
	Mon1* temp_mon = new Mon1();

	// 初始化精灵
	//temp_mon->sprite_init(Vec2(winSize.width / 2, winSize.height / 2));

	// 获取动画帧
	//auto animFrames = temp_mon->getAnimation("picture/Mon1_%d.png", 2);

	// 创建动画
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.5f);

	// 创建动画动作
	auto animate = Animate::create(animation);
	auto repeatForever = RepeatForever::create(animate);
	// 运行动画动作
	temp_mon->sprite->runAction(repeatForever);
	temp_mon->sprite->runAction(MoveTo::create(5.0f, Vec2(-100.0, 500)));
	// 将精灵添加到当前层
	this->addChild(temp_mon->sprite, 3);
	*/
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

