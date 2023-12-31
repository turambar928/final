
#ifndef __CarrotFantasy__MonsterLayer__
#define __CarrotFantasy__MonsterLayer__

// ����ʵ�������ͷ�ļ�
#include "EntityLayerBase.h"

// ǰ�������������
class MonsterBase;


// ����һ��������࣬�̳���ʵ������
class MonsterLayer :public EntityLayerBase
{
public:

    // ʹ�ú궨�崴��һ����������ľ�̬����
    CREATE_FUNC(MonsterLayer);

protected:

    // ��дʵ������ĳ�ʼ������
    virtual bool init();

    // ����һ��ע����������¼��ĺ���
    virtual void registerMonsterDeadEvent();

    // ����һ�����������ĺ�����������һ��ָ���������͵�ָ��
    virtual void monsterDead(Ref* pData);

    // ��дʵ��������˳���������
    virtual void onExit()override;

};


#endif /* defined(__CarrotFantasy__MonsterLayer__) */
