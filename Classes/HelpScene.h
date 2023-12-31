#ifndef __CarrotFantasy__HelpScene__
#define __CarrotFantasy__HelpScene__

#include "PublicDefine.h"

// ���������࣬�̳���cocos2d::Scene
class HelpScene : public Scene
{
public:
    // �������������Ĺ�������
    CREATE_FUNC(HelpScene);

    // ����������������
    virtual ~HelpScene();

protected:
    // ������ʼ�����������Ǹ��෽��
    virtual bool init()override;

    // ��������ʱ�Ļص����������Ǹ��෽��
    virtual void onEnter()override;

private:
    // �����˵����ͼ��ָ��
    Layer* _pMenuPanelLayer = nullptr;
};

#endif /* defined(__CarrotFantasy__HelpScene__) */
