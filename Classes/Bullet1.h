#ifndef Bullet1_H_
#define Bullet1_H_

#include "cocos2d.h"
#include "bulletbase.h"


USING_NS_CC;

class Bullet1 :public Bullet
{
public:
	Bullet1(const Vec2& position_);
	~Bullet1() = default;
	virtual void bullet_init();// ��ʼ������
	virtual void update(double update_time); // ���Ⱥ��� ���������ȼ��ʱ��
	virtual void bullet_move_animation(); //�����ӵ��ƶ�����
	virtual void sprite_init(const Vec2& position_); //����ͼ��ʼ��


};









#endif

