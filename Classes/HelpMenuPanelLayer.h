#ifndef __CarrotFantasy__HelpMenuPanelLayer__
#define __CarrotFantasy__HelpMenuPanelLayer__

#include "PublicDefine.h"

// �����˵����ͼ����
class HelpMenuPanelLayer : public Layer
{
public:
    // ����ʵ���ĺ궨��
    CREATE_FUNC(HelpMenuPanelLayer);

protected:
    // ��ʼ�������ĸ���
    virtual bool init() override;

    // �����˵����ķ���
    virtual void createMenuPanel();

private:
    // ������ť
    MenuItemToggle* pHelpBtn;

    // ���������ť
    MenuItemToggle* pMonsterHelpBtn;

    // ������������ť
    MenuItemToggle* pTowerHelpBtn;

    // ���ͼ������
    LayerMultiplex* _pLayers = nullptr;
};

#endif /* defined(__CarrotFantasy__HelpMenuPanelLayer__) */
