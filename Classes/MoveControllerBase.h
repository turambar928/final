// 防止头文件重复包含
#ifndef CarrotFantasy_MoveControllerBase_h
#define CarrotFantasy_MoveControllerBase_h

// 包含怪物基类的头文件
#include "MonsterBase.h"

// 定义一个移动控制器基类，继承自节点类
class MoveControllerBase : public Node
{
    // 声明怪物基类为友元类，可以访问移动控制器基类的私有成员
    friend class MonsterBase;
public:

    // 定义移动控制器基类的虚析构函数，释放内存
    virtual ~MoveControllerBase();

    // 定义一个虚函数，监听怪物对象的移动事件，参数是一个浮点类型的变量，表示移动的时间间隔
    virtual void listenerMonster(float t);


private:

    // 定义一个私有函数，设置成员变量为参数指向的怪物对象，参数是一个指向怪物基类的指针
    void setMonster(MonsterBase* pMomster);

    // 定义一个私有函数，删除移动路径的第一个点
    void erasePoint();

    // 定义一个虚函数，初始化移动控制器对象，参数是一个指向怪物基类的指针，返回一个布尔类型的值，表示是否初始化成功
    virtual bool init(MonsterBase* pMomster);

    // 定义一个静态函数，创建一个移动控制器对象，参数是一个指向怪物基类的指针，返回一个指向移动控制器基类的指针
    static MoveControllerBase* create(MonsterBase* pMomster);

    // 使用宏定义声明和定义一个整数类型的成员变量，表示怪物对象的速度，以及相应的获取和设置函数
    CC_SYNTHESIZE_PASS_BY_REF(int, _iMonsterSpeed, IMonsterSpeed);

    // 定义一个私有函数，根据子弹的类型和动画的时间间隔，创建一个动画对象，参数是一个整数类型的变量，表示子弹的类型，和一个浮点类型的变量，表示动画的时间间隔，返回一个指向动画对象的指针
    Animation* AnimationMaker(int iBulletType, float t);

    // 定义移动控制器基类的私有构造函数
    MoveControllerBase() {}
private:

    // 定义一个指向怪物基类的指针，表示关联的怪物对象
    MonsterBase* _pMonster = nullptr;

    // 定义一个指向二维向量的向量的指针，表示移动路径的点的坐标
    std::vector<Vec2>* _pMapPonits;

};


#endif
