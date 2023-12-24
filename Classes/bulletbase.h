#ifndef bulletbase_H
#define bulletbase_H

#include "cocos2d.h"

USING_NS_CC;


class Bullet :public Sprite {
public:
	Bullet();//构造函数

	~Bullet() = default;
	virtual void bullet_init();// 初始化函数
	virtual void update(double update_time); // 调度函数 参数：调度间隔时间
	virtual void bullet_move_animation(); //创建子弹移动动画

	//精灵初始化  参1 图片名字  参2：二维坐标
	virtual void sprite_init(const Vec2& position_);
	virtual Vec2 get_position() const; // 获取二维坐标
	virtual double get_x() const; // getPositionX
	virtual double get_y() const;
	virtual void set_crash(); // 设置为判断
	virtual bool judge_crash(); // crash judgement, if ture, delete the bullet
	virtual void set_attack_num(double damage);// 设置子弹伤害
	virtual void delete_sprite(); // 删除精灵 
	int row;
	//变量
	Vec2 position; // 二维坐标
	Sprite* sprite; //精灵变量
	double attack_num; // 攻击伤害
	bool is_crash; // 是否碰撞   true:碰撞  false：未碰撞
	Animate* bullet_move_animate; // 子弹移动动作变量
	int x, y;      //还没初始化
	int speed;     //子弹速度
	int attack_range;//子弹攻击范围
};















#endif