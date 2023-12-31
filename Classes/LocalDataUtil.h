#ifndef __CarrotFantasy__LocalDataUtil__ //如果没有定义__CarrotFantasy__LocalDataUtil__宏，防止头文件重复包含
#define __CarrotFantasy__LocalDataUtil__ //定义__CarrotFantasy__LocalDataUtil__宏

#include "PublicDefine.h" //包含公共定义的头文件

class LocalDataUtil : public Ref //定义一个类，继承自Ref类，用于管理本地数据
{
public:

    CREATE_INSTANCE_FUNC(LocalDataUtil); //使用宏定义一个创建实例的函数，用于获取本地数据工具的单例

    DESTROY_INSTANCE_FUNC(); //使用宏定义一个销毁实例的函数，用于释放本地数据工具的单例

    virtual ValueMap& getLevelData(); //定义一个虚函数，用于获取关卡数据，返回一个值映射的引用

    virtual void setLevelData(const ValueMap& rValueMap); //定义一个虚函数，用于设置关卡数据，参数为一个值映射的引用

protected:

    virtual bool init(); //定义一个虚函数，用于初始化对象，返回一个布尔值

    virtual void registerLevelDataChangeEvent(); //定义一个虚函数，用于注册关卡数据变化事件，添加一个观察者

    virtual void levelDataChange(Ref* pData); //定义一个虚函数，用于在关卡数据变化时执行，参数为一个引用类型的指针

private:

    ValueMap _levelData; //定义一个值映射类型的成员变量，用于存储关卡数据

    std::string _sLevelDataFileName = ""; //定义一个字符串类型的成员变量，用于存储关卡数据文件的名称

private:

    LocalDataUtil() {} //定义一个私有的构造函数，用于创建对象，防止外部创建

    virtual ~LocalDataUtil(); //定义一个虚的析构函数，用于销毁对象，释放资源

    LocalDataUtil(const LocalDataUtil&) = delete; //删除拷贝构造函数，防止拷贝对象

    LocalDataUtil& operator=(const LocalDataUtil&) = delete; //删除赋值运算符，防止赋值对象



};

#endif /* defined(__CarrotFantasy__LocalDataUtil__) */ //结束条件编译
