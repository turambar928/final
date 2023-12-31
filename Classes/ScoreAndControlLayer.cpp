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
        CC_BREAK_IF(!Layer::init());  // ��ʼ������Layer�����ʧ��������do-whileѭ��

        _iMoney = LevelConfigUtil::getInstance()->getCurLevelMoney();  // ��ȡ��ǰ�ؿ��Ľ����

        registerNotifyEvent();  // ע��֪ͨ�¼�

        loadBg();  // ���ر���

        createTopPanel();  // �����������

        bRet = true;  // ��ʼ���ɹ�

    } while (0);

    return bRet;
}

void ScoreAndControllerLayer::loadBg()
{
    auto tVisibleSize = Director::getInstance()->getVisibleSize();  // ��ȡ���������С
    auto pPanelBg = Sprite::createWithSpriteFrameName("MenuBG.png");  // ������������
    pPanelBg->setPosition(Vec2(tVisibleSize.width / 2, tVisibleSize.height - pPanelBg->getContentSize().height / 2));
    addChild(pPanelBg);  // ������������ӵ���ǰ��

    auto pTitle = Sprite::createWithSpriteFrameName("MenuCenter_01_CN.png");  // �������⾫��
    pTitle->setPosition(Vec2(tVisibleSize.width / 2, tVisibleSize.height - pTitle->getContentSize().height / 2 - 5));
    addChild(pTitle);  // �����⾫����ӵ���ǰ��

    auto tSize = Sprite::create(MONSTERBATCHIMAGE)->getContentSize();  // ��ȡ��������ͼƬ�Ĵ�С
    auto pMonsterBatchCountSprite = NumSprite::createNum(StringUtils::format("%d", LevelConfigUtil::getInstance()->getCurLevelMonsterBatchCount()), MONEYNUMIMAGE);  // �������������������־���
    addChild(pMonsterBatchCountSprite);  // �����������������־�����ӵ���ǰ��
    auto tScreenSize = Director::getInstance()->getVisibleSize();
    pMonsterBatchCountSprite->setPosition(tScreenSize.width / 2, 603);  // ���ù��������������־����λ��
    pMonsterBatchCountSprite->release();  // �ͷ�����

    _pMoneyLabel = NumSprite::createNum(StringUtils::format("%d", _iMoney), MONEYNUMIMAGE);  // ������������־���
    addChild(_pMoneyLabel);  // ����������־�����ӵ���ǰ��
    _pMoneyLabel->release();  // �ͷ�����
    _pMoneyLabel->setPosition(100, 603);  // ���ý�������־����λ��

    _pMonsterBatchIndex = NumSprite::createNum(StringUtils::format("%02d", 1), MONSTERBATCHIMAGE);  // �������������������־���
    addChild(_pMonsterBatchIndex);  // �����������������־�����ӵ���ǰ��
    _pMonsterBatchIndex->release();  // �ͷ�����
    _pMonsterBatchIndex->setPosition(379, 603);  // ���ù��������������־����λ��
}


void ScoreAndControllerLayer::createTopPanel()
{
    // �����ٶ��л���ť
    auto pSpeedNormalItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("speed11.png"), Sprite::createWithSpriteFrameName("speed12.png"));
    auto pSpeedDoubleItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("speed21.png"), Sprite::createWithSpriteFrameName("speed22.png"));
    auto pSpeedToggleItem = MenuItemToggle::createWithCallback([&](Ref* pSender)
        {
            // �л��ٶ�״̬��������ʱ������
            auto pScheduler = Director::getInstance()->getScheduler();
            _bIsOpenSpeedUp = !_bIsOpenSpeedUp ? true : false;
            pScheduler->setTimeScale(_bIsOpenSpeedUp ? 2.8 : 1.8);

        }, pSpeedNormalItem, pSpeedDoubleItem, nullptr);
    pSpeedToggleItem->setPosition(185, 280);

    // ������ͣ/�����л���ť
    auto pPauseItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("pause01.png"), Sprite::createWithSpriteFrameName("pause02.png"));
    auto pContinueItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("pause11.png"), Sprite::createWithSpriteFrameName("pause12.png"));
    auto pPauseItemToggleItem = MenuItemToggle::createWithCallback([&](Ref* pSender)
        {
            // �л���ͣ״̬����֪ͨ��Ϸ������
            auto pDirector = Director::getInstance();
            pDirector->isPaused() ? pDirector->resume() : pDirector->pause();
            auto pGameManager = GameManager::getInstance();
            pGameManager->setIsPause(!pGameManager->getIsPause());

        }, pPauseItem, pContinueItem, nullptr);
    pPauseItemToggleItem->setPosition(285, 280);

    // �����˵�ѡ��ť
    auto pChooseItems = MenuItemSprite::create(Sprite::createWithSpriteFrameName("menu01.png"), Sprite::createWithSpriteFrameName("menu02.png"), [&](Ref* pSender)
        {
            this->clickChooseItem();  // ����˵�ѡ�����¼�
        });
    pChooseItems->setPosition(385, 280);
    _pChooseItem = pChooseItems;  // ����˵�ѡ��ť������

    // �����˵�������ť��ӵ��˵���
    auto pMenuPanel = Menu::create(pSpeedToggleItem, pPauseItemToggleItem, pChooseItems, nullptr);
    addChild(pMenuPanel);  // ���˵���ӵ���ǰ��
}

void ScoreAndControllerLayer::registerNotifyEvent()
{
    // ע��֪ͨ�¼�����������Ӧ�Ļص�����
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(ScoreAndControllerLayer::monsterBatchChange), "monsterBatchChange", nullptr);
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(ScoreAndControllerLayer::moneyChange), "moneyChange", nullptr);
}


void ScoreAndControllerLayer::unRegisterNotifyEvent()
{
    // �Ƴ���ǰ���������֪ͨ�۲���
    NOTIFY->removeAllObservers(this);
}

void ScoreAndControllerLayer::moneyChange(cocos2d::Ref* pData)
{
    // �����ұ仯֪ͨ�����½����ʾ
    setMoneyNum(*(reinterpret_cast<int*>(pData)));
}

void ScoreAndControllerLayer::monsterBatchChange(cocos2d::Ref* pData)
{
    // ����������α仯֪ͨ�����¹���������ʾ
    setMonsterBatchCount(*(reinterpret_cast<int*>(pData)));
}

void ScoreAndControllerLayer::setMoneyNum(const int& rIMoneyNum)
{
    // ����ԭʼ��ұ�ǩλ��
    auto tPos = _pMoneyLabel->getPosition();

    // �Ӹ��ڵ��Ƴ�ԭʼ��ұ�ǩ
    _pMoneyLabel->removeFromParent();

    // ���½�������������µĽ�ұ�ǩ
    _iMoney += rIMoneyNum;
    _pMoneyLabel = NumSprite::createNum(StringUtils::format("%d", _iMoney), MONEYNUMIMAGE);

    // ���µĽ�ұ�ǩ��ӵ���ǰ�ڵ㣬������λ��
    addChild(_pMoneyLabel);
    _pMoneyLabel->setPosition(tPos);
}

void ScoreAndControllerLayer::setMonsterBatchCount(const int& rIMonsterBatchIndex)
{
    // ����ԭʼ�������α�ǩλ��
    auto tPos = _pMonsterBatchIndex->getPosition();

    // �Ӹ��ڵ��Ƴ�ԭʼ�������α�ǩ
    _pMonsterBatchIndex->removeFromParent();

    // �����µĹ������α�ǩ����������ʾ
    _pMonsterBatchIndex = NumSprite::createNum(StringUtils::format("%02d", rIMonsterBatchIndex), MONSTERBATCHIMAGE);

    // ���µĹ������α�ǩ��ӵ���ǰ�ڵ㣬������λ��
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





