#ifndef setting_H
#define setting_H

#include "cocos2d.h"


USING_NS_CC;
class setting_layer :public Layer {
public:
	static Scene* scene();

	void onVoiceUp(Ref* pSender);
	void onVoiceDown(Ref* pSender);

	virtual bool init();
	void onBackCallback(Ref* pSender);
	void mute(Ref* pSender);
	void unmute(Ref* pSender);


	CREATE_FUNC(setting_layer);

};


#endif // __HELLOWORLD_SCENE_H__
