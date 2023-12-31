
#include "MapUtil.h" //包含地图工具的头文件

MapUtil* MapUtil::_gInstance; //定义一个指向地图工具的指针，表示地图工具的单例

/* 定义一个析构函数，用于销毁对象，释放资源 */
MapUtil::~MapUtil()
{
    CC_SAFE_DELETE(_pMovePosMap); //使用宏定义一个安全删除函数，参数为指向移动位置映射的指针，释放内存
    CC_SAFE_DELETE(_pBarrierPosMap); //使用宏定义一个安全删除函数，参数为指向障碍物位置向量的指针，释放内存
    CC_SAFE_DELETE(_pEffectTowerRectVec); //使用宏定义一个安全删除函数，参数为指向效果塔矩形向量的指针，释放内存
    CC_SAFE_RELEASE_NULL(_pTildeMap); //使用宏定义一个安全释放函数，参数为指向瓦片地图的指针，将其设为nullptr
}

/* 定义一个初始化函数，用于创建对象，返回一个布尔值 */
bool MapUtil::init()
{
    bool bRet = false; //定义一个布尔变量，用于存储返回值，初始值为false

    do
    {
        _pBarrierPosMap = new std::vector<std::pair<std::string, Rect>>; //使用new运算符，创建一个指向障碍物位置向量的指针，每个元素为一个字符串和矩形的对，表示障碍物的名称和位置
        _pEffectTowerRectVec = new std::vector<Rect>; //使用new运算符，创建一个指向效果塔矩形向量的指针，每个元素为一个矩形，表示效果塔的位置
        _pMovePosMap = new std::map<int, Vec2>; //使用new运算符，创建一个指向移动位置映射的指针，每个元素为一个整数和向量的对，表示移动的索引和位置

        bRet = true; //将返回值设为true
    } while (0); //循环条件为0，表示只执行一次

    return bRet; //返回返回值
}

/* 定义一个设置当前关卡瓦片地图的函数，参数为一个指向瓦片地图的指针 */
void MapUtil::setCurrentLevelTiledMap(cocos2d::TMXTiledMap* pTiledMap)
{
    clearMap(); //调用清除地图的函数，清除之前的地图数据
    CC_SAFE_RELEASE_NULL(_pTildeMap); //使用宏定义一个安全释放函数，参数为指向瓦片地图的指针，将其设为nullptr
    CC_SAFE_RETAIN(pTiledMap); //使用宏定义一个安全保留函数，参数为指向瓦片地图的指针，增加其引用计数，防止被自动释放
    _pTildeMap = pTiledMap; //将成员变量赋值为参数的指针
    _gridSize = _pTildeMap->getTileSize(); //调用瓦片地图的获取瓦片大小的函数，赋值给一个大小变量，表示网格大小
    _mapSize = Size(_pTildeMap->getMapSize().width * _gridSize.width, _pTildeMap->getMapSize().height * _gridSize.height); //计算地图的大小，赋值给一个大小变量，表示地图大小

    auto tMapGroup = _pTildeMap->getObjectGroup("PATH"); //调用瓦片地图的获取对象组的函数，参数为"PATH"，赋值给一个指针变量，表示路径对象组
    auto tObjs = tMapGroup->getObjects(); //调用对象组的获取对象的函数，赋值给一个值向量变量，表示对象的集合

    for (auto& iter : tObjs) //遍历对象的集合，每个元素为一个值，表示对象的属性，使用引用避免拷贝
    {
        auto tObjMap = iter.asValueMap(); //将对象的值转换为值映射，赋值给一个值映射变量，表示对象的属性映射
        auto tObjName = tObjMap.at("name").asString(); //从对象的属性映射中根据"name"获取值，转换为字符串，赋值给一个字符串变量，表示对象的名称
        auto tX = tObjMap.at("x").asFloat(); //从对象的属性映射中根据"x"获取值，转换为浮点数，赋值给一个浮点变量，表示对象的横坐标
        auto tY = tObjMap.at("y").asFloat(); //从对象的属性映射中根据"y"获取值，转换为浮点数，赋值给一个浮点变量，表示对象的纵坐标
        auto tPos = Vec2(tX, tY); //创建一个向量，参数为对象的横坐标和纵坐标，赋值给一个向量变量，表示对象的位置
        auto tWidth = tObjMap.at("width").asFloat(); //从对象的属性映射中根据"width"获取值，转换为浮点数，赋值给一个浮点变量，表示对象的宽度
        auto tHeight = tObjMap.at("height").asFloat(); //从对象的属性映射中根据"height"获取值，转换为浮点数，赋值给一个浮点变量，表示对象的高度
        auto tRect = Rect(tX, tY, tWidth, tHeight); //创建一个矩形，参数为对象的横坐标，纵坐标，宽度，高度，赋值给一个矩形变量，表示对象的矩形

        if (tObjName.find("PT") != std::string::npos) //如果对象的名称中包含"PT"，表示移动点
        {
            _pMovePosMap->insert(std::make_pair(atoi(tObjName.substr(2).c_str()), tPos)); //将对象的名称去掉前两个字符，转换为整数，作为键，对象的位置作为值，插入到移动位置映射中
            continue; //跳过本次循环，继续下一次循环
        }
        if (tObjName.find("Obj") != std::string::npos) //如果对象的名称中包含"Obj"，表示障碍物
        {
            rectTransVec(tRect); //调用矩形转换向量的函数，参数为对象的矩形，将矩形中的每个网格的位置添加到障碍物位置向量中
            continue; //跳过本次循环，继续下一次循环
        }

        auto tIndex = tObjName.find("Ob"); //在对象的名称中查找"Ob"，返回一个位置变量，表示"Ob"的位置
        if (std::string::npos != tIndex) //如果位置不等于无效值，表示找到了"Ob"
        {
            _pBarrierPosMap->push_back(std::make_pair(tObjName.substr(0, tIndex + 2), tRect)); //将对象的名称截取前tIndex+2个字符，作为键，对象的矩形作为值，添加到障碍物位置向量中
            continue; //跳过本次循环，继续下一次循环
        }

        _pEffectTowerRectVec->push_back(tRect); //将对象的矩形添加到效果塔矩形向量中
    }
}
void MapUtil::clearMap()
{
    _pEffectTowerRectVec->clear(); //调用效果塔矩形向量的清除函数，清除所有元素
    _pBarrierPosMap->clear(); //调用障碍物位置向量的清除函数，清除所有元素
    _pMovePosMap->clear(); //调用移动位置映射的清除函数，清除所有元素
}

/* 定义一个矩形转换向量的函数，用于将矩形中的每个网格的位置添加到效果塔矩形向量中，参数为一个矩形的引用 */
void MapUtil::rectTransVec(const Rect& rRect)
{
    auto tWidth = rRect.size.width; //获取矩形的宽度，赋值给一个浮点变量
    auto tHeight = rRect.size.height; //获取矩形的高度，赋值给一个浮点变量
    auto tX = rRect.origin.x; //获取矩形的横坐标，赋值给一个浮点变量
    auto tY = rRect.origin.y; //获取矩形的纵坐标，赋值给一个浮点变量
    if (TILESIZE == tWidth && TILESIZE == tHeight) //如果矩形的宽度和高度都等于瓦片大小，表示矩形只包含一个网格
    {
        _pEffectTowerRectVec->push_back(Rect(tX, tY, _gridSize.width, _gridSize.height)); //将矩形的横坐标，纵坐标，网格宽度，网格高度，创建一个矩形，添加到效果塔矩形向量中
        return; //返回，结束函数
    }
    if (tWidth > TILESIZE && tHeight > TILESIZE) //如果矩形的宽度和高度都大于瓦片大小，表示矩形包含多个网格
    {
        for (int i = 0; i < tWidth / TILESIZE; ++i) //遍历矩形的宽度，每次增加一个瓦片大小
        {
            for (int j = 0; j < tHeight / TILESIZE; ++j) //遍历矩形的高度，每次增加一个瓦片大小
            {
                _pEffectTowerRectVec->push_back(Rect(tX + TILESIZE * i, tY + TILESIZE * j, TILESIZE, TILESIZE)); //将矩形的横坐标加上瓦片大小乘以i，纵坐标加上瓦片大小乘以j，瓦片大小，瓦片大小，创建一个矩形，添加到效果塔矩形向量中
            }
        }
        return; //返回，结束函数
    }

    if (tWidth > TILESIZE) //如果矩形的宽度大于瓦片大小，表示矩形包含一行多列的网格
    {
        for (int i = 0; i < tWidth / TILESIZE; ++i) //遍历矩形的宽度，每次增加一个瓦片大小
        {
            _pEffectTowerRectVec->push_back(Rect(tX + i * TILESIZE, tY, _gridSize.width, _gridSize.height)); //将矩形的横坐标加上瓦片大小乘以i，纵坐标，网格宽度，网格高度，创建一个矩形，添加到效果塔矩形向量中
        }
    }

    if (tHeight > TILESIZE) //如果矩形的高度大于瓦片大小，表示矩形包含一列多行的网格
    {
        for (int i = 0; i < tHeight / TILESIZE; ++i) //遍历矩形的高度，每次增加一个瓦片大小
        {
            _pEffectTowerRectVec->push_back(Rect(tX, tY + i * TILESIZE, _gridSize.width, _gridSize.height)); //将矩形的横坐标，纵坐标加上瓦片大小乘以i，网格宽度，网格高度，创建一个矩形，添加到效果塔矩形向量中
        }
    }
}

/* 定义一个获取移动位置的函数，返回一个向量的值，每个元素为一个向量，表示移动的位置 */
std::vector<Vec2> MapUtil::getMovePoses()
{
    std::vector<Vec2> tRetMovePosVec; //定义一个向量变量，用于存储移动位置的向量
    for (auto& iter : *_pMovePosMap) //遍历移动位置映射，每个元素为一个整数和向量的对，表示移动的索引和位置，使用引用避免拷贝
        tRetMovePosVec.push_back(iter.second); //将移动位置映射中的值，即移动的位置，添加到移动位置的向量中

    return tRetMovePosVec; //返回移动位置的向量
}
/* 定义一个获取效果塔位置的函数，返回一个矩形向量的值，每个元素为一个矩形，表示效果塔的位置 */
std::vector<Rect> MapUtil::getEffectTowerPoses()
{
    return *_pEffectTowerRectVec; //返回效果塔矩形向量的值
}

/* 定义一个获取障碍物位置的函数，返回一个字符串和矩形的对的向量的值，每个元素为一个字符串和矩形的对，表示障碍物的名称和位置 */
std::vector<std::pair<std::string, Rect>> MapUtil::getBarrierPoses()
{
    return *_pBarrierPosMap; //返回障碍物位置向量的值
}

/* 定义一个移除障碍物矩形的函数，用于在障碍物被消除时，从障碍物位置向量中移除对应的矩形，参数为一个向量的引用，表示障碍物的位置 */
void MapUtil::removeBarrierRect(const Vec2& rPos)
{
    for (auto barrierIter = _pBarrierPosMap->begin(); barrierIter != _pBarrierPosMap->end(); ++barrierIter) //遍历障碍物位置向量，每个元素为一个字符串和矩形的对，表示障碍物的名称和位置，使用迭代器方便删除
    {
        auto tBarrier = *barrierIter; //解引用迭代器，赋值给一个字符串和矩形的对变量，表示当前的障碍物
        if (tBarrier.second.containsPoint(rPos)) //如果障碍物的矩形包含参数的位置，表示找到了对应的障碍物
        {
            rectTransVec(tBarrier.second); //调用矩形转换向量的函数，参数为障碍物的矩形，将矩形中的每个网格的位置添加到效果塔矩形向量中
            _pBarrierPosMap->erase(barrierIter); //从障碍物位置向量中删除迭代器指向的元素
            break; //跳出循环，结束函数
        }
    }
}






