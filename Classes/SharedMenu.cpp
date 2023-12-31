#include "SharedMenu.h"
#include "SoundUtil.h"
#include "PublicSourceDefine.h"
bool SharedMenu::init()
{
    bool bRet = false;

    do
    {
        // 调用创建菜单的函数
        createMenu();

        bRet = true;
    } while (0);

    return bRet;
}

void SharedMenu::createMenu()
{
    // 获取屏幕可见尺寸
    auto tVisibleSize = Director::getInstance()->getVisibleSize();

    // 创建背景精灵
    auto pBg = Sprite::createWithSpriteFrameName("share_bg.png");
    addChild(pBg);
    pBg->setOpacity(140);
    pBg->setPosition(Vec2(tVisibleSize.width / 2, pBg->getContentSize().height / 2));

    // 创建标题精灵
    auto pTitle = Sprite::createWithSpriteFrameName("share_bg_CN.png");
    addChild(pTitle);
    pTitle->setPosition(Vec2(480, 52));

    // 创建新浪微博分享菜单项
    auto pSinaSharedItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("share_tweibo_normal.png"),
        Sprite::createWithSpriteFrameName("share_tweibo_press.png"),
        [](Ref* pSender) {
            log("Sina");
        });
    pSinaSharedItem->setPosition(Vec2(340, 37));

    // 创建微信分享菜单项
    auto pWeChatSharedItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("share_wechat_normal.png"),
        Sprite::createWithSpriteFrameName("share_wechat_press.png"),
        [](Ref* pSender) {
            log("Weixin");
        });
    pWeChatSharedItem->setPosition(Vec2(480, 37));

    // 创建微博分享菜单项
    auto pWeiBoSharedItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("share_weibo_normal.png"),
        Sprite::createWithSpriteFrameName("share_weibo_normal.png"),
        [](Ref* pSender) {
            log("Weibo");
        });
    pWeiBoSharedItem->setPosition(Vec2(620, 37));

    // 创建菜单，并将菜单项添加到菜单中
    auto pMenu = Menu::create(pSinaSharedItem, pWeChatSharedItem, pWeiBoSharedItem, nullptr);
    addChild(pMenu);
}
