#include "AppDelegate.h"
#include "SceneManager.h"
#include "CsvUtil.h"
#include "Config.h"
#include "GameScene.h"
#include "SoundUtil.h"
USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SceneManager::destroyInstance();//���ٳ����������ĵ��������ͷų�����ص��ڴ档
    Config::getInstance()->saveSoundConfig();//�����������õ������ļ��С�
    Config::destroyInstance();//�������ù������ĵ��������ͷ�������ص��ڴ档
    SoundUtil::destroyInstance();//��������������ĵ��������ͷ�������ص��ڴ档
    unLoadSource();//�ͷ���Ϸ��ռ�õľ���֡��CSV �ļ�����Դ��
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();//��ȡһ�� Director ����ĵ��������� Cocos2d-x �ĺ����࣬������������������¼��ȡ�
    auto glview = director->getOpenGLView();//��ȡһ�� GLView ��������һ�� OpenGL ��ͼ��������Ⱦ��Ϸ���档
    if(!glview)
    {
        glview = GLViewImpl::create("My Game");//����һ�� GLViewImpl �������� GLView �ľ���ʵ���࣬����һ���ַ���������Ϊ��Ϸ���ڵı��⡣
        director->setOpenGLView(glview);//�������õ� GLViewImpl �������ø� Director ��������������Ϸ���ڡ�
    }
    glview->setDesignResolutionSize(960, 640, ResolutionPolicy::EXACT_FIT);//������Ϸ���ڵ���Ʒֱ���Ϊ 960x640 ���أ���ʹ�� EXACT_FIT ���ԣ���ǿ��������Ϸ��������Ӧ��ͬ����Ļ�ߴ硣


    
    director->setAnimationInterval(1.0 / 60);//������Ϸ�Ķ������Ϊ 1/60 �룬��ÿ�� 60 ֡������һ����Ϸ�ı�׼֡�ʡ�
    preLoadSource();//����һ���Զ���ĺ���������Ԥ������Ϸ�������Դ������ͼƬ�����֡�����ȣ��������������Ϸ������Ч�ʺ��û����顣
    Config::getInstance()->setSoundConfig();//��ȡһ�� Config ����ĵ���������һ���Զ�����࣬���ڹ�����Ϸ��������Ϣ��Ȼ��������� setSoundConfig ����������������Ϸ���������ã�������������Ч���������ֵȡ�

    SceneManager::getInstance()->initWelComeScene();//��ȡһ�� SceneManager ����ĵ���������һ���Զ�����࣬���ڹ�����Ϸ�ĳ����л���Ȼ��������� initWelComeScene ���������ڳ�ʼ����Ϸ�Ļ�ӭ������������ʾ��Ϸ�ı��⡢�˵�����ť�ȡ�

    return true;
}


void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    //���� Director ����� stopAnimation ������������ͣ��Ϸ�Ķ�����Ⱦ���Խ�ʡ��Դ�͵�����
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();//���� Director ����� startAnimation ���������ڻָ���Ϸ�Ķ�����Ⱦ���Լ�����Ϸ�����С�
    auto pCurScene = Director::getInstance()->getRunningScene();
    if ((pCurScene != NULL) && pCurScene->getName() == "GameScene")
    {
        auto pGameScene = dynamic_cast<GameScene*>(pCurScene);//��ʾ����ʱ������Ϸ�����Ľ����
        if(!pGameScene->getChildByName("CoundDown") && !pGameScene->getChildByName("GameEnd"))
            dynamic_cast<GameScene*>(pCurScene)->clickChooseItem();
    }
   
}

void AppDelegate::preLoadSource()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Themes/scene/mainscene1-hd.plist", "Themes/scene/mainscene1-hd.png");//��ȡһ�� SpriteFrameCache ����ĵ���
    auto pCsvUtil = CsvUtil::getInstance();//��ȡһ�� CsvUtil ����ĵ���,��ȡ�ͽ��� CSV �ļ�
    pCsvUtil->addFileData(BARRIERCSVFILE);//���� CsvUtil ����� addFileData ���������ڴ�ָ���� CSV �ļ��ж�ȡ���ݣ�������洢���ڴ���
    pCsvUtil->addFileData(TOWERCSVFILE);
    pCsvUtil->addFileData(MONSTERCSVFILE);
    pCsvUtil->addFileData(BULLETCSVFILE);
    pCsvUtil->addFileData(LEVELCSVFILE);
}


void AppDelegate::unLoadSource()
{
    SpriteFrameCache::getInstance()->removeSpriteFrames();//��������е����о���֡���ͷ��ڴ�ռ䡣
    CsvUtil::destroyInstance();//���� CsvUtil ����ĵ���
}






