#ifndef level1_H
#define level1_H

#include "cocos2d.h"
#include"Mon1.h"
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
	Size winSize;
	virtual void onEnter();
	void upadte(float dt);
	CREATE_FUNC(level1);
};









#endif