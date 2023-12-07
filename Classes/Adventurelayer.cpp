#include"Adventurelayer.h"
#include"SysMenu.h"


USING_NS_CC;
Scene* Adventure_layer::scene()
{
	Scene* scene = Scene::create();
	Adventure_layer* adventure = Adventure_layer::create();
	scene->addChild(adventure);
	return scene;
}

bool Adventure_layer::init() {
	if (!Layer::init()) {
		return false;
	}
	return true;

}

void Adventure_layer::onBackCallback(Ref* pSender)
{
	/*Scene* scene = SysMenu::scene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.2, scene));*/
}
