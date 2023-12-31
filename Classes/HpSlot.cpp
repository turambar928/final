#include "HpSlot.h"
#include "VictimEntityBase.h"

// HpSlot析构函数
HpSlot::~HpSlot()
{
    CC_SAFE_RELEASE_NULL(_pVictimEntity);
    CC_SAFE_RELEASE_NULL(_pHpSlot);
}

// 创建HpSlot实例的静态工厂方法
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

// 初始化HpSlot对象
bool HpSlot::init(VictimEntityBase* pVictimEntity)
{
    bool bRet = false;

    do
    {
        // 保证受害者实体的引用
        CC_SAFE_RETAIN(pVictimEntity);
        _pVictimEntity = pVictimEntity;
        _iHpMax = _pVictimEntity->getIHp();

        // 创建并设置血条背景
        auto pHpBg = Sprite::createWithSpriteFrameName("MonsterHP01.png");
        pHpBg->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        addChild(pHpBg);

        // 创建并设置血条进度
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

// 设置血量
void HpSlot::setHp(const int& rIHp)
{
    _pHpSlot->setPercentage(100 - _pVictimEntity->getIHp() * 1.0f / _iHpMax * 100);
}

// 获取内容尺寸
const Size& HpSlot::getContentSize() const
{
    return _pHpSlot->getContentSize();
}
