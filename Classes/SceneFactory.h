#ifndef __newCardDefence__SceneFactory__
#define __newCardDefence__SceneFactory__

#include "PublicDefine.h"

class SceneFactory
{
public:
    
    static Scene *createScene(const SceneType &rEnSceneType);
};

#endif /* defined(__newCardDefence__SceneFactory__) */
