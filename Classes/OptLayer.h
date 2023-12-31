// 防止头文件重复包含
#ifndef __CarrotFantasy__OptLayer__
#define __CarrotFantasy__OptLayer__

// 引入cocos2d头文件
#include "cocos2d.h"
// 声明一个TowerOptBtn类，用于显示塔的选项菜单
class TowerOptBtn;

// 使用cocos2d命名空间
using namespace cocos2d;

// 定义一个OptLayer类，继承自Layer类，用于显示和操作塔和怪物的界面层
class OptLayer :public Layer
{
public:

	// 定义一个宏，用于创建OptLayer对象
	CREATE_FUNC(OptLayer);

protected:
	// 声明一个虚函数，用于初始化OptLayer对象，返回一个布尔值
	virtual bool init();

	// 声明一个虚函数，用于添加触摸事件监听
	virtual void listener();

protected:
	// 声明一个TowerOptBtn类型的指针，用于指向显示塔的选项菜单的对象
	TowerOptBtn* towerOptBtn;
	// 声明一个布尔类型的变量，用于表示是否显示塔的选项菜单
	bool _KeyOptBtn;
	// 声明一个Sprite类型的指针，用于指向显示禁止图标的精灵对象
	Sprite* _pforbiddenSp;

};

// 结束头文件的定义
#endif /* defined(__CarrotFantasy__OptLayer__) */
