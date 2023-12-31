// SceneBase.cpp

#include "SceneBase.h"

// 管理场景资源加载和卸载
void SceneBase::sourceManager(const std::vector<std::string>& rSourceNameVec, const bool& rBLoad) {
    // 获取精灵帧缓存实例
    auto pSpriteFrameCache = SpriteFrameCache::getInstance();

    // 遍历传入的资源名称向量
    for (auto& iterSourceName : rSourceNameVec) {
        // 如果需要加载资源
        if (rBLoad) {
            // 使用精灵帧缓存加载图片集合和定义
            pSpriteFrameCache->addSpriteFramesWithFile(iterSourceName + PLISTPOSTFIX, iterSourceName + PHOTOPOSTFIX);
        }
        else {
            // 否则从精灵帧缓存中移除指定的图片集合和定义
            pSpriteFrameCache->removeSpriteFramesFromFile(iterSourceName + PLISTPOSTFIX);
        }
    }
}
