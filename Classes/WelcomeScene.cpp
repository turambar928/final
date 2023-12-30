#include "WelcomeScene.h"
#include "SpritesLayer.h"
#include "MenusLayer.h"
#include "LoadingSourceLayer.h"
#include "Config.h"

/**
 * @brief WelcomeScene��������
 * @details �ͷ�_menusLayer��_spritesLayer���ڴ�
 */
WelcomeScene::~WelcomeScene()
{
    CC_SAFE_RELEASE_NULL(_pMenusLayer);
    CC_SAFE_RELEASE_NULL(_pSpritesLayer);
}

/**
 * @brief ��ʼ������
 * @return ��ʼ���Ƿ�ɹ�
 * @details ��ʼ��WelcomeScene������_spritesLayer��_menusLayer
 */
bool WelcomeScene::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Scene::init());

        // ����������_spritesLayer
        _pSpritesLayer = SpritesLayer::create();
        _pSpritesLayer->retain();

        // ����������_menusLayer
        _pMenusLayer = MenusLayer::create();
        _pMenusLayer->retain();

        bRet = true;
    } while (0);

    return bRet;
}

/**
 * @brief ���볡���ص�����
 * @details �ڽ��볡��ʱ���_spritesLayer����������Դ����״̬���_loadingLayer��_menusLayer
 */
void WelcomeScene::onEnter()
{
    Scene::onEnter();
    addChild(_pSpritesLayer);

    // ������Դ����״̬���_loadingLayer��_menusLayer
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
 * @brief ��ʾ�˵�����
 * @details �Ƴ�_loadingLayer�����_menusLayer��ͬʱ������Դ����״̬Ϊ�Ѽ���
 */
void WelcomeScene::showMenu()
{
    // �Ƴ�_loadingLayer�����_menusLayer
    getChildByName("loadingLayer")->removeFromParent();
    addChild(_pMenusLayer);

    // ������Դ����״̬Ϊ�Ѽ���
    Config::getInstance()->setIsLoadSource(true);
}





