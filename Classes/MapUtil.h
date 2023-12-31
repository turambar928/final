#ifndef __CarrotFantasy__MapUtil__ //如果没有定义__CarrotFantasy__MapUtil__宏，防止头文件重复包含
#define __CarrotFantasy__MapUtil__ //定义__CarrotFantasy__MapUtil__宏

#include "PublicDefine.h" //包含公共定义的头文件

class MapUtil : public Ref //定义一个类，继承自Ref类，用于管理地图数据
{
public:

    CREATE_INSTANCE_FUNC(MapUtil); //使用宏定义一个创建实例的函数，用于获取地图工具的单例

    DESTROY_INSTANCE_FUNC(); //使用宏定义一个销毁实例的函数，用于释放地图工具的单例

    virtual void setCurrentLevelTiledMap(TMXTiledMap* pTiledMap); //定义一个虚函数，用于设置当前关卡的瓦片地图，参数为一个指向瓦片地图的指针

    virtual std::vector<Vec2> getMovePoses(); //定义一个虚函数，用于获取移动位置，返回一个向量的值，每个元素为一个向量，表示移动的位置

    virtual std::vector<std::pair<std::string, Rect>> getBarrierPoses(); //定义一个虚函数，用于获取障碍物位置，返回一个字符串和矩形的对的向量的值，每个元素为一个字符串和矩形的对，表示障碍物的名称和位置

    virtual std::vector<Rect> getEffectTowerPoses(); //定义一个虚函数，用于获取效果塔位置，返回一个矩形向量的值，每个元素为一个矩形，表示效果塔的位置

    virtual void removeBarrierRect(const Vec2& rPos); //定义一个虚函数，用于移除障碍物矩形，参数为一个向量的引用，表示障碍物的位置

protected:

    virtual bool init(); //定义一个虚函数，用于初始化对象，返回一个布尔值

    virtual void clearMap(); //定义一个虚函数，用于清除地图数据，释放资源

    virtual void rectTransVec(const Rect& rRect); //定义一个虚函数，用于将矩形中的每个网格的位置添加到效果塔矩形向量中，参数为一个矩形的引用

private:

    TMXTiledMap* _pTildeMap = nullptr; //定义一个指向瓦片地图的指针，用于存储当前关卡的瓦片地图

    std::map<int, Vec2>* _pMovePosMap = nullptr; //定义一个指向移动位置映射的指针，用于存储移动的索引和位置

    std::vector<std::pair<std::string, Rect>>* _pBarrierPosMap = nullptr; //定义一个指向障碍物位置向量的指针，用于存储障碍物的名称和位置

    std::vector<Rect>* _pEffectTowerRectVec = nullptr; //定义一个指向效果塔矩形向量的指针，用于存储效果塔的位置

private:

    Size _gridSize; //定义一个大小类型的成员变量，用于存储网格大小

    Size _mapSize; //定义一个大小类型的成员变量，用于存储地图大小

private:

    virtual ~MapUtil(); //定义一个虚的析构函数，用于销毁对象，释放资源

};


#endif /* defined(__CarrotFantasy__MapUtil__) */ //结束条件编译
