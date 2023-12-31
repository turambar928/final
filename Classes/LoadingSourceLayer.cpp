#include "LoadingSourceLayer.h" //����������Դ���ͷ�ļ�

/* ����һ����ʼ�����������ڴ������󣬷���һ������ֵ */
bool LoadingSourceLayer::init()
{
    bool bRet = false; //����һ���������������ڴ洢����ֵ����ʼֵΪfalse

    do
    {
        CC_BREAK_IF(!Layer::init()); //���ø���ĳ�ʼ�����������ʧ�ܣ�����ѭ��
        auto pProgressBarBg = Sprite::create("loading/fight_blood_top.png"); //����һ�����飬ʹ��loading/fight_blood_top.pngͼƬ����ʾ�������ı���
        pProgressBarBg->setPosition(465, 50); //�������λ������Ϊ(465, 50)
        addChild(pProgressBarBg); //��������ӵ���ǰ����
        pProgressBarBg->setScaleX(1.4f); //������ĺ������ű�������Ϊ1.4f

        auto pProgressBar = ProgressTimer::create(Sprite::create("loading/fight_blood_bg.png")); //����һ�����ȼ�ʱ����ʹ��Sprite::create("loading/fight_blood_bg.png")����һ�����飬��ʾ��������ǰ��
        pProgressBar->setType(ProgressTimer::Type::BAR); //���ý��ȼ�ʱ��������Ϊ����
        pProgressBar->setName("progressBar"); //���ý��ȼ�ʱ��������Ϊ"progressBar"
        pProgressBar->setMidpoint(Vec2::ANCHOR_MIDDLE_LEFT); //���ý��ȼ�ʱ�����е�Ϊ����
        pProgressBar->setBarChangeRate(Vec2::ANCHOR_BOTTOM_RIGHT); //���ý��ȼ�ʱ���ı仯��Ϊ����
        pProgressBar->setPercentage(100); //���ý��ȼ�ʱ���İٷֱ�Ϊ100
        pProgressBar->setPosition(465, 50); //�����ȼ�ʱ����λ������Ϊ(465, 50)
        addChild(pProgressBar); //�����ȼ�ʱ����ӵ���ǰ����
        pProgressBar->setScaleX(1.4f); //�����ȼ�ʱ���ĺ������ű�������Ϊ1.4f

        _pLoadingTitle = Label::createWithSystemFont("loading", "Arial", 20); //����һ����ǩ��ʹ��ϵͳ���壬����Ϊ"loading"������Ϊ"Arial"���ֺ�Ϊ20
        addChild(_pLoadingTitle); //����ǩ��ӵ���ǰ����
        _pLoadingTitle->setPosition(Vec2(410, 70)); //����ǩ��λ������Ϊ(410, 70)
        _pLoadingTitle->setAnchorPoint(Vec2(0, 0.5)); //����ǩ��ê������Ϊ(0, 0.5)

        bRet = true; //������ֵ��Ϊtrue
    } while (0); //ѭ������Ϊ0����ʾִֻ��һ��

    return bRet; //���ط���ֵ
}

/* ����һ��������Դ�ĺ����������첽����������Դ����ӵ�����֡������ */
void LoadingSourceLayer::loadSource()
{

    auto pDirector = Director::getInstance(); //��ȡ���ݵ�ʵ������ֵ��һ��ָ�����
    static auto tIndex = 0; //����һ����̬���������������ڴ洢���ص���Դ��������ʼֵΪ0
    for (auto& iterSourceFile : ALLSOURCE) //����������Դ��������ÿ��Ԫ��Ϊһ���ַ�������ʾ��Դ�ļ������ƣ�ʹ�����ñ��⿽��
        pDirector->getInstance()->getTextureCache()->addImageAsync(iterSourceFile + PHOTOPOSTFIX, [&](Texture2D* pTexture) //���õ��ݵ�ʵ������������첽���ͼƬ�ĺ���������ΪͼƬ�ļ������ƣ�ƴ����Դ�ļ������ƺ�ͼƬ��׺����һ���ص�����������Ϊһ��ָ�������ָ��
            {
                SpriteFrameCache::getInstance()->addSpriteFramesWithFile(iterSourceFile + PLISTPOSTFIX, pTexture); //���þ���֡�����ʵ������Ӿ���֡�ĺ���������Ϊplist�ļ������ƣ�ƴ����Դ�ļ������ƺ�plist��׺��������ָ��
                ++tIndex; //����Դ������1
                auto tPercentage = tIndex * 1.0f / ALLSOURCE.size() * 100; //������صİٷֱȣ���ֵ��һ���������
                (dynamic_cast<ProgressTimer*>(getChildByName("progressBar")))->setPercentage(tPercentage); //�������ƻ�ȡ�ӽڵ㣬ǿ������ת��Ϊ���ȼ�ʱ����Ȼ��������ٷֱ�Ϊ���صİٷֱ�
                _pLoadingTitle->setString(StringUtils::format("Loading %.f%%", tPercentage)); //ʹ���ַ��������࣬��ʽ���ַ��������ñ�ǩ������Ϊ���صİٷֱ�
                if (tIndex == ALLSOURCE.size()) _funShowMenuPanel(); //�����Դ��������������Դ�Ĵ�С����ʾ������ɣ�������ʾ�˵����ĺ���

            });
}

/* ����һ��������ʾ�˵����ĺ��������ڴ���һ���������󣬲���Ϊһ��������������� */
void LoadingSourceLayer::setFuncShowMenuPanel(const std::function<void()>& rFuncShowMenuPanel)
{
    _funShowMenuPanel = rFuncShowMenuPanel; //����Ա������ֵΪ�������������
}

/* ����һ�����뺯���������ڲ����ʱִ�� */
void LoadingSourceLayer::onEnter()
{
    Layer::onEnter(); //���ø���Ľ��뺯��
    loadSource(); //���ü�����Դ�ĺ���
}

