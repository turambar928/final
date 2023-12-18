#include "monsterbase.h"
#include"Mon1.h"
#include"myresource.h"
int Mon::mon_id;

void Mon::Mon_init() {
//��ʼ������
}

//�����ʼ�� ����1����ͼƬ������ ����2:��ά���������
void Mon::sprite_init(const Vec2& position_) {
	sprite->setPosition(position_);
}

void readpath() {
	int i = mypath.size();
	mypathjudge[0] = 1;
	
}
// ���þ���Ĵ�С  ���������ű���
void Mon::set_scale(float val_) {
	sprite->setScale(val_);
}

//��ȡ��ά����
Vec2 Mon::get_position() const {
	return position;
}

//��ȡ��ά�����X
double Mon::get_x() {
	return sprite->getPositionX();
}

//��ȡ��ά�����Y
double Mon::get_y() {
	return sprite->getPositionY();
}

//��ȡ��ǰѪ��
int Mon::get_blood() const {
	return blood;
}

//��ȡ����ֵ
int Mon::get_attack_num() const {
	return attack_num;
}

//�����ƶ��ٶ�
double Mon::get_move_rate() const {
	return move_rate;
}

// ���� �ƶ�����
void Mon::init_mon_move_animation() {

}

//��ʬ ��������
void Mon::init_mon_die_animation() {

}

//ʱ�俪������
//���Ƕ��⹹��������Ŀ���,���ô��ڴ�����ݣ���ԭ�еĴ�����
bool Mon::run_mon_move_animation(int i) {
	
	if (is_dead==true) {return false;}  //δ�ҵ�ԭ��is_dead�ڳ�ʼ��ɺ���Ϊ1
	if (sprite == nullptr || mon_move_animate == nullptr) { 
		return false; }
	is_dead = false;
	//is_eat = false;
	is_move = true;
	//is_wait = false;
	sprite->stopAllActions();
	sprite->runAction(RepeatForever::create(
		Animate::create(Animation::createWithSpriteFrames(mon_move, 1.0/2)))); // �����ƶ�����,ÿ֮֡����ӳ���1��
	sprite->runAction(MoveTo::create(5.0f, Vec2(mypath[i].x, mypath[i].y)));  // 5�����ƶ�������������λ��.���޸��ƶ��ٶ� ��ʱ����Ҫ�޸�
	
	return true;
	
}

void Mon::run_mon_die_animation() {
	if (sprite == nullptr || mon_move_animate == nullptr) return;
	//auto delayt = DelayTime::create(3);
	is_dead = true;
	is_move = false;
	sprite->stopAllActions();
	sprite->runAction(
		Animate::create(Animation::createWithSpriteFrames(mon_die, 1.0 / 2)));
	sprite->runAction(Sequence::create(DelayTime::create(2.0f), Blink::create(2.0f, 5), RemoveSelf::create(), nullptr));
	removeFromParent();

}
bool Mon::judge_dead() const {
	return is_dead;
}

bool Mon::judge_move() const {
	return is_move;
}

