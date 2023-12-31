
#include "PauseLayer.h"
#include "SceneManager.h"
#include "SharedMenu.h"
#include "SoundUtil.h"
#include "PublicSourceDefine.h"
#include "GameManager.h"

bool PauseLayer::init()
{
    bool bRet = false; // ����һ���������������ڷ��غ����Ƿ�ɹ���ʼ��

    do
    {
        CC_BREAK_IF(!Layer::init()); // ������� Layer �� init ����ʧ�ܣ�������ѭ��

        auto pBlackLayer = LayerColor::create(Color4B(0, 0, 0, 170)); // ����һ����͸���ĺ�ɫ��

        addChild(pBlackLayer); // ����ɫ�����Ϊ�ӽڵ�

        createMenu(); // �����Զ���� createMenu ����������һ���˵�

        closeTouchEvent(); // �����Զ���� closeTouchEvent �������رմ����¼�

        bRet = true; // ������ֵ��Ϊ true����ʾ��ʼ���ɹ�
    } while (0); // ����һ��ִֻ��һ�ε�ѭ�������ڷ�������

    return bRet; // ���غ����Ƿ�ɹ���ʼ��

} // ��������

void PauseLayer::createMenu()
{
    auto pMenuBg = Sprite::createWithSpriteFrameName("menu_bg.png"); // ����һ�����飬������ʾ�˵��ı���ͼƬ
    pMenuBg->setPosition(VisibleRect::center()); // ���þ����λ��Ϊ��Ļ����
    addChild(pMenuBg); // ���������Ϊ�ӽڵ�

    MenuItemSprite* pBtnResume = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("menu_resume_normal_CN.png"), // ����һ�����飬������ʾ������ť������״̬ͼƬ
        Sprite::createWithSpriteFrameName("menu_resume_pressed_CN.png"), // ����һ�����飬������ʾ������ť�İ���״̬ͼƬ
        [this](Ref* pSender) // ����һ���ص����������ڴ��������ť�ĵ���¼�
    {
        _funcFlagPauseLayerIsClose(); // �����Զ���� _funcFlagPauseLayerIsClose ������������ͣ��رյı�־
        removeFromParentAndCleanup(true); // ����ͣ��Ӹ��ڵ��Ƴ�������
    }
    );
    pBtnResume->setPosition(Vec2(481, 417)); // ���ü�����ť��λ��
    // ���´������������ƣ�ֻ�Ǵ�����������ť��ѡ��ؿ���ť���������˲�ͬ��λ�úͻص�����
    MenuItemSprite* pBtnRstart = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("menu_restart_normal_CN.png"),
        Sprite::createWithSpriteFrameName("menu_restart_pressed_CN.png"),
        [this](Ref* pSender)
    {
        auto enGameScene = std::make_tuple(en_GameScene, SceneManager::getInstance()->getCurLevelIndex()); // ����һ��Ԫ�飬���ڴ洢��Ϸ���������ͺ͵�ǰ�ؿ�������
        NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enGameScene)); // ����һ��֪ͨ�������л�����

    }
    );
    pBtnRstart->setPosition(Vec2(481, 322));

    MenuItemSprite* pBtnSelectLevel = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("menu_quit_normal_CN.png"),
        Sprite::createWithSpriteFrameName("menu_quit_pressed_CN.png"),
        [this](Ref* pSender)
    {
        auto enLevelSelectScene = std::make_tuple(en_LevelSelectScene, SceneManager::getInstance()->getCurPageIndex()); // ����һ��Ԫ�飬���ڴ洢�ؿ�ѡ�񳡾������ͺ͵�ǰҳ�������
        NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enLevelSelectScene)); // ����һ��֪ͨ�������л�����

    }
    );
    pBtnSelectLevel->setPosition(Vec2(481, 227));

    Menu* pMenu = Menu::create(pBtnResume, pBtnRstart, pBtnSelectLevel, nullptr); // ����һ���˵�����������������ť
    pMenu->setPosition(Vec2::ZERO); // ���ò˵���λ��Ϊԭ��
    addChild(pMenu, 1); // ���˵����Ϊ�ӽڵ㣬������ z ��˳��Ϊ 1

} // ��������

//����һ������˵��ķ���
void PauseLayer::createSharedMenu()
{
    //��һ������˵���ʵ�����Ϊ�ӽڵ㣬�㼶Ϊ1
    addChild(SharedMenu::create(), 1);
}

//����һ��������־����ʾ��ͣ���Ƿ�رյķ���
void PauseLayer::setFuncFlagPauseLayerIsClose(const std::function<void()>& rFuncFlagPauseLayerIsClose)
{
    //������ĺ�����ֵ����Ա����_funcFlagPauseLayerIsClose
    _funcFlagPauseLayerIsClose = rFuncFlagPauseLayerIsClose;
}


//�رմ����¼��ķ���
void PauseLayer::closeTouchEvent()
{
    //����һ�����㴥��������
    auto pListener = EventListenerTouchOneByOne::create();

    //���ô�����ʼʱ�Ļص�����������true��ʾ���Ѹ��¼�
    pListener->onTouchBegan = [](Touch* pTouch, Event* pEvent)
    {
        return true;
    };
    //�����Ƿ����ɴ����¼�����ֹ�¼����ݸ��²�ڵ�
    pListener->setSwallowTouches(true);
    //����������ӵ��¼��ַ����У��뵱ǰ�ڵ��
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pListener, this);
}

//������ͣ��ʱ�ķ���
void PauseLayer::onEnter()
{
    //���ø����onEnter����
    Layer::onEnter();
    //��ͣ��Ϸ����ѭ��
    Director::getInstance()->pause();
}

//�˳���ͣ��ʱ�ķ���
void PauseLayer::onExit()
{
    //�����Ϸ����������ͣ״̬Ϊfalse���ָ���Ϸ����ѭ��
    if (!GameManager::getInstance()->getIsPause()) Director::getInstance()->resume();
    //���ø����onExit����
    Layer::onExit();
}






