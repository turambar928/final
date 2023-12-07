#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include"SysMenu.h"

USING_NS_CC;
class Adventure_layer :public Layer {
public:
	static Scene* scene();

	virtual bool init();
	void onBackCallback(Ref* pSender);

	
	CREATE_FUNC(Adventure_layer);
};


#endif // __HELLOWORLD_SCENE_H__
