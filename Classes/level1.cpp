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
	//����
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