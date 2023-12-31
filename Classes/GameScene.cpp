#include "GameScene.h"
#include "SceneManager.h"
#include "OptLayer.h"
#include "MonsterLayer.h"
#include "ScoreAndControlLayer.h"
#include "TiledMapLayer.h"
#include "TowersLayer.h"
#include "BarriersLayer.h"
#include "BulletsLayer.h"
#include "BulletManager.h"
#include "TowerManager.h"
#include "BarrierManager.h"
#include "MonsterManager.h"
#include "MapUtil.h"
#include "BarrierBase.h"
#include "CollisionManager.h"
#include "MonsterBuilder.h"
#include "TowerFactory.h"
#include "Carrot.h"
#include "TowerOptBtn.h"
#include "CountDownLayer.h"
#include "GameEndLayer.h"
#include "SoundUtil.h"
#include "LevelConfigUtil.h"

GameScene::~GameScene()
{
	CC_SAFE_RELEASE_NULL(_pOptLayer);
	CC_SAFE_RELEASE_NULL(_pScoreAndControllerLayer);
	CC_SAFE_RELEASE_NULL(_pTowersLayer);
	CC_SAFE_RELEASE_NULL(_pMonsterLayer);
	CC_SAFE_RELEASE_NULL(_pBarriersLayer);
	CC_SAFE_RELEASE_NULL(_pBulletsLayer);
	CC_SAFE_RELEASE_NULL(_pTiledMapLayer);
	CC_SAFE_RELEASE_NULL(_pCarrot);
	clearAllManager();
    CC_SAFE_DELETE(_pSourceVec);
}

bool GameScene::init()
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(!Scene::init());
        
        _pSourceVec = new std::vector<std::string>;
        this->setName("GameScene");
		preLoadSource();

		bRet = true;
        
	} while (0);
	return bRet;
}

void GameScene::createLayers()
{
    //创建地图层
    _pTiledMapLayer = TiledMapLayer::create();
    _pTiledMapLayer->retain();
    //障碍物
    _pBarriersLayer = BarriersLayer::create();
    _pBarriersLayer->retain();
    BarrierManager::getInstance()->setFuncAddBarrierToLayer(CC_CALLBACK_1(BarriersLayer::addEntity, _pBarriersLayer));
    //怪物
    _pMonsterLayer = MonsterLayer::create();
    _pMonsterLayer->setName("monsterLayer");
    _pMonsterLayer->retain();
    MonsterManager::getInstance()->setFuncAddMonsterToLayer(CC_CALLBACK_1(MonsterLayer::addEntity, _pMonsterLayer));
    //防御塔
    _pTowersLayer = TowersLayer::create();
    _pTowersLayer->retain();

    TowerManager::getInstance()->setFuncAddTowerLayer(CC_CALLBACK_1(TowersLayer::addEntity, _pTowersLayer));
    //子弹
    _pBulletsLayer = BulletsLayer::create();
	_pBulletsLayer->setTag(1);
    _pBulletsLayer->retain();
    BulletManager::getInstance()->setFuncAddBulletLayer(CC_CALLBACK_1(BulletsLayer::addEntity, _pBulletsLayer));
    //分数与控制器
    _pScoreAndControllerLayer = ScoreAndControllerLayer::create();
    _pScoreAndControllerLayer->retain();
	TowerManager::getInstance()->setFuncCheckMoney(CC_CALLBACK_0(ScoreAndControllerLayer::getCurMoney, dynamic_cast<ScoreAndControllerLayer*>(_pScoreAndControllerLayer)));
    //操作按钮
    _pOptLayer = OptLayer::create();
    _pOptLayer->retain();
    dynamic_cast<TowerOptBtn*>(_pOptLayer->getChildByName("towerOptBtn"))->setFuncCheckMoney(CC_CALLBACK_0(ScoreAndControllerLayer::getCurMoney, dynamic_cast<ScoreAndControllerLayer*>(_pScoreAndControllerLayer)));
    //萝卜
    _pCarrot = Carrot::create();
    _pCarrot->retain();
}

void GameScene::preLoadSource()
{
    //游戏场景的资源文件的加载
    auto tICurPageIndex = SceneManager::getInstance()->getCurPageIndex() + 1;
    auto tICurLevelIndex = SceneManager::getInstance()->getCurLevelIndex() + 1;
    auto tSSourceBg1Str = StringUtils::format(GAMESCENEBG1, tICurPageIndex);
    
    LevelConfigUtil::getInstance()->loadLevelConfig();
    
    _pSourceVec->push_back(StringUtils::format(GAMESCENEBG1, tICurPageIndex));
    _pSourceVec->push_back(StringUtils::format(GAMESCENEMAP, tICurPageIndex, tICurLevelIndex) + "BG-hd");
    _pSourceVec->push_back(StringUtils::format(GAMESCENEBARRIER, tICurPageIndex));
    _pSourceVec->push_back(StringUtils::format(GAMESCENEMONSTER1, tICurPageIndex));
    _pSourceVec->push_back(StringUtils::format(GAMESCENEMONSTER2, tICurPageIndex));
    
    for(auto &iterSourceName : *_pSourceVec)
        Director::getInstance()->getTextureCache()->addImageAsync(iterSourceName + PHOTOPOSTFIX, [&](Texture2D *pTexture)
    {
        ++_iSourceCount;
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(iterSourceName + PLISTPOSTFIX, pTexture);
        if(_iSourceCount == _pSourceVec->size())
        {
            createLayers();
            NOTIFY->postNotification("loadFinish", static_cast<Ref*>(this));
        }
    });
}

void GameScene::unLoadSource()
{
	sourceManager(*_pSourceVec, false);
}

void GameScene::addLayers()
{
    //添加图层
    auto pCountDownLayer = CountDownLayer::create();
    pCountDownLayer->setName("CoundDown");
    
    addChild(pCountDownLayer, 100);
    
	addChild(_pTiledMapLayer);
    
	addChild(_pBarriersLayer);
    
	addChild(_pTowersLayer);
    
	addChild(_pMonsterLayer);
    
	addChild(_pBulletsLayer);
    
	addChild(_pOptLayer);
    
	addChild(_pScoreAndControllerLayer);
}

void GameScene::onEnter()
{
    //入口
	Scene::onEnter();
    
    addLayers();

	createBarriers();

	_pMonsterLayer->addEntity(_pCarrot);

	registerGameEvent();
    
    SoundUtil::getInstance()->playBackgroundSound(StringUtils::format(THEMEBACKGROUNDMUSIC, SceneManager::getInstance()->getCurPageIndex() + 1).c_str());
	
	schedule(CC_SCHEDULE_SELECTOR(GameScene::collisionUpDate), 0.2);
}

void GameScene::onExit()
{
	NOTIFY->removeAllObservers(this);
	unLoadSource();
	Scene::onExit();
}

void GameScene::collisionUpDate(float dt)
{
    //更新消失图像
	CollisionManager::collision(BarrierManager::getInstance()->getBarrierVec(), MonsterManager::getInstance()->getMonsterVec(), BulletManager::getInstance()->getBulletVec());
}

void GameScene::createBarriers()
{
    //创建障碍物
	auto barriers = MapUtil::getInstance()->getBarrierPoses();
	CsvUtil * pCsvUtil = CsvUtil::getInstance();
	for (auto &iter : barriers)
	{
		int iLine = pCsvUtil->findValueInWithLine(iter.first, 1, BARRIERCSVFILE);
		Vec2 tPos = iter.second.origin;
		Size tSize = iter.second.size;
		auto pBarrier = BarrierBase::create(iLine);
		pBarrier->setPosition(Vec2(tPos.x + tSize.width / 2, tPos.y + tSize.height / 2));
	}
}

void GameScene::clearAllManager()
{
    //清除
	BarrierManager::getInstance()->clearManager();
	MonsterManager::getInstance()->clearManager();
	TowerManager::getInstance()->clearManager();
	BulletManager::getInstance()->clearManager();
}

void GameScene::registerGameEvent()
{
	NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(GameScene::showGameEndLayer), "gameEnd", nullptr);
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(GameScene::startBuildMonster), "startBuildMonster", nullptr);
}

void GameScene::showGameEndLayer(Ref *pDate)
{
    //游戏结束
	auto tGameEndType = *(reinterpret_cast<GameEndType*>(pDate));
    auto pGameEndLayer = GameEndLayer::create(tGameEndType);
    pGameEndLayer->setName("GameEnd");
	addChild(pGameEndLayer, 1);
}

void GameScene::startBuildMonster(Ref *pData)
{
    //建立怪兽
    addChild(MonsterBuilder::create());
    auto pScheduler = Director::getInstance()->getScheduler();
    pScheduler->setTimeScale(1.6);
}

Carrot* GameScene::getCarrot(){
	return _pCarrot;
}

void GameScene::clickChooseItem()
{
    dynamic_cast<ScoreAndControllerLayer*>(_pScoreAndControllerLayer)->clickChooseItem();
}

