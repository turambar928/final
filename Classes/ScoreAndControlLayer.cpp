#include "ScoreAndControlLayer.h"
#include "PauseLayer.h"
#include "NumSprite.h"
#include "LevelConfigUtil.h"
#include "SoundUtil.h"
#include "PublicSourceDefine.h"
#include "MonsterLayer.h"
#include "GameScene.h"
#include "GameManager.h"

bool ScoreAndControllerLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Layer::init());  // 初始化基类Layer，如果失败则跳出do-while循环

        _iMoney = LevelConfigUtil::getInstance()->getCurLevelMoney();  // 获取当前关卡的金币数

        registerNotifyEvent();  // 注册通知事件

        loadBg();  // 加载背景

        createTopPanel();  // 创建顶部面板

        bRet = true;  // 初始化成功

    } while (0);

    return bRet;
}

void ScoreAndControllerLayer::loadBg()
{
    auto tVisibleSize = Director::getInstance()->getVisibleSize();  // 获取可视区域大小
    auto pPanelBg = Sprite::createWithSpriteFrameName("MenuBG.png");  // 创建背景精灵
    pPanelBg->setPosition(Vec2(tVisibleSize.width / 2, tVisibleSize.height - pPanelBg->getContentSize().height / 2));
    addChild(pPanelBg);  // 将背景精灵添加到当前层

    auto pTitle = Sprite::createWithSpriteFrameName("MenuCenter_01_CN.png");  // 创建标题精灵
    pTitle->setPosition(Vec2(tVisibleSize.width / 2, tVisibleSize.height - pTitle->getContentSize().height / 2 - 5));
    addChild(pTitle);  // 将标题精灵添加到当前层

    auto tSize = Sprite::create(MONSTERBATCHIMAGE)->getContentSize();  // 获取怪物批次图片的大小
    auto pMonsterBatchCountSprite = NumSprite::createNum(StringUtils::format("%d", LevelConfigUtil::getInstance()->getCurLevelMonsterBatchCount()), MONEYNUMIMAGE);  // 创建怪物批次数量数字精灵
    addChild(pMonsterBatchCountSprite);  // 将怪物批次数量数字精灵添加到当前层
    auto tScreenSize = Director::getInstance()->getVisibleSize();
    pMonsterBatchCountSprite->setPosition(tScreenSize.width / 2, 603);  // 设置怪物批次数量数字精灵的位置
    pMonsterBatchCountSprite->release();  // 释放引用

    _pMoneyLabel = NumSprite::createNum(StringUtils::format("%d", _iMoney), MONEYNUMIMAGE);  // 创建金币数数字精灵
    addChild(_pMoneyLabel);  // 将金币数数字精灵添加到当前层
    _pMoneyLabel->release();  // 释放引用
    _pMoneyLabel->setPosition(100, 603);  // 设置金币数数字精灵的位置

    _pMonsterBatchIndex = NumSprite::createNum(StringUtils::format("%02d", 1), MONSTERBATCHIMAGE);  // 创建怪物批次索引数字精灵
    addChild(_pMonsterBatchIndex);  // 将怪物批次索引数字精灵添加到当前层
    _pMonsterBatchIndex->release();  // 释放引用
    _pMonsterBatchIndex->setPosition(379, 603);  // 设置怪物批次索引数字精灵的位置
}


void ScoreAndControllerLayer::createTopPanel()
{
    // 创建速度切换按钮
    auto pSpeedNormalItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("speed11.png"), Sprite::createWithSpriteFrameName("speed12.png"));
    auto pSpeedDoubleItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("speed21.png"), Sprite::createWithSpriteFrameName("speed22.png"));
    auto pSpeedToggleItem = MenuItemToggle::createWithCallback([&](Ref* pSender)
        {
            // 切换速度状态，并设置时间缩放
            auto pScheduler = Director::getInstance()->getScheduler();
            _bIsOpenSpeedUp = !_bIsOpenSpeedUp ? true : false;
            pScheduler->setTimeScale(_bIsOpenSpeedUp ? 2.8 : 1.8);

        }, pSpeedNormalItem, pSpeedDoubleItem, nullptr);
    pSpeedToggleItem->setPosition(185, 280);

    // 创建暂停/继续切换按钮
    auto pPauseItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("pause01.png"), Sprite::createWithSpriteFrameName("pause02.png"));
    auto pContinueItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("pause11.png"), Sprite::createWithSpriteFrameName("pause12.png"));
    auto pPauseItemToggleItem = MenuItemToggle::createWithCallback([&](Ref* pSender)
        {
            // 切换暂停状态，并通知游戏管理器
            auto pDirector = Director::getInstance();
            pDirector->isPaused() ? pDirector->resume() : pDirector->pause();
            auto pGameManager = GameManager::getInstance();
            pGameManager->setIsPause(!pGameManager->getIsPause());

        }, pPauseItem, pContinueItem, nullptr);
    pPauseItemToggleItem->setPosition(285, 280);

    // 创建菜单选择按钮
    auto pChooseItems = MenuItemSprite::create(Sprite::createWithSpriteFrameName("menu01.png"), Sprite::createWithSpriteFrameName("menu02.png"), [&](Ref* pSender)
        {
            this->clickChooseItem();  // 处理菜单选择点击事件
        });
    pChooseItems->setPosition(385, 280);
    _pChooseItem = pChooseItems;  // 保存菜单选择按钮的引用

    // 创建菜单并将按钮添加到菜单中
    auto pMenuPanel = Menu::create(pSpeedToggleItem, pPauseItemToggleItem, pChooseItems, nullptr);
    addChild(pMenuPanel);  // 将菜单添加到当前层
}

void ScoreAndControllerLayer::registerNotifyEvent()
{
    // 注册通知事件，关联到相应的回调函数
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(ScoreAndControllerLayer::monsterBatchChange), "monsterBatchChange", nullptr);
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(ScoreAndControllerLayer::moneyChange), "moneyChange", nullptr);
}


void ScoreAndControllerLayer::unRegisterNotifyEvent()
{
    // 移除当前对象的所有通知观察者
    NOTIFY->removeAllObservers(this);
}

void ScoreAndControllerLayer::moneyChange(cocos2d::Ref* pData)
{
    // 处理金币变化通知，更新金币显示
    setMoneyNum(*(reinterpret_cast<int*>(pData)));
}

void ScoreAndControllerLayer::monsterBatchChange(cocos2d::Ref* pData)
{
    // 处理怪物批次变化通知，更新怪物批次显示
    setMonsterBatchCount(*(reinterpret_cast<int*>(pData)));
}

void ScoreAndControllerLayer::setMoneyNum(const int& rIMoneyNum)
{
    // 保存原始金币标签位置
    auto tPos = _pMoneyLabel->getPosition();

    // 从父节点移除原始金币标签
    _pMoneyLabel->removeFromParent();

    // 更新金币数量并创建新的金币标签
    _iMoney += rIMoneyNum;
    _pMoneyLabel = NumSprite::createNum(StringUtils::format("%d", _iMoney), MONEYNUMIMAGE);

    // 将新的金币标签添加到当前节点，并设置位置
    addChild(_pMoneyLabel);
    _pMoneyLabel->setPosition(tPos);
}

void ScoreAndControllerLayer::setMonsterBatchCount(const int& rIMonsterBatchIndex)
{
    // 保存原始怪物批次标签位置
    auto tPos = _pMonsterBatchIndex->getPosition();

    // 从父节点移除原始怪物批次标签
    _pMonsterBatchIndex->removeFromParent();

    // 创建新的怪物批次标签，并更新显示
    _pMonsterBatchIndex = NumSprite::createNum(StringUtils::format("%02d", rIMonsterBatchIndex), MONSTERBATCHIMAGE);

    // 将新的怪物批次标签添加到当前节点，并设置位置
    addChild(_pMonsterBatchIndex);
    _pMonsterBatchIndex->setPosition(tPos);
}





void ScoreAndControllerLayer::setPauseFlagIsClose()
{
    _bIsOpenChooceMenu = false;
}

void ScoreAndControllerLayer::onExit()
{
    Layer::onExit();
    unRegisterNotifyEvent();
}

void ScoreAndControllerLayer::clickChooseItem()
{
    if(!_bIsOpenChooceMenu)
    {
        auto pPauseLayer = PauseLayer::create();
        pPauseLayer->setFuncFlagPauseLayerIsClose(CC_CALLBACK_0(ScoreAndControllerLayer::setPauseFlagIsClose, this));
        this->addChild(pPauseLayer, 1);
        _bIsOpenChooceMenu = true;
    }
}





