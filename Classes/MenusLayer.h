// ��ֹͷ�ļ��ظ�����
#ifndef __CarrotFantasy__MenusLayer__
#define __CarrotFantasy__MenusLayer__

// �������������ͷ�ļ�
#include "PublicDefine.h"

// ����һ���˵�����࣬�̳���Layer��
class MenusLayer :public Layer
{
public:

    // ʹ�ú궨�崴��һ����̬�Ĵ�������
    CREATE_FUNC(MenusLayer);

protected:

    // ��д��ʼ������
    virtual bool init();

    // �����˵���ĺ���
    virtual void createMenuItems();
};

// ����ͷ�ļ��Ķ���
#endif /* defined(__CarrotFantasy__MenusLayer__) */
