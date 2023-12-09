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
	;
}

void Mon1::init_mon_die_animation() { //��������

	;
}