#include "bulletbase.h"
#include "AudioEngine.h"
#include "monsterbase.h"
#include "myresource.h"

Bullet::Bullet() {
	//调用init函数
	//调用精灵初始化函数 并且赋值
	sprite = Sprite::create();
	//长和宽都设计成2倍
	sprite->setScale(2);
	//调用动作初始化函数  并且赋值
	bullet_init();
	//让该函数每一帧都执行update函数，以便更新精灵的状态与位置
	this->scheduleUpdate();
}

void Bullet::bullet_init() {
	//子弹的伤害
	attack_num = 1; // damage scale
	is_crash = false; // 判断是否碰撞变量 
}

//精灵初始化  参1 精灵图片名字  参2 二维坐标
// 精灵图 使用 豌豆的   大小设置为1  位置
void Bullet::sprite_init(const Vec2& position_) {
	sprite = Sprite::create("bullet_bottom1.png");
	//传入Vec2类型的参数，确定精灵对象位置
	sprite->setPosition(position_);
	//赋值给子弹位置
	position = position_;
}

//修改系统的时间调度函数  
//参数 update_time 是系统调用该函数 的间隔时间
void Bullet::update(double update_time) {
	//状态 如果is_crash 为true 则删除子弹 并且产生碰撞音效 	
	if (is_crash) {
		//删除子弹
		delete this;
		//播放碰撞音效
		//AudioManager::getInstance()->playSound("crash.wav");
		auto effect_audio = AudioEngine::play2d("music/Select.mp3");
	}
	else {
		//获取子弹的目标怪物
		//需要添加遍历，观察是否存在
		Mon* target = my_mon[0];
		//如果目标怪物不存在或已经死亡，那么就删除子弹
		if (target == nullptr || target->judge_dead()) {
			delete this;
			return;
		}
		//获取目标怪物的位置
		double tx = target->get_x();
		double ty = target->get_y();
		//计算子弹和目标怪物的距离
		double dist = sqrt((x - tx) * (x - tx) + (y - ty) * (y - ty));
		//如果距离小于子弹的攻击范围，那么就造成伤害，并且删除子弹
		if (dist < attack_range) {
			//子弹造成伤害
			target->blood-=attack_num;
			delete this;
			return;
		}
		//计算子弹和目标怪物的夹角
		double angle = atan2(ty - y, tx - x);
		//根据子弹的速度和夹角，计算出子弹在下一帧的位置
		double dx = speed * cos(angle) * update_time;
		double dy = speed * sin(angle) * update_time;
		//更新子弹的坐标
		x += dx;
		y += dy;
	}
} // 

//创建子弹移动动画 
void Bullet::bullet_move_animation() {
	//auto bullet_movement = MoveTo::create(2.0f, Vec2(1000,position.y)); // Position of the leftmost zombie in that row
	//sprite->setScale(1.0f);
	//auto bullet_move_animate = Sequence::create(bullet_callback_audio, bullet_movement, nullptr);
	sprite->runAction(MoveTo::create(4.0f, Vec2(1000, position.y)));
}


//获取二维坐标
Vec2 Bullet::get_position() const {
	return position;
}

//获取精灵 x坐标
double Bullet::get_x() const {
	return sprite->getPositionX();
}

//获取精灵 y 坐标
double Bullet::get_y() const {
	return sprite->getPositionY();
}

// 判断是否碰撞
bool Bullet::judge_crash() {
	//调用寻路函数，如果碰撞则
	return  1;
}

//设置碰撞
void Bullet::set_crash() {
	is_crash = true;
}

//设置 攻击伤害   参数：子弹伤害
void Bullet::set_attack_num(double plant_damage) {// damage scale
	this->attack_num = plant_damage;
}

//删除 精灵 is_crash 变量执行  未完善
void Bullet::delete_sprite() {
	if (is_crash) {
		this->removeChild(this, true); // "this" stands for bullet object
	}
}
