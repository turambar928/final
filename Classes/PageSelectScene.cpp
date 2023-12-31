// ����ͷ�ļ�
#include "PageSelectScene.h"
#include "PageViewLayer.h"
#include "MenuPanelLayer.h"

// �����������ͷ��ڴ�
PageSelectScene::~PageSelectScene()
{
    // ��ȫ���ͷ�_pPageViewLayerָ��ָ��Ķ��󣬲���ָ���ÿ�
    CC_SAFE_RELEASE_NULL(_pPageViewLayer);
    // ��ȫ���ͷ�_pMenuPanelLayerָ��ָ��Ķ��󣬲���ָ���ÿ�
    CC_SAFE_RELEASE_NULL(_pMenuPanelLayer);
}

// ��ʼ������������һ������ֵ��ʾ�Ƿ�ɹ���ʼ��
bool PageSelectScene::init()
{
    bool bRet = false; // ����һ������ֵ��������ʼΪfalse
    do
    {
        // �������Scene�ĳ�ʼ��ʧ�ܣ�������ѭ��
        CC_BREAK_IF(!Scene::init());

        // ����һ��PageViewLayer����������ʾ�ؿ��Ļ�����ͼ
        _pPageViewLayer = PageViewLayer::create();
        // ����_pPageViewLayer��������ü�������ֹ���Զ��ͷ�
        _pPageViewLayer->retain();

        // ����һ��MenuPanelLayer����������ʾ�˵���
        _pMenuPanelLayer = MenuPanelLayer::create();
        // ����_pMenuPanelLayer��������ü�������ֹ���Զ��ͷ�
        _pMenuPanelLayer->retain();

        // ��_pMenuPanelLayerָ�붯̬ת��ΪMenuPanelLayer���͵�ָ�룬��������䷽��
        auto pMenuPanelLayer = dynamic_cast<MenuPanelLayer*>(_pMenuPanelLayer);
        // ����pMenuPanelLayer����ķ�ҳ�ص�����������PageViewLayer�����pageTurn����
        pMenuPanelLayer->setPageTurnFunc(CC_CALLBACK_1(PageViewLayer::pageTurn, dynamic_cast<PageViewLayer*>(_pPageViewLayer)));

        // ���÷���ֵΪtrue
        bRet = true;
    } while (0); // ѭ������Ϊ0��ִֻ��һ��

    // ����bRet
    return bRet;
}

// ���볡��ʱ�ĺ������޷���ֵ
void PageSelectScene::onEnter()
{
    // ���ø���Scene��onEnter����
    Scene::onEnter();
    // ��_pPageViewLayer�������Ϊ�ӽڵ�
    addChild(_pPageViewLayer);
    // ��_pMenuPanelLayer�������Ϊ�ӽڵ�
    addChild(_pMenuPanelLayer);
}
