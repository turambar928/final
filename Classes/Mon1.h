#ifndef Mon1_H_
#define Mon1_H_

#include "cocos2d.h"
#include "monsterbase.h"

USING_NS_CC;

class Mon1 :public Mon
{
public:
	Mon1();
	~Mon1() = default;
	virtual void update(float update_time); //���Ⱥ���  ��������ʱ����
	virtual void mon_init();// ������ʼ��
	//��д���ද��
	virtual void init_mon_move_animation();
	virtual void init_mon_die_animation(); //��������
	static bool is_run_frame;   //�����ж��Ƿ����֡������   ��ֹ�ظ�����
	Vector<SpriteFrame*> getAnimation(const char* format, int count);
	


};



#endif // Mon_H_