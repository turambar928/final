
#include "LevelConfigUtil.h"
#include "external/tinyxml2/tinyxml2.h"
#include "CsvUtil.h"
#include "SceneManager.h"
using namespace tinyxml2;
// LevelConfigUtil��ľ�̬ʵ��
LevelConfigUtil* LevelConfigUtil::_gInstance;

// LevelConfigUtil���캯��
LevelConfigUtil::LevelConfigUtil()
{
}

// LevelConfigUtil��������
LevelConfigUtil::~LevelConfigUtil()
{
    // �ͷ�_effectTowers���ڴ�
    CC_SAFE_DELETE(_pEffectTowers);
}

// LevelConfigUtil��ʼ������
bool LevelConfigUtil::init()
{
    // ����ֵ��Ĭ��Ϊfalse
    bool bRet = false;

    do
    {
        // ����һ���µ��ַ����������ڴ洢Ч����������
        _pEffectTowers = new std::vector<std::string>;

        // ��ʼ���ɹ���������ֵ��Ϊtrue
        bRet = true;
    } while (0);

    // ���س�ʼ�����
    return bRet;
}


void LevelConfigUtil::loadLevelConfig() //����һ�����������ڼ��عؿ�����
{
    _pEffectTowers->clear(); //���Ӱ����������

    tinyxml2::XMLDocument tXmlDoc; //����һ��XML�ĵ�����

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  //���Ŀ��ƽ̨�ǰ�׿
    //auto sFileName = FileUtils::getInstance()->fullPathForFilename(LEVELCONFIGFILENAME); //��ȡ�ؿ������ļ�������·����ע�͵��Ĵ��룩
    tinyxml2::XMLError pError; //����һ��XML�������
    std::string sFileName = LEVELCONFIGFILENAME; //���ؿ������ļ�����ֵ���ַ�������
    ssize_t* temp = 0;    //����һ��ָ���С���͵�ָ�룬��ʼ��Ϊ0
    unsigned char* pBuffer = NULL; //����һ��ָ���޷����ַ���ָ�룬��ʼ��ΪNULL
    pBuffer = FileUtils::sharedFileUtils()->getFileData(sFileName, "r", temp); //����FileUtils�ľ�̬��������ֻ��ģʽ��ȡ�ؿ������ļ������ݣ�������洢��pBufferָ����ڴ��У�ͬʱ���ļ��Ĵ�С��ֵ��tempָ��ı���
    if (pBuffer) //���pBuffer��Ϊ�գ�˵���ļ����ݻ�ȡ�ɹ�
    {
        pError = tXmlDoc.Parse((const char*)pBuffer); //��pBufferָ�������ת��Ϊ�����ַ�ָ�룬Ȼ����tXmlDoc�����������������ֵ��pError
    }
    else //����˵���ļ����ݻ�ȡʧ��
    {
        CCLOG("[%d]%s %s error ", __LINE__, __func__, __FILE__); //��ӡ������Ϣ�������кţ����������ļ���
        return;// nullptr; //���ؿ�ָ�룬��������
    }

    //if (tXmlDoc.LoadFile(sFileName.c_str()) != tinyxml2::XML_NO_ERROR) //�����tXmlDoc�����ļ�����Ӧ���ļ������������XML�޴���ע�͵��Ĵ��룩
    //    CCLOG("[%d]%s %s error ", __LINE__, __func__, __FILE__); //��ӡ������Ϣ�������кţ����������ļ���
    //else //����˵�����سɹ�
    //    CCLOG("[%d]%s %s OK ", __LINE__, __func__, __FILE__); //��ӡ�ɹ���Ϣ�������кţ����������ļ���
#else //���Ŀ��ƽ̨���ǰ�׿
    auto sFileName = FileUtils::getInstance()->fullPathForFilename(LEVELCONFIGFILENAME); //��ȡ�ؿ������ļ�������·��

    auto tIndex = sFileName.find(LEVELCONFIGFILENAME); //������·���в��ҹؿ������ļ�����λ��

    sFileName = sFileName.substr(0, tIndex); //��ȡ����·���дӿ�ͷ���ļ���λ�õ����ַ�������Ϊ�µ��ļ�·��

    //auto tfile = LEVELCONFIGFILENAME.substr(2, LEVELCONFIGFILENAME.size() - 2); //��ȡ�ؿ������ļ����дӵڶ����ַ��������ڶ����ַ������ַ�����ע�͵��Ĵ��룩
    auto tfile = LEVELCONFIGFILENAME;//.substr(0, LEVELCONFIGFILENAME.size()); //���ؿ������ļ�����ֵ���ַ�������

    CCLOG("[1]config %s  %s %s", LEVELCONFIGFILENAME.c_str(), sFileName.c_str(), ((std::string)tfile).c_str()); //��ӡ������Ϣ�������ؿ������ļ������ļ�·�����ļ���
    sFileName = sFileName + tfile; //���ļ�·�����ļ���ƴ����������Ϊ�µ�����·��
    CCLOG("[2]config %s  %s %s", LEVELCONFIGFILENAME.c_str(), sFileName.c_str(), ((std::string)tfile).c_str()); //��ӡ������Ϣ�������ؿ������ļ���������·�����ļ���

    tXmlDoc.LoadFile(sFileName.c_str()); //��tXmlDoc��������·����Ӧ���ļ�
    //CCLOG("[%d]%s %s", __LINE__, __func__, __FILE__); //��ӡ��Ϣ�������кţ����������ļ�����ע�͵��Ĵ��룩
#endif //������������

    auto pRoot = tXmlDoc.RootElement(); //��ȡXML�ĵ��ĸ�Ԫ��

    auto pSceneManager = SceneManager::getInstance(); //��ȡ������������ʵ��

    auto pLevelElement = pRoot->FirstChildElement(StringUtils::format("%d_%02d", pSceneManager->getCurPageIndex() + 1, pSceneManager->getCurLevelIndex() + 1).c_str()); //���ݳ����������ĵ�ǰҳ�������͵�ǰ�ؿ���������ʽ���ַ�����Ȼ���ڸ�Ԫ���в��ҵ�һ��ƥ�����Ԫ�أ���Ϊ�ؿ�Ԫ��

    auto pElement = pLevelElement->FirstChildElement(); //��ȡ�ؿ�Ԫ�صĵ�һ����Ԫ��

    while (pElement) //����Ԫ�ز�Ϊ��ʱ��ѭ��ִ�����²���
    {
        if (LEVELCONFIGTYPE[0] == pElement->Name()) //�����Ԫ�ص����Ƶ��ڹؿ��������͵ĵ�һ��Ԫ�أ���"page"
            _iCurPageIndex = pElement->IntAttribute(LEVELCONFIGTYPE[0].c_str()); //����Ԫ�ص�"page"���Ե�����ֵ��ֵ����ǰҳ������
        if (LEVELCONFIGTYPE[1] == pElement->Name()) //�����Ԫ�ص����Ƶ��ڹؿ��������͵ĵڶ���Ԫ�أ���"level"
            _iCurLevelIndex = pElement->IntAttribute(LEVELCONFIGTYPE[1].c_str()); //����Ԫ�ص�"level"���Ե�����ֵ��ֵ����ǰ�ؿ�����
        if (LEVELCONFIGTYPE[2] == pElement->Name()) //�����Ԫ�ص����Ƶ��ڹؿ��������͵ĵ�����Ԫ�أ���"money"
            _iCurLevelMoney = pElement->IntAttribute(LEVELCONFIGTYPE[2].c_str()); //����Ԫ�ص�"money"���Ե�����ֵ��ֵ����ǰ�ؿ���Ǯ
        if (LEVELCONFIGTYPE[3] == pElement->Name()) //�����Ԫ�ص����Ƶ��ڹؿ��������͵ĵ��ĸ�Ԫ�أ���"monsterBatchCount"
            _iMonsterBatchCount = pElement->IntAttribute(LEVELCONFIGTYPE[3].c_str()); //����Ԫ�ص�"monsterBatchCount"���Ե�����ֵ��ֵ��������������


        if (TOWERTYPE == pElement->Name()) //�����Ԫ�ص����Ƶ��������ͣ���"tower"
        {
            auto pTower = pElement->FirstChildElement(); //��ȡ��Ԫ�صĵ�һ����Ԫ�أ���Ϊ��Ԫ��

            while (pTower) //����Ԫ�ز�Ϊ��ʱ��ѭ��ִ�����²���
            {
                _pEffectTowers->push_back(pTower->Name()); //����Ԫ�ص�������ӵ�Ӱ������������
                pTower = pTower->NextSiblingElement(); //����Ԫ��ָ����һ���ֵ�Ԫ��
            }
            return; //���أ���������
        }
        pElement = pElement->NextSiblingElement(); //����Ԫ��ָ����һ���ֵ�Ԫ��
    }
}

std::tuple<int, int, int, std::vector<std::string>> LevelConfigUtil::getLevelConfig()const //����һ��������Ա���������ڻ�ȡ�ؿ����ã�����һ��Ԫ�飬������ǰҳ����������ǰ�ؿ�����������������������Ӱ�����������б�
{
    return std::make_tuple(_iCurPageIndex, _iCurLevelIndex, _iMonsterBatchCount, *_pEffectTowers); //ʹ��std::make_tuple���������ݳ�Ա������ֵ������������һ��Ԫ��
}

std::vector<std::string> LevelConfigUtil::getCurLevelTowersInfo()const //����һ��������Ա���������ڻ�ȡ��ǰ�ؿ�������Ϣ������һ���ַ�������������Ӱ�����������б�
{
    return *_pEffectTowers; //����Ӱ�����������б������
}

int LevelConfigUtil::getCurLevelMonsterBatchCount()const //����һ��������Ա���������ڻ�ȡ��ǰ�ؿ��Ĺ�����������������һ������
{
    return _iMonsterBatchCount; //���ع�������������ֵ
}

int LevelConfigUtil::getCurLevelMoney()const //����һ��������Ա���������ڻ�ȡ��ǰ�ؿ��Ľ�Ǯ������һ������
{
    return _iCurLevelMoney; //���ؽ�Ǯ��ֵ
}

void LevelConfigUtil::buildLevelConfig() //����һ����Ա���������ڹ����ؿ����ã���CSV�ļ��ж�ȡ���ݣ�Ȼ������XML�ļ�
{
    auto pCsvUtil = CsvUtil::getInstance(); //��ȡCsvUtil��ʵ�������ڲ���CSV�ļ�
    pCsvUtil->addFileData(LEVELCSVFILE); //���ؿ����õ�CSV�ļ���������ӵ�CsvUtil��

    auto tColumnRowCount = pCsvUtil->getFileRowColNum(LEVELCSVFILE); //��ȡ�ؿ����õ�CSV�ļ���������������һ��Ԫ��

    auto tColumn = std::get<0>(tColumnRowCount); //��Ԫ���л�ȡ����
    auto tRow = std::get<1>(tColumnRowCount); //��Ԫ���л�ȡ����

    auto pXmldoc = new tinyxml2::XMLDocument; //����һ��XML�ĵ��������ڲ���XML�ļ�

    auto pLevelConfigRoot = pXmldoc->NewElement(LEVELCONFIGROOT.c_str()); //����һ���µ�XMLԪ�أ���Ϊ�ؿ����õĸ�Ԫ�أ�����ΪLEVELCONFIGROOT
    pXmldoc->LinkEndChild(pLevelConfigRoot); //����Ԫ�����ӵ�XML�ĵ���

    for (int row = 1; row < tRow; ++row) //�ӵ�һ�п�ʼ������ÿһ�У����������У���ͷ��
    {

        auto tColumnCount = 0; //��ʼ���м���Ϊ0
        auto tThemeIndex = pCsvUtil->getInt(row, 0, LEVELCSVFILE); //��CSV�ļ��л�ȡ��row�е�0�е�����ֵ����Ϊ��������
        auto tLevelIndex = pCsvUtil->getInt(row, 1, LEVELCSVFILE); //��CSV�ļ��л�ȡ��row�е�1�е�����ֵ����Ϊ�ؿ�����

        auto pLevelElement = pXmldoc->NewElement(StringUtils::format("%d_%02d", tThemeIndex, tLevelIndex).c_str()); //����һ���µ�XMLԪ�أ���Ϊ�ؿ�Ԫ�أ�����Ϊ���������͹ؿ������ĸ�ʽ���ַ���
        pLevelConfigRoot->LinkEndChild(pLevelElement); //���ؿ�Ԫ�����ӵ���Ԫ����
        for (int column = 0; column < 4; ++column) //�ӵ�0�п�ʼ������ǰ���У��ֱ��Ӧpage, level, money, monsterBatchCount
        {
            auto pElement = pXmldoc->NewElement(LEVELCONFIGTYPE[column].c_str()); //����һ���µ�XMLԪ�أ�����ΪLEVELCONFIGTYPE�����еĵ�column��Ԫ��
            auto tValue = pCsvUtil->getInt(row, column, LEVELCSVFILE); //��CSV�ļ��л�ȡ��row�е�column�е�����ֵ����ΪԪ�ص�ֵ
            pElement->SetAttribute(LEVELCONFIGTYPE[column].c_str(), StringUtils::format("%d", tValue).c_str()); //��Ԫ�ص���������ΪLEVELCONFIGTYPE�����еĵ�column��Ԫ�أ�ֵΪ��ʽ���������ֵ
            pLevelElement->LinkEndChild(pElement); //��Ԫ�����ӵ��ؿ�Ԫ����
            tColumnCount = column; //�����м���Ϊcolumn
        }
        ++tColumnCount; //�����м���
        auto pTowerElement = pXmldoc->NewElement(TOWERTYPE.c_str()); //����һ���µ�XMLԪ�أ���Ϊ��Ԫ�أ�����ΪTOWERTYPE
        pLevelElement->LinkEndChild(pTowerElement); //����Ԫ�����ӵ��ؿ�Ԫ����
        for (; tColumnCount < tColumn; ++tColumnCount) //�ӵ����п�ʼ������ʣ����У��ֱ��Ӧ��ͬ���͵���
        {

            auto tValue = pCsvUtil->getInt(row, tColumnCount, LEVELCSVFILE); //��CSV�ļ��л�ȡ��row�е�tColumnCount�е�����ֵ����Ϊ����ֵ
            if (1 == tValue) //�������ֵΪ1����ʾ�����͵����ڵ�ǰ�ؿ��п���
            {
                auto pElement = pXmldoc->NewElement(LEVELCONFIGTYPE[tColumnCount].c_str()); //����һ���µ�XMLԪ�أ�����ΪLEVELCONFIGTYPE�����еĵ�tColumnCount��Ԫ�أ���ʾ��������
                pTowerElement->LinkEndChild(pElement); //��Ԫ�����ӵ���Ԫ����
            }
        }
    }

    pXmldoc->SaveFile((FileUtils::getInstance()->getWritablePath() + "LevelConfig.xml").c_str()); //��XML�ĵ����浽�ļ��У��ļ���ΪLevelConfig.xml��·��ΪFileUtils�Ŀ�д·��
    pCsvUtil->releaseFile(LEVELCSVFILE); //�ͷ�CsvUtil�еĹؿ����õ�CSV�ļ�������
    delete pXmldoc; //ɾ��XML�ĵ�����
}



