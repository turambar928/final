#ifndef __CarrotFantasy__HelpScene__
#define __CarrotFantasy__HelpScene__

#include "PublicDefine.h"

// 帮助场景类，继承自cocos2d::Scene
class HelpScene : public Scene
{
public:
    // 创建帮助场景的工厂方法
    CREATE_FUNC(HelpScene);

    // 帮助场景析构函数
    virtual ~HelpScene();

protected:
    // 场景初始化方法，覆盖父类方法
    virtual bool init()override;

    // 场景进入时的回调方法，覆盖父类方法
    virtual void onEnter()override;

private:
    // 帮助菜单面板图层指针
    Layer* _pMenuPanelLayer = nullptr;
};

#endif /* defined(__CarrotFantasy__HelpScene__) */
