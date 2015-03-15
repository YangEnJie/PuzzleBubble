#include "GiftLayer.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "UserData.h"
#include "GameScene.h"

using namespace cocostudio;

bool GiftLayer::init()
{
	if (!LayerColor::init())
	{
		return false;
	}

	this->initWithColor(Color4B(0, 0, 0, 100));

	_giftNode = CSLoader::createNode("GiftLayer.csb");
	auto frameSize = Director::getInstance()->getVisibleSize();
	_giftNode->setContentSize(frameSize);
	ui::Helper::doLayout(_giftNode);
	addChild(_giftNode);

	auto getButton = (ui::Button*)_giftNode->getChildByTag(19);
	getButton->addClickEventListener(CC_CALLBACK_1(GiftLayer::getButtonCallBack, this));

	auto giftBg = (Sprite*)_giftNode->getChildByTag(16);
	auto returnButton = (ui::Button*)giftBg->getChildByTag(148);
	returnButton->addClickEventListener(CC_CALLBACK_1(GiftLayer::returnButtonCallBack, this));

	return true;
}

void GiftLayer::getButtonCallBack(Ref* Pesender)
{
	if (this->isGameScene)
	{
		auto gameScene = (GameScene*)this->getParent();
		gameScene->mResume();
	}

	this->removeFromParent();



}

void GiftLayer::returnButtonCallBack(Ref* Pesender)
{

	if (this->isGameScene)
	{
		auto gameScene = (GameScene*)this->getParent();
		gameScene->mResume();
	}

	this->removeFromParent();

}