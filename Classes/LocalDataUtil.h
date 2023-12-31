#ifndef __CarrotFantasy__LocalDataUtil__ //���û�ж���__CarrotFantasy__LocalDataUtil__�꣬��ֹͷ�ļ��ظ�����
#define __CarrotFantasy__LocalDataUtil__ //����__CarrotFantasy__LocalDataUtil__��

#include "PublicDefine.h" //�������������ͷ�ļ�

class LocalDataUtil : public Ref //����һ���࣬�̳���Ref�࣬���ڹ���������
{
public:

    CREATE_INSTANCE_FUNC(LocalDataUtil); //ʹ�ú궨��һ������ʵ���ĺ��������ڻ�ȡ�������ݹ��ߵĵ���

    DESTROY_INSTANCE_FUNC(); //ʹ�ú궨��һ������ʵ���ĺ����������ͷű������ݹ��ߵĵ���

    virtual ValueMap& getLevelData(); //����һ���麯�������ڻ�ȡ�ؿ����ݣ�����һ��ֵӳ�������

    virtual void setLevelData(const ValueMap& rValueMap); //����һ���麯�����������ùؿ����ݣ�����Ϊһ��ֵӳ�������

protected:

    virtual bool init(); //����һ���麯�������ڳ�ʼ�����󣬷���һ������ֵ

    virtual void registerLevelDataChangeEvent(); //����һ���麯��������ע��ؿ����ݱ仯�¼������һ���۲���

    virtual void levelDataChange(Ref* pData); //����һ���麯���������ڹؿ����ݱ仯ʱִ�У�����Ϊһ���������͵�ָ��

private:

    ValueMap _levelData; //����һ��ֵӳ�����͵ĳ�Ա���������ڴ洢�ؿ�����

    std::string _sLevelDataFileName = ""; //����һ���ַ������͵ĳ�Ա���������ڴ洢�ؿ������ļ�������

private:

    LocalDataUtil() {} //����һ��˽�еĹ��캯�������ڴ������󣬷�ֹ�ⲿ����

    virtual ~LocalDataUtil(); //����һ����������������������ٶ����ͷ���Դ

    LocalDataUtil(const LocalDataUtil&) = delete; //ɾ���������캯������ֹ��������

    LocalDataUtil& operator=(const LocalDataUtil&) = delete; //ɾ����ֵ���������ֹ��ֵ����



};

#endif /* defined(__CarrotFantasy__LocalDataUtil__) */ //������������
