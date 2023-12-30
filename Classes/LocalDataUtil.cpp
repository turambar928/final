#include "LocalDataUtil.h" //�����������ݹ��ߵ�ͷ�ļ�

LocalDataUtil* LocalDataUtil::_gInstance; //����һ��ָ�򱾵����ݹ��ߵ�ָ�룬��ʾ�������ݹ��ߵĵ���

/* ����һ����ʼ�����������ڴ������󣬷���һ������ֵ */
bool LocalDataUtil::init()
{
    bool bRet = false; //����һ���������������ڴ洢����ֵ����ʼֵΪfalse
    do
    {
        auto pFileUtil = FileUtils::getInstance(); //��ȡ�ļ����ߵ�ʵ������ֵ��һ��ָ�����
        _sLevelDataFileName = pFileUtil->getWritablePath() + DATAFILE; //��ȡ��д·����ƴ�������ļ������ƣ���ֵ��һ���ַ�����������ʾ�ؿ������ļ�������
        _levelData = pFileUtil->getValueMapFromFile(_sLevelDataFileName); //�ӹؿ������ļ��л�ȡֵӳ�䣬��ֵ��һ��ֵӳ���������ʾ�ؿ�����

        registerLevelDataChangeEvent(); //����ע��ؿ����ݱ仯�¼��ĺ��������ڼ����ؿ����ݵı仯
        bRet = true; //������ֵ��Ϊtrue
    } while (0); //ѭ������Ϊ0����ʾִֻ��һ��

    return  bRet; //���ط���ֵ
}

/* ����һ�������������������ٶ����ͷ���Դ */
LocalDataUtil::~LocalDataUtil()
{
    NOTIFY->removeAllObservers(this); //ʹ��֪ͨ���ģ��Ƴ����й��ڵ�ǰ����Ĺ۲���
}

/* ����һ����ȡ�ؿ����ݵĺ���������һ��ֵӳ������� */
ValueMap& LocalDataUtil::getLevelData()
{
    return _levelData; //���عؿ�����
}

/* ����һ�����ùؿ����ݵĺ���������Ϊһ��ֵӳ������� */
void LocalDataUtil::setLevelData(const ValueMap& rValueMap)
{
    _levelData = rValueMap; //���ؿ����ݸ�ֵΪ������ֵӳ��
    FileUtils::getInstance()->writeToFile(_levelData, _sLevelDataFileName); //��ȡ�ļ����ߵ�ʵ����Ȼ�󽫹ؿ�����д�뵽�ؿ������ļ���
}

/* ����һ��ע��ؿ����ݱ仯�¼��ĺ������������һ���۲��ߣ������ؿ����ݵı仯 */
void LocalDataUtil::registerLevelDataChangeEvent()
{
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(LocalDataUtil::levelDataChange), LEVELDATACHANGE, nullptr); //ʹ��֪ͨ���ģ����һ���۲��ߣ�����Ϊ��ǰ���󣬻ص�������֪ͨ���ƣ����û�����
}

/* ����һ���ؿ����ݱ仯�Ļص������������ڹؿ����ݱ仯ʱִ�У�����Ϊһ���������͵�ָ�� */
void LocalDataUtil::levelDataChange(Ref* pData)
{
    auto tLevelData = *(reinterpret_cast<std::tuple<int, int, int, int>*>(pData)); //��������ָ��ǿ������ת��Ϊһ��ָ��Ԫ���ָ�룬Ȼ������ã���ֵ��һ��Ԫ���������ʾ�ؿ�����
    auto tLevelType = std::get<0>(tLevelData); //��Ԫ���л�ȡ��0��Ԫ�أ���ֵ��һ��������������ʾ�ؿ�����
    auto tData = std::get<1>(tLevelData); //��Ԫ���л�ȡ��1��Ԫ�أ���ֵ��һ��������������ʾ�ؿ�����
    auto tThemeIndex = std::get<2>(tLevelData); //��Ԫ���л�ȡ��2��Ԫ�أ���ֵ��һ��������������ʾ��������
    auto tLevelIndex = std::get<3>(tLevelData); //��Ԫ���л�ȡ��3��Ԫ�أ���ֵ��һ��������������ʾ�ؿ�����
    auto tLevelKey = StringUtils::format(LEVELKEY, tThemeIndex, tLevelIndex); //ʹ���ַ��������࣬��ʽ���ַ�����ƴ�����������͹ؿ���������ֵ��һ���ַ�����������ʾ�ؿ���
    auto tCurLevelData = _levelData[tLevelKey].asInt(); //�ӹؿ������и��ݹؿ�����ȡֵ��ת��Ϊ��������ֵ��һ��������������ʾ��ǰ�ؿ�����
    auto tCarrotType = tCurLevelData / 10; //����ǰ�ؿ����ݳ���10��ȡ�̣���ֵ��һ��������������ʾ���ܲ�����
    auto tBarrierCleanFlag = tCurLevelData % 10; //����ǰ�ؿ����ݳ���10��ȡ�࣬��ֵ��һ��������������ʾ�ϰ��������־

    if (!tLevelType) //����ؿ�����Ϊ0����ʾ���ܲ�����
    {
        if (tCarrotType < tData) _levelData[tLevelKey] = StringUtils::format("%d%d", tData, tBarrierCleanFlag); //������ܲ�����С�ڹؿ����ݣ���ʾ���ܲ��������������ؿ����ݸ�ֵΪ�ؿ����ݺ��ϰ��������־��ƴ��
    }
    else //����ؿ�����Ϊ1����ʾ�ϰ��������־
    {
        _levelData[tLevelKey] = StringUtils::format("%d%d", tCarrotType, tData); //���ؿ����ݸ�ֵΪ���ܲ����ͺ͹ؿ����ݵ�ƴ��
    }

    FileUtils::getInstance()->writeToFile(_levelData, _sLevelDataFileName); //��ȡ�ļ����ߵ�ʵ����Ȼ�󽫹ؿ�����д�뵽�ؿ������ļ���
}

