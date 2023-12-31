#include "HelpLayer.h"
#include"NumSprite.h"
#include "SceneManager.h"
HelpLayer::~HelpLayer() {
	
}
bool HelpLayer::init()
{
	bool bRet = false;

	do
	{
		
		CC_BREAK_IF(!Layer::init());
		
		auto pBtnBack = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ss_back_normal.png"), Sprite::createWithSpriteFrameName("ss_back_pressed.png"), [&](Ref* pSender)
			{
				
				auto enWelcomeScene = std::make_tuple(en_WelcomeScene, 0);
				NOTIFY->postNotification("changeScene", reinterpret_cast<Ref*>(&enWelcomeScene));
			});
		pBtnBack->setPosition(Vec2(-430, 280));


		addChild(Menu::create(pBtnBack, nullptr)); 

		
		auto pTitle = Label::createWithSystemFont("帮助", "Arial", 30);
		pTitle->setPosition(Vec2(480, 585));
		pTitle->setTextColor(Color4B(255, 0, 0, 255));
		addChild(pTitle);
	
		
		bRet = true;
	} while (0);


	
	return bRet;
}