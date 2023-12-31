#include "MenusLayer.h" //�����˵����ͷ�ļ�
#include "SoundUtil.h" //�����������ߵ�ͷ�ļ�
#include "PublicSourceDefine.h" //����������Դ�����ͷ�ļ�
/* ����һ����ʼ�����������ڴ������󣬷���һ������ֵ */
bool MenusLayer::init()
{
    bool bRet = false; //����һ���������������ڴ洢����ֵ����ʼֵΪfalse

    do
    {
        CC_BREAK_IF(!Layer::init()); //ʹ�ú궨��һ�������жϣ��������ĳ�ʼ����������false��������ѭ��

        createMenuItems(); //���ô����˵���ĺ��������ڴ����˵���ť

        bRet = true; //������ֵ��Ϊtrue
    } while (0); //ѭ������Ϊ0����ʾִֻ��һ��

    return bRet; //���ط���ֵ
}

/* ����һ�������˵���ĺ��������ڴ����˵���ť */
void MenusLayer::createMenuItems()
{
    auto pBtnadventureMode = MenuItemSprite::create(
                                                    Sprite::createWithSpriteFrameName("btn_adventure_normal_CN.png"),//����һ�����飬����Ϊ֡�����е�ͼƬ���ƣ���ʾ����״̬��ͼƬ�����ڴ���ð��ģʽ��ť
                                                    Sprite::createWithSpriteFrameName("btn_adventure_pressed_CN.png"),//����һ�����飬����Ϊ֡�����е�ͼƬ���ƣ���ʾ����״̬��ͼƬ�����ڴ���ð��ģʽ��ť
                                                    [](Ref *pSender)
                                                    {
            //����һ����������������Ϊһ���������͵�ָ�룬��ʾ�����¼��Ķ������ڴ���ð��ģʽ��ť�Ļص�����
                                                        auto enLevelScene = std::make_tuple(en_PageSelectScene, 0);
                                                        //����һ��Ԫ�飬����Ϊ��ҳѡ�񳡾���ö��ֵ��0����ֵ��һ��Ԫ���������ʾҪ�л��ĳ���
                                                        NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enLevelScene));
                                                        //ʹ��֪ͨ���ģ�����һ��֪ͨ������Ϊ"changeScene"��Ҫ�л��ĳ�����ָ�룬��ʾ�����л�����
                                                    }
                                                    );
    
    pBtnadventureMode->setPosition(Vec2(480, 100));
    
    auto pBtnSetting = MenuItemSprite::create(
                                              Sprite::createWithSpriteFrameName("btn_setting_normal.png"),//����һ�����飬����Ϊ֡�����е�ͼƬ���ƣ���ʾ����״̬��ͼƬ�����ڴ������ð�ť
                                              Sprite::createWithSpriteFrameName("btn_setting_pressed.png"),//����һ�����飬����Ϊ֡�����е�ͼƬ���ƣ���ʾ����״̬��ͼƬ�����ڴ������ð�ť
                                              [](Ref *pSender)
                                              {
                                                  auto enGameSettingScene = std::make_tuple(en_GameSettingScene, 0);
                                                  NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enGameSettingScene));
                                              }
                                              );
    pBtnSetting->setPosition(Vec2(200, 220));
    
    auto pBtnHelp = MenuItemSprite::create(
                                           Sprite::createWithSpriteFrameName("btn_help_normal.png"),
                                           Sprite::createWithSpriteFrameName("btn_help_pressed.png"),
                                           [](Ref *pSender)
                                           {
                                               auto tEnGameHelpSceneType = std::make_tuple(en_GameHelpScene, 0);//����һ��Ԫ�飬����Ϊ��Ϸ����������ö��ֵ��0����ֵ��һ��Ԫ���������ʾҪ�л��ĳ���
                                               NOTIFY->postNotification("changeScene", reinterpret_cast<Ref *>(&tEnGameHelpSceneType));
                                           });
    pBtnHelp->setPosition(Vec2(750, 220));
    
    auto pMenu = Menu::create(pBtnadventureMode, pBtnSetting, pBtnHelp, nullptr);//����һ���˵�������Ϊð��ģʽ��ť�����ð�ť��������ť���Ϳ�ָ�룬��ʾ�˵�����
    pMenu->setPosition(Vec2::ZERO);
    addChild(pMenu);//���˵����Ϊ�ӽڵ�


}