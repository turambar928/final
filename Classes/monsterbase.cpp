// ������������ͷ�ļ�
#include "MonsterBase.h"
// ���������������ͷ�ļ�
#include "MonsterManager.h"
// �����ƶ������������ͷ�ļ�
#include "MoveControllerBase.h"
// �����������ߵ�ͷ�ļ�
#include "SoundUtil.h"

// ��ʼ���������ĺ����������ǹ����ID
bool MonsterBase::init(const int& rIId)
{
    // ����һ������ֵ����ʼΪfalse
    bool bRet = false;

    // ʹ��do-whileѭ�����г�ʼ������
    do
    {
        // ����ܺ���ʵ�����ĳ�ʼ��ʧ�ܣ�������ѭ��
        CC_BREAK_IF(!VictimEntityBase::init(rIId, MONSTERCSVFILE));
        // �����̬���Խӿڵĳ�ʼ��ʧ�ܣ�������ѭ��
        CC_BREAK_IF(!DynamicPropertyInterFace::init(rIId, MONSTERCSVFILE));
        // ���ù���ĳ���Ϊ��
        _bIsLeft = true;
        // ��������Ķ���
        createAnimation();
        // ִ�й���Ķ����������Ƕ������ӳ�ʱ��
        doAction(0.15f);
        // ����һ���ƶ����������󣬲����ǹ��������
        _pMoveController = MoveControllerBase::create(this);
        // �����������ӵ������������
        MonsterManager::getInstance()->addMonster(this);
        // ���÷���ֵΪtrue����ʾ��ʼ���ɹ�
        bRet = true;
    }
    // ���ѭ������Ϊ0���ͽ���ѭ��
    while (0);
    // ���س�ʼ�����
    return  bRet;
}

// �����������ľ�̬�����������ǹ����ID
MonsterBase* MonsterBase::create(const int& rIId)
{
    // ����һ���������ʹ��new�ؼ��ַ����ڴ�
    auto pMonster = new MonsterBase();
    // ����������Ϊ�գ��ҳ�ʼ���ɹ�
    if (pMonster && pMonster->init(rIId)) {
        // �������������ü�����һ����ֹ���Զ��ͷ�
        pMonster->autorelease();
        // ���ع�������ָ��
        return pMonster;
    }
    // ����������Ϊ�գ����߳�ʼ��ʧ��
    // ʹ��CC_SAFE_DELETE�갲ȫ��ɾ����������ͷ��ڴ�
    CC_SAFE_DELETE(pMonster);
    // ���ؿ�ָ��
    return nullptr;
}

// ����������˵Ķ�������ʱΪ��
void MonsterBase::behurtAction()
{

}

// ��������Ķ����ĺ���
void MonsterBase::createAnimation()
{
    // ����һ���ַ���������������Ŷ���֡���ļ���
    std::vector<std::string> tAniamtionFiles;
    // ʹ��forѭ����������֡������
    for (int i = 1; i <= _IAnimationFrameCount; i++)
        // ��ÿһ֡���ļ���ƴ�Ӻ���ӵ��ַ���������
        tAniamtionFiles.push_back(_sModelName + StringUtils::format("%d.png", i));
    // ���ö�̬ʵ�����ĺ����������ַ�������������������
    createDynamicEntityAnimation(tAniamtionFiles);
}

// ִ�й���Ķ����ĺ����������Ƕ������ӳ�ʱ��
void MonsterBase::doAction(const float& rDt)
{
    // ���ö��������ÿ֡�ӳ�ʱ��
    _pAnimation->setDelayPerUnit(rDt);
    // ��ȡ����ľ����������ִ�ж�������Ķ���
    getSprite()->runAction(Animate::create(_pAnimation));
}

// ������������Ķ���������������ʱ��ͼƬ�ļ���
void MonsterBase::deadAction(const std::string& rSDeadImageFile)
{
    // ���ù��﷢�������ĺ���
    MonsterSound();
    // ����һ��֪ͨ������������������Ѿ������������ǹ��������
    NOTIFY->postNotification("MonsterDead", this);
    // ��ȡ����ľ�������Ƴ����������ӽڵ㣬�������Ƿ������ڴ�
    getSprite()->removeAllChildrenWithCleanup(true);
    // ��ȡ������ƶ�����������ֹͣ�������ж���
    _pMoveController->stopAllActions();
    // �����ܺ���ʵ������������������
    VictimEntityBase::deadAction();
}

// ������﷢�������ĺ���
void MonsterBase::MonsterSound()
{
    // ����һ��1��3֮��������������ѡ��ͬ�������ļ�
    int fFigure = rand() % 3 + 1;
    // �������������а���"land"����ʾ��½�ع���
    if (_sName.find("land") != std::string::npos)
    {
        // �����������ߵĺ��������Ŷ�Ӧ�������ļ����������ļ���
        SoundUtil::getInstance()->playEffect(MONSTERMUSIC + StringUtils::format("Land11%d.mp3", fFigure));
    }
    // �������������а���"fly"����ʾ�Ƿ��й���
    else if (_sName.find("fly") != std::string::npos)
    {
        // �����������ߵĺ��������Ŷ�Ӧ�������ļ����������ļ���
        SoundUtil::getInstance()->playEffect(MONSTERMUSIC + StringUtils::format("Fat14%d.mp3", fFigure));
    }
    // �������������а���"fat"����ʾ�Ƿ��ֹ���
    else if (_sName.find("fat") != std::string::npos)
    {
        // �����������ߵĺ��������Ŷ�Ӧ�������ļ����������ļ���
        SoundUtil::getInstance()->playEffect(MONSTERMUSIC + StringUtils::format("Fat14%d.mp3", fFigure));
    }
    // �����������ֶ������������ַ�������ʾ�Ǵ�Boss
    else
    {
        // �����������ߵĺ��������Ŷ�Ӧ�������ļ����������ļ���
        SoundUtil::getInstance()->playEffect(MONSTERMUSIC + "BigBoss.mp3");
    }
}

// ���ù��������ٶȵĺ������������ٶ�ֵ
void MonsterBase::setMaxSpeed(const int& iSpeed)
{
    // ���ö�̬���Խӿڵĺ��������ù�����ٶ�����
    setISpeed(iSpeed);
    // �����ƶ�����������ĺ��������ù�����ƶ��ٶ�
    _pMoveController->setIMonsterSpeed(iSpeed);
}
