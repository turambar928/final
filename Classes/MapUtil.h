#ifndef __CarrotFantasy__MapUtil__ //���û�ж���__CarrotFantasy__MapUtil__�꣬��ֹͷ�ļ��ظ�����
#define __CarrotFantasy__MapUtil__ //����__CarrotFantasy__MapUtil__��

#include "PublicDefine.h" //�������������ͷ�ļ�

class MapUtil : public Ref //����һ���࣬�̳���Ref�࣬���ڹ����ͼ����
{
public:

    CREATE_INSTANCE_FUNC(MapUtil); //ʹ�ú궨��һ������ʵ���ĺ��������ڻ�ȡ��ͼ���ߵĵ���

    DESTROY_INSTANCE_FUNC(); //ʹ�ú궨��һ������ʵ���ĺ����������ͷŵ�ͼ���ߵĵ���

    virtual void setCurrentLevelTiledMap(TMXTiledMap* pTiledMap); //����һ���麯�����������õ�ǰ�ؿ�����Ƭ��ͼ������Ϊһ��ָ����Ƭ��ͼ��ָ��

    virtual std::vector<Vec2> getMovePoses(); //����һ���麯�������ڻ�ȡ�ƶ�λ�ã�����һ��������ֵ��ÿ��Ԫ��Ϊһ����������ʾ�ƶ���λ��

    virtual std::vector<std::pair<std::string, Rect>> getBarrierPoses(); //����һ���麯�������ڻ�ȡ�ϰ���λ�ã�����һ���ַ����;��εĶԵ�������ֵ��ÿ��Ԫ��Ϊһ���ַ����;��εĶԣ���ʾ�ϰ�������ƺ�λ��

    virtual std::vector<Rect> getEffectTowerPoses(); //����һ���麯�������ڻ�ȡЧ����λ�ã�����һ������������ֵ��ÿ��Ԫ��Ϊһ�����Σ���ʾЧ������λ��

    virtual void removeBarrierRect(const Vec2& rPos); //����һ���麯���������Ƴ��ϰ�����Σ�����Ϊһ�����������ã���ʾ�ϰ����λ��

protected:

    virtual bool init(); //����һ���麯�������ڳ�ʼ�����󣬷���һ������ֵ

    virtual void clearMap(); //����һ���麯�������������ͼ���ݣ��ͷ���Դ

    virtual void rectTransVec(const Rect& rRect); //����һ���麯�������ڽ������е�ÿ�������λ����ӵ�Ч�������������У�����Ϊһ�����ε�����

private:

    TMXTiledMap* _pTildeMap = nullptr; //����һ��ָ����Ƭ��ͼ��ָ�룬���ڴ洢��ǰ�ؿ�����Ƭ��ͼ

    std::map<int, Vec2>* _pMovePosMap = nullptr; //����һ��ָ���ƶ�λ��ӳ���ָ�룬���ڴ洢�ƶ���������λ��

    std::vector<std::pair<std::string, Rect>>* _pBarrierPosMap = nullptr; //����һ��ָ���ϰ���λ��������ָ�룬���ڴ洢�ϰ�������ƺ�λ��

    std::vector<Rect>* _pEffectTowerRectVec = nullptr; //����һ��ָ��Ч��������������ָ�룬���ڴ洢Ч������λ��

private:

    Size _gridSize; //����һ����С���͵ĳ�Ա���������ڴ洢�����С

    Size _mapSize; //����һ����С���͵ĳ�Ա���������ڴ洢��ͼ��С

private:

    virtual ~MapUtil(); //����һ����������������������ٶ����ͷ���Դ

};


#endif /* defined(__CarrotFantasy__MapUtil__) */ //������������
