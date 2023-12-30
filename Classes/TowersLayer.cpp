#include "TowersLayer.h"
#include "TowerManager.h"
#include "TowerBase.h"

/**
 * @brief TowersLayer�ĳ�ʼ������
 * @return �Ƿ��ʼ���ɹ�
 */
bool TowersLayer::init()
{
    bool bRet = false;

    do
    {
        // ��ʼ������Layer
        CC_BREAK_IF(!Layer::init());

        // ��ȡSpriteFrameCacheʵ��
        auto cache = SpriteFrameCache::getInstance();

        // ����TOWERS�б����ض�Ӧ�ľ���֡����
        for (auto& iterSource : TOWERS)
            cache->addSpriteFramesWithFile(iterSource + PLISTPOSTFIX, iterSource + PHOTOPOSTFIX);

        // ע��checkTowerGrade�������Թ̶���ʱ��������
        schedule(CC_SCHEDULE_SELECTOR(TowersLayer::checkTowerGrade));

        // ��ʼ���ɹ�
        bRet = true;
    } while (0);

    return bRet;
}

/**
 * @brief ������ĵȼ�����ʾ������־
 * @param dt ��ǰһ֡��ʱ����
 */
void TowersLayer::checkTowerGrade(float dt)
{
    // ����TowerManager�е�������
    for (auto& item : TowerManager::getInstance()->getTowerVec())
    {
       
        if (item->getIUpgradeCount() <= 1)
        {
            // ������������ǮС�ڵ������ӵ�еĽ�Ǯ����ʾ������־
            if (item->getTowerGradeCost() <= TowerManager::getInstance()->getMoney())
                item->showGradeMark();
            else
                item->hideGradeMark();
        }
    }
}
