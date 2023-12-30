#include "MenuPanelLayer.h" //�����˵������ͷ�ļ�
#include "SoundUtil.h" //�����������ߵ�ͷ�ļ�
#include "PublicSourceDefine.h" //����������Դ�����ͷ�ļ�

/* ����һ����ʼ�����������ڴ������󣬷���һ������ֵ */
bool MenuPanelLayer::init()
{
    bool bRet = false; //����һ���������������ڴ洢����ֵ����ʼֵΪfalse

    do
    {
        CC_BREAK_IF(!Layer::init()); //ʹ�ú궨��һ�������жϣ��������ĳ�ʼ����������false��������ѭ��

        createItemPanel(); //���ô�����Ŀ���ĺ��������ڴ����˵���

        bRet = true; //������ֵ��Ϊtrue
    } while (0); //ѭ������Ϊ0����ʾִֻ��һ��

    return bRet; //���ط���ֵ
}
/* ����һ�����÷�ҳ�����ĺ������������÷�ҳ�Ļص�����������Ϊһ��������������ã���ʾ��ҳ�ĺ��� */
void MenuPanelLayer::setPageTurnFunc(const std::function<void(const bool&)>& rFuncPageTurn)
{
    _funcPageTurn = rFuncPageTurn; //����Ա������ֵΪ�����ĺ������󣬱�ʾ��ҳ�ĺ���
}
/* ����һ��������Ŀ���ĺ��������ڴ����˵��� */
void MenuPanelLayer::createItemPanel()
{
    //����һ���˵���飬����Ϊ����״̬�ľ��飬����״̬�ľ��飬��һ��������������ʾ���ذ�ť
    auto pBtnBack = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ss_back_normal.png"), Sprite::createWithSpriteFrameName("ss_back_pressed.png"), [&](Ref* pSender)
        {
            //����һ��Ԫ�飬����Ϊ��ӭ������ö��ֵ��-1����ֵ��һ��Ԫ���������ʾҪ�л��ĳ���
            auto enWelcomeScene = std::make_tuple(en_WelcomeScene, -1);
            NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enWelcomeScene));
        });
    pBtnBack->setPosition(Vec2(-430, 280));
    //����һ���˵���飬����Ϊ����״̬�ľ��飬����״̬�ľ��飬��һ��������������ʾ��ҳ��ť
    auto pBtnHome = MenuItemSprite::create(Sprite::createWithSpriteFrameName("theme_home_normal.png"), Sprite::createWithSpriteFrameName("theme_home_pressed.png"), [](Ref *pSender)
                                           {
                                               auto enWelcomeScene = std::make_tuple(en_WelcomeScene, -1);//����һ��Ԫ�飬����Ϊ��ӭ������ö��ֵ��-1����ֵ��һ��Ԫ���������ʾҪ�л��ĳ���
                                               NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enWelcomeScene));
                                           });
    pBtnHome->setPosition(Vec2(30, 615));
    //����һ���˵���飬����Ϊ����״̬�ľ��飬����״̬�ľ��飬��һ��������������ʾ������ť
    auto pBtnHelp = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ss_help_normal.png"), Sprite::createWithSpriteFrameName("ss_help_pressed.png"), [](Ref *pSender)
                                           {
            //����һ��Ԫ�飬����Ϊ��Ϸ����������ö��ֵ��0����ֵ��һ��Ԫ���������ʾҪ�л��ĳ���
                                               auto tEnHelpScene = std::make_tuple(en_GameHelpScene, 0);
                                               NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&tEnHelpScene));
                                           });
    pBtnHelp->setPosition(Vec2(930, 615));
    //����һ���˵���飬����Ϊ����״̬�ľ��飬����״̬�ľ��飬��һ��������������ʾ��ҳ��ť
    auto pBtnLeft = MenuItemSprite::create(Sprite::createWithSpriteFrameName("theme_pointleft_normal.png"), Sprite::createWithSpriteFrameName("theme_pointleft_pressed.png"), [this](Ref *pSender)
                                           {
                                               _funcPageTurn(true);//���÷�ҳ����������Ϊtrue����ʾ����ҳ
                                           });
    pBtnLeft->setPosition(Vec2(80, 320));//������ҳ��ť��λ�ã�����Ϊһ����������ʾ��ť��λ��
    
    auto pBtnRight = MenuItemSprite::create(Sprite::createWithSpriteFrameName("theme_pointright_normal.png"), Sprite::createWithSpriteFrameName("theme_pointright_pressed.png"), [this](Ref *pSender)
                                            {
                                                _funcPageTurn(false);//���÷�ҳ����������Ϊfalse����ʾ���ҷ�ҳ
                                            });
    pBtnRight->setPosition(Vec2(880, 320));
    //�����ҷ�ҳ��ť��λ�ã�����Ϊһ����������ʾ��ť��λ��
    auto pMenu = Menu::create(pBtnBack, nullptr);//����һ���˵�������Ϊ���ذ�ť�Ϳ�ָ�룬��ʾ�˵�����
    addChild(pMenu, 16); //���˵����Ϊ�ӽڵ㣬����Ϊ�˵���16����ʾ�˵��Ĳ㼶

}


