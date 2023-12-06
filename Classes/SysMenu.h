#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include"AudioEngine.h"

class SysMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void onButtonEffect();

    void onadventure(Ref* pSender);
    void onboss(Ref* pSender);
    void onmonster(Ref* pEender);

    void onsetting(Ref* pSender);
    void onquestion(Ref* pSender);

    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
   
    // implement the "static create()" method manually
    CREATE_FUNC(SysMenu);             //相当于一个整体的析构函数，清除上述部分所create的所有
};

#endif // __HELLOWORLD_SCENE_H__


