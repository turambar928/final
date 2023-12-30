#include "LevelSelectScene.h" //包含关卡选择场景的头文件
#include "LevelSelectLayer.h" //包含关卡选择层的头文件
#include "SceneManager.h" //包含场景管理器的头文件

/* 定义一个析构函数，用于销毁对象，释放资源 */
LevelSelectScene::~LevelSelectScene()
{
    CC_SAFE_RELEASE_NULL(_pLevelSelectLayer); //使用宏定义一个安全释放函数，参数为指向关卡选择层的指针，将其设为nullptr
    sourceManager(std::vector<std::string>{THEMESSOURCE[_iThemeIndex]}, false); //调用资源管理器的函数，参数为一个字符串向量，包含当前主题的资源名称，和一个布尔值，表示是否加载资源，这里为false，表示卸载资源

}

/* 定义一个初始化函数，用于创建对象，返回一个布尔值 */
bool LevelSelectScene::init()
{
    bool bRet = false; //定义一个布尔变量，用于存储返回值，初始值为false

    do
    {
        CC_BREAK_IF(!Scene::init()); //调用父类的初始化函数，如果失败，跳出循环
        _iThemeIndex = SceneManager::getInstance()->getCurPageIndex(); //获取场景管理器的实例，然后获取当前页面索引，赋值给成员变量
        sourceManager(std::vector<std::string>{THEMESSOURCE[_iThemeIndex]}, true); //调用资源管理器的函数，参数为一个字符串向量，包含当前主题的资源名称，和一个布尔值，表示是否加载资源，这里为true，表示加载资源

        _pLevelSelectLayer = LevelSelectLayer::create(); //调用关卡选择层的创建函数，返回一个对象，赋值给指向关卡选择层的指针
        _pLevelSelectLayer->retain(); //调用关卡选择层的保留函数，增加其引用计数，防止被自动释放
        bRet = true; //将返回值设为true
    } while (0); //循环条件为0，表示只执行一次

    return bRet; //返回返回值
}

/* 定义一个进入函数，用于在场景进入时执行 */
void LevelSelectScene::onEnter()
{
    Scene::onEnter(); //调用父类的进入函数
    addChild(_pLevelSelectLayer); //将关卡选择层添加到当前场景中
}

