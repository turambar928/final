#ifndef __CarrotFantasy__HelpMenuPanelLayer__
#define __CarrotFantasy__HelpMenuPanelLayer__

#include "PublicDefine.h"

// 帮助菜单面板图层类
class HelpMenuPanelLayer : public Layer
{
public:
    // 创建实例的宏定义
    CREATE_FUNC(HelpMenuPanelLayer);

protected:
    // 初始化方法的覆盖
    virtual bool init() override;

    // 创建菜单面板的方法
    virtual void createMenuPanel();

private:
    // 帮助按钮
    MenuItemToggle* pHelpBtn;

    // 怪物帮助按钮
    MenuItemToggle* pMonsterHelpBtn;

    // 防御塔帮助按钮
    MenuItemToggle* pTowerHelpBtn;

    // 多层图层容器
    LayerMultiplex* _pLayers = nullptr;
};

#endif /* defined(__CarrotFantasy__HelpMenuPanelLayer__) */
