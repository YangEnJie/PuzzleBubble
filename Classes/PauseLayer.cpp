#include "PauseLayer.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "UserData.h"
#include "StartScene.h"
#include "GiftLayer.h"

using namespace cocostudio::timeline;

bool PauseLayer::init()
{
	if (!LayerColor::init())
	{
		return false;
	}

	this->initWithColor(Color4B(0,0,0,100));

	auto pauseLayer = CSLoader::createNode("PauseLayer.csb");
	auto frameSize = Director::getInstance()->getVisibleSize();
	pauseLayer->setContentSize(frameSize);
	ui::Helper::doLayout(pauseLayer);
	addChild(pauseLayer);

	auto continueButton = (ui::Button*)pauseLayer->getChildByTag(36);
	continueButton->addClickEventListener(CC_CALLBACK_1(PauseLayer::menuContinueCallBack, this));

	auto pause_bg = (Sprite*)pauseLayer->getChildByTag(133);
	auto getButton = (ui::Button*)pause_bg->getChildByTag(37);
	getButton->addClickEventListener(CC_CALLBACK_1(PauseLayer::menuGetCallBack, this));

	auto homeButton = (ui::Button*)pauseLayer->getChildByTag(38);
	homeButton->addClickEventListener(CC_CALLBACK_1(PauseLayer::menuHomeCallBack, this));

	return true;
}

void PauseLayer::menuContinueCallBack(Ref* Psender)
{
	auto gameScene = dynamic_cast<GameScene *>(this->getParent());
	gameScene->mResume();
	gameScene->removeChild(this);
}
void PauseLayer::menuGetCallBack(Ref* Psender)
{
	auto gameScene = dynamic_cast<GameScene *>(this->getParent());
	auto giftLayer = GiftLayer::create();
	giftLayer->isGameScene = true;
	gameScene->addChild(giftLayer);
	this->removeFromParent();
}
void PauseLayer::menuHomeCallBack(Ref* Psender)
{
	Director::getInstance()->replaceScene(StartLayer::scene());
}
