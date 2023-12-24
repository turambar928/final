//�������

#include "cocos2d.h"
#include "Bullet1.h"
#include "AudioEngine.h"
#include "myresource.h"
USING_NS_CC;

//bool Mon1::is_run_frame = false; // �Ѿ���ʼ��  ���캯������

//���캯��������init����������Ȼ���������init����
Bullet1::Bullet1(const Vec2& position_) {
	//�����Եĳ�ʼ��
	this->bullet_init();
	this->sprite_init(position_);	
	this->bullet_move_animation();
	//is_run_frame = true;
	//ִ�е�����
	this->scheduleUpdate();

}

void Bullet1::bullet_init() {
	attack_num=2; // �����˺�
	is_crash=0; // �Ƿ���ײ   true:��ײ  false��δ��ײ
	Animate* bullet_move_animate; // �ӵ��ƶ���������
	int x, y;      //��û��ʼ��
	speed=100;     //�ӵ��ٶ�
	attack_range=100;//�ӵ�������Χ  ,��û����
}// ������ʼ��

void Bullet1::sprite_init(const Vec2& position_) {
	sprite = Sprite::create("bullet_bottom1.png");
	//����Vec2���͵Ĳ�����ȷ���������λ��
	sprite->setPosition(position_);
	// ���þ������ת�Ƕ�,˳ʱ��
	sprite->setRotation(90);
	// ��������ӵ���ǰ����
	this->addChild(sprite,3);
	//��ֵ���ӵ�λ��
	position = position_;
}

//���� update_time ��ϵͳ���øú��� �ļ��ʱ��
void Bullet1::update(double update_time) {
	//״̬ ���is_crash Ϊtrue ��ɾ���ӵ� ���Ҳ�����ײ��Ч 	
	if (is_crash) {
		//ɾ���ӵ�
		delete this;
		//������ײ��Ч
		//AudioManager::getInstance()->playSound("crash.wav");
		auto effect_audio = AudioEngine::play2d("music/Select.mp3");
	}
	else {
		//��ȡ�ӵ���Ŀ�����
		//��Ҫ��ӱ������۲��Ƿ����
		Mon* target = my_mon[0];
		//���Ŀ����ﲻ���ڻ��Ѿ���������ô��ɾ���ӵ�
		if (target == nullptr || target->judge_dead()) {
			delete this;
			return;
		}
		//��ȡĿ������λ��
		double tx = target->get_x();
		double ty = target->get_y();
		//�����ӵ���Ŀ�����ľ���
		double dist = sqrt((x - tx) * (x - tx) + (y - ty) * (y - ty));
		//�������С���ӵ��Ĺ�����Χ����ô������˺�������ɾ���ӵ�
		if (dist < attack_range) {
			//�ӵ�����˺�
			target->blood -= attack_num;
			delete this;
			return;
		}
		//�����ӵ���Ŀ�����ļн�
		double angle = atan2(ty - y, tx - x);
		//�����ӵ����ٶȺͼнǣ�������ӵ�����һ֡��λ��
		double dx = speed * cos(angle) * update_time;
		double dy = speed * sin(angle) * update_time;
		//�����ӵ�������
		x += dx;
		y += dy;
	}
} // 
//�����ӵ��ƶ����� 
void Bullet1::bullet_move_animation() {
	//auto bullet_movement = MoveTo::create(2.0f, Vec2(1000,position.y)); // Position of the leftmost zombie in that row
	//sprite->setScale(1.0f);
	//auto bullet_move_animate = Sequence::create(bullet_callback_audio, bullet_movement, nullptr);
	sprite->runAction(MoveTo::create(2.0f, Vec2(position.x, position.y)));
}