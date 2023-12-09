#include "cocos2d.h"
#include "Mon1.h"
#include "AudioEngine.h"

USING_NS_CC;

bool Mon1::is_run_frame = false; // 已经初始化  构造函数不用

//构造函数，调用init（）函数，然后加载两个init动画
Mon1::Mon1() {
	//类属性的初始化
	this->Mon_init();
	this->init_mon_move_animation();
	this->init_mon_die_animation();
	sprite = Sprite::create();
	sprite->setScale(1.6f);
	is_run_frame = true;
	//执行调度器
	this->scheduleUpdate();

}

void Mon1::update(float update_time) {
	time_count += update_time;

	//auto move_sound = AudioEngine::play2d("Music/.ogg", true);//没有
	//auto eat_sound = AudioEngine::play2d("Music/chomp.ogg", true);
	if (is_dead) {
		this->unscheduleUpdate();
		removeFromParent();
	}
} //调度函数  参数调度时间间隔

void Mon1::mon_init() {
	this->mon_id = -1; // 编号 
	this->blood = 10;	// 血量
	this->time_count = 0.0;// 时间计时器  统计使用精灵 到结束
	this->attack_num = 1; //攻击值
	this->move_rate = 0; // 移速 相对于移动时间
	this->mon_type = MonType::Mon_typel; //僵尸类型
	this->is_move = false;//是否处于行走状态
	this->is_dead = false;//是否已经死亡
}// 变量初始化

void Mon1::init_mon_move_animation() {
	;
}

void Mon1::init_mon_die_animation() { //死亡动画

	;
}