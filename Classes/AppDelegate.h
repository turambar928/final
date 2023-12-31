#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    
    virtual bool applicationDidFinishLaunching();

    
    virtual void applicationDidEnterBackground();

  
    virtual void applicationWillEnterForeground();
    
protected:
    
    virtual void preLoadSource();
    
    virtual void unLoadSource();

};

#endif 

