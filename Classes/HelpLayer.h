

#ifndef __CarrotFantasy__HelpLayer__
#define __CarrotFantasy__HelpLayer__

#include "PublicDefine.h"
#include "ui/CocosGUI.h"
using namespace ui;

class HelpLayer:public Layer
{
public:
    
    CREATE_FUNC(HelpLayer);// ����CREATE_FUNC�꣬���ڴ���HelpLayer����
    
    virtual ~HelpLayer();// ������������
    
protected:
    
    virtual bool init()override;// �麯�������ڳ�ʼ��HelpLayer����
    
private:
	Sprite * bottomSprite;// �ײ��������ָ��

	int _iCurLevelIndex = 0;// ��ǰ��������
	
	PageView *_pPageView = nullptr;// ҳ����ͼ����ָ��
	
};

#endif /* defined(__CarrotFantasy__HelpLayer__) */
