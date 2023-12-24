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
	//����
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
	//����
	Sprite* level1_terrain = Sprite::create("picture/level1_terrain.png");
	level1_terrain->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	level1_terrain->setScale(2.15);
	this->addChild(level1_terrain, 1);
	//�������¼�
	auto listener = EventListenerTouchOneByOne::create();
	//listener->onTouchBegan = CC_CALLBACK_2(level1::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(level1::onTouchMoved, this);
	//listener->onTouchEnded = CC_CALLBACK_2(level1::onTouchEnded, this);
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//ע���¼������������¼�ѭ���С����������û�����Ļ�ϴ�����Ļʱ���ͻᴥ����Ӧ�Ļص���������ִ�����е��߼���
	
    Mon* temp_mon = new Mon1();//��ʼ��is_dead�ĳ�ʼ���ƺ�������
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
	// ����Mon1����
	Mon1* temp_mon = new Mon1();

	// ��ʼ������
	//temp_mon->sprite_init(Vec2(winSize.width / 2, winSize.height / 2));

	// ��ȡ����֡
	//auto animFrames = temp_mon->getAnimation("picture/Mon1_%d.png", 2);

	// ��������
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.5f);

	// ������������
	auto animate = Animate::create(animation);
	auto repeatForever = RepeatForever::create(animate);
	// ���ж�������
	temp_mon->sprite->runAction(repeatForever);
	temp_mon->sprite->runAction(MoveTo::create(5.0f, Vec2(-100.0, 500)));
	// ��������ӵ���ǰ��
	this->addChild(temp_mon->sprite, 3);
	*/
	return true;
}


void level1::onEnter() {//��������ڽ��봰�ڵ�ʱ��ͻ�ִ��
	Layer::onEnter();
	int judgemusic = 0;
	// ����Ƿ����ڲ��ű�������
	if (AudioEngine::getState(judgemusic) == AudioEngine::AudioState::PLAYING)
	{
		// ��ȡ��ǰ���ŵ������ļ���
		//std::string currentMusic;

		// ��鵱ǰ���ŵ������Ƿ�������Ҫ������
		//if (currentMusic == "BGMusic.mp3")
		//{
			// �����������Ҫ�����֣���ôֹͣ
		AudioEngine::stop(judgemusic);
		//}
	}

}

