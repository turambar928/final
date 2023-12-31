#ifndef __CarrotFantasy__LevelConfigUtil__ //如果没有定义__CarrotFantasy__LevelConfigUtil__宏，防止头文件重复包含
#define __CarrotFantasy__LevelConfigUtil__ //定义__CarrotFantasy__LevelConfigUtil__宏

#include "PublicDefine.h" //包含公共定义的头文件

class LevelConfigUtil :public Ref //定义一个类，继承自Ref类，用于管理关卡配置
{
public:

    CREATE_INSTANCE_FUNC(LevelConfigUtil); //使用宏定义一个创建实例的静态函数，用于获取单例对象

    DESTROY_INSTANCE_FUNC(); //使用宏定义一个销毁实例的静态函数，用于释放单例对象

    virtual void loadLevelConfig(); //定义一个虚函数，用于加载关卡配置，从XML文件中读取数据

    virtual std::tuple<int, int, int, std::vector<std::string>> getLevelConfig()const; //定义一个常量虚函数，用于获取关卡配置，返回一个元组，包含当前页面索引，当前关卡索引，怪物批次数量，和影响塔的名称列表

    virtual std::vector<std::string> getCurLevelTowersInfo()const; //定义一个常量虚函数，用于获取当前关卡的塔信息，返回一个字符串向量，包含影响塔的名称列表

    virtual int getCurLevelMonsterBatchCount()const; //定义一个常量虚函数，用于获取当前关卡的怪物批次数量，返回一个整数

    virtual void buildLevelConfig(); //定义一个虚函数，用于构建关卡配置，从CSV文件中读取数据，然后生成XML文件

    virtual int getCurLevelMoney()const; //定义一个常量虚函数，用于获取当前关卡的金钱，返回一个整数

protected:

    virtual bool init(); //定义一个虚函数，用于初始化对象，返回一个布尔值

protected:

    int _iCurPageIndex = 0; //定义一个整数类型的成员变量，用于存储当前页面索引，初始值为0

    int _iCurLevelIndex = 0; //定义一个整数类型的成员变量，用于存储当前关卡索引，初始值为0

    int _iCurLevelMoney = 0; //定义一个整数类型的成员变量，用于存储当前关卡金钱，初始值为0

    int _iMonsterBatchCount = 0; //定义一个整数类型的成员变量，用于存储怪物批次数量，初始值为0

    std::vector<std::string>* _pEffectTowers = nullptr; //定义一个指向字符串向量的指针，用于存储影响塔的名称列表，初始值为nullptr

private:

    LevelConfigUtil(); //定义一个私有的构造函数，用于创建对象，实现单例模式

    virtual ~LevelConfigUtil(); //定义一个虚的析构函数，用于销毁对象，释放资源

    LevelConfigUtil(const LevelConfigUtil&) = delete; //删除拷贝构造函数，防止对象被复制

    LevelConfigUtil& operator=(const LevelConfigUtil&) = delete; //删除赋值运算符，防止对象被赋值
};

#endif /* defined(__CarrotFantasy__LevelConfigUtil__) */ //结束条件编译
