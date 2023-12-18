#ifndef Mon1_H_
#define Mon1_H_

#include "cocos2d.h"
#include "monsterbase.h"

USING_NS_CC;

class Mon1 :public Mon
{
public:
	Mon1();
	~Mon1() = default;
	virtual void update(float update_time); //调度函数  参数调度时间间隔
	virtual void mon_init();// 变量初始化
	//重写基类动画
	virtual void init_mon_move_animation();
	virtual void init_mon_die_animation(); //死亡动画
	static bool is_run_frame;   //用于判断是否加载帧动画了   防止重复加载
	Vector<SpriteFrame*> getAnimation(const char* format, int count);
	


};



#endif // Mon_H_