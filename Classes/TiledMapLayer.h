#ifndef __CarrotFantasy__TiledMapLayer__
#define __CarrotFantasy__TiledMapLayer__

#include "cocos2d.h"
using namespace cocos2d;


class TiledMapLayer: public Layer
{
public:
    
    CREATE_FUNC(TiledMapLayer);
    
protected:
    
    virtual bool init();
    
    virtual void loadSource();

private:
    
    TMXTiledMap *_pTiledMap = nullptr;
};

#endif /* defined(__CarrotFantasy__TiledMapLayer__) */
