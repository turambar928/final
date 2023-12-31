#include "TiledMapLayer.h"
#include "SceneManager.h"
#include "MapUtil.h"

bool TiledMapLayer::init()
{
    bool bRet = false;

    do
    {
        // ��ʼ��ͼ��
        CC_BREAK_IF(!Layer::init());

        // ������Դ
        loadSource();

        bRet = true;
    } while (0);

    return bRet;
}

void TiledMapLayer::loadSource()
{
    auto pSceneManager = SceneManager::getInstance();

    // ���ɵ�ǰҳ��͹ؿ���Ӧ�ĵ�ͼ·��
    auto pageLevelStr = StringUtils::format(GAMESCENEMAP, pSceneManager->getCurPageIndex() + 1, pSceneManager->getCurLevelIndex() + 1) + "BGPath.tmx";

    // ����Tiled��ͼ
    _pTiledMap = TMXTiledMap::create(pageLevelStr);
    addChild(_pTiledMap);

    // ���õ�ǰ��ͼΪ�ؿ���ͼ
    MapUtil::getInstance()->setCurrentLevelTiledMap(_pTiledMap);

    // ��������ӱ���
    auto pBg = Sprite::createWithSpriteFrameName("BG1.png");
    pBg->setPosition(VisibleRect::center());
    addChild(pBg);

    // ��������ӵ�ͼͼƬ
    auto pMapImage = Sprite::createWithSpriteFrameName("Path.png");
    pMapImage->setPosition(VisibleRect::center());
    addChild(pMapImage);
}





