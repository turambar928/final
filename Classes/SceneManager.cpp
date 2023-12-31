#include "SceneManager.h"
#include "SceneFactory.h"
#include "SoundUtil.h"

SceneManager *SceneManager::_gInstance;

bool SceneManager::init()
{
    bool bRet = false;
    do
    {
        registerChangeSceneEvent();  // ע�᳡���л��¼�

        bRet = true;
    } while (0);
    return bRet;
}

void SceneManager::initWelComeScene()
{
    auto enCurScene = std::make_tuple(_enCurScene, 0);  // ��ʼ����ǰ����Ϊ��ӭ����
    changeScene(enCurScene);  // �����л���������
}

void SceneManager::unRegisterAllEvent()
{
    NOTIFY->removeAllObservers(this);  // ȡ����ǰ�����������¼�����
}

void SceneManager::changeScene(const std::tuple<SceneType, int>& rEnSceneType)
{
    Director::getInstance()->getScheduler()->setTimeScale(1);  // ����ʱ������Ϊ�����ٶ�

    auto tSceneType = std::get<0>(rEnSceneType);  // ��ȡĿ�곡������

    // ���µ�ǰ�ؿ���ҳ������
    if (en_GameScene == tSceneType) _iCurLevelIndex = std::get<1>(rEnSceneType);
    if (en_LevelSelectScene == tSceneType) _iCurPageIndex = std::get<1>(rEnSceneType);

    // ���������Ϸ���������ű�������
    if (en_GameScene != tSceneType) SoundUtil::getInstance()->playBackgroundSound(BACKGROUNDSOUND.c_str());

    checkCurPageAndLevel();  // ��鵱ǰҳ��͹ؿ�

    auto pScene = SceneFactory::createScene(tSceneType);  // ����Ŀ�곡������

    auto pDirector = Director::getInstance();
    auto pRunScene = pDirector->getRunningScene();

    // ʹ�ó����л�Ч����ע�Ͳ���Ϊʹ�õ��뵭��Ч����
    // auto pTransScene = TransitionFade::create(0.2f, pScene);
    // pRunScene ? pDirector->replaceScene(pTransScene) : pDirector->runWithScene(pTransScene);

    pRunScene ? pDirector->replaceScene(pScene) : pDirector->runWithScene(pScene);  // �л�����
}

void SceneManager::checkCurPageAndLevel()
{
    auto tCurPageLevelCount = THEME_LEVELCOUNT_ARRAY[_iCurPageIndex];  // ��ȡ��ǰҳ��Ĺؿ�����
    if (tCurPageLevelCount == _iCurLevelIndex)
    {
        ++_iCurPageIndex;  // �����ǰ�ؿ��ﵽ��ǰҳ��Ĺؿ��������л�����һ��ҳ��
        _iCurLevelIndex = 0;  // ���õ�ǰ�ؿ�����Ϊ0
    }
}

void SceneManager::notifyChangeScene(Ref* pData)
{
    auto enSceneType = *(reinterpret_cast<std::tuple<SceneType, int> *>(pData));  // �������ݵĳ������ͺ�����
    changeScene(enSceneType);  // �����л���������������֪ͨ�ĳ������ͽ����л�
}

void SceneManager::registerChangeSceneEvent()
{
    // ע���¼����������յ���Ϊ "changeScene" ��֪ͨʱ������ notifyChangeScene ��������
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(SceneManager::notifyChangeScene), "changeScene", nullptr);
}

int SceneManager::getCurPageIndex() const
{
    return _iCurPageIndex;  // ���ص�ǰҳ������
}

int SceneManager::getCurLevelIndex() const
{
    return _iCurLevelIndex;  // ���ص�ǰ�ؿ�����
}



