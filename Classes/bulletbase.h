#ifndef bulletbase_H
#define bulletbase_H

#include "cocos2d.h"

USING_NS_CC;


class Bullet :public Sprite {
public:
	Bullet();//���캯��

	~Bullet() = default;
	virtual void bullet_init();// ��ʼ������
	virtual void update(double update_time); // ���Ⱥ��� ���������ȼ��ʱ��
	virtual void bullet_move_animation(); //�����ӵ��ƶ�����

	//�����ʼ��  ��1 ͼƬ����  ��2����ά����
	virtual void sprite_init(const Vec2& position_);
	virtual Vec2 get_position() const; // ��ȡ��ά����
	virtual double get_x() const; // getPositionX
	virtual double get_y() const;
	virtual void set_crash(); // ����Ϊ�ж�
	virtual bool judge_crash(); // crash judgement, if ture, delete the bullet
	virtual void set_attack_num(double damage);// �����ӵ��˺�
	virtual void delete_sprite(); // ɾ������ 
	int row;
	//����
	Vec2 position; // ��ά����
	Sprite* sprite; //�������
	double attack_num; // �����˺�
	bool is_crash; // �Ƿ���ײ   true:��ײ  false��δ��ײ
	Animate* bullet_move_animate; // �ӵ��ƶ���������
	int x, y;      //��û��ʼ��
	int speed;     //�ӵ��ٶ�
	int attack_range;//�ӵ�������Χ
};















#endif