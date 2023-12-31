#include "TiledMapLayer.h"
#include "SceneManager.h"
#include "MapUtil.h"

bool TiledMapLayer::init()
{
    bool bRet = false;

    do
    {
        // 初始化图层
        CC_BREAK_IF(!Layer::init());

        // 加载资源
        loadSource();

        bRet = true;
    } while (0);

    return bRet;
}

void TiledMapLayer::loadSource()
{
    auto pSceneManager = SceneManager::getInstance();

    // 生成当前页面和关卡对应的地图路径
    auto pageLevelStr = StringUtils::format(GAMESCENEMAP, pSceneManager->getCurPageIndex() + 1, pSceneManager->getCurLevelIndex() + 1) + "BGPath.tmx";

    // 创建Tiled地图
    _pTiledMap = TMXTiledMap::create(pageLevelStr);
    addChild(_pTiledMap);

    // 设置当前地图为关卡地图
    MapUtil::getInstance()->setCurrentLevelTiledMap(_pTiledMap);

    // 创建并添加背景
    auto pBg = Sprite::createWithSpriteFrameName("BG1.png");
    pBg->setPosition(VisibleRect::center());
    addChild(pBg);

    // 创建并添加地图图片
    auto pMapImage = Sprite::createWithSpriteFrameName("Path.png");
    pMapImage->setPosition(VisibleRect::center());
    addChild(pMapImage);
}





