#include "bulletbase.h"
#include "AudioEngine.h"
#include "monsterbase.h"
#include "myresource.h"

Bullet::Bullet() {
	//����init����
	//���þ����ʼ������ ���Ҹ�ֵ
	sprite = Sprite::create();
	//���Ϳ���Ƴ�2��
	sprite->setScale(2);
	//���ö�����ʼ������  ���Ҹ�ֵ
	bullet_init();
	//�øú���ÿһ֡��ִ��update�������Ա���¾����״̬��λ��
	this->scheduleUpdate();
}

void Bullet::bullet_init() {
	//�ӵ����˺�
	attack_num = 1; // damage scale
	is_crash = false; // �ж��Ƿ���ײ���� 
}

//�����ʼ��  ��1 ����ͼƬ����  ��2 ��ά����
// ����ͼ ʹ�� �㶹��   ��С����Ϊ1  λ��
void Bullet::sprite_init(const Vec2& position_) {
	sprite = Sprite::create("bullet_bottom1.png");
	//����Vec2���͵Ĳ�����ȷ���������λ��
	sprite->setPosition(position_);
	//��ֵ���ӵ�λ��
	position = position_;
}

//�޸�ϵͳ��ʱ����Ⱥ���  
//���� update_time ��ϵͳ���øú��� �ļ��ʱ��
void Bullet::update(double update_time) {
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
			target->blood-=attack_num;
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
void Bullet::bullet_move_animation() {
	//auto bullet_movement = MoveTo::create(2.0f, Vec2(1000,position.y)); // Position of the leftmost zombie in that row
	//sprite->setScale(1.0f);
	//auto bullet_move_animate = Sequence::create(bullet_callback_audio, bullet_movement, nullptr);
	sprite->runAction(MoveTo::create(4.0f, Vec2(1000, position.y)));
}


//��ȡ��ά����
Vec2 Bullet::get_position() const {
	return position;
}

//��ȡ���� x����
double Bullet::get_x() const {
	return sprite->getPositionX();
}

//��ȡ���� y ����
double Bullet::get_y() const {
	return sprite->getPositionY();
}

// �ж��Ƿ���ײ
bool Bullet::judge_crash() {
	//����Ѱ·�����������ײ��
	return  1;
}

//������ײ
void Bullet::set_crash() {
	is_crash = true;
}

//���� �����˺�   �������ӵ��˺�
void Bullet::set_attack_num(double plant_damage) {// damage scale
	this->attack_num = plant_damage;
}

//ɾ�� ���� is_crash ����ִ��  δ����
void Bullet::delete_sprite() {
	if (is_crash) {
		this->removeChild(this, true); // "this" stands for bullet object
	}
}
