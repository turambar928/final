#ifndef __CarrotFantasy__GameSettingScene__
#define __CarrotFantasy__GameSettingScene__

#include "PublicDefine.h"

class GameSettingScene:public Scene
{
public:
    
    CREATE_FUNC(GameSettingScene);
    
    virtual ~GameSettingScene();
    
protected:
    
    virtual bool init();
    
    virtual void onEnter()override;
    
private:
    
    Layer *_pPanelLayer = nullptr;
};

#endif 
