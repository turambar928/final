// 引入头文件
#include "PageSelectScene.h"
#include "PageViewLayer.h"
#include "MenuPanelLayer.h"

// 析构函数，释放内存
PageSelectScene::~PageSelectScene()
{
    // 安全地释放_pPageViewLayer指针指向的对象，并将指针置空
    CC_SAFE_RELEASE_NULL(_pPageViewLayer);
    // 安全地释放_pMenuPanelLayer指针指向的对象，并将指针置空
    CC_SAFE_RELEASE_NULL(_pMenuPanelLayer);
}

// 初始化函数，返回一个布尔值表示是否成功初始化
bool PageSelectScene::init()
{
    bool bRet = false; // 定义一个返回值变量，初始为false
    do
    {
        // 如果父类Scene的初始化失败，就跳出循环
        CC_BREAK_IF(!Scene::init());

        // 创建一个PageViewLayer对象，用于显示关卡的滑动视图
        _pPageViewLayer = PageViewLayer::create();
        // 增加_pPageViewLayer对象的引用计数，防止被自动释放
        _pPageViewLayer->retain();

        // 创建一个MenuPanelLayer对象，用于显示菜单栏
        _pMenuPanelLayer = MenuPanelLayer::create();
        // 增加_pMenuPanelLayer对象的引用计数，防止被自动释放
        _pMenuPanelLayer->retain();

        // 将_pMenuPanelLayer指针动态转换为MenuPanelLayer类型的指针，方便调用其方法
        auto pMenuPanelLayer = dynamic_cast<MenuPanelLayer*>(_pMenuPanelLayer);
        // 设置pMenuPanelLayer对象的翻页回调函数，传入PageViewLayer对象的pageTurn方法
        pMenuPanelLayer->setPageTurnFunc(CC_CALLBACK_1(PageViewLayer::pageTurn, dynamic_cast<PageViewLayer*>(_pPageViewLayer)));

        // 设置返回值为true
        bRet = true;
    } while (0); // 循环条件为0，只执行一次

    // 返回bRet
    return bRet;
}

// 进入场景时的函数，无返回值
void PageSelectScene::onEnter()
{
    // 调用父类Scene的onEnter方法
    Scene::onEnter();
    // 将_pPageViewLayer对象添加为子节点
    addChild(_pPageViewLayer);
    // 将_pMenuPanelLayer对象添加为子节点
    addChild(_pMenuPanelLayer);
}
