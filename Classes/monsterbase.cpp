#include "monsterbase.h"
#include"Mon1.h"
#include"myresource.h"
int Mon::mon_id;

void Mon::Mon_init() {
//初始化变量
}

//精灵初始化 参数1精灵图片的名字 参数2:二维坐标的名字
void Mon::sprite_init(const Vec2& position_) {
	sprite->setPosition(position_);
}

void readpath() {
	int i = mypath.size();
	mypathjudge[0] = 1;
	
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
	
	if (is_dead==true) {return false;}  //未找到原因，is_dead在初始完成后结果为1
	if (sprite == nullptr || mon_move_animate == nullptr) { 
		return false; }
	is_dead = false;
	//is_eat = false;
	is_move = true;
	//is_wait = false;
	sprite->stopAllActions();
	
	sprite->runAction(RepeatForever::create(
		Animate::create(Animation::createWithSpriteFrames(mon_move, 1.0/2)))); // 运行移动动画,每帧之间的延迟是1秒
	//sprite->runAction(MoveTo::create(5.0f, Vec2(mypath[1].x, mypath[1].y)));  // 5秒内移动到给定的坐标位置.可修改移动速度 此时还需要修改
	Vector<FiniteTimeAction*> actions;
	for (int i = 1; i < mypath.size(); i++) {
		float distance= sqrt(pow(mypath[i-1].x - mypath[i].x, 2) + pow(mypath[i-1].y - mypath[i].y, 2));
		auto move = MoveTo::create(distance/move_rate, Vec2(mypath[i].x, mypath[i].y));
		actions.pushBack(move);
	}
	auto sequence = Sequence::create(actions);
	sprite->runAction(sequence);
	return true;
	
}

/*
	auto moveAction = cocos2d::MoveBy::create(move_rate, cocos2d::Vec2(n_x, n_y));
	auto sequence = cocos2d::Sequence::create(
		moveAction,
		cocos2d::CallFunc::create([this]() {
			cocos2d::Vec2 sp = this->getPosition();
			if (sp.x == mypath[0].x && sp.y > mypath[1].y)
				this->run_mon_move_animation(sp.x, sp.y, 0, -1, 1);
			}),
		nullptr
	);

	*/
void Mon::run_mon_die_animation() {
	if (sprite == nullptr || mon_move_animate == nullptr) return;
	//auto delayt = DelayTime::create(3);
	is_dead = true;
	is_move = false;
	sprite->stopAllActions();
	sprite->runAction(
		Animate::create(Animation::createWithSpriteFrames(mon_die, 1.0 / 10)));
	sprite->runAction(Sequence::create(DelayTime::create(6.0/10), RemoveSelf::create(), nullptr));
	removeFromParent();

}
bool Mon::judge_dead() const {
	return is_dead;
}

bool Mon::judge_move() const {
	return is_move;
}

