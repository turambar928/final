
#include "LevelConfigUtil.h"
#include "external/tinyxml2/tinyxml2.h"
#include "CsvUtil.h"
#include "SceneManager.h"
using namespace tinyxml2;
// LevelConfigUtil类的静态实例
LevelConfigUtil* LevelConfigUtil::_gInstance;

// LevelConfigUtil构造函数
LevelConfigUtil::LevelConfigUtil()
{
}

// LevelConfigUtil析构函数
LevelConfigUtil::~LevelConfigUtil()
{
    // 释放_effectTowers的内存
    CC_SAFE_DELETE(_pEffectTowers);
}

// LevelConfigUtil初始化方法
bool LevelConfigUtil::init()
{
    // 返回值，默认为false
    bool bRet = false;

    do
    {
        // 创建一个新的字符串向量用于存储效果塔的配置
        _pEffectTowers = new std::vector<std::string>;

        // 初始化成功，将返回值设为true
        bRet = true;
    } while (0);

    // 返回初始化结果
    return bRet;
}


void LevelConfigUtil::loadLevelConfig() //定义一个函数，用于加载关卡配置
{
    _pEffectTowers->clear(); //清空影响塔的容器

    tinyxml2::XMLDocument tXmlDoc; //创建一个XML文档对象

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  //如果目标平台是安卓
    //auto sFileName = FileUtils::getInstance()->fullPathForFilename(LEVELCONFIGFILENAME); //获取关卡配置文件的完整路径（注释掉的代码）
    tinyxml2::XMLError pError; //创建一个XML错误对象
    std::string sFileName = LEVELCONFIGFILENAME; //将关卡配置文件名赋值给字符串变量
    ssize_t* temp = 0;    //创建一个指向大小类型的指针，初始化为0
    unsigned char* pBuffer = NULL; //创建一个指向无符号字符的指针，初始化为NULL
    pBuffer = FileUtils::sharedFileUtils()->getFileData(sFileName, "r", temp); //调用FileUtils的静态方法，以只读模式获取关卡配置文件的数据，并将其存储在pBuffer指向的内存中，同时将文件的大小赋值给temp指向的变量
    if (pBuffer) //如果pBuffer不为空，说明文件数据获取成功
    {
        pError = tXmlDoc.Parse((const char*)pBuffer); //将pBuffer指向的数据转换为常量字符指针，然后用tXmlDoc解析，将解析结果赋值给pError
    }
    else //否则，说明文件数据获取失败
    {
        CCLOG("[%d]%s %s error ", __LINE__, __func__, __FILE__); //打印错误信息，包括行号，函数名，文件名
        return;// nullptr; //返回空指针，结束函数
    }

    //if (tXmlDoc.LoadFile(sFileName.c_str()) != tinyxml2::XML_NO_ERROR) //如果用tXmlDoc加载文件名对应的文件，结果不等于XML无错误（注释掉的代码）
    //    CCLOG("[%d]%s %s error ", __LINE__, __func__, __FILE__); //打印错误信息，包括行号，函数名，文件名
    //else //否则，说明加载成功
    //    CCLOG("[%d]%s %s OK ", __LINE__, __func__, __FILE__); //打印成功信息，包括行号，函数名，文件名
#else //如果目标平台不是安卓
    auto sFileName = FileUtils::getInstance()->fullPathForFilename(LEVELCONFIGFILENAME); //获取关卡配置文件的完整路径

    auto tIndex = sFileName.find(LEVELCONFIGFILENAME); //在完整路径中查找关卡配置文件名的位置

    sFileName = sFileName.substr(0, tIndex); //截取完整路径中从开头到文件名位置的子字符串，作为新的文件路径

    //auto tfile = LEVELCONFIGFILENAME.substr(2, LEVELCONFIGFILENAME.size() - 2); //截取关卡配置文件名中从第二个字符到倒数第二个字符的子字符串（注释掉的代码）
    auto tfile = LEVELCONFIGFILENAME;//.substr(0, LEVELCONFIGFILENAME.size()); //将关卡配置文件名赋值给字符串变量

    CCLOG("[1]config %s  %s %s", LEVELCONFIGFILENAME.c_str(), sFileName.c_str(), ((std::string)tfile).c_str()); //打印配置信息，包括关卡配置文件名，文件路径，文件名
    sFileName = sFileName + tfile; //将文件路径和文件名拼接起来，作为新的完整路径
    CCLOG("[2]config %s  %s %s", LEVELCONFIGFILENAME.c_str(), sFileName.c_str(), ((std::string)tfile).c_str()); //打印配置信息，包括关卡配置文件名，完整路径，文件名

    tXmlDoc.LoadFile(sFileName.c_str()); //用tXmlDoc加载完整路径对应的文件
    //CCLOG("[%d]%s %s", __LINE__, __func__, __FILE__); //打印信息，包括行号，函数名，文件名（注释掉的代码）
#endif //结束条件编译

    auto pRoot = tXmlDoc.RootElement(); //获取XML文档的根元素

    auto pSceneManager = SceneManager::getInstance(); //获取场景管理器的实例

    auto pLevelElement = pRoot->FirstChildElement(StringUtils::format("%d_%02d", pSceneManager->getCurPageIndex() + 1, pSceneManager->getCurLevelIndex() + 1).c_str()); //根据场景管理器的当前页面索引和当前关卡索引，格式化字符串，然后在根元素中查找第一个匹配的子元素，作为关卡元素

    auto pElement = pLevelElement->FirstChildElement(); //获取关卡元素的第一个子元素

    while (pElement) //当子元素不为空时，循环执行以下操作
    {
        if (LEVELCONFIGTYPE[0] == pElement->Name()) //如果子元素的名称等于关卡配置类型的第一个元素，即"page"
            _iCurPageIndex = pElement->IntAttribute(LEVELCONFIGTYPE[0].c_str()); //将子元素的"page"属性的整数值赋值给当前页面索引
        if (LEVELCONFIGTYPE[1] == pElement->Name()) //如果子元素的名称等于关卡配置类型的第二个元素，即"level"
            _iCurLevelIndex = pElement->IntAttribute(LEVELCONFIGTYPE[1].c_str()); //将子元素的"level"属性的整数值赋值给当前关卡索引
        if (LEVELCONFIGTYPE[2] == pElement->Name()) //如果子元素的名称等于关卡配置类型的第三个元素，即"money"
            _iCurLevelMoney = pElement->IntAttribute(LEVELCONFIGTYPE[2].c_str()); //将子元素的"money"属性的整数值赋值给当前关卡金钱
        if (LEVELCONFIGTYPE[3] == pElement->Name()) //如果子元素的名称等于关卡配置类型的第四个元素，即"monsterBatchCount"
            _iMonsterBatchCount = pElement->IntAttribute(LEVELCONFIGTYPE[3].c_str()); //将子元素的"monsterBatchCount"属性的整数值赋值给怪物批次数量


        if (TOWERTYPE == pElement->Name()) //如果子元素的名称等于塔类型，即"tower"
        {
            auto pTower = pElement->FirstChildElement(); //获取子元素的第一个子元素，作为塔元素

            while (pTower) //当塔元素不为空时，循环执行以下操作
            {
                _pEffectTowers->push_back(pTower->Name()); //将塔元素的名称添加到影响塔的容器中
                pTower = pTower->NextSiblingElement(); //将塔元素指向下一个兄弟元素
            }
            return; //返回，结束函数
        }
        pElement = pElement->NextSiblingElement(); //将子元素指向下一个兄弟元素
    }
}

std::tuple<int, int, int, std::vector<std::string>> LevelConfigUtil::getLevelConfig()const //定义一个常量成员函数，用于获取关卡配置，返回一个元组，包含当前页面索引，当前关卡索引，怪物批次数量，和影响塔的名称列表
{
    return std::make_tuple(_iCurPageIndex, _iCurLevelIndex, _iMonsterBatchCount, *_pEffectTowers); //使用std::make_tuple函数，根据成员变量的值，创建并返回一个元组
}

std::vector<std::string> LevelConfigUtil::getCurLevelTowersInfo()const //定义一个常量成员函数，用于获取当前关卡的塔信息，返回一个字符串向量，包含影响塔的名称列表
{
    return *_pEffectTowers; //返回影响塔的名称列表的引用
}

int LevelConfigUtil::getCurLevelMonsterBatchCount()const //定义一个常量成员函数，用于获取当前关卡的怪物批次数量，返回一个整数
{
    return _iMonsterBatchCount; //返回怪物批次数量的值
}

int LevelConfigUtil::getCurLevelMoney()const //定义一个常量成员函数，用于获取当前关卡的金钱，返回一个整数
{
    return _iCurLevelMoney; //返回金钱的值
}

void LevelConfigUtil::buildLevelConfig() //定义一个成员函数，用于构建关卡配置，从CSV文件中读取数据，然后生成XML文件
{
    auto pCsvUtil = CsvUtil::getInstance(); //获取CsvUtil的实例，用于操作CSV文件
    pCsvUtil->addFileData(LEVELCSVFILE); //将关卡配置的CSV文件的数据添加到CsvUtil中

    auto tColumnRowCount = pCsvUtil->getFileRowColNum(LEVELCSVFILE); //获取关卡配置的CSV文件的行列数，返回一个元组

    auto tColumn = std::get<0>(tColumnRowCount); //从元组中获取列数
    auto tRow = std::get<1>(tColumnRowCount); //从元组中获取行数

    auto pXmldoc = new tinyxml2::XMLDocument; //创建一个XML文档对象，用于操作XML文件

    auto pLevelConfigRoot = pXmldoc->NewElement(LEVELCONFIGROOT.c_str()); //创建一个新的XML元素，作为关卡配置的根元素，名称为LEVELCONFIGROOT
    pXmldoc->LinkEndChild(pLevelConfigRoot); //将根元素链接到XML文档中

    for (int row = 1; row < tRow; ++row) //从第一行开始，遍历每一行，跳过第零行（表头）
    {

        auto tColumnCount = 0; //初始化列计数为0
        auto tThemeIndex = pCsvUtil->getInt(row, 0, LEVELCSVFILE); //从CSV文件中获取第row行第0列的整数值，作为主题索引
        auto tLevelIndex = pCsvUtil->getInt(row, 1, LEVELCSVFILE); //从CSV文件中获取第row行第1列的整数值，作为关卡索引

        auto pLevelElement = pXmldoc->NewElement(StringUtils::format("%d_%02d", tThemeIndex, tLevelIndex).c_str()); //创建一个新的XML元素，作为关卡元素，名称为主题索引和关卡索引的格式化字符串
        pLevelConfigRoot->LinkEndChild(pLevelElement); //将关卡元素链接到根元素中
        for (int column = 0; column < 4; ++column) //从第0列开始，遍历前四列，分别对应page, level, money, monsterBatchCount
        {
            auto pElement = pXmldoc->NewElement(LEVELCONFIGTYPE[column].c_str()); //创建一个新的XML元素，名称为LEVELCONFIGTYPE数组中的第column个元素
            auto tValue = pCsvUtil->getInt(row, column, LEVELCSVFILE); //从CSV文件中获取第row行第column列的整数值，作为元素的值
            pElement->SetAttribute(LEVELCONFIGTYPE[column].c_str(), StringUtils::format("%d", tValue).c_str()); //将元素的属性设置为LEVELCONFIGTYPE数组中的第column个元素，值为格式化后的整数值
            pLevelElement->LinkEndChild(pElement); //将元素链接到关卡元素中
            tColumnCount = column; //更新列计数为column
        }
        ++tColumnCount; //增加列计数
        auto pTowerElement = pXmldoc->NewElement(TOWERTYPE.c_str()); //创建一个新的XML元素，作为塔元素，名称为TOWERTYPE
        pLevelElement->LinkEndChild(pTowerElement); //将塔元素链接到关卡元素中
        for (; tColumnCount < tColumn; ++tColumnCount) //从第四列开始，遍历剩余的列，分别对应不同类型的塔
        {

            auto tValue = pCsvUtil->getInt(row, tColumnCount, LEVELCSVFILE); //从CSV文件中获取第row行第tColumnCount列的整数值，作为塔的值
            if (1 == tValue) //如果塔的值为1，表示该类型的塔在当前关卡中可用
            {
                auto pElement = pXmldoc->NewElement(LEVELCONFIGTYPE[tColumnCount].c_str()); //创建一个新的XML元素，名称为LEVELCONFIGTYPE数组中的第tColumnCount个元素，表示塔的类型
                pTowerElement->LinkEndChild(pElement); //将元素链接到塔元素中
            }
        }
    }

    pXmldoc->SaveFile((FileUtils::getInstance()->getWritablePath() + "LevelConfig.xml").c_str()); //将XML文档保存到文件中，文件名为LevelConfig.xml，路径为FileUtils的可写路径
    pCsvUtil->releaseFile(LEVELCSVFILE); //释放CsvUtil中的关卡配置的CSV文件的数据
    delete pXmldoc; //删除XML文档对象
}



