// 防止头文件重复包含
#ifndef __CarrotFantasy__MonsterBase__
#define __CarrotFantasy__MonsterBase__

// 包含受害者实体基类的头文件
#include "VictimEntityBase.h"
// 包含动态属性接口的头文件
#include "DynamicPropertyInterFace.h"

// 前置声明移动控制器基类
class MoveControllerBase;

// 定义一个怪物基类，继承自受害者实体基类和动态属性接口
class MonsterBase : public VictimEntityBase, public DynamicPropertyInterFace
{
    // 声明怪物工厂类为友元类，可以访问私有成员
    friend class MonsterFactory;

public:

    // 使用静态函数创建一个怪物对象，参数是怪物的ID
    static MonsterBase* create(const int& rIId);

    // 设置怪物的最大速度，参数是速度值
    void setMaxSpeed(const int& iSpeed);

protected:

    // 重写受害者实体基类的死亡动作函数，参数是死亡时的图片文件名
    virtual void deadAction(const std::string& rSDeadImageFile = "")override;

    // 定义怪物的动作函数，参数是动画的延迟时间
    virtual void doAction(const float& rDt);

    // 初始化怪物对象的函数，参数是怪物的ID
    virtual bool init(const int& rIId);

    // 定义怪物受伤的动作函数，暂时为空
    virtual void behurtAction();

    // 创建怪物的动画的函数
    virtual void createAnimation();

    // 定义怪物发出声音的函数
    virtual void MonsterSound();

    // 使用宏定义声明和定义一个布尔类型的成员变量，表示怪物的朝向是否为左
    CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsLeft, IsLeft);

    // 声明一个指向移动控制器基类的指针，用来控制怪物的移动
    MoveControllerBase* _pMoveController = nullptr;
};

// 结束头文件的定义
#endif /* defined(__CarrotFantasy__MonsterBase__) */
