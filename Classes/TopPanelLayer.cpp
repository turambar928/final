#include "TopPanelLayer.h"
#include "OptionLayer.h"
#include "DesignLayer.h"
#include "DataCollectLayer.h"
#include "SoundUtil.h"
#include "PublicSourceDefine.h"

TopPanelLayer::~TopPanelLayer()
{
    // 安全释放多功能图层实例
    CC_SAFE_RELEASE_NULL(_pLayerMultiplex);
}

bool TopPanelLayer::init()
{
    bool bRet = false;

    do
    {
        // 初始化图层
        CC_BREAK_IF(!Layer::init());

        // 创建多功能图层
        createMultiplexLayer();

        // 创建菜单面板
        createMenuPanel();

        bRet = true;
    } while (0);

    return bRet;
}

void TopPanelLayer::createMultiplexLayer()
{
    // 创建多功能图层，包含选项图层、数据收集图层和设计图层
    _pLayerMultiplex = LayerMultiplex::create(OptionLayer::create(), DataCollectLayer::create(), DesignLayer::create(), nullptr);

    // 保留多功能图层的引用
    _pLayerMultiplex->retain();

    // 将多功能图层置于屏幕中央
    _pLayerMultiplex->setPosition(VisibleRect::center());

    // 将多功能图层添加到当前图层
    addChild(_pLayerMultiplex);
}

void TopPanelLayer::createMenuPanel()
{
    // 创建主页菜单项，点击后切换到欢迎场景
    auto pHomeMenuItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("setting_home_normal.png"),
        Sprite::createWithSpriteFrameName("setting_home_pressed.png"),
        [](Ref* pSender)
        {
            // 发送场景切换通知至欢迎场景
            auto enWelcomeScene = std::make_tuple(en_WelcomeScene, 0);
            NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enWelcomeScene));
        });
    pHomeMenuItem->setPosition(pHomeMenuItem->getContentSize().width / 2, 640 - pHomeMenuItem->getContentSize().height / 2 + 5);

    // 创建选项菜单项，点击后切换到选项图层
    auto pOptionMenuItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("options_normal_CN.png"),
        Sprite::createWithSpriteFrameName("options_selected_CN.png"),
        [&](Ref* pSender)
        {
            _pLayerMultiplex->switchTo(0);
        });
    pOptionMenuItem->setPosition(279, 593);

    // 创建统计菜单项，点击后切换到数据收集图层
    auto pStatisticsMenuItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("statistics_normal_CN.png"),
        Sprite::createWithSpriteFrameName("statistics_selected_CN.png"),
        [&](Ref* pSender)
        {
            _pLayerMultiplex->switchTo(1);
        });
    pStatisticsMenuItem->setPosition(479, 593);

    // 创建积分菜单项，点击后切换到设计图层
    auto pCreditsMenuItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("credits_normal_CN.png"),
        Sprite::createWithSpriteFrameName("credits_selected_CN.png"),
        [&](Ref* pSender)
        {
            _pLayerMultiplex->switchTo(2);
        });
    pCreditsMenuItem->setPosition(679, 593);

    // 创建菜单并添加所有菜单项
    auto pMenu = Menu::create(pHomeMenuItem, pOptionMenuItem, pStatisticsMenuItem, pCreditsMenuItem, nullptr);
    addChild(pMenu);
}
