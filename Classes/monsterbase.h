#ifndef monsterbase_H
#define monsterbase_H

#include "cocos2d.h"


USING_NS_CC;

enum MonType {
	Mon_type_none = -1,
	Mon_typel, 
	Mon_type2,
	Mon_type3,
	Mon_type4 
	// Other Mon
};

class Mon :public Sprite {
public:
	Mon() = default; //按默认方式来构建
	~Mon() = default;
	virtual void Mon_init();    //变量初始化
	void sprite_init(const Vec2& position_);//精灵初始化
	virtual void set_scale(float val_);// 设置精灵的大小
	virtual Vec2 get_position() const;
	virtual double get_x();
	virtual double get_y();
	virtual int get_blood() const;
	virtual int get_attack_num() const;
	virtual double get_move_rate() const;
	//加载动作
	virtual void init_mon_move_animation();
	virtual void init_mon_die_animation();
	//运行动作
	virtual bool run_mon_move_animation();
	virtual void run_mon_die_animation();
	//设置状态
	virtual bool judge_dead() const;
	virtual bool judge_move() const;
	//变量
	static int mon_id; // 僵尸编号 唯一性
	double blood;	// 血量
	double time_count;// 时间计时器  统计使用精灵 到结束
	float move_rate; // 移速
	double attack_num; //攻击值

	Vec2 position;//二维位置 变量
	Sprite* sprite;// 精灵变量

	//动作变量 
	Animate* mon_move_animate;
	Animate* mon_die_animate;

	Vector<SpriteFrame*> mon_move;
	Vector<SpriteFrame*> mon_die;

	//僵尸类型 enum 结合switch遍历
	MonType mon_type;
	//僵尸状态变量
	bool is_move;//僵尸是否处于行走状态
	bool is_dead;//僵尸是否已经死亡
	int row;
};












#endif
