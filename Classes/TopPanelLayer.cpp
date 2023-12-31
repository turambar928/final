#include "TopPanelLayer.h"
#include "OptionLayer.h"
#include "DesignLayer.h"
#include "DataCollectLayer.h"
#include "SoundUtil.h"
#include "PublicSourceDefine.h"

TopPanelLayer::~TopPanelLayer()
{
    // ��ȫ�ͷŶ๦��ͼ��ʵ��
    CC_SAFE_RELEASE_NULL(_pLayerMultiplex);
}

bool TopPanelLayer::init()
{
    bool bRet = false;

    do
    {
        // ��ʼ��ͼ��
        CC_BREAK_IF(!Layer::init());

        // �����๦��ͼ��
        createMultiplexLayer();

        // �����˵����
        createMenuPanel();

        bRet = true;
    } while (0);

    return bRet;
}

void TopPanelLayer::createMultiplexLayer()
{
    // �����๦��ͼ�㣬����ѡ��ͼ�㡢�����ռ�ͼ������ͼ��
    _pLayerMultiplex = LayerMultiplex::create(OptionLayer::create(), DataCollectLayer::create(), DesignLayer::create(), nullptr);

    // �����๦��ͼ�������
    _pLayerMultiplex->retain();

    // ���๦��ͼ��������Ļ����
    _pLayerMultiplex->setPosition(VisibleRect::center());

    // ���๦��ͼ����ӵ���ǰͼ��
    addChild(_pLayerMultiplex);
}

void TopPanelLayer::createMenuPanel()
{
    // ������ҳ�˵��������л�����ӭ����
    auto pHomeMenuItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("setting_home_normal.png"),
        Sprite::createWithSpriteFrameName("setting_home_pressed.png"),
        [](Ref* pSender)
        {
            // ���ͳ����л�֪ͨ����ӭ����
            auto enWelcomeScene = std::make_tuple(en_WelcomeScene, 0);
            NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enWelcomeScene));
        });
    pHomeMenuItem->setPosition(pHomeMenuItem->getContentSize().width / 2, 640 - pHomeMenuItem->getContentSize().height / 2 + 5);

    // ����ѡ��˵��������л���ѡ��ͼ��
    auto pOptionMenuItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("options_normal_CN.png"),
        Sprite::createWithSpriteFrameName("options_selected_CN.png"),
        [&](Ref* pSender)
        {
            _pLayerMultiplex->switchTo(0);
        });
    pOptionMenuItem->setPosition(279, 593);

    // ����ͳ�Ʋ˵��������л��������ռ�ͼ��
    auto pStatisticsMenuItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("statistics_normal_CN.png"),
        Sprite::createWithSpriteFrameName("statistics_selected_CN.png"),
        [&](Ref* pSender)
        {
            _pLayerMultiplex->switchTo(1);
        });
    pStatisticsMenuItem->setPosition(479, 593);

    // �������ֲ˵��������л������ͼ��
    auto pCreditsMenuItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("credits_normal_CN.png"),
        Sprite::createWithSpriteFrameName("credits_selected_CN.png"),
        [&](Ref* pSender)
        {
            _pLayerMultiplex->switchTo(2);
        });
    pCreditsMenuItem->setPosition(679, 593);

    // �����˵���������в˵���
    auto pMenu = Menu::create(pHomeMenuItem, pOptionMenuItem, pStatisticsMenuItem, pCreditsMenuItem, nullptr);
    addChild(pMenu);
}
