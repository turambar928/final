// 包含怪物层的头文件
#include "MonsterLayer.h"
// 包含地图工具的头文件
#include "MapUtil.h"

// 定义怪物层的初始化函数
bool MonsterLayer::init()
{
    // 定义一个布尔类型的返回值，初始为false
    bool bRet = false;

    // 使用do-while循环，方便跳出
    do
    {
        // 如果父类的初始化函数失败，就跳出循环
        CC_BREAK_IF(!Layer::init());

        // 创建一个精灵对象，用精灵帧缓存中的名为start01.png的精灵帧初始化
        auto pStart = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("start01.png"));
        // 设置精灵对象的位置，根据地图工具的函数获取移动路径的第一个点，并做一些偏移
        pStart->setPosition(MapUtil::getInstance()->getMovePoses().at(0) + Vec2(40, -15));
        // 将精灵对象添加为怪物层的子节点
        addChild(pStart);

        // 调用注册怪物死亡事件的函数
        registerMonsterDeadEvent();
        // 设置返回值为true，表示初始化成功
        bRet = true;
    }
    // 如果循环条件为0，就结束循环
    while (0);

    // 返回初始化结果
    return bRet;
}


// 定义一个注册怪物死亡事件的函数
void MonsterLayer::registerMonsterDeadEvent()
{
    // 调用通知中心的函数，添加一个观察者，当收到名为monsterDeadMoney的通知时，调用怪物死亡的函数，不传递任何数据
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(MonsterLayer::monsterDead), "monsterDeadMoney", nullptr);
}

// 定义一个怪物死亡的函数，参数是一个指向引用类型的指针
void MonsterLayer::monsterDead(Ref* pData)
{
    // 将指针转换为一个指向二元组的指针，二元组的元素分别是一个二维向量和一个整数，然后解引用得到二元组的值，赋给一个自动类型的变量
    auto tValue = *(reinterpret_cast<std::tuple<Vec2, int>*>(pData));
    // 从二元组中获取第二个元素，即整数，赋给一个自动类型的变量，表示怪物死亡时掉落的金钱
    auto tMoney = std::get<1>(tValue);
    // 创建一个精灵对象，用字符串格式化函数生成一个文件名，根据金钱的数量选择不同的图片，然后用精灵帧缓存中的对应的精灵帧初始化
    auto pMoney = Sprite::createWithSpriteFrameName(StringUtils::format("money%d.png", tMoney));
    // 从二元组中获取第一个元素，即二维向量，赋给一个自动类型的变量，表示怪物死亡时的位置
    auto pVec2 = std::get<0>(tValue);
    // 设置精灵对象的位置为怪物死亡时的位置
    pMoney->setPosition(pVec2);
    // 将精灵对象添加为怪物层的子节点
    addChild(pMoney);
    // 让精灵对象执行一个序列动作，包括向上移动一段距离，延迟一段时间，渐隐消失，以及一个回调函数，用来从父节点中移除精灵对象
    pMoney->runAction(Sequence::create(MoveBy::create(0.6f, Vec2(0, 100)), DelayTime::create(0.4), FadeOut::create(0.4f), CallFunc::create([=]() {pMoney->removeFromParent(); }), NULL));

}

// 重写层类的退出场景函数
void MonsterLayer::onExit()
{
    // 调用父类的退出场景函数
    Layer::onExit();
    // 调用通知中心的函数，移除所有关于这个对象的观察者
    NOTIFY->removeAllObservers(this);
}
