#include "AppDelegate.h"
#include "SceneManager.h"
#include "CsvUtil.h"
#include "Config.h"
#include "GameScene.h"
#include "SoundUtil.h"
USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SceneManager::destroyInstance();//销毁场景管理器的单例对象，释放场景相关的内存。
    Config::getInstance()->saveSoundConfig();//保存声音配置到本地文件中。
    Config::destroyInstance();//销毁配置管理器的单例对象，释放配置相关的内存。
    SoundUtil::destroyInstance();//销毁声音工具类的单例对象，释放声音相关的内存。
    unLoadSource();//释放游戏所占用的精灵帧、CSV 文件等资源。
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();//获取一个 Director 对象的单例，它是 Cocos2d-x 的核心类，负责管理场景、动画、事件等。
    auto glview = director->getOpenGLView();//获取一个 GLView 对象，它是一个 OpenGL 视图，用于渲染游戏画面。
    if(!glview)
    {
        glview = GLViewImpl::create("My Game");//创建一个 GLViewImpl 对象，它是 GLView 的具体实现类，传入一个字符串参数作为游戏窗口的标题。
        director->setOpenGLView(glview);//将创建好的 GLViewImpl 对象设置给 Director 对象，让它管理游戏窗口。
    }
    glview->setDesignResolutionSize(960, 640, ResolutionPolicy::EXACT_FIT);//设置游戏窗口的设计分辨率为 960x640 像素，并使用 EXACT_FIT 策略，即强制拉伸游戏画面以适应不同的屏幕尺寸。


    
    director->setAnimationInterval(1.0 / 60);//设置游戏的动画间隔为 1/60 秒，即每秒 60 帧，这是一般游戏的标准帧率。
    preLoadSource();//调用一个自定义的函数，用于预加载游戏所需的资源，比如图片、音乐、字体等，这样可以提高游戏的运行效率和用户体验。
    Config::getInstance()->setSoundConfig();//获取一个 Config 对象的单例，它是一个自定义的类，用于管理游戏的配置信息，然后调用它的 setSoundConfig 方法，用于设置游戏的声音配置，比如音量、音效、背景音乐等。

    SceneManager::getInstance()->initWelComeScene();//获取一个 SceneManager 对象的单例，它是一个自定义的类，用于管理游戏的场景切换，然后调用它的 initWelComeScene 方法，用于初始化游戏的欢迎场景，比如显示游戏的标题、菜单、按钮等。

    return true;
}


void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    //调用 Director 对象的 stopAnimation 方法，用于暂停游戏的动画渲染，以节省资源和电量。
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();//调用 Director 对象的 startAnimation 方法，用于恢复游戏的动画渲染，以继续游戏的运行。
    auto pCurScene = Director::getInstance()->getRunningScene();
    if ((pCurScene != NULL) && pCurScene->getName() == "GameScene")
    {
        auto pGameScene = dynamic_cast<GameScene*>(pCurScene);//显示倒计时或者游戏结束的界面的
        if(!pGameScene->getChildByName("CoundDown") && !pGameScene->getChildByName("GameEnd"))
            dynamic_cast<GameScene*>(pCurScene)->clickChooseItem();
    }
   
}

void AppDelegate::preLoadSource()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Themes/scene/mainscene1-hd.plist", "Themes/scene/mainscene1-hd.png");//获取一个 SpriteFrameCache 对象的单例
    auto pCsvUtil = CsvUtil::getInstance();//获取一个 CsvUtil 对象的单例,读取和解析 CSV 文件
    pCsvUtil->addFileData(BARRIERCSVFILE);//调用 CsvUtil 对象的 addFileData 方法，用于从指定的 CSV 文件中读取数据，并将其存储在内存中
    pCsvUtil->addFileData(TOWERCSVFILE);
    pCsvUtil->addFileData(MONSTERCSVFILE);
    pCsvUtil->addFileData(BULLETCSVFILE);
    pCsvUtil->addFileData(LEVELCSVFILE);
}


void AppDelegate::unLoadSource()
{
    SpriteFrameCache::getInstance()->removeSpriteFrames();//清除缓存中的所有精灵帧，释放内存空间。
    CsvUtil::destroyInstance();//销毁 CsvUtil 对象的单例
}






