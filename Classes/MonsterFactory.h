// ��ֹͷ�ļ��ظ�����
#ifndef __CarrotFantasy__MonsterFactory__
#define __CarrotFantasy__MonsterFactory__

// �������������ͷ�ļ�
#include "PublicDefine.h"

// ����һ�����﹤����
class MonsterFactory
{
public:

    // ����һ����̬���������ݴ���Ĺ������Ͳ���������������һ����Ӧ���͵Ĺ������
    static MonsterBase* createMonster(const MonsterType& rMonsterType);
};

// ����ͷ�ļ��Ķ���
#endif /* defined(__CarrotFantasy__MonsterFactory__) */
