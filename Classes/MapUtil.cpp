
#include "MapUtil.h" //������ͼ���ߵ�ͷ�ļ�

MapUtil* MapUtil::_gInstance; //����һ��ָ���ͼ���ߵ�ָ�룬��ʾ��ͼ���ߵĵ���

/* ����һ�������������������ٶ����ͷ���Դ */
MapUtil::~MapUtil()
{
    CC_SAFE_DELETE(_pMovePosMap); //ʹ�ú궨��һ����ȫɾ������������Ϊָ���ƶ�λ��ӳ���ָ�룬�ͷ��ڴ�
    CC_SAFE_DELETE(_pBarrierPosMap); //ʹ�ú궨��һ����ȫɾ������������Ϊָ���ϰ���λ��������ָ�룬�ͷ��ڴ�
    CC_SAFE_DELETE(_pEffectTowerRectVec); //ʹ�ú궨��һ����ȫɾ������������Ϊָ��Ч��������������ָ�룬�ͷ��ڴ�
    CC_SAFE_RELEASE_NULL(_pTildeMap); //ʹ�ú궨��һ����ȫ�ͷź���������Ϊָ����Ƭ��ͼ��ָ�룬������Ϊnullptr
}

/* ����һ����ʼ�����������ڴ������󣬷���һ������ֵ */
bool MapUtil::init()
{
    bool bRet = false; //����һ���������������ڴ洢����ֵ����ʼֵΪfalse

    do
    {
        _pBarrierPosMap = new std::vector<std::pair<std::string, Rect>>; //ʹ��new�����������һ��ָ���ϰ���λ��������ָ�룬ÿ��Ԫ��Ϊһ���ַ����;��εĶԣ���ʾ�ϰ�������ƺ�λ��
        _pEffectTowerRectVec = new std::vector<Rect>; //ʹ��new�����������һ��ָ��Ч��������������ָ�룬ÿ��Ԫ��Ϊһ�����Σ���ʾЧ������λ��
        _pMovePosMap = new std::map<int, Vec2>; //ʹ��new�����������һ��ָ���ƶ�λ��ӳ���ָ�룬ÿ��Ԫ��Ϊһ�������������Ķԣ���ʾ�ƶ���������λ��

        bRet = true; //������ֵ��Ϊtrue
    } while (0); //ѭ������Ϊ0����ʾִֻ��һ��

    return bRet; //���ط���ֵ
}

/* ����һ�����õ�ǰ�ؿ���Ƭ��ͼ�ĺ���������Ϊһ��ָ����Ƭ��ͼ��ָ�� */
void MapUtil::setCurrentLevelTiledMap(cocos2d::TMXTiledMap* pTiledMap)
{
    clearMap(); //���������ͼ�ĺ��������֮ǰ�ĵ�ͼ����
    CC_SAFE_RELEASE_NULL(_pTildeMap); //ʹ�ú궨��һ����ȫ�ͷź���������Ϊָ����Ƭ��ͼ��ָ�룬������Ϊnullptr
    CC_SAFE_RETAIN(pTiledMap); //ʹ�ú궨��һ����ȫ��������������Ϊָ����Ƭ��ͼ��ָ�룬���������ü�������ֹ���Զ��ͷ�
    _pTildeMap = pTiledMap; //����Ա������ֵΪ������ָ��
    _gridSize = _pTildeMap->getTileSize(); //������Ƭ��ͼ�Ļ�ȡ��Ƭ��С�ĺ�������ֵ��һ����С��������ʾ�����С
    _mapSize = Size(_pTildeMap->getMapSize().width * _gridSize.width, _pTildeMap->getMapSize().height * _gridSize.height); //�����ͼ�Ĵ�С����ֵ��һ����С��������ʾ��ͼ��С

    auto tMapGroup = _pTildeMap->getObjectGroup("PATH"); //������Ƭ��ͼ�Ļ�ȡ������ĺ���������Ϊ"PATH"����ֵ��һ��ָ���������ʾ·��������
    auto tObjs = tMapGroup->getObjects(); //���ö�����Ļ�ȡ����ĺ�������ֵ��һ��ֵ������������ʾ����ļ���

    for (auto& iter : tObjs) //��������ļ��ϣ�ÿ��Ԫ��Ϊһ��ֵ����ʾ��������ԣ�ʹ�����ñ��⿽��
    {
        auto tObjMap = iter.asValueMap(); //�������ֵת��Ϊֵӳ�䣬��ֵ��һ��ֵӳ���������ʾ���������ӳ��
        auto tObjName = tObjMap.at("name").asString(); //�Ӷ��������ӳ���и���"name"��ȡֵ��ת��Ϊ�ַ�������ֵ��һ���ַ�����������ʾ���������
        auto tX = tObjMap.at("x").asFloat(); //�Ӷ��������ӳ���и���"x"��ȡֵ��ת��Ϊ����������ֵ��һ�������������ʾ����ĺ�����
        auto tY = tObjMap.at("y").asFloat(); //�Ӷ��������ӳ���и���"y"��ȡֵ��ת��Ϊ����������ֵ��һ�������������ʾ�����������
        auto tPos = Vec2(tX, tY); //����һ������������Ϊ����ĺ�����������꣬��ֵ��һ��������������ʾ�����λ��
        auto tWidth = tObjMap.at("width").asFloat(); //�Ӷ��������ӳ���и���"width"��ȡֵ��ת��Ϊ����������ֵ��һ�������������ʾ����Ŀ��
        auto tHeight = tObjMap.at("height").asFloat(); //�Ӷ��������ӳ���и���"height"��ȡֵ��ת��Ϊ����������ֵ��һ�������������ʾ����ĸ߶�
        auto tRect = Rect(tX, tY, tWidth, tHeight); //����һ�����Σ�����Ϊ����ĺ����꣬�����꣬��ȣ��߶ȣ���ֵ��һ�����α�������ʾ����ľ���

        if (tObjName.find("PT") != std::string::npos) //�������������а���"PT"����ʾ�ƶ���
        {
            _pMovePosMap->insert(std::make_pair(atoi(tObjName.substr(2).c_str()), tPos)); //�����������ȥ��ǰ�����ַ���ת��Ϊ��������Ϊ���������λ����Ϊֵ�����뵽�ƶ�λ��ӳ����
            continue; //��������ѭ����������һ��ѭ��
        }
        if (tObjName.find("Obj") != std::string::npos) //�������������а���"Obj"����ʾ�ϰ���
        {
            rectTransVec(tRect); //���þ���ת�������ĺ���������Ϊ����ľ��Σ��������е�ÿ�������λ����ӵ��ϰ���λ��������
            continue; //��������ѭ����������һ��ѭ��
        }

        auto tIndex = tObjName.find("Ob"); //�ڶ���������в���"Ob"������һ��λ�ñ�������ʾ"Ob"��λ��
        if (std::string::npos != tIndex) //���λ�ò�������Чֵ����ʾ�ҵ���"Ob"
        {
            _pBarrierPosMap->push_back(std::make_pair(tObjName.substr(0, tIndex + 2), tRect)); //����������ƽ�ȡǰtIndex+2���ַ�����Ϊ��������ľ�����Ϊֵ����ӵ��ϰ���λ��������
            continue; //��������ѭ����������һ��ѭ��
        }

        _pEffectTowerRectVec->push_back(tRect); //������ľ�����ӵ�Ч��������������
    }
}
void MapUtil::clearMap()
{
    _pEffectTowerRectVec->clear(); //����Ч������������������������������Ԫ��
    _pBarrierPosMap->clear(); //�����ϰ���λ������������������������Ԫ��
    _pMovePosMap->clear(); //�����ƶ�λ��ӳ�������������������Ԫ��
}

/* ����һ������ת�������ĺ��������ڽ������е�ÿ�������λ����ӵ�Ч�������������У�����Ϊһ�����ε����� */
void MapUtil::rectTransVec(const Rect& rRect)
{
    auto tWidth = rRect.size.width; //��ȡ���εĿ�ȣ���ֵ��һ���������
    auto tHeight = rRect.size.height; //��ȡ���εĸ߶ȣ���ֵ��һ���������
    auto tX = rRect.origin.x; //��ȡ���εĺ����꣬��ֵ��һ���������
    auto tY = rRect.origin.y; //��ȡ���ε������꣬��ֵ��һ���������
    if (TILESIZE == tWidth && TILESIZE == tHeight) //������εĿ�Ⱥ͸߶ȶ�������Ƭ��С����ʾ����ֻ����һ������
    {
        _pEffectTowerRectVec->push_back(Rect(tX, tY, _gridSize.width, _gridSize.height)); //�����εĺ����꣬�����꣬�����ȣ�����߶ȣ�����һ�����Σ���ӵ�Ч��������������
        return; //���أ���������
    }
    if (tWidth > TILESIZE && tHeight > TILESIZE) //������εĿ�Ⱥ͸߶ȶ�������Ƭ��С����ʾ���ΰ����������
    {
        for (int i = 0; i < tWidth / TILESIZE; ++i) //�������εĿ�ȣ�ÿ������һ����Ƭ��С
        {
            for (int j = 0; j < tHeight / TILESIZE; ++j) //�������εĸ߶ȣ�ÿ������һ����Ƭ��С
            {
                _pEffectTowerRectVec->push_back(Rect(tX + TILESIZE * i, tY + TILESIZE * j, TILESIZE, TILESIZE)); //�����εĺ����������Ƭ��С����i�������������Ƭ��С����j����Ƭ��С����Ƭ��С������һ�����Σ���ӵ�Ч��������������
            }
        }
        return; //���أ���������
    }

    if (tWidth > TILESIZE) //������εĿ�ȴ�����Ƭ��С����ʾ���ΰ���һ�ж��е�����
    {
        for (int i = 0; i < tWidth / TILESIZE; ++i) //�������εĿ�ȣ�ÿ������һ����Ƭ��С
        {
            _pEffectTowerRectVec->push_back(Rect(tX + i * TILESIZE, tY, _gridSize.width, _gridSize.height)); //�����εĺ����������Ƭ��С����i�������꣬�����ȣ�����߶ȣ�����һ�����Σ���ӵ�Ч��������������
        }
    }

    if (tHeight > TILESIZE) //������εĸ߶ȴ�����Ƭ��С����ʾ���ΰ���һ�ж��е�����
    {
        for (int i = 0; i < tHeight / TILESIZE; ++i) //�������εĸ߶ȣ�ÿ������һ����Ƭ��С
        {
            _pEffectTowerRectVec->push_back(Rect(tX, tY + i * TILESIZE, _gridSize.width, _gridSize.height)); //�����εĺ����꣬�����������Ƭ��С����i�������ȣ�����߶ȣ�����һ�����Σ���ӵ�Ч��������������
        }
    }
}

/* ����һ����ȡ�ƶ�λ�õĺ���������һ��������ֵ��ÿ��Ԫ��Ϊһ����������ʾ�ƶ���λ�� */
std::vector<Vec2> MapUtil::getMovePoses()
{
    std::vector<Vec2> tRetMovePosVec; //����һ���������������ڴ洢�ƶ�λ�õ�����
    for (auto& iter : *_pMovePosMap) //�����ƶ�λ��ӳ�䣬ÿ��Ԫ��Ϊһ�������������Ķԣ���ʾ�ƶ���������λ�ã�ʹ�����ñ��⿽��
        tRetMovePosVec.push_back(iter.second); //���ƶ�λ��ӳ���е�ֵ�����ƶ���λ�ã���ӵ��ƶ�λ�õ�������

    return tRetMovePosVec; //�����ƶ�λ�õ�����
}
/* ����һ����ȡЧ����λ�õĺ���������һ������������ֵ��ÿ��Ԫ��Ϊһ�����Σ���ʾЧ������λ�� */
std::vector<Rect> MapUtil::getEffectTowerPoses()
{
    return *_pEffectTowerRectVec; //����Ч��������������ֵ
}

/* ����һ����ȡ�ϰ���λ�õĺ���������һ���ַ����;��εĶԵ�������ֵ��ÿ��Ԫ��Ϊһ���ַ����;��εĶԣ���ʾ�ϰ�������ƺ�λ�� */
std::vector<std::pair<std::string, Rect>> MapUtil::getBarrierPoses()
{
    return *_pBarrierPosMap; //�����ϰ���λ��������ֵ
}

/* ����һ���Ƴ��ϰ�����εĺ������������ϰ��ﱻ����ʱ�����ϰ���λ���������Ƴ���Ӧ�ľ��Σ�����Ϊһ�����������ã���ʾ�ϰ����λ�� */
void MapUtil::removeBarrierRect(const Vec2& rPos)
{
    for (auto barrierIter = _pBarrierPosMap->begin(); barrierIter != _pBarrierPosMap->end(); ++barrierIter) //�����ϰ���λ��������ÿ��Ԫ��Ϊһ���ַ����;��εĶԣ���ʾ�ϰ�������ƺ�λ�ã�ʹ�õ���������ɾ��
    {
        auto tBarrier = *barrierIter; //�����õ���������ֵ��һ���ַ����;��εĶԱ�������ʾ��ǰ���ϰ���
        if (tBarrier.second.containsPoint(rPos)) //����ϰ���ľ��ΰ���������λ�ã���ʾ�ҵ��˶�Ӧ���ϰ���
        {
            rectTransVec(tBarrier.second); //���þ���ת�������ĺ���������Ϊ�ϰ���ľ��Σ��������е�ÿ�������λ����ӵ�Ч��������������
            _pBarrierPosMap->erase(barrierIter); //���ϰ���λ��������ɾ��������ָ���Ԫ��
            break; //����ѭ������������
        }
    }
}






