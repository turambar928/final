#include "LevelSelectScene.h" //�����ؿ�ѡ�񳡾���ͷ�ļ�
#include "LevelSelectLayer.h" //�����ؿ�ѡ����ͷ�ļ�
#include "SceneManager.h" //����������������ͷ�ļ�

/* ����һ�������������������ٶ����ͷ���Դ */
LevelSelectScene::~LevelSelectScene()
{
    CC_SAFE_RELEASE_NULL(_pLevelSelectLayer); //ʹ�ú궨��һ����ȫ�ͷź���������Ϊָ��ؿ�ѡ����ָ�룬������Ϊnullptr
    sourceManager(std::vector<std::string>{THEMESSOURCE[_iThemeIndex]}, false); //������Դ�������ĺ���������Ϊһ���ַ���������������ǰ�������Դ���ƣ���һ������ֵ����ʾ�Ƿ������Դ������Ϊfalse����ʾж����Դ

}

/* ����һ����ʼ�����������ڴ������󣬷���һ������ֵ */
bool LevelSelectScene::init()
{
    bool bRet = false; //����һ���������������ڴ洢����ֵ����ʼֵΪfalse

    do
    {
        CC_BREAK_IF(!Scene::init()); //���ø���ĳ�ʼ�����������ʧ�ܣ�����ѭ��
        _iThemeIndex = SceneManager::getInstance()->getCurPageIndex(); //��ȡ������������ʵ����Ȼ���ȡ��ǰҳ����������ֵ����Ա����
        sourceManager(std::vector<std::string>{THEMESSOURCE[_iThemeIndex]}, true); //������Դ�������ĺ���������Ϊһ���ַ���������������ǰ�������Դ���ƣ���һ������ֵ����ʾ�Ƿ������Դ������Ϊtrue����ʾ������Դ

        _pLevelSelectLayer = LevelSelectLayer::create(); //���ùؿ�ѡ���Ĵ�������������һ�����󣬸�ֵ��ָ��ؿ�ѡ����ָ��
        _pLevelSelectLayer->retain(); //���ùؿ�ѡ���ı������������������ü�������ֹ���Զ��ͷ�
        bRet = true; //������ֵ��Ϊtrue
    } while (0); //ѭ������Ϊ0����ʾִֻ��һ��

    return bRet; //���ط���ֵ
}

/* ����һ�����뺯���������ڳ�������ʱִ�� */
void LevelSelectScene::onEnter()
{
    Scene::onEnter(); //���ø���Ľ��뺯��
    addChild(_pLevelSelectLayer); //���ؿ�ѡ�����ӵ���ǰ������
}

