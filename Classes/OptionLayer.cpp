
#include "OptionLayer.h"
#include "SoundUtil.h"
// 初始化函数，返回一个布尔值表示是否成功初始化
bool OptionLayer::init()
{
    bool bRet = false; // 定义一个返回值变量，初始为false
    do
    {
        CC_BREAK_IF(!Layer::init()); // 如果父类Layer的初始化失败，就跳出循环

        loadSource(); // 调用loadSource函数，加载资源

        bRet = true; // 设置返回值为true
    } while (0); // 循环条件为0，只执行一次
    return bRet; // 返回bRet
}

void OptionLayer::loadSource()
{
    auto pSoundUtil = SoundUtil::getInstance();// 获取SoundUtil的单例对象，用于控制音效
    bool bIsBackGroundSound = pSoundUtil->getIsBackGroundSound();// 获取背景音乐是否开启的状态
    bool bIsEffectSound = pSoundUtil->getIsEffectSound();// 获取音效是否开启的状态
    
    auto pBg = Sprite::createWithSpriteFrameName("setting_bg.png");// 创建一个精灵对象，用于显示背景图片
    addChild(pBg); // 将背景精灵添加为子节点
    
    auto pTitle = Sprite::createWithSpriteFrameName("options_normal_CN.png");
    pTitle->setPosition(0, 100);
    addChild(pTitle);
    // 创建一个菜单项精灵对象，用于显示返回按钮
    auto pBtnBack = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ss_back_normal.png"), Sprite::createWithSpriteFrameName("ss_back_pressed.png"), [&](Ref* pSender)
        {
            // 创建一个元组对象，用于表示欢迎场景的枚举值和参数
            auto enWelcomeScene = std::make_tuple(en_WelcomeScene, 0);
            // 发送一个通知，用于切换场景
            NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enWelcomeScene));
        });
    pBtnBack->setPosition(Vec2(0, -215));
    
    // 创建一个菜单项切换对象，用于显示音效开关
    auto pEffectSoundBtnOn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("soundfx_on_CN.png"), Sprite::createWithSpriteFrameName("soundfx_on_CN.png"));
    auto pEffectSoundBtnOff = MenuItemSprite::create(Sprite::createWithSpriteFrameName("soundfx_off_CN.png"), Sprite::createWithSpriteFrameName("soundfx_off_CN.png"));
    auto pEffectSoundToggle = MenuItemToggle::createWithCallback(// 定义一个回调函数，用于切换音效状态
                                                                [pSoundUtil](Ref *pSender)
                                                                {
                                                                    pSoundUtil->setIsEffectSound(!pSoundUtil->getIsEffectSound());
                                                                },
                                                                 bIsEffectSound ? pEffectSoundBtnOn : pEffectSoundBtnOff,// 根据音效状态，选择显示开启或关闭的图片
                                                                 bIsEffectSound ? pEffectSoundBtnOff : pEffectSoundBtnOn,// 根据音效状态，选择显示关闭或开启的图片
                                                                 nullptr);
    pEffectSoundToggle->setPosition(Vec2(0, -120));
    // 创建一个菜单项切换对象，用于显示背景音乐开关
    auto pBackGroundSoundOn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("bgmusic_on_CN.png"), Sprite::createWithSpriteFrameName("bgmusic_on_CN.png"));
    auto pBackGroundSoundOff = MenuItemSprite::create(Sprite::createWithSpriteFrameName("bgmusic_off_CN.png"), Sprite::createWithSpriteFrameName("bgmusic_off_CN.png"));
    auto pBackGroundSoundToggle = MenuItemToggle::createWithCallback(// 调用SoundUtil的方法，设置背景音乐状态为相反值
                                                                     [pSoundUtil](Ref *pSender)
                                                                     {
                                                                         pSoundUtil->setIsBackGroundSound(!pSoundUtil->getIsBackGroundSound());
                                                                     },
                                                                     bIsBackGroundSound ? pBackGroundSoundOn : pBackGroundSoundOff,
                                                                     bIsBackGroundSound ? pBackGroundSoundOff : pBackGroundSoundOn,
                                                                     nullptr);
    pBackGroundSoundToggle->setPosition(Vec2(0, -50));
    auto pMenu = Menu::create(pBtnBack,pBackGroundSoundToggle, pEffectSoundToggle, NULL); 
    pMenu->setPosition(0, 0);
    addChild(pMenu);
}


