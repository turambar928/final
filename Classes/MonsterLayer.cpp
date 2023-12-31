// ����������ͷ�ļ�
#include "MonsterLayer.h"
// ������ͼ���ߵ�ͷ�ļ�
#include "MapUtil.h"

// ��������ĳ�ʼ������
bool MonsterLayer::init()
{
    // ����һ���������͵ķ���ֵ����ʼΪfalse
    bool bRet = false;

    // ʹ��do-whileѭ������������
    do
    {
        // �������ĳ�ʼ������ʧ�ܣ�������ѭ��
        CC_BREAK_IF(!Layer::init());

        // ����һ����������þ���֡�����е���Ϊstart01.png�ľ���֡��ʼ��
        auto pStart = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("start01.png"));
        // ���þ�������λ�ã����ݵ�ͼ���ߵĺ�����ȡ�ƶ�·���ĵ�һ���㣬����һЩƫ��
        pStart->setPosition(MapUtil::getInstance()->getMovePoses().at(0) + Vec2(40, -15));
        // ������������Ϊ�������ӽڵ�
        addChild(pStart);

        // ����ע����������¼��ĺ���
        registerMonsterDeadEvent();
        // ���÷���ֵΪtrue����ʾ��ʼ���ɹ�
        bRet = true;
    }
    // ���ѭ������Ϊ0���ͽ���ѭ��
    while (0);

    // ���س�ʼ�����
    return bRet;
}


// ����һ��ע����������¼��ĺ���
void MonsterLayer::registerMonsterDeadEvent()
{
    // ����֪ͨ���ĵĺ��������һ���۲��ߣ����յ���ΪmonsterDeadMoney��֪ͨʱ�����ù��������ĺ������������κ�����
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(MonsterLayer::monsterDead), "monsterDeadMoney", nullptr);
}

// ����һ�����������ĺ�����������һ��ָ���������͵�ָ��
void MonsterLayer::monsterDead(Ref* pData)
{
    // ��ָ��ת��Ϊһ��ָ���Ԫ���ָ�룬��Ԫ���Ԫ�طֱ���һ����ά������һ��������Ȼ������õõ���Ԫ���ֵ������һ���Զ����͵ı���
    auto tValue = *(reinterpret_cast<std::tuple<Vec2, int>*>(pData));
    // �Ӷ�Ԫ���л�ȡ�ڶ���Ԫ�أ�������������һ���Զ����͵ı�������ʾ��������ʱ����Ľ�Ǯ
    auto tMoney = std::get<1>(tValue);
    // ����һ������������ַ�����ʽ����������һ���ļ��������ݽ�Ǯ������ѡ��ͬ��ͼƬ��Ȼ���þ���֡�����еĶ�Ӧ�ľ���֡��ʼ��
    auto pMoney = Sprite::createWithSpriteFrameName(StringUtils::format("money%d.png", tMoney));
    // �Ӷ�Ԫ���л�ȡ��һ��Ԫ�أ�����ά����������һ���Զ����͵ı�������ʾ��������ʱ��λ��
    auto pVec2 = std::get<0>(tValue);
    // ���þ�������λ��Ϊ��������ʱ��λ��
    pMoney->setPosition(pVec2);
    // ������������Ϊ�������ӽڵ�
    addChild(pMoney);
    // �þ������ִ��һ�����ж��������������ƶ�һ�ξ��룬�ӳ�һ��ʱ�䣬������ʧ���Լ�һ���ص������������Ӹ��ڵ����Ƴ��������
    pMoney->runAction(Sequence::create(MoveBy::create(0.6f, Vec2(0, 100)), DelayTime::create(0.4), FadeOut::create(0.4f), CallFunc::create([=]() {pMoney->removeFromParent(); }), NULL));

}

// ��д������˳���������
void MonsterLayer::onExit()
{
    // ���ø�����˳���������
    Layer::onExit();
    // ����֪ͨ���ĵĺ������Ƴ����й����������Ĺ۲���
    NOTIFY->removeAllObservers(this);
}
