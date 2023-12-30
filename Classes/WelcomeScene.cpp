#include "WelcomeScene.h"
#include "SpritesLayer.h"
#include "MenusLayer.h"
#include "LoadingSourceLayer.h"
#include "Config.h"

/**
 * @brief WelcomeScene析构函数
 * @details 释放_menusLayer和_spritesLayer的内存
 */
WelcomeScene::~WelcomeScene()
{
    CC_SAFE_RELEASE_NULL(_pMenusLayer);
    CC_SAFE_RELEASE_NULL(_pSpritesLayer);
}

/**
 * @brief 初始化函数
 * @return 初始化是否成功
 * @details 初始化WelcomeScene，创建_spritesLayer和_menusLayer
 */
bool WelcomeScene::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Scene::init());

        // 创建并保持_spritesLayer
        _pSpritesLayer = SpritesLayer::create();
        _pSpritesLayer->retain();

        // 创建并保持_menusLayer
        _pMenusLayer = MenusLayer::create();
        _pMenusLayer->retain();

        bRet = true;
    } while (0);

    return bRet;
}

/**
 * @brief 进入场景回调函数
 * @details 在进入场景时添加_spritesLayer，并根据资源加载状态添加_loadingLayer或_menusLayer
 */
void WelcomeScene::onEnter()
{
    Scene::onEnter();
    addChild(_pSpritesLayer);

    // 根据资源加载状态添加_loadingLayer或_menusLayer
    if (!Config::getInstance()->getIsLoadSource())
    {
        auto pLoadingLayer = LoadingSourceLayer::create();
        pLoadingLayer->setFuncShowMenuPanel(CC_CALLBACK_0(WelcomeScene::showMenu, this));
        pLoadingLayer->setName("loadingLayer");
        addChild(pLoadingLayer);
    }
    else
    {
        addChild(_pMenusLayer);
    }
}

/**
 * @brief 显示菜单函数
 * @details 移除_loadingLayer并添加_menusLayer，同时设置资源加载状态为已加载
 */
void WelcomeScene::showMenu()
{
    // 移除_loadingLayer并添加_menusLayer
    getChildByName("loadingLayer")->removeFromParent();
    addChild(_pMenusLayer);

    // 设置资源加载状态为已加载
    Config::getInstance()->setIsLoadSource(true);
}





