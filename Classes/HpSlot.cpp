#include "HpSlot.h"
#include "VictimEntityBase.h"

// HpSlot��������
HpSlot::~HpSlot()
{
    CC_SAFE_RELEASE_NULL(_pVictimEntity);
    CC_SAFE_RELEASE_NULL(_pHpSlot);
}

// ����HpSlotʵ���ľ�̬��������
HpSlot* HpSlot::create(VictimEntityBase* pVictimEntity)
{
    auto pHpSlot = new HpSlot();
    if (pHpSlot && pHpSlot->init(pVictimEntity)) {
        pHpSlot->autorelease();
    }
    else {
        CC_SAFE_DELETE(pHpSlot);
    }
    return pHpSlot;
}

// ��ʼ��HpSlot����
bool HpSlot::init(VictimEntityBase* pVictimEntity)
{
    bool bRet = false;

    do
    {
        // ��֤�ܺ���ʵ�������
        CC_SAFE_RETAIN(pVictimEntity);
        _pVictimEntity = pVictimEntity;
        _iHpMax = _pVictimEntity->getIHp();

        // ����������Ѫ������
        auto pHpBg = Sprite::createWithSpriteFrameName("MonsterHP01.png");
        pHpBg->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        addChild(pHpBg);

        // ����������Ѫ������
        _pHpSlot = ProgressTimer::create(Sprite::createWithSpriteFrameName("MonsterHP02.png"));
        _pHpSlot->setType(ProgressTimer::Type::BAR);
        _pHpSlot->setMidpoint(Vec2::ANCHOR_MIDDLE_RIGHT);
        _pHpSlot->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        _pHpSlot->setBarChangeRate(Vec2::ANCHOR_BOTTOM_RIGHT);
        _pHpSlot->setPercentage(0);
        _pHpSlot->setPositionX(2);
        addChild(_pHpSlot);

        bRet = true;
    } while (0);

    return bRet;
}

// ����Ѫ��
void HpSlot::setHp(const int& rIHp)
{
    _pHpSlot->setPercentage(100 - _pVictimEntity->getIHp() * 1.0f / _iHpMax * 100);
}

// ��ȡ���ݳߴ�
const Size& HpSlot::getContentSize() const
{
    return _pHpSlot->getContentSize();
}
