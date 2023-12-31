#ifndef __newCardDefence__LevelSelectScene__ //���û�ж���__newCardDefence__LevelSelectScene__�꣬��ֹͷ�ļ��ظ�����
#define __newCardDefence__LevelSelectScene__ //����__newCardDefence__LevelSelectScene__��

#include "SceneBase.h" //�������������ͷ�ļ�

class LevelSelectScene : public SceneBase //����һ���࣬�̳���SceneBase�࣬������ʾ�ؿ�ѡ�񳡾�
{
public:

    CREATE_FUNC(LevelSelectScene); //ʹ�ú궨��һ���������������ڴ�������

    virtual ~LevelSelectScene(); //����һ����������������������ٶ����ͷ���Դ

protected:

    virtual bool init(); //����һ���麯�������ڳ�ʼ�����󣬷���һ������ֵ

    virtual void onEnter()override; //����һ���麯���������ڳ�������ʱִ�У����Ǹ����ͬ������

private:

    int _iThemeIndex = 0; //����һ���������͵ĳ�Ա���������ڴ洢��ǰ������������ʼֵΪ0

    Layer* _pLevelSelectLayer = nullptr; //����һ��ָ����ָ�룬���ڴ洢�ؿ�ѡ��㣬��ʼֵΪnullptr
};

#endif /* defined(__newCardDefence__LevelSelectScene__) */ //������������
