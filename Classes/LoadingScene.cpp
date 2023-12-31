#include "LoadingScene.h" //包含加载场景的头文件
#include "GameScene.h" //包含游戏场景的头文件
#include "SoundUtil.h" //包含声音工具的头文件

/* 定义一个初始化函数，用于创建对象，返回一个布尔值 */
bool LoadingScene::init()
{
    bool bRet = false; //定义一个布尔变量，用于存储返回值，初始值为false
    do
    {
        CC_BREAK_IF(!Scene::init()); //调用父类的初始化函数，如果失败，跳出循环

        auto pBg = Sprite::create(LOADINGSOURCE); //创建一个精灵，使用LOADINGSOURCE宏定义的图片
        pBg->setPosition(VisibleRect::center()); //将精灵的位置设置为可见矩形的中心
        addChild(pBg); //将精灵添加到当前场景中

        bRet = true; //将返回值设为true
    } while (0); //循环条件为0，表示只执行一次
    return bRet; //返回返回值
}

/* 定义一个进入函数，用于在场景进入时执行 */
void LoadingScene::onEnter()
{
    Scene::onEnter(); //调用父类的进入函数
    SoundUtil::getInstance()->stopBackGroundSound(); //获取声音工具的实例，然后停止背景音乐
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(LoadingScene::sourceLoadCallBack), "loadFinish", nullptr); //使用通知中心，添加一个观察者，参数为当前对象，回调函数，通知名称，和用户数据
    _pGameScene = GameScene::create(); //调用游戏场景的创建函数，返回一个对象，赋值给指向游戏场景的指针
    _pGameScene->retain(); //调用游戏场景的保留函数，增加其引用计数，防止被自动释放
}

/* 定义一个退出函数，用于在场景退出时执行 */
void LoadingScene::onExit()
{
    NOTIFY->removeAllObservers(this); //使用通知中心，移除所有关于当前对象的观察者
    CC_SAFE_RELEASE_NULL(_pGameScene); //使用宏定义一个安全释放函数，参数为指向游戏场景的指针，将其设为nullptr
    Scene::onExit(); //调用父类的退出函数
}

/* 定义一个资源加载回调函数，用于在资源加载完成时执行，参数为一个引用类型的指针 */
void LoadingScene::sourceLoadCallBack(Ref* pData)
{
    auto pTransScene = TransitionFade::create(0.2f, dynamic_cast<Scene*>(pData)); //创建一个过渡场景，使用淡入淡出的效果，参数为持续时间和目标场景，目标场景为参数的强制类型转换
    Director::getInstance()->replaceScene(pTransScene); //获取导演的实例，然后替换当前场景为过渡场景
}
