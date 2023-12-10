#include "cocos2d.h"
#include "Mon1.h"
#include "AudioEngine.h"

USING_NS_CC;

bool Mon1::is_run_frame = false; // �Ѿ���ʼ��  ���캯������

//���캯��������init����������Ȼ���������init����
Mon1::Mon1() {
	//�����Եĳ�ʼ��
	this->Mon_init();
	this->init_mon_move_animation();
	this->init_mon_die_animation();
	sprite = Sprite::create();
	sprite->setScale(1.6f);
	is_run_frame = true;
	//ִ�е�����
	this->scheduleUpdate();

}

void Mon1::update(float update_time) {
	time_count += update_time;

	//auto move_sound = AudioEngine::play2d("Music/.ogg", true);//û��
	//auto eat_sound = AudioEngine::play2d("Music/chomp.ogg", true);
	if (is_dead) {
		this->unscheduleUpdate();
		removeFromParent();
	}
} //���Ⱥ���  ��������ʱ����

void Mon1::mon_init() {
	this->mon_id = -1; // ��� 
	this->blood = 10;	// Ѫ��
	this->time_count = 0.0;// ʱ���ʱ��  ͳ��ʹ�þ��� ������
	this->attack_num = 1; //����ֵ
	this->move_rate = 0; // ���� ������ƶ�ʱ��
	this->mon_type = MonType::Mon_typel; //��ʬ����
	this->is_move = false;//�Ƿ�������״̬
	this->is_dead = false;//�Ƿ��Ѿ�����
}// ������ʼ��

void Mon1::init_mon_move_animation() {
	//auto Mon1 = Sprite::create("picture/Mon1_1.png");
	//Mon1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//this->addChild(Mon1, 20);
	//auto animation = Animation::create();//������һ���µĶ�������
	//animation->addSpriteFrameWithFile("picture/Mon1_1.png");
	//animation->addSpriteFrameWithFile("picture/Mon1_2.png");//������ͼ��֡��ӵ������С�
	//animation->setDelayPerUnit(0.5f);   //������ÿ֡�������ӳ�ʱ�䣬��ÿ֡������ʾ0.5��
	//animation->setLoops(-1);      //�����˶���ѭ���Ĵ�����-1��ʾ����������ѭ��
	//animation->setRestoreOriginalFrame(true); //�����˶���������Ϻ��Ƿ�ָ�����һ֡
	//mon_move_animate = Animate::create(animation);
	//Mon1->runAction(animate);//ʹ��ִ�ж���
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ZomBies/NomalZombie/ZombieMove/Zombie_default.plist");
	mon_move = getAnimation("pciture/Mon1_%d.png", 2); // ���ü���ͼƬ
	auto animation1 = Animation::createWithSpriteFrames(mon_move, 1.0 / 5); // ����ʱ�� ԼС�����Խ��  
	mon_move_animate = Animate::create(animation1);

}

void Mon1::init_mon_die_animation() { //��������
	mon_die = getAnimation("pciture/Mondie%d.png", 6); // ���ü���ͼƬ
	auto animation1 = Animation::createWithSpriteFrames(mon_die, 1.0 / 5); // ����ʱ�� ԼС�����Խ��  
	mon_die_animate = Animate::create(animation1);
}



Vector<SpriteFrame*> Mon1::getAnimation(const char* format, int count) {
	Vector<SpriteFrame*> animFrames;
	auto director = Director::getInstance();//��ȡ��Director���ʵ��
	auto textureCache = director->getTextureCache();//���д����ȡ���������ʵ��
	char str[100];
	for (int i = 1; i <= count; i++) {
		sprintf(str, format, i);//��string��format��ʽ����ֵ��������%d������i����
		auto texture = textureCache->addImage(str); //���ļ�ϵͳ�м���ͼƬ����������ӵ���������
		Size imageSize = texture->getContentSize(); //�����ȡ������Ĵ�С��
		float spriteWidth = imageSize.width;
		float spriteHeight = imageSize.height;
		auto frame = SpriteFrame::create(str, Rect(0, 0, spriteWidth, spriteHeight)); // spriteWidth �� spriteHeight ��Ҫ�����ʵ�ʵľ���֡��С��������
		animFrames.pushBack(frame);
	}
	return animFrames;
}