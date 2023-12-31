

#ifndef __CarrotFantasy__HelpLayer__
#define __CarrotFantasy__HelpLayer__

#include "PublicDefine.h"
#include "ui/CocosGUI.h"
using namespace ui;

class HelpLayer:public Layer
{
public:
    
    CREATE_FUNC(HelpLayer);// 定义CREATE_FUNC宏，用于创建HelpLayer对象
    
    virtual ~HelpLayer();// 析构函数声明
    
protected:
    
    virtual bool init()override;// 虚函数，用于初始化HelpLayer对象
    
private:
	Sprite * bottomSprite;// 底部精灵对象指针

	int _iCurLevelIndex = 0;// 当前级别索引
	
	PageView *_pPageView = nullptr;// 页面视图对象指针
	
};

#endif /* defined(__CarrotFantasy__HelpLayer__) */
