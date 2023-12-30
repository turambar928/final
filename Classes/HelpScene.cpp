#include "HelpScene.h"
#include "HelpMenuPanelLayer.h"

// ����������������
HelpScene::~HelpScene()
{
    CC_SAFE_RELEASE_NULL(_pMenuPanelLayer);
}

// ��ʼ������
bool HelpScene::init()
{
    // ����ֵ��־
    bool bRet = false;

    // do-while ѭ��������ʵ�ְ�ȫ�˳�
    do
    {
        // ���������ʼ��ʧ�ܣ����ж�
        CC_BREAK_IF(!Scene::init());

        // ��������ʼ�������˵����ͼ��
        _pMenuPanelLayer = HelpMenuPanelLayer::create();
        _pMenuPanelLayer->retain();

        // ���÷���ֵ��־Ϊ true
        bRet = true;
    } while (0);

    // ���س�ʼ�����
    return bRet;
}

// ��������ʱ�Ļص�����
void HelpScene::onEnter()
{
    // ���ø���� onEnter ����
    Scene::onEnter();

    // �������˵����ͼ����ӵ�������
    addChild(_pMenuPanelLayer);
}
