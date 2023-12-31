// 包含怪物帮助层的头文件
#include "MonsterHelpLayer.h"

// 定义怪物帮助层的初始化函数
bool MonsterHelpLayer::init()
{
    // 定义一个布尔类型的返回值，初始为false
    bool bRet = false;

    // 使用do-while循环，方便跳出
    do
    {
        // 如果父类的初始化函数失败，就跳出循环
        CC_BREAK_IF(!Layer::init());

        // 设置返回值为true，表示初始化成功
        bRet = true;
    }
    // 如果循环条件为0，就结束循环
    while (0);
    // 创建一个精灵对象，用精灵帧缓存中的名为help_monster.png的精灵帧初始化
    auto monsterHelpLayer = Sprite::createWithSpriteFrameName("help_monster.png");
    // 设置精灵对象的位置为(480,280)
    monsterHelpLayer->setPosition(480, 280);
    // 设置精灵对象的缩放比例为0.95
    monsterHelpLayer->setScale(0.95f);
    // 将精灵对象添加为怪物帮助层的子节点
    addChild(monsterHelpLayer);
    // 返回初始化结果
    return bRet;
}
