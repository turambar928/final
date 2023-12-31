#ifndef __CarrotFantasy__LoadingScene__ //���û�ж���__CarrotFantasy__LoadingScene__�꣬��ֹͷ�ļ��ظ�����
#define __CarrotFantasy__LoadingScene__ //����__CarrotFantasy__LoadingScene__��

#include "cocos2d.h" //����cocos2d��ܵ�ͷ�ļ�
using namespace cocos2d; //ʹ��cocos2d�����ռ�

class GameScene; //����һ���࣬��ʾ��Ϸ����

class LoadingScene :public Scene //����һ���࣬�̳���Scene�࣬������ʾ���س���
{
public:

    CREATE_FUNC(LoadingScene); //ʹ�ú궨��һ���������������ڴ�������

protected:

    virtual bool init()override; //����һ���麯�������ڳ�ʼ�����󣬷���һ������ֵ�����Ǹ����ͬ������

    virtual void onEnter()override; //����һ���麯���������ڳ�������ʱִ�У����Ǹ����ͬ������

    virtual void onExit()override; //����һ���麯���������ڳ����˳�ʱִ�У����Ǹ����ͬ������

    virtual void sourceLoadCallBack(Ref* pData); //����һ���麯������������Դ�������ʱִ�У�����Ϊһ���������͵�ָ��

protected:

    GameScene* _pGameScene = nullptr; //����һ��ָ����Ϸ������ָ�룬���ڴ洢��Ϸ�������󣬳�ʼֵΪnullptr

};

#endif /* defined(__CarrotFantasy__LoadingScene__) */ //������������
