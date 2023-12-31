#include "LoadingScene.h" //�������س�����ͷ�ļ�
#include "GameScene.h" //������Ϸ������ͷ�ļ�
#include "SoundUtil.h" //�����������ߵ�ͷ�ļ�

/* ����һ����ʼ�����������ڴ������󣬷���һ������ֵ */
bool LoadingScene::init()
{
    bool bRet = false; //����һ���������������ڴ洢����ֵ����ʼֵΪfalse
    do
    {
        CC_BREAK_IF(!Scene::init()); //���ø���ĳ�ʼ�����������ʧ�ܣ�����ѭ��

        auto pBg = Sprite::create(LOADINGSOURCE); //����һ�����飬ʹ��LOADINGSOURCE�궨���ͼƬ
        pBg->setPosition(VisibleRect::center()); //�������λ������Ϊ�ɼ����ε�����
        addChild(pBg); //��������ӵ���ǰ������

        bRet = true; //������ֵ��Ϊtrue
    } while (0); //ѭ������Ϊ0����ʾִֻ��һ��
    return bRet; //���ط���ֵ
}

/* ����һ�����뺯���������ڳ�������ʱִ�� */
void LoadingScene::onEnter()
{
    Scene::onEnter(); //���ø���Ľ��뺯��
    SoundUtil::getInstance()->stopBackGroundSound(); //��ȡ�������ߵ�ʵ����Ȼ��ֹͣ��������
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(LoadingScene::sourceLoadCallBack), "loadFinish", nullptr); //ʹ��֪ͨ���ģ����һ���۲��ߣ�����Ϊ��ǰ���󣬻ص�������֪ͨ���ƣ����û�����
    _pGameScene = GameScene::create(); //������Ϸ�����Ĵ�������������һ�����󣬸�ֵ��ָ����Ϸ������ָ��
    _pGameScene->retain(); //������Ϸ�����ı������������������ü�������ֹ���Զ��ͷ�
}

/* ����һ���˳������������ڳ����˳�ʱִ�� */
void LoadingScene::onExit()
{
    NOTIFY->removeAllObservers(this); //ʹ��֪ͨ���ģ��Ƴ����й��ڵ�ǰ����Ĺ۲���
    CC_SAFE_RELEASE_NULL(_pGameScene); //ʹ�ú궨��һ����ȫ�ͷź���������Ϊָ����Ϸ������ָ�룬������Ϊnullptr
    Scene::onExit(); //���ø�����˳�����
}

/* ����һ����Դ���ػص���������������Դ�������ʱִ�У�����Ϊһ���������͵�ָ�� */
void LoadingScene::sourceLoadCallBack(Ref* pData)
{
    auto pTransScene = TransitionFade::create(0.2f, dynamic_cast<Scene*>(pData)); //����һ�����ɳ�����ʹ�õ��뵭����Ч��������Ϊ����ʱ���Ŀ�곡����Ŀ�곡��Ϊ������ǿ������ת��
    Director::getInstance()->replaceScene(pTransScene); //��ȡ���ݵ�ʵ����Ȼ���滻��ǰ����Ϊ���ɳ���
}
