
#include "PageViewLayer.h"
#include "SceneManager.h"
#include "ui/UIButton.h"
#include "SoundUtil.h"
#include "PublicSourceDefine.h"

PageViewLayer::~PageViewLayer()
{
    CC_SAFE_RELEASE_NULL(_pPageView);
    CC_SAFE_DELETE(_pPageFlagVec);
}

bool PageViewLayer::init()
{
    bool bRet = false;

    do
    {
        CC_BREAK_IF(!Layer::init());
        // 获取SceneManager对象的当前页面索引，赋值给_iPageIndex变量
        _iPageIndex = SceneManager::getInstance()->getCurPageIndex();
        _pPageFlagVec = new Vector<MenuItemSprite*>;// 创建一个Vector<MenuItemSprite*>对象，用于存储页面标志的精灵菜单项

        // 调用loadBg函数，加载背景图片和标题
        loadBg();
        // 调用createThemePageView函数，创建关卡的滑动视图
        createThemePageView();
        // 调用createThemeFlags函数，创建页面标志的按钮
        createThemeFlags();

        bRet = true;
    } while (0);
    return bRet;
}

void PageViewLayer::pageTurn(const bool& rBLeft)/*翻页函数，决定是左移还是右移*/
{
    if (rBLeft) 
    {
        if (_pPageView->getCurrentPageIndex() == 0) return;
        _pPageView->scrollToPage(_pPageView->getCurrentPageIndex() - 1);
    }
    else 
    {
        //if(_pPageView->getCurPageIndex() + 1 == _pPageView->getPageCount()) return;
        _pPageView->scrollToPage(_pPageView->getCurrentPageIndex() + 1);
    }
}

void PageViewLayer::setPageFlag(const int& rIIndex)
{
    int tIndex = -1; 
    for (auto& flagIter : *_pPageFlagVec) 
    {
        if (rIIndex == ++tIndex) 
        {
            flagIter->selected(); 
            continue; 
        }
        flagIter->unselected();  
    }
}
// 设置页面标志的函数，根据参数决定哪个页面标志被选中，无返回值



void PageViewLayer::loadBg()
{
    auto pBg = Sprite::createWithSpriteFrameName(BG);
    pBg->setPosition(VisibleRect::center());
    addChild(pBg);

    auto pTitle = Label::createWithSystemFont("选择关卡", "Arial", 30);
    pTitle->setPosition(Vec2(480, 615));
    addChild(pTitle);
}
// 加载背景的函数，无返回值

void PageViewLayer::createThemeFlags()
{
    // 创建一个菜单对象，用于容纳页面标志的精灵菜单项
    auto pPageFlagMenu = Menu::create();
    // 获取页面的数量，赋值给tFlagCount变量，这里暂时写死为5
    auto tFlagCount = 5;//_pPageView->getPageCount();
    // 用一个循环，根据页面的数量创建对应数量的页面标志
    for (int i = 0; i < tFlagCount; ++i)
    {
        // 创建一个精灵菜单项对象，用于表示页面标志，参数为正常状态和选中状态的图片
        auto pPageFlagItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("theme_pos_normal.png"), Sprite::createWithSpriteFrameName("theme_pos_active.png"));
        // 设置精灵菜单项对象的位置，根据循环变量i计算横坐标，纵坐标固定为30
        pPageFlagItem->setPosition(Vec2(430 + 20 * i, 30));
        // 将精灵菜单项对象添加到_pPageFlagVec指针指向的向量中，方便后续操作
        _pPageFlagVec->pushBack(pPageFlagItem);
        // 将精灵菜单项对象添加到菜单对象中，作为其子节点
        pPageFlagMenu->addChild(pPageFlagItem);
    }
    // 根据_iPageIndex变量的值，从_pPageFlagVec指针指向的向量中获取对应的页面标志，设置为选中状态
    _pPageFlagVec->at(_iPageIndex)->selected();
    // 将菜单对象添加为子节点
    addChild(pPageFlagMenu);
}

void PageViewLayer::createThemePageView()
{
    _pPageView = PageView::create();
    _pPageView->retain(); 
    _pPageView->setContentSize(Size(960.0f, 640.0f));

    Size tBackgroundSize = this->getContentSize();
    Layout* pLayout = nullptr;
    int i = -1;
    for (auto& iterThemeName : PAGESOURCE) 
    {
        pLayout = Layout::create();
        auto pButton = Button::create(iterThemeName, iterThemeName, iterThemeName, cocos2d::ui::Layout::TextureResType::PLIST);
        pButton->setPosition(Vec2(tBackgroundSize.width / 2, tBackgroundSize.height / 2 - 20));
        pButton->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType event)
            {
                if (event == Widget::TouchEventType::ENDED) // 如果触摸事件的类型是结束，表示用户点击了按钮
                {
                    int tCurPageIndex = _pPageView->getCurrentPageIndex();
                    auto tEnSceneType = std::make_tuple(en_LevelSelectScene, tCurPageIndex);
                    NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&tEnSceneType));
                }
            });
        pLayout->addChild(pButton);
        auto pThemeFlag = Sprite::createWithSpriteFrameName(StringUtils::format("theme_pack0%d_CN.png", i + 2));
        pThemeFlag->setScale(1.3f);
        pThemeFlag->setPosition(490, 320);
        pLayout->addChild(pThemeFlag);

        auto pThemeMark = Sprite::createWithSpriteFrameName(StringUtils::format("bookmark_10-12.png"));
        pThemeMark->setScale(1.5f);
        pThemeMark->setPosition(Vec2(710, 70));
        pLayout->addChild(pThemeMark);
        _pPageView->insertPage(pLayout, ++i);

    }
    _pPageView->setPassFocusToChild(true);
    _pPageView->scrollToPage(_iPageIndex);
    _pPageView->addEventListener([&](Ref* pSender, PageView::EventType event)
        {
            if (PageView::EventType::TURNING == event)// 如果事件的类型是翻页，表示用户滑动了页面
            {
                this->setPageFlag(_pPageView->getCurrentPageIndex());
            }
        });
    addChild(_pPageView, 14);
}
// 创建关卡的滑动视图的函数，无返回值

