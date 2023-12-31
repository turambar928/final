//start
#ifndef __newCardDefence__WelcomeScene__
#define __newCardDefence__WelcomeScene__

#include "PublicDefine.h"

class WelcomeScene:public Scene
{
    
public:
    
    CREATE_FUNC(WelcomeScene);
    virtual ~WelcomeScene();
    
protected:
    
    virtual void onEnter()override;
    virtual bool init();
    virtual void showMenu();

private:
    
    Layer *_pSpritesLayer = nullptr; 
    Layer *_pMenusLayer = nullptr;

};

#endif /* defined(__newCardDefence__WelcomeScene__) */
