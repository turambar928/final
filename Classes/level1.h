#ifndef level1_H
#define level1_H

#include "cocos2d.h"
USING_NS_CC;

class level1 :public Layer {
public:
	static Scene* scene();

	virtual bool init();
	void onBackCallback(Ref* pSender);
	void onButtonEffect();
	void onStart(Ref* pSender);

	//bool onTouchBegan(Touch* touch, Event* unused_event);
	//void onTouchMoved(Touch* touch, Event* unused_event);
	//void onTouchEnded(Touch* touch, Event* unused_event);
	
	virtual void onEnter();

	CREATE_FUNC(level1);
};









#endif