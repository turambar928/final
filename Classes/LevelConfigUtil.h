#ifndef __CarrotFantasy__LevelConfigUtil__ //���û�ж���__CarrotFantasy__LevelConfigUtil__�꣬��ֹͷ�ļ��ظ�����
#define __CarrotFantasy__LevelConfigUtil__ //����__CarrotFantasy__LevelConfigUtil__��

#include "PublicDefine.h" //�������������ͷ�ļ�

class LevelConfigUtil :public Ref //����һ���࣬�̳���Ref�࣬���ڹ���ؿ�����
{
public:

    CREATE_INSTANCE_FUNC(LevelConfigUtil); //ʹ�ú궨��һ������ʵ���ľ�̬���������ڻ�ȡ��������

    DESTROY_INSTANCE_FUNC(); //ʹ�ú궨��һ������ʵ���ľ�̬�����������ͷŵ�������

    virtual void loadLevelConfig(); //����һ���麯�������ڼ��عؿ����ã���XML�ļ��ж�ȡ����

    virtual std::tuple<int, int, int, std::vector<std::string>> getLevelConfig()const; //����һ�������麯�������ڻ�ȡ�ؿ����ã�����һ��Ԫ�飬������ǰҳ����������ǰ�ؿ�����������������������Ӱ�����������б�

    virtual std::vector<std::string> getCurLevelTowersInfo()const; //����һ�������麯�������ڻ�ȡ��ǰ�ؿ�������Ϣ������һ���ַ�������������Ӱ�����������б�

    virtual int getCurLevelMonsterBatchCount()const; //����һ�������麯�������ڻ�ȡ��ǰ�ؿ��Ĺ�����������������һ������

    virtual void buildLevelConfig(); //����һ���麯�������ڹ����ؿ����ã���CSV�ļ��ж�ȡ���ݣ�Ȼ������XML�ļ�

    virtual int getCurLevelMoney()const; //����һ�������麯�������ڻ�ȡ��ǰ�ؿ��Ľ�Ǯ������һ������

protected:

    virtual bool init(); //����һ���麯�������ڳ�ʼ�����󣬷���һ������ֵ

protected:

    int _iCurPageIndex = 0; //����һ���������͵ĳ�Ա���������ڴ洢��ǰҳ����������ʼֵΪ0

    int _iCurLevelIndex = 0; //����һ���������͵ĳ�Ա���������ڴ洢��ǰ�ؿ���������ʼֵΪ0

    int _iCurLevelMoney = 0; //����һ���������͵ĳ�Ա���������ڴ洢��ǰ�ؿ���Ǯ����ʼֵΪ0

    int _iMonsterBatchCount = 0; //����һ���������͵ĳ�Ա���������ڴ洢����������������ʼֵΪ0

    std::vector<std::string>* _pEffectTowers = nullptr; //����һ��ָ���ַ���������ָ�룬���ڴ洢Ӱ�����������б���ʼֵΪnullptr

private:

    LevelConfigUtil(); //����һ��˽�еĹ��캯�������ڴ�������ʵ�ֵ���ģʽ

    virtual ~LevelConfigUtil(); //����һ����������������������ٶ����ͷ���Դ

    LevelConfigUtil(const LevelConfigUtil&) = delete; //ɾ���������캯������ֹ���󱻸���

    LevelConfigUtil& operator=(const LevelConfigUtil&) = delete; //ɾ����ֵ���������ֹ���󱻸�ֵ
};

#endif /* defined(__CarrotFantasy__LevelConfigUtil__) */ //������������
