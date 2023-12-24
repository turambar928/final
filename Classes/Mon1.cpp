#include "cocos2d.h"
#include "Mon1.h"
#include "AudioEngine.h"
#include "myresource.h"
USING_NS_CC;

bool Mon1::is_run_frame = false; // �Ѿ���ʼ��  ���캯������

//���캯��������init����������Ȼ���������init����
Mon1::Mon1() {
	//�����Եĳ�ʼ��
	this->mon_init();
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
	
	/*if (my_mon[0]->get_x() == mypath[1].x && my_mon[0]->get_y() == mypath[1].y) {
		
		my_mon[0]->sprite->setPosition(Vec2(mypath[2].x, mypath[2].y));
	}*/

	
	

	//auto eat_sound = AudioEngine::play2d("Music/chomp.ogg", true);
	if (is_dead) {
		this->unscheduleUpdate();
		removeFromParent();
	}
} //���Ⱥ���  ��������ʱ����

void Mon1::mon_init() {
	this->mon_id = 1; // ��� 
	this->blood = 10;	// Ѫ��
	this->time_count = 0.0;// ʱ���ʱ��  ͳ��ʹ�þ��� ������
	this->attack_num = 1; //����ֵ
	this->move_rate = 100; // ���� ������ƶ�ʱ��
	this->mon_type = MonType::Mon_typel; //��ʬ����
	this->is_move = false;//�Ƿ�������״̬
	this->is_dead = false;//�Ƿ��Ѿ�����
	this->money = 1;
}// ������ʼ��

void Mon1::init_mon_move_animation() {
	mon_move = getAnimation("picture/Mon1_%d.png", 2); // ���ü���ͼƬ
	sprite = Sprite::createWithSpriteFrame(mon_move.front());
	auto animation1 = Animation::createWithSpriteFrames(mon_move, 1.0 / 5); // ����ʱ�� ԼС�����Խ��  
	mon_move_animate = Animate::create(animation1);

}

void Mon1::init_mon_die_animation() { //��������
	mon_die = getAnimation("picture/Mondie%d.png", 6); // ���ü���ͼƬ
	sprite = Sprite::createWithSpriteFrame(mon_die.front());
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