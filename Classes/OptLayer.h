// ��ֹͷ�ļ��ظ�����
#ifndef __CarrotFantasy__OptLayer__
#define __CarrotFantasy__OptLayer__

// ����cocos2dͷ�ļ�
#include "cocos2d.h"
// ����һ��TowerOptBtn�࣬������ʾ����ѡ��˵�
class TowerOptBtn;

// ʹ��cocos2d�����ռ�
using namespace cocos2d;

// ����һ��OptLayer�࣬�̳���Layer�࣬������ʾ�Ͳ������͹���Ľ����
class OptLayer :public Layer
{
public:

	// ����һ���꣬���ڴ���OptLayer����
	CREATE_FUNC(OptLayer);

protected:
	// ����һ���麯�������ڳ�ʼ��OptLayer���󣬷���һ������ֵ
	virtual bool init();

	// ����һ���麯����������Ӵ����¼�����
	virtual void listener();

protected:
	// ����һ��TowerOptBtn���͵�ָ�룬����ָ����ʾ����ѡ��˵��Ķ���
	TowerOptBtn* towerOptBtn;
	// ����һ���������͵ı��������ڱ�ʾ�Ƿ���ʾ����ѡ��˵�
	bool _KeyOptBtn;
	// ����һ��Sprite���͵�ָ�룬����ָ����ʾ��ֹͼ��ľ������
	Sprite* _pforbiddenSp;

};

// ����ͷ�ļ��Ķ���
#endif /* defined(__CarrotFantasy__OptLayer__) */
