
#include "OptionLayer.h"
#include "SoundUtil.h"
// ��ʼ������������һ������ֵ��ʾ�Ƿ�ɹ���ʼ��
bool OptionLayer::init()
{
    bool bRet = false; // ����һ������ֵ��������ʼΪfalse
    do
    {
        CC_BREAK_IF(!Layer::init()); // �������Layer�ĳ�ʼ��ʧ�ܣ�������ѭ��

        loadSource(); // ����loadSource������������Դ

        bRet = true; // ���÷���ֵΪtrue
    } while (0); // ѭ������Ϊ0��ִֻ��һ��
    return bRet; // ����bRet
}

void OptionLayer::loadSource()
{
    auto pSoundUtil = SoundUtil::getInstance();// ��ȡSoundUtil�ĵ����������ڿ�����Ч
    bool bIsBackGroundSound = pSoundUtil->getIsBackGroundSound();// ��ȡ���������Ƿ�����״̬
    bool bIsEffectSound = pSoundUtil->getIsEffectSound();// ��ȡ��Ч�Ƿ�����״̬
    
    auto pBg = Sprite::createWithSpriteFrameName("setting_bg.png");// ����һ���������������ʾ����ͼƬ
    addChild(pBg); // �������������Ϊ�ӽڵ�
    
    auto pTitle = Sprite::createWithSpriteFrameName("options_normal_CN.png");
    pTitle->setPosition(0, 100);
    addChild(pTitle);
    // ����һ���˵�������������ʾ���ذ�ť
    auto pBtnBack = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ss_back_normal.png"), Sprite::createWithSpriteFrameName("ss_back_pressed.png"), [&](Ref* pSender)
        {
            // ����һ��Ԫ��������ڱ�ʾ��ӭ������ö��ֵ�Ͳ���
            auto enWelcomeScene = std::make_tuple(en_WelcomeScene, 0);
            // ����һ��֪ͨ�������л�����
            NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enWelcomeScene));
        });
    pBtnBack->setPosition(Vec2(0, -215));
    
    // ����һ���˵����л�����������ʾ��Ч����
    auto pEffectSoundBtnOn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("soundfx_on_CN.png"), Sprite::createWithSpriteFrameName("soundfx_on_CN.png"));
    auto pEffectSoundBtnOff = MenuItemSprite::create(Sprite::createWithSpriteFrameName("soundfx_off_CN.png"), Sprite::createWithSpriteFrameName("soundfx_off_CN.png"));
    auto pEffectSoundToggle = MenuItemToggle::createWithCallback(// ����һ���ص������������л���Ч״̬
                                                                [pSoundUtil](Ref *pSender)
                                                                {
                                                                    pSoundUtil->setIsEffectSound(!pSoundUtil->getIsEffectSound());
                                                                },
                                                                 bIsEffectSound ? pEffectSoundBtnOn : pEffectSoundBtnOff,// ������Ч״̬��ѡ����ʾ������رյ�ͼƬ
                                                                 bIsEffectSound ? pEffectSoundBtnOff : pEffectSoundBtnOn,// ������Ч״̬��ѡ����ʾ�رջ�����ͼƬ
                                                                 nullptr);
    pEffectSoundToggle->setPosition(Vec2(0, -120));
    // ����һ���˵����л�����������ʾ�������ֿ���
    auto pBackGroundSoundOn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("bgmusic_on_CN.png"), Sprite::createWithSpriteFrameName("bgmusic_on_CN.png"));
    auto pBackGroundSoundOff = MenuItemSprite::create(Sprite::createWithSpriteFrameName("bgmusic_off_CN.png"), Sprite::createWithSpriteFrameName("bgmusic_off_CN.png"));
    auto pBackGroundSoundToggle = MenuItemToggle::createWithCallback(// ����SoundUtil�ķ��������ñ�������״̬Ϊ�෴ֵ
                                                                     [pSoundUtil](Ref *pSender)
                                                                     {
                                                                         pSoundUtil->setIsBackGroundSound(!pSoundUtil->getIsBackGroundSound());
                                                                     },
                                                                     bIsBackGroundSound ? pBackGroundSoundOn : pBackGroundSoundOff,
                                                                     bIsBackGroundSound ? pBackGroundSoundOff : pBackGroundSoundOn,
                                                                     nullptr);
    pBackGroundSoundToggle->setPosition(Vec2(0, -50));
    auto pMenu = Menu::create(pBtnBack,pBackGroundSoundToggle, pEffectSoundToggle, NULL); 
    pMenu->setPosition(0, 0);
    addChild(pMenu);
}


