// ��ֹͷ�ļ��ظ�����
#ifndef __CarrotFantasy__OptionLayer__
#define __CarrotFantasy__OptionLayer__

// ����cocos2dͷ�ļ�
#include "cocos2d.h"
// ʹ��cocos2d�����ռ�
using namespace cocos2d;

// ����һ��OptionLayer�࣬�̳���Layer��
class OptionLayer :public Layer
{

public:

    // ����һ���꣬���ڴ���OptionLayer����
    CREATE_FUNC(OptionLayer);

protected:

    // ����һ���麯�������ڳ�ʼ��OptionLayer���󣬷���һ������ֵ
    virtual bool init();

    // ����һ���麯�������ڼ�����Դ
    virtual void loadSource();
};

// ����ͷ�ļ��Ķ���
#endif /* defined(__CarrotFantasy__OptionLayer__) */
