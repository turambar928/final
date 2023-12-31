#ifndef __newCardDefence__LevelSelectLayer__ //���û�ж���__newCardDefence__LevelSelectLayer__�꣬��ֹͷ�ļ��ظ�����
#define __newCardDefence__LevelSelectLayer__ //����__newCardDefence__LevelSelectLayer__��

#include "PublicDefine.h" //�������������ͷ�ļ�

class LevelSelectLayer : public Layer //����һ���࣬�̳���Layer�࣬������ʾ�ؿ�ѡ�����
{
public:

    CREATE_FUNC(LevelSelectLayer); //ʹ�ú궨��һ���������������ڴ�������

    virtual ~LevelSelectLayer(); //����һ����������������������ٶ����ͷ���Դ

protected:

    virtual bool init(); //����һ���麯�������ڳ�ʼ�����󣬷���һ������ֵ

    virtual void loadSource(); //����һ���麯�������ڼ�����Դ���Ӿ���֡�����л�ȡͼƬ

    virtual void loadLevel(); //����һ���麯�������ڼ��عؿ����ӱ��������л�ȡ�ؿ�����

    virtual void loadMenuItem(); //����һ���麯�������ڼ��ز˵����������Ӳ˵���

    virtual std::tuple<int, bool> checkLevelIsLockAndBarrierIsClean(const int& rILevelIndex); //����һ�������麯�������ڼ��ؿ��Ƿ��������ϰ����Ƿ����������Ϊһ���������͵����ã���ʾ�ؿ�����������һ��Ԫ�飬����һ��������һ������ֵ

    virtual void changeToGameScene(); //����һ���麯���������л�����Ϸ��������ʼ��Ϸ

    virtual void loadData(); //����һ���麯�������ڼ������ݣ���CSV�ļ��ж�ȡ����

private:

    int _iPageIndex = 0; //����һ���������͵ĳ�Ա���������ڴ洢��ǰҳ����������ʼֵΪ0

    int _iCurLevelIndex = 0; //����һ���������͵ĳ�Ա���������ڴ洢��ǰ�ؿ���������ʼֵΪ0

    ValueMap _DataValueMap; //����һ��ֵӳ�����͵ĳ�Ա���������ڴ洢�ؿ�����

private:

    Sprite* _pLockSprite = nullptr; //����һ��ָ�����ָ�룬���ڴ洢�������飬��ʼֵΪnullptr

    MenuItemSprite* _pStartBtn = nullptr; //����һ��ָ��˵�����ָ�룬���ڴ洢��ʼ��ť����ʼֵΪnullptr
};

#endif /* defined(__newCardDefence__LevelSelectLayer__) */ //������������
