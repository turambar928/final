#include "LocalDataUtil.h" //包含本地数据工具的头文件

LocalDataUtil* LocalDataUtil::_gInstance; //定义一个指向本地数据工具的指针，表示本地数据工具的单例

/* 定义一个初始化函数，用于创建对象，返回一个布尔值 */
bool LocalDataUtil::init()
{
    bool bRet = false; //定义一个布尔变量，用于存储返回值，初始值为false
    do
    {
        auto pFileUtil = FileUtils::getInstance(); //获取文件工具的实例，赋值给一个指针变量
        _sLevelDataFileName = pFileUtil->getWritablePath() + DATAFILE; //获取可写路径，拼接数据文件的名称，赋值给一个字符串变量，表示关卡数据文件的名称
        _levelData = pFileUtil->getValueMapFromFile(_sLevelDataFileName); //从关卡数据文件中获取值映射，赋值给一个值映射变量，表示关卡数据

        registerLevelDataChangeEvent(); //调用注册关卡数据变化事件的函数，用于监听关卡数据的变化
        bRet = true; //将返回值设为true
    } while (0); //循环条件为0，表示只执行一次

    return  bRet; //返回返回值
}

/* 定义一个析构函数，用于销毁对象，释放资源 */
LocalDataUtil::~LocalDataUtil()
{
    NOTIFY->removeAllObservers(this); //使用通知中心，移除所有关于当前对象的观察者
}

/* 定义一个获取关卡数据的函数，返回一个值映射的引用 */
ValueMap& LocalDataUtil::getLevelData()
{
    return _levelData; //返回关卡数据
}

/* 定义一个设置关卡数据的函数，参数为一个值映射的引用 */
void LocalDataUtil::setLevelData(const ValueMap& rValueMap)
{
    _levelData = rValueMap; //将关卡数据赋值为参数的值映射
    FileUtils::getInstance()->writeToFile(_levelData, _sLevelDataFileName); //获取文件工具的实例，然后将关卡数据写入到关卡数据文件中
}

/* 定义一个注册关卡数据变化事件的函数，用于添加一个观察者，监听关卡数据的变化 */
void LocalDataUtil::registerLevelDataChangeEvent()
{
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(LocalDataUtil::levelDataChange), LEVELDATACHANGE, nullptr); //使用通知中心，添加一个观察者，参数为当前对象，回调函数，通知名称，和用户数据
}

/* 定义一个关卡数据变化的回调函数，用于在关卡数据变化时执行，参数为一个引用类型的指针 */
void LocalDataUtil::levelDataChange(Ref* pData)
{
    auto tLevelData = *(reinterpret_cast<std::tuple<int, int, int, int>*>(pData)); //将参数的指针强制类型转换为一个指向元组的指针，然后解引用，赋值给一个元组变量，表示关卡数据
    auto tLevelType = std::get<0>(tLevelData); //从元组中获取第0个元素，赋值给一个整数变量，表示关卡类型
    auto tData = std::get<1>(tLevelData); //从元组中获取第1个元素，赋值给一个整数变量，表示关卡数据
    auto tThemeIndex = std::get<2>(tLevelData); //从元组中获取第2个元素，赋值给一个整数变量，表示主题索引
    auto tLevelIndex = std::get<3>(tLevelData); //从元组中获取第3个元素，赋值给一个整数变量，表示关卡索引
    auto tLevelKey = StringUtils::format(LEVELKEY, tThemeIndex, tLevelIndex); //使用字符串工具类，格式化字符串，拼接主题索引和关卡索引，赋值给一个字符串变量，表示关卡键
    auto tCurLevelData = _levelData[tLevelKey].asInt(); //从关卡数据中根据关卡键获取值，转换为整数，赋值给一个整数变量，表示当前关卡数据
    auto tCarrotType = tCurLevelData / 10; //将当前关卡数据除以10，取商，赋值给一个整数变量，表示胡萝卜类型
    auto tBarrierCleanFlag = tCurLevelData % 10; //将当前关卡数据除以10，取余，赋值给一个整数变量，表示障碍物清除标志

    if (!tLevelType) //如果关卡类型为0，表示胡萝卜类型
    {
        if (tCarrotType < tData) _levelData[tLevelKey] = StringUtils::format("%d%d", tData, tBarrierCleanFlag); //如果胡萝卜类型小于关卡数据，表示胡萝卜类型升级，将关卡数据赋值为关卡数据和障碍物清除标志的拼接
    }
    else //如果关卡类型为1，表示障碍物清除标志
    {
        _levelData[tLevelKey] = StringUtils::format("%d%d", tCarrotType, tData); //将关卡数据赋值为胡萝卜类型和关卡数据的拼接
    }

    FileUtils::getInstance()->writeToFile(_levelData, _sLevelDataFileName); //获取文件工具的实例，然后将关卡数据写入到关卡数据文件中
}

