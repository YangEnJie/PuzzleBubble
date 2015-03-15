#include "ReviveLayer.h"
#include "GameoverLayer.h"
#include "GameScene.h"


bool ReviveLayer::init()
{
	if (!LayerColor::init())
	{
		return false;
	}

	this->initWithColor(Color4B(0, 0, 0, 100));

	auto itemOver = MenuItemFont::create("GameOver", CC_CALLBACK_1(ReviveLayer::menuOverCallBack, this));
	auto menu = Menu::create(itemOver, nullptr);
	addChild(menu);


	return true;
}

void ReviveLayer::menuOverCallBack(Ref* Psender)
{
	auto gameScene = dynamic_cast<GameScene*>(this->getParent());
	gameScene->mPause();
	auto overLayer = GameoverLayer::create();
	addChild(overLayer);
}