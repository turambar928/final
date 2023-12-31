#include "MenusLayer.h" //包含菜单层的头文件
#include "SoundUtil.h" //包含声音工具的头文件
#include "PublicSourceDefine.h" //包含公共资源定义的头文件
/* 定义一个初始化函数，用于创建对象，返回一个布尔值 */
bool MenusLayer::init()
{
    bool bRet = false; //定义一个布尔变量，用于存储返回值，初始值为false

    do
    {
        CC_BREAK_IF(!Layer::init()); //使用宏定义一个条件判断，如果父类的初始化函数返回false，就跳出循环

        createMenuItems(); //调用创建菜单项的函数，用于创建菜单按钮

        bRet = true; //将返回值设为true
    } while (0); //循环条件为0，表示只执行一次

    return bRet; //返回返回值
}

/* 定义一个创建菜单项的函数，用于创建菜单按钮 */
void MenusLayer::createMenuItems()
{
    auto pBtnadventureMode = MenuItemSprite::create(
                                                    Sprite::createWithSpriteFrameName("btn_adventure_normal_CN.png"),//创建一个精灵，参数为帧缓存中的图片名称，表示正常状态的图片，用于创建冒险模式按钮
                                                    Sprite::createWithSpriteFrameName("btn_adventure_pressed_CN.png"),//创建一个精灵，参数为帧缓存中的图片名称，表示按下状态的图片，用于创建冒险模式按钮
                                                    [](Ref *pSender)
                                                    {
            //创建一个匿名函数，参数为一个引用类型的指针，表示触发事件的对象，用于创建冒险模式按钮的回调函数
                                                        auto enLevelScene = std::make_tuple(en_PageSelectScene, 0);
                                                        //创建一个元组，参数为分页选择场景的枚举值和0，赋值给一个元组变量，表示要切换的场景
                                                        NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enLevelScene));
                                                        //使用通知中心，发送一个通知，参数为"changeScene"和要切换的场景的指针，表示请求切换场景
                                                    }
                                                    );
    
    pBtnadventureMode->setPosition(Vec2(480, 100));
    
    auto pBtnSetting = MenuItemSprite::create(
                                              Sprite::createWithSpriteFrameName("btn_setting_normal.png"),//创建一个精灵，参数为帧缓存中的图片名称，表示正常状态的图片，用于创建设置按钮
                                              Sprite::createWithSpriteFrameName("btn_setting_pressed.png"),//创建一个精灵，参数为帧缓存中的图片名称，表示按下状态的图片，用于创建设置按钮
                                              [](Ref *pSender)
                                              {
                                                  auto enGameSettingScene = std::make_tuple(en_GameSettingScene, 0);
                                                  NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enGameSettingScene));
                                              }
                                              );
    pBtnSetting->setPosition(Vec2(200, 220));
    
    auto pBtnHelp = MenuItemSprite::create(
                                           Sprite::createWithSpriteFrameName("btn_help_normal.png"),
                                           Sprite::createWithSpriteFrameName("btn_help_pressed.png"),
                                           [](Ref *pSender)
                                           {
                                               auto tEnGameHelpSceneType = std::make_tuple(en_GameHelpScene, 0);//创建一个元组，参数为游戏帮助场景的枚举值和0，赋值给一个元组变量，表示要切换的场景
                                               NOTIFY->postNotification("changeScene", reinterpret_cast<Ref *>(&tEnGameHelpSceneType));
                                           });
    pBtnHelp->setPosition(Vec2(750, 220));
    
    auto pMenu = Menu::create(pBtnadventureMode, pBtnSetting, pBtnHelp, nullptr);//创建一个菜单，参数为冒险模式按钮，设置按钮，帮助按钮，和空指针，表示菜单的项
    pMenu->setPosition(Vec2::ZERO);
    addChild(pMenu);//将菜单添加为子节点


}