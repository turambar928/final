#include "MenuPanelLayer.h" //包含菜单面板层的头文件
#include "SoundUtil.h" //包含声音工具的头文件
#include "PublicSourceDefine.h" //包含公共资源定义的头文件

/* 定义一个初始化函数，用于创建对象，返回一个布尔值 */
bool MenuPanelLayer::init()
{
    bool bRet = false; //定义一个布尔变量，用于存储返回值，初始值为false

    do
    {
        CC_BREAK_IF(!Layer::init()); //使用宏定义一个条件判断，如果父类的初始化函数返回false，就跳出循环

        createItemPanel(); //调用创建项目面板的函数，用于创建菜单项

        bRet = true; //将返回值设为true
    } while (0); //循环条件为0，表示只执行一次

    return bRet; //返回返回值
}
/* 定义一个设置翻页函数的函数，用于设置翻页的回调函数，参数为一个函数对象的引用，表示翻页的函数 */
void MenuPanelLayer::setPageTurnFunc(const std::function<void(const bool&)>& rFuncPageTurn)
{
    _funcPageTurn = rFuncPageTurn; //将成员变量赋值为参数的函数对象，表示翻页的函数
}
/* 定义一个创建项目面板的函数，用于创建菜单项 */
void MenuPanelLayer::createItemPanel()
{
    //创建一个菜单项精灵，参数为正常状态的精灵，按下状态的精灵，和一个匿名函数，表示返回按钮
    auto pBtnBack = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ss_back_normal.png"), Sprite::createWithSpriteFrameName("ss_back_pressed.png"), [&](Ref* pSender)
        {
            //创建一个元组，参数为欢迎场景的枚举值和-1，赋值给一个元组变量，表示要切换的场景
            auto enWelcomeScene = std::make_tuple(en_WelcomeScene, -1);
            NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enWelcomeScene));
        });
    pBtnBack->setPosition(Vec2(-430, 280));
    //创建一个菜单项精灵，参数为正常状态的精灵，按下状态的精灵，和一个匿名函数，表示主页按钮
    auto pBtnHome = MenuItemSprite::create(Sprite::createWithSpriteFrameName("theme_home_normal.png"), Sprite::createWithSpriteFrameName("theme_home_pressed.png"), [](Ref *pSender)
                                           {
                                               auto enWelcomeScene = std::make_tuple(en_WelcomeScene, -1);//创建一个元组，参数为欢迎场景的枚举值和-1，赋值给一个元组变量，表示要切换的场景
                                               NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enWelcomeScene));
                                           });
    pBtnHome->setPosition(Vec2(30, 615));
    //创建一个菜单项精灵，参数为正常状态的精灵，按下状态的精灵，和一个匿名函数，表示帮助按钮
    auto pBtnHelp = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ss_help_normal.png"), Sprite::createWithSpriteFrameName("ss_help_pressed.png"), [](Ref *pSender)
                                           {
            //创建一个元组，参数为游戏帮助场景的枚举值和0，赋值给一个元组变量，表示要切换的场景
                                               auto tEnHelpScene = std::make_tuple(en_GameHelpScene, 0);
                                               NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&tEnHelpScene));
                                           });
    pBtnHelp->setPosition(Vec2(930, 615));
    //创建一个菜单项精灵，参数为正常状态的精灵，按下状态的精灵，和一个匿名函数，表示左翻页按钮
    auto pBtnLeft = MenuItemSprite::create(Sprite::createWithSpriteFrameName("theme_pointleft_normal.png"), Sprite::createWithSpriteFrameName("theme_pointleft_pressed.png"), [this](Ref *pSender)
                                           {
                                               _funcPageTurn(true);//调用翻页函数，参数为true，表示向左翻页
                                           });
    pBtnLeft->setPosition(Vec2(80, 320));//设置左翻页按钮的位置，参数为一个向量，表示按钮的位置
    
    auto pBtnRight = MenuItemSprite::create(Sprite::createWithSpriteFrameName("theme_pointright_normal.png"), Sprite::createWithSpriteFrameName("theme_pointright_pressed.png"), [this](Ref *pSender)
                                            {
                                                _funcPageTurn(false);//调用翻页函数，参数为false，表示向右翻页
                                            });
    pBtnRight->setPosition(Vec2(880, 320));
    //设置右翻页按钮的位置，参数为一个向量，表示按钮的位置
    auto pMenu = Menu::create(pBtnBack, nullptr);//创建一个菜单，参数为返回按钮和空指针，表示菜单的项
    addChild(pMenu, 16); //将菜单添加为子节点，参数为菜单和16，表示菜单的层级

}


