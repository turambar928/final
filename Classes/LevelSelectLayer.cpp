#include "LevelSelectLayer.h"
#include "ui/CocosGUI.h"
#include "SceneManager.h"
#include "SoundUtil.h"
#include "LocalDataUtil.h"

using namespace ui;
/* 定义一个析构函数，用于销毁对象，释放资源 */
LevelSelectLayer::~LevelSelectLayer()
{
}

/* 定义一个初始化函数，用于创建对象，返回一个布尔值 */
bool LevelSelectLayer::init()
{
    bool bRet = false; /* 定义一个布尔变量，用于存储返回值，初始值为false */
    do
    {
        CC_BREAK_IF(!Layer::init()); /* 调用父类的初始化函数，如果失败，跳出循环 */

        _iPageIndex = SceneManager::getInstance()->getCurPageIndex(); /* 获取场景管理器的实例，然后获取当前页面索引，赋值给成员变量 */

        loadData(); /* 调用加载数据的函数，从本地数据中获取关卡数据 */
        loadSource(); /* 调用加载资源的函数，从精灵帧缓存中获取图片资源 */
        bRet = true; /* 将返回值设为true */
    } while (0); /* 循环条件为0，表示只执行一次 */
    return bRet; /* 返回返回值 */
}

/* 定义一个加载资源的函数，用于创建并添加精灵，标签，菜单等 */
void LevelSelectLayer::loadSource()
{
    auto pBg = Sprite::createWithSpriteFrameName("ss_bg.png"); /* 创建一个精灵，使用精灵帧缓存中的ss_bg.png图片 */
    pBg->setPosition(VisibleRect::center()); /* 将精灵的位置设置为可见矩形的中心 */
    addChild(pBg); /* 将精灵添加到当前层中 */

    auto pTitle = Label::createWithSystemFont("选择关卡", "Arial", 30); /* 创建一个标签，使用系统字体，内容为"选择关卡"，字体为Arial，大小为30 */
    pTitle->setPosition(Vec2(480, 615)); /* 将标签的位置设置为(480, 615) */
    addChild(pTitle); /* 将标签添加到当前层中 */

    auto pCloud = Sprite::createWithSpriteFrameName("ss_cloud.png"); /* 创建一个精灵，使用精灵帧缓存中的ss_cloud.png图片 */
    pCloud->setPosition(VisibleRect::center()); /* 将精灵的位置设置为可见矩形的中心 */
    addChild(pCloud); /* 将精灵添加到当前层中 */

    loadLevel(); /* 调用加载关卡的函数，创建并添加关卡按钮 */
    loadMenuItem(); /* 调用加载菜单项的函数，创建并添加菜单项 */
}

/* 定义一个加载数据的函数，用于从本地数据中获取关卡数据 */
void LevelSelectLayer::loadData()
{
    _DataValueMap = LocalDataUtil::getInstance()->getLevelData(); /* 获取本地数据的实例，然后获取关卡数据，赋值给成员变量 */
}
/* 定义一个加载菜单项的函数，用于创建并添加菜单项 */
void LevelSelectLayer::loadMenuItem()
{
    /* 创建一个菜单项精灵，正常状态和按下状态使用精灵帧缓存中的ss_back_normal.png和ss_back_pressed.png图片，点击回调函数为一个lambda表达式，参数为一个引用类型的指针 */
    auto pBtnBack = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ss_back_normal.png"), Sprite::createWithSpriteFrameName("ss_back_pressed.png"), [&](Ref *pSender)
                                           {
                                               auto enPageSelectScene = std::make_tuple(en_PageSelectScene, _iPageIndex); /* 创建一个元组，包含页面选择场景的枚举值和当前页面索引 */
                                               NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enPageSelectScene));/* 使用通知中心，发送一个名为"changeScene"的通知，参数为元组的指针的强制类型转换 */
                                           });
    pBtnBack->setPosition(Vec2(-430, 280));
    /* 创建一个菜单项精灵，正常状态和按下状态使用精灵帧缓存中的ss_help_normal.png和ss_help_pressed.png图片，点击回调函数为一个lambda表达式，参数为一个引用类型的指针 */
    auto pBtnHelp = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ss_help_normal.png"), Sprite::createWithSpriteFrameName("ss_help_pressed.png"), [](Ref *pSender)
                                           {
                                               auto tEnHelpScene = std::make_tuple(en_GameHelpScene, 0);
                                               NOTIFY->postNotification("changeScene", reinterpret_cast<Ref *>(&tEnHelpScene));
                                           });
    pBtnHelp->setPosition(Vec2(130, 615));
    /* 创建一个菜单项精灵，正常状态和按下状态使用精灵帧缓存中的ss_play_normal_CN.png和ss_play_pressed_CN.png图片，点击回调函数为一个lambda表达式，参数为一个引用类型的指针 */
    _pStartBtn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ss_play_normal_CN.png"), Sprite::createWithSpriteFrameName("ss_play_pressed_CN.png"), [&](Ref *pSender)
    {
        this->changeToGameScene();
    });
    _pStartBtn->setPosition(Vec2(0, -255));
    addChild(Menu::create(pBtnBack, pBtnHelp, _pStartBtn, nullptr));
    /* 创建一个精灵，使用精灵帧缓存中的ss_locked_CN.png图片，表示关卡被锁定 */
    _pLockSprite = Sprite::createWithSpriteFrameName("ss_locked_CN.png");
    _pLockSprite->setPosition(Vec2(480, 75));
    addChild(_pLockSprite);
    _pLockSprite->setVisible(!_pLockSprite->isVisible());
    
}
/* 定义一个检查关卡是否被锁定和障碍物是否被清除的函数，参数为一个整数类型的引用，表示关卡索引，返回一个元组，包含一个整数和一个布尔值 */
std::tuple<int, bool> LevelSelectLayer::checkLevelIsLockAndBarrierIsClean(const int& rILevelIndex)
{
    auto tKey = StringUtils::format(LEVELKEY, _iPageIndex + 1, rILevelIndex); /* 使用字符串工具类，格式化字符串，作为关卡数据的键，包含当前页面索引和关卡索引 */
    auto value = _DataValueMap[tKey].asInt(); /* 从关卡数据的映射中，根据键获取值，转换为整数类型 */

    auto tCarrotType = value / 10; /* 将值除以10，得到胡萝卜的类型，0表示被锁定，1表示普通，2表示银色，3表示金色 */
    auto tBarrierClean = value % 10; /* 将值对10取余，得到障碍物是否被清除，0表示未清除，1表示已清除 */
    return std::make_tuple(tCarrotType, tBarrierClean); /* 使用std::make_tuple函数，根据胡萝卜的类型和障碍物是否被清除，创建并返回一个元组 */
}

/* 定义一个切换到游戏场景的函数，用于开始游戏 */
void LevelSelectLayer::changeToGameScene()
{
    //if(!std::get<0>(checkLevelIsLockAndBarrierIsClean(_iCurLevelIndex + 1))) return; /* 如果当前关卡被锁定，直接返回，不进行切换 */
    auto enGameScene = std::make_tuple(en_GameScene, _iCurLevelIndex); /* 创建一个元组，包含游戏场景的枚举值和当前关卡索引 */
    NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enGameScene)); /* 使用通知中心，发送一个名为"changeScene"的通知，参数为元组的指针的强制类型转换 */
}

/* 定义一个加载关卡的函数，用于创建并添加关卡按钮 */
void LevelSelectLayer::loadLevel()
{
    auto pageView = PageView::create();/* 创建一个页面视图对象，用于显示多个页面 */
    pageView->setContentSize(Size(960.0f, 640.0f));/* 设置页面视图的内容大小为(960.0f, 640.0f) */
    Size backgroundSize = this->getContentSize();/* 获取当前层的内容大小，赋值给一个尺寸变量 */
    Layout *pLayout = nullptr;/* 定义一个指向布局的指针，初始值为nullptr */

    std::string tMapImageName = "";/* 定义一个字符串变量，用于存储地图图片的名称，初始值为空 */
    /* 从0开始，遍历当前页面的关卡数量，每次增加1，i表示关卡索引 */
    for(int i = 0; i < THEME_LEVELCOUNT_ARRAY[_iPageIndex]; ++i)
    {
        /* 使用字符串工具类，格式化字符串，拼接地图图片的名称，包含地图前缀，关卡索引，和图片后缀 */
        tMapImageName = MAPNAME + StringUtils::format("%02d", i + 1) + PHOTOPOSTFIX;
        pLayout = Layout::create();/* 创建一个布局对象，用于存放关卡按钮和其他元素 */
        /* 获取CsvUtil的实例，然后从关卡配置的CSV文件中，根据行列索引，获取当前关卡的怪物批次数量，赋值给一个整数变量 */
        auto tTotalMonsterBatchCount = CsvUtil::getInstance()->getInt(1 + SceneManager::getInstance()->getCurPageIndex() * 12 + i, 3, LEVELCSVFILE);
        /* 创建一个精灵，使用精灵帧缓存中的ss_waves_%d.png图片，%d表示怪物批次数量 */
        auto pTotalMonsterBatch = Sprite::createWithSpriteFrameName(StringUtils::format("ss_waves_%d.png", tTotalMonsterBatchCount));
        pTotalMonsterBatch->setPosition(Vec2(500, 535));
        pLayout->addChild(pTotalMonsterBatch);/* 将精灵添加到布局中 */
        /* 创建一个按钮，正常状态，选中状态，不可用状态使用精灵帧缓存中的地图图片，纹理资源类型为PLIST */
        auto pButton = Button::create(tMapImageName, tMapImageName, tMapImageName, cocos2d::ui::Layout::TextureResType::PLIST);
        pButton->setPosition(Vec2(backgroundSize.width / 2, backgroundSize.height / 2 + 35));
        /* 为按钮添加触摸事件监听器，回调函数为一个lambda表达式，参数为一个引用类型的指针和一个触摸事件类型 */
        pButton->addTouchEventListener([&](Ref *pSender, Widget::TouchEventType event)
                                       {
                                           if(event == Widget::TouchEventType::ENDED)/* 如果触摸事件类型为结束 */
                                           {
                                               this->changeToGameScene();/* 调用切换到游戏场景的函数 */
                                           }
                                       });
        /* 创建一个精灵，使用精灵帧缓存中的塔图片，拼接塔前缀，关卡索引，和图片后缀 */
        auto pTowerFlag = Sprite::createWithSpriteFrameName(TOWERNAME + StringUtils::format("%02d", i + 1) + PHOTOPOSTFIX);

        pTowerFlag->setPosition(Vec2(backgroundSize.width / 2, backgroundSize.height / 2 - pButton->getContentSize().height / 2 - pTowerFlag->getContentSize().height / 2 + 35));
        pLayout->addChild(pButton);
        pLayout->addChild(pTowerFlag);
        
        auto tLevelData = this->checkLevelIsLockAndBarrierIsClean(i + 1);
        /* 调用检查关卡是否被锁定和障碍物是否被清除的函数，参数为关卡索引加1，返回一个元组，赋值给一个元组变量 */
        auto tCarrotType = std::get<0>(tLevelData);
        /* 从元组中获取第0个元素，表示胡萝卜的类型，赋值给一个整数变量 */
        auto tBarrierCleanFlag = std::get<1>(tLevelData);
        /* 从元组中获取第1个元素，表示障碍物是否被清除，赋值给一个布尔变量 */

        if(!tCarrotType)/* 如果胡萝卜的类型为0，表示关卡被锁定 */
        {
            auto pLock = Sprite::createWithSpriteFrameName("ss_locked_icon.png");
            /* 创建一个精灵，使用精灵帧缓存中的ss_locked_icon.png图片，表示锁定图标 */
            pLock->setPosition(Vec2(620, 255));
            pLayout->addChild(pLock);
        }
        else
        {
            std::string sCarrotType = ""; /* 定义一个字符串变量，用于存储胡萝卜图片的名称，初始值为空 */
            if (tCarrotType == 4) /* 如果胡萝卜的类型为4，表示金色胡萝卜 */
                sCarrotType = GOLDCARROT; /* 将胡萝卜图片的名称设为GOLDCARROT */
            if (tCarrotType == 3) /* 如果胡萝卜的类型为3，表示银色胡萝卜 */
                sCarrotType = SILVERCARROT; /* 将胡萝卜图片的名称设为SILVERCARROT */
            if (tCarrotType == 2) /* 如果胡萝卜的类型为2，表示普通胡萝卜 */
                sCarrotType = NORMALCARROT; /* 将胡萝卜图片的名称设为NORMALCARROT */

            if (tCarrotType > 1) /* 如果胡萝卜的类型大于1，表示有胡萝卜 */
            {
                auto pCarrot = Sprite::createWithSpriteFrameName(sCarrotType);
                pLayout->addChild(pCarrot);
                pCarrot->setPosition(620, 255);
            }
            
            if (tBarrierCleanFlag) /* 如果障碍物被清除 */
            {
                auto pBarrierClean = Sprite::createWithSpriteFrameName(BARRIERCLEAN); /* 创建一个精灵，使用精灵帧缓存中的BARRIERCLEAN图片，表示障碍物被清除的图标 */
                pLayout->addChild(pBarrierClean); /* 将精灵添加到布局中 */
                pBarrierClean->setPosition(500, 255); /* 将精灵的位置设置为(500, 255) */
            }
            
        }
        pageView->insertPage(pLayout, i);/* 将布局插入到页面视图中，索引为i */

    }
    pageView->setPassFocusToChild(true); /* 设置页面视图是否将焦点传递给子节点，参数为true */
    pageView->scrollToPage(_iCurLevelIndex); /* 设置页面视图滚动到指定的页面，参数为当前关卡索引 */
    pageView->addEventListener([=](Ref* pSender, PageView::EventType event) /* 为页面视图添加事件监听器，回调函数为一个lambda表达式，参数为一个引用类型的指针和一个页面视图事件类型 */
        {
            if (PageView::EventType::TURNING == event) /* 如果页面视图事件类型为翻页 */
            {
                _iCurLevelIndex = pageView->getCurrentPageIndex(); /* 获取页面视图的当前页面索引，赋值给成员变量 */
                auto tLockFlag = std::get<0>(this->checkLevelIsLockAndBarrierIsClean(_iCurLevelIndex + 1)); /* 调用检查关卡是否被锁定和障碍物是否被清除的函数，参数为当前关卡索引加1，返回一个元组，从中获取第0个元素，表示关卡是否被锁定，赋值给一个布尔变量 */
                tLockFlag = true; /* 将关卡是否被锁定的变量设为true，表示可以开始游戏 */
                _pStartBtn->setEnabled(tLockFlag); /* 设置开始按钮是否可用，参数为关卡是否被锁定的变量 */
                _pLockSprite->setVisible(!tLockFlag); /* 设置锁定精灵是否可见，参数为关卡是否被锁定的变量的取反，表示如果关卡被锁定，锁定精灵可见，否则不可见 */

            }
        });
    addChild(pageView); /* 将页面视图添加到当前层中 */
    
}


