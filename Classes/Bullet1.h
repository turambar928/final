#ifndef Bullet1_H_
#define Bullet1_H_

#include "cocos2d.h"
#include "bulletbase.h"


USING_NS_CC;

class Bullet1 :public Bullet
{
public:
	Bullet1(const Vec2& position_);
	~Bullet1() = default;
	virtual void bullet_init();// 初始化函数
	virtual void update(double update_time); // 调度函数 参数：调度间隔时间
	virtual void bullet_move_animation(); //创建子弹移动动画
	virtual void sprite_init(const Vec2& position_); //精灵图初始化


};









#endif

