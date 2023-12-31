// 防止头文件重复包含
#ifndef __CarrotFantasy__MonsterBuilder__
#define __CarrotFantasy__MonsterBuilder__
// 包含cocos2d命名空间的头文件
#include "cocos2d.h"
using namespace cocos2d;
// 定义一个怪物建造者类，继承自节点类
class MonsterBuilder :public Node {

protected:

	// 重写节点类的初始化函数
	virtual bool init();

	// 定义一个浮点类型的成员变量，表示创建怪物的延迟时间
	float _fDelayTime;

	// 定义一个整型的成员变量，表示当前批次的怪物计数
	int _MonsterCount;

	// 定义一个整型的成员变量，表示总共创建的怪物计数
	int _MonsterBuilderNumber;

	// 定义一个整型的成员变量，表示从文件中读取的当前关卡的怪物批次数量
	int _iReadFileMonsterCount;

	// 定义一个布尔类型的成员变量，表示是否延迟创建怪物
	bool _bDelay;

	// 定义一个整型的常量，表示创建怪物的延迟时间的常量值
	const int _iConstDelayTime = 8;

	// 定义一个整型的成员变量，表示每批次的怪物编号
	int _iNumber;

	// 定义一个整型的成员变量，表示当前的批次
	int _iBatch;

	// 重写节点类的进入场景函数
	virtual void onEnter();

	// 定义一个创建怪物的更新函数，参数是时间间隔
	void createMonsterUpdate(float t);

	// 定义一个怪物工厂控制器的函数，用来根据不同的批次和编号创建不同类型的怪物
	void MonsterFactoryController();

	// 定义一个指向动画类的指针，用来存放创建怪物的动画对象
	Animation* _createMonsterAnimation;

	// 定义怪物建造者类的析构函数
	~MonsterBuilder();

public:

	// 定义一个获取当前批次的函数，返回当前批次的值
	int getBatch();

	// 使用宏定义创建一个怪物建造者对象的静态函数
	CREATE_FUNC(MonsterBuilder);

	// 使用宏定义声明和定义一个整型的成员变量，表示每批次创建的怪物数量
	CC_SYNTHESIZE_PASS_BY_REF(int, _iBuildNumber, IBuildNumber);
};
// 结束头文件的定义
#endif
