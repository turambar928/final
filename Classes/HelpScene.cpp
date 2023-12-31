#include "HelpScene.h"
#include "HelpMenuPanelLayer.h"

// 帮助场景析构函数
HelpScene::~HelpScene()
{
    CC_SAFE_RELEASE_NULL(_pMenuPanelLayer);
}

// 初始化方法
bool HelpScene::init()
{
    // 返回值标志
    bool bRet = false;

    // do-while 循环，用于实现安全退出
    do
    {
        // 如果场景初始化失败，则中断
        CC_BREAK_IF(!Scene::init());

        // 创建并初始化帮助菜单面板图层
        _pMenuPanelLayer = HelpMenuPanelLayer::create();
        _pMenuPanelLayer->retain();

        // 设置返回值标志为 true
        bRet = true;
    } while (0);

    // 返回初始化结果
    return bRet;
}

// 场景进入时的回调方法
void HelpScene::onEnter()
{
    // 调用父类的 onEnter 方法
    Scene::onEnter();

    // 将帮助菜单面板图层添加到场景中
    addChild(_pMenuPanelLayer);
}
