#ifndef monsterbase_H
#define monsterbase_H

#include "cocos2d.h"


USING_NS_CC;

enum MonType {
	Mon_type_none = -1,
	Mon_typel, 
	Mon_type2,
	Mon_type3,
	Mon_type4 
	// Other Mon
};

class Mon :public Sprite {
public:
	Mon() = default; //��Ĭ�Ϸ�ʽ������
	~Mon() = default;
	virtual void Mon_init();    //������ʼ��
	void sprite_init(const Vec2& position_);//�����ʼ��
	virtual void set_scale(float val_);// ���þ���Ĵ�С
	virtual Vec2 get_position() const;
	virtual double get_x();
	virtual double get_y();
	virtual int get_blood() const;
	virtual int get_attack_num() const;
	virtual double get_move_rate() const;
	//���ض���
	virtual void init_mon_move_animation();
	virtual void init_mon_die_animation();
	//���ж���
	virtual bool run_mon_move_animation();
	virtual void run_mon_die_animation();
	//����״̬
	virtual bool judge_dead() const;
	virtual bool judge_move() const;
	//����
	static int mon_id; // ��ʬ��� Ψһ��
	double blood;	// Ѫ��
	double time_count;// ʱ���ʱ��  ͳ��ʹ�þ��� ������
	float move_rate; // ����
	double attack_num; //����ֵ

	Vec2 position;//��άλ�� ����
	Sprite* sprite;// �������

	//�������� 
	Animate* mon_move_animate;
	Animate* mon_die_animate;

	Vector<SpriteFrame*> mon_move;
	Vector<SpriteFrame*> mon_die;

	//��ʬ���� enum ���switch����
	MonType mon_type;
	//��ʬ״̬����
	bool is_move;//��ʬ�Ƿ�������״̬
	bool is_dead;//��ʬ�Ƿ��Ѿ�����
	int row;
};












#endif
