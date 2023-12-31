
#include "PauseLayer.h"
#include "SceneManager.h"
#include "SharedMenu.h"
#include "SoundUtil.h"
#include "PublicSourceDefine.h"
#include "GameManager.h"

bool PauseLayer::init()
{
    bool bRet = false; // 定义一个布尔变量，用于返回函数是否成功初始化

    do
    {
        CC_BREAK_IF(!Layer::init()); // 如果父类 Layer 的 init 方法失败，就跳出循环

        auto pBlackLayer = LayerColor::create(Color4B(0, 0, 0, 170)); // 创建一个半透明的黑色层

        addChild(pBlackLayer); // 将黑色层添加为子节点

        createMenu(); // 调用自定义的 createMenu 方法，创建一个菜单

        closeTouchEvent(); // 调用自定义的 closeTouchEvent 方法，关闭触摸事件

        bRet = true; // 将返回值设为 true，表示初始化成功
    } while (0); // 这是一个只执行一次的循环，用于方便跳出

    return bRet; // 返回函数是否成功初始化

} // 函数结束

void PauseLayer::createMenu()
{
    auto pMenuBg = Sprite::createWithSpriteFrameName("menu_bg.png"); // 创建一个精灵，用于显示菜单的背景图片
    pMenuBg->setPosition(VisibleRect::center()); // 设置精灵的位置为屏幕中心
    addChild(pMenuBg); // 将精灵添加为子节点

    MenuItemSprite* pBtnResume = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("menu_resume_normal_CN.png"), // 创建一个精灵，用于显示继续按钮的正常状态图片
        Sprite::createWithSpriteFrameName("menu_resume_pressed_CN.png"), // 创建一个精灵，用于显示继续按钮的按下状态图片
        [this](Ref* pSender) // 创建一个回调函数，用于处理继续按钮的点击事件
    {
        _funcFlagPauseLayerIsClose(); // 调用自定义的 _funcFlagPauseLayerIsClose 方法，设置暂停层关闭的标志
        removeFromParentAndCleanup(true); // 将暂停层从父节点移除并清理
    }
    );
    pBtnResume->setPosition(Vec2(481, 417)); // 设置继续按钮的位置
    // 以下代码与上面类似，只是创建了重启按钮和选择关卡按钮，并设置了不同的位置和回调函数
    MenuItemSprite* pBtnRstart = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("menu_restart_normal_CN.png"),
        Sprite::createWithSpriteFrameName("menu_restart_pressed_CN.png"),
        [this](Ref* pSender)
    {
        auto enGameScene = std::make_tuple(en_GameScene, SceneManager::getInstance()->getCurLevelIndex()); // 创建一个元组，用于存储游戏场景的类型和当前关卡的索引
        NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enGameScene)); // 发送一个通知，用于切换场景

    }
    );
    pBtnRstart->setPosition(Vec2(481, 322));

    MenuItemSprite* pBtnSelectLevel = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("menu_quit_normal_CN.png"),
        Sprite::createWithSpriteFrameName("menu_quit_pressed_CN.png"),
        [this](Ref* pSender)
    {
        auto enLevelSelectScene = std::make_tuple(en_LevelSelectScene, SceneManager::getInstance()->getCurPageIndex()); // 创建一个元组，用于存储关卡选择场景的类型和当前页面的索引
        NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enLevelSelectScene)); // 发送一个通知，用于切换场景

    }
    );
    pBtnSelectLevel->setPosition(Vec2(481, 227));

    Menu* pMenu = Menu::create(pBtnResume, pBtnRstart, pBtnSelectLevel, nullptr); // 创建一个菜单，用于容纳三个按钮
    pMenu->setPosition(Vec2::ZERO); // 设置菜单的位置为原点
    addChild(pMenu, 1); // 将菜单添加为子节点，设置其 z 轴顺序为 1

} // 函数结束

//创建一个共享菜单的方法
void PauseLayer::createSharedMenu()
{
    //将一个共享菜单的实例添加为子节点，层级为1
    addChild(SharedMenu::create(), 1);
}

//设置一个函数标志，表示暂停层是否关闭的方法
void PauseLayer::setFuncFlagPauseLayerIsClose(const std::function<void()>& rFuncFlagPauseLayerIsClose)
{
    //将传入的函数赋值给成员变量_funcFlagPauseLayerIsClose
    _funcFlagPauseLayerIsClose = rFuncFlagPauseLayerIsClose;
}


//关闭触摸事件的方法
void PauseLayer::closeTouchEvent()
{
    //创建一个单点触摸监听器
    auto pListener = EventListenerTouchOneByOne::create();

    //设置触摸开始时的回调函数，返回true表示消费该事件
    pListener->onTouchBegan = [](Touch* pTouch, Event* pEvent)
    {
        return true;
    };
    //设置是否吞噬触摸事件，防止事件传递给下层节点
    pListener->setSwallowTouches(true);
    //将监听器添加到事件分发器中，与当前节点绑定
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pListener, this);
}

//进入暂停层时的方法
void PauseLayer::onEnter()
{
    //调用父类的onEnter方法
    Layer::onEnter();
    //暂停游戏的主循环
    Director::getInstance()->pause();
}

//退出暂停层时的方法
void PauseLayer::onExit()
{
    //如果游戏管理器的暂停状态为false，恢复游戏的主循环
    if (!GameManager::getInstance()->getIsPause()) Director::getInstance()->resume();
    //调用父类的onExit方法
    Layer::onExit();
}






