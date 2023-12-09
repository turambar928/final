#include "monsterbase.h"

int Mon::mon_id;

void Mon::Mon_init() {
//初始化变量
}

//精灵初始化 参数1精灵图片的名字 参数2:二维坐标的名字
void Mon::sprite_init(const Vec2& position_) {
	sprite->setPosition(position_);
}

// 设置精灵的大小  参数：缩放倍数
void Mon::set_scale(float val_) {
	sprite->setScale(val_);
}

//获取二维坐标
Vec2 Mon::get_position() const {
	return position;
}

//获取二维坐标的X
double Mon::get_x() {
	return sprite->getPositionX();
}

//获取二维坐标的Y
double Mon::get_y() {
	return sprite->getPositionY();
}

//获取当前血量
int Mon::get_blood() const {
	return blood;
}

//获取攻击值
int Mon::get_attack_num() const {
	return attack_num;
}

//设置移动速度
double Mon::get_move_rate() const {
	return move_rate;
}

// 创建 移动动画
void Mon::init_mon_move_animation() {

}

//僵尸 死亡动画
void Mon::init_mon_die_animation() {

}

//时间开销分析
//就是额外构造俩对象的开销,不用从内存读数据，和原有的代码差不多
bool Mon::run_mon_move_animation() {
	if (is_dead) return false;
	if (sprite == nullptr || mon_move_animate == nullptr) return false;
	is_dead = false;
	//is_eat = false;
	is_move = true;
	//is_wait = false;
	sprite->stopAllActions();
	sprite->runAction(RepeatForever::create(
		Animate::create(Animation::createWithSpriteFrames(mon_move, 1.0 / 10)))); // 运行移动动画
	sprite->runAction(MoveTo::create(5.0f, Vec2(-100.0, get_y())));  // 可修改移动速度 此时还需要修改
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

