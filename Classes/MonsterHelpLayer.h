
#ifndef __CarrotFantasy__MonsterHelpLayer__
#define __CarrotFantasy__MonsterHelpLayer__

// �������������ͷ�ļ�
#include "PublicDefine.h"

// ����һ������������࣬�̳��Բ���
class MonsterHelpLayer :public Layer
{
public:

    // ʹ�ú궨�崴��һ��������������ľ�̬����
    CREATE_FUNC(MonsterHelpLayer);

protected:

    // ��д����ĳ�ʼ������
    virtual bool init()override;
};

#endif /* defined(__CarrotFantasy__MonsterHelpLayer__) */
