#include "SceneManager.h"
#include "SceneFactory.h"
#include "SoundUtil.h"

SceneManager *SceneManager::_gInstance;

bool SceneManager::init()
{
    bool bRet = false;
    do
    {
        registerChangeSceneEvent();  // 注册场景切换事件

        bRet = true;
    } while (0);
    return bRet;
}

void SceneManager::initWelComeScene()
{
    auto enCurScene = std::make_tuple(_enCurScene, 0);  // 初始化当前场景为欢迎场景
    changeScene(enCurScene);  // 调用切换场景函数
}

void SceneManager::unRegisterAllEvent()
{
    NOTIFY->removeAllObservers(this);  // 取消当前场景的所有事件监听
}

void SceneManager::changeScene(const std::tuple<SceneType, int>& rEnSceneType)
{
    Director::getInstance()->getScheduler()->setTimeScale(1);  // 重置时间缩放为正常速度

    auto tSceneType = std::get<0>(rEnSceneType);  // 获取目标场景类型

    // 更新当前关卡或页面索引
    if (en_GameScene == tSceneType) _iCurLevelIndex = std::get<1>(rEnSceneType);
    if (en_LevelSelectScene == tSceneType) _iCurPageIndex = std::get<1>(rEnSceneType);

    // 如果不是游戏场景，播放背景音乐
    if (en_GameScene != tSceneType) SoundUtil::getInstance()->playBackgroundSound(BACKGROUNDSOUND.c_str());

    checkCurPageAndLevel();  // 检查当前页面和关卡

    auto pScene = SceneFactory::createScene(tSceneType);  // 创建目标场景对象

    auto pDirector = Director::getInstance();
    auto pRunScene = pDirector->getRunningScene();

    // 使用场景切换效果（注释部分为使用淡入淡出效果）
    // auto pTransScene = TransitionFade::create(0.2f, pScene);
    // pRunScene ? pDirector->replaceScene(pTransScene) : pDirector->runWithScene(pTransScene);

    pRunScene ? pDirector->replaceScene(pScene) : pDirector->runWithScene(pScene);  // 切换场景
}

void SceneManager::checkCurPageAndLevel()
{
    auto tCurPageLevelCount = THEME_LEVELCOUNT_ARRAY[_iCurPageIndex];  // 获取当前页面的关卡总数
    if (tCurPageLevelCount == _iCurLevelIndex)
    {
        ++_iCurPageIndex;  // 如果当前关卡达到当前页面的关卡总数，切换到下一个页面
        _iCurLevelIndex = 0;  // 重置当前关卡索引为0
    }
}

void SceneManager::notifyChangeScene(Ref* pData)
{
    auto enSceneType = *(reinterpret_cast<std::tuple<SceneType, int> *>(pData));  // 解析传递的场景类型和索引
    changeScene(enSceneType);  // 调用切换场景函数，根据通知的场景类型进行切换
}

void SceneManager::registerChangeSceneEvent()
{
    // 注册事件监听，当收到名为 "changeScene" 的通知时，调用 notifyChangeScene 函数处理
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(SceneManager::notifyChangeScene), "changeScene", nullptr);
}

int SceneManager::getCurPageIndex() const
{
    return _iCurPageIndex;  // 返回当前页面索引
}

int SceneManager::getCurLevelIndex() const
{
    return _iCurLevelIndex;  // 返回当前关卡索引
}



