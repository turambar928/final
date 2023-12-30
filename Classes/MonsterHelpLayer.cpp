// ��������������ͷ�ļ�
#include "MonsterHelpLayer.h"

// ������������ĳ�ʼ������
bool MonsterHelpLayer::init()
{
    // ����һ���������͵ķ���ֵ����ʼΪfalse
    bool bRet = false;

    // ʹ��do-whileѭ������������
    do
    {
        // �������ĳ�ʼ������ʧ�ܣ�������ѭ��
        CC_BREAK_IF(!Layer::init());

        // ���÷���ֵΪtrue����ʾ��ʼ���ɹ�
        bRet = true;
    }
    // ���ѭ������Ϊ0���ͽ���ѭ��
    while (0);
    // ����һ����������þ���֡�����е���Ϊhelp_monster.png�ľ���֡��ʼ��
    auto monsterHelpLayer = Sprite::createWithSpriteFrameName("help_monster.png");
    // ���þ�������λ��Ϊ(480,280)
    monsterHelpLayer->setPosition(480, 280);
    // ���þ����������ű���Ϊ0.95
    monsterHelpLayer->setScale(0.95f);
    // ������������Ϊ�����������ӽڵ�
    addChild(monsterHelpLayer);
    // ���س�ʼ�����
    return bRet;
}
