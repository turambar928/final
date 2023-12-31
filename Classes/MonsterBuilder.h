// ��ֹͷ�ļ��ظ�����
#ifndef __CarrotFantasy__MonsterBuilder__
#define __CarrotFantasy__MonsterBuilder__
// ����cocos2d�����ռ��ͷ�ļ�
#include "cocos2d.h"
using namespace cocos2d;
// ����һ�����ｨ�����࣬�̳��Խڵ���
class MonsterBuilder :public Node {

protected:

	// ��д�ڵ���ĳ�ʼ������
	virtual bool init();

	// ����һ���������͵ĳ�Ա��������ʾ����������ӳ�ʱ��
	float _fDelayTime;

	// ����һ�����͵ĳ�Ա��������ʾ��ǰ���εĹ������
	int _MonsterCount;

	// ����һ�����͵ĳ�Ա��������ʾ�ܹ������Ĺ������
	int _MonsterBuilderNumber;

	// ����һ�����͵ĳ�Ա��������ʾ���ļ��ж�ȡ�ĵ�ǰ�ؿ��Ĺ�����������
	int _iReadFileMonsterCount;

	// ����һ���������͵ĳ�Ա��������ʾ�Ƿ��ӳٴ�������
	bool _bDelay;

	// ����һ�����͵ĳ�������ʾ����������ӳ�ʱ��ĳ���ֵ
	const int _iConstDelayTime = 8;

	// ����һ�����͵ĳ�Ա��������ʾÿ���εĹ�����
	int _iNumber;

	// ����һ�����͵ĳ�Ա��������ʾ��ǰ������
	int _iBatch;

	// ��д�ڵ���Ľ��볡������
	virtual void onEnter();

	// ����һ����������ĸ��º�����������ʱ����
	void createMonsterUpdate(float t);

	// ����һ�����﹤���������ĺ������������ݲ�ͬ�����κͱ�Ŵ�����ͬ���͵Ĺ���
	void MonsterFactoryController();

	// ����һ��ָ�򶯻����ָ�룬������Ŵ�������Ķ�������
	Animation* _createMonsterAnimation;

	// ������ｨ���������������
	~MonsterBuilder();

public:

	// ����һ����ȡ��ǰ���εĺ��������ص�ǰ���ε�ֵ
	int getBatch();

	// ʹ�ú궨�崴��һ�����ｨ���߶���ľ�̬����
	CREATE_FUNC(MonsterBuilder);

	// ʹ�ú궨�������Ͷ���һ�����͵ĳ�Ա��������ʾÿ���δ����Ĺ�������
	CC_SYNTHESIZE_PASS_BY_REF(int, _iBuildNumber, IBuildNumber);
};
// ����ͷ�ļ��Ķ���
#endif
