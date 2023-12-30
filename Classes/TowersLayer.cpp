#include "TowersLayer.h"
#include "TowerManager.h"
#include "TowerBase.h"

/**
 * @brief TowersLayer的初始化函数
 * @return 是否初始化成功
 */
bool TowersLayer::init()
{
    bool bRet = false;

    do
    {
        // 初始化基类Layer
        CC_BREAK_IF(!Layer::init());

        // 获取SpriteFrameCache实例
        auto cache = SpriteFrameCache::getInstance();

        // 遍历TOWERS列表，加载对应的精灵帧缓存
        for (auto& iterSource : TOWERS)
            cache->addSpriteFramesWithFile(iterSource + PLISTPOSTFIX, iterSource + PHOTOPOSTFIX);

        // 注册checkTowerGrade函数，以固定的时间间隔调用
        schedule(CC_SCHEDULE_SELECTOR(TowersLayer::checkTowerGrade));

        // 初始化成功
        bRet = true;
    } while (0);

    return bRet;
}

/**
 * @brief 检查塔的等级并显示升级标志
 * @param dt 与前一帧的时间间隔
 */
void TowersLayer::checkTowerGrade(float dt)
{
    // 遍历TowerManager中的塔向量
    for (auto& item : TowerManager::getInstance()->getTowerVec())
    {
       
        if (item->getIUpgradeCount() <= 1)
        {
            // 如果升级所需金钱小于等于玩家拥有的金钱，显示升级标志
            if (item->getTowerGradeCost() <= TowerManager::getInstance()->getMoney())
                item->showGradeMark();
            else
                item->hideGradeMark();
        }
    }
}
