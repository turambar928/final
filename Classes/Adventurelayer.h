#ifndef Adventurelayer_H
#define Adventurelayer_H

#include "cocos2d.h"
USING_NS_CC;

class Adventure_layer :public Layer {
public:
	static Scene* scene();

	virtual bool init();
	void onBackCallback(Ref* pSender);
	void onButtonEffect();
	void onStart(Ref* pSender);
	virtual void onEnter();
	CREATE_FUNC(Adventure_layer);
};


#endif // __HELLOWORLD_SCENE_H__
