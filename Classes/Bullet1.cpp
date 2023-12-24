//设计升级

#include "cocos2d.h"
#include "Bullet1.h"
#include "AudioEngine.h"
#include "myresource.h"
USING_NS_CC;

//bool Mon1::is_run_frame = false; // 已经初始化  构造函数不用

//构造函数，调用init（）函数，然后加载两个init动画
Bullet1::Bullet1(const Vec2& position_) {
	//类属性的初始化
	this->bullet_init();
	this->sprite_init(position_);	
	this->bullet_move_animation();
	//is_run_frame = true;
	//执行调度器
	this->scheduleUpdate();

}

void Bullet1::bullet_init() {
	attack_num=2; // 攻击伤害
	is_crash=0; // 是否碰撞   true:碰撞  false：未碰撞
	Animate* bullet_move_animate; // 子弹移动动作变量
	int x, y;      //还没初始化
	speed=100;     //子弹速度
	attack_range=100;//子弹攻击范围  ,还没量化
}// 变量初始化

void Bullet1::sprite_init(const Vec2& position_) {
	sprite = Sprite::create("bullet_bottom1.png");
	//传入Vec2类型的参数，确定精灵对象位置
	sprite->setPosition(position_);
	// 设置精灵的旋转角度,顺时针
	sprite->setRotation(90);
	// 将精灵添加到当前场景
	this->addChild(sprite,3);
	//赋值给子弹位置
	position = position_;
}

//参数 update_time 是系统调用该函数 的间隔时间
void Bullet1::update(double update_time) {
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
			target->blood -= attack_num;
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
void Bullet1::bullet_move_animation() {
	//auto bullet_movement = MoveTo::create(2.0f, Vec2(1000,position.y)); // Position of the leftmost zombie in that row
	//sprite->setScale(1.0f);
	//auto bullet_move_animate = Sequence::create(bullet_callback_audio, bullet_movement, nullptr);
	sprite->runAction(MoveTo::create(2.0f, Vec2(position.x, position.y)));
}