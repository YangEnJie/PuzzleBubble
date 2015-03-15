#include "ShopLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "UserData.h"
#include "GameConst.h"


bool ShopLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->initWithColor(Color4B(0, 0, 0, 100));

	_shopLayer = CSLoader::createNode("ShopLayer.csb");
	auto frameSize = Director::getInstance()->getVisibleSize();
	_shopLayer->setContentSize(frameSize);
	ui::Helper::doLayout(_shopLayer);
	addChild(_shopLayer);

	auto goldLabel = Label::createWithCharMap("white_font.png", 25, 29, '0');
	CCLOG("bestLabel %d", UserData::getInstance()->getBestScore());
	goldLabel->setString(StringUtils::format("%d", UserData::getInstance()->getGold()));
	this->addChild(goldLabel);
	goldLabel->setPosition(370.0f, 210.0f);

	buyGold();

	auto buttonReturn = (ui::Button*)((Sprite*)_shopLayer->getChildByTag(40))->getChildByTag(50);
	buttonReturn->addClickEventListener(CC_CALLBACK_1(ShopLayer::menuReturnCallBack, this));

	return true;
}

void ShopLayer::menuReturnCallBack(Ref* pSender)
{
	this->removeFromParentAndCleanup(true);
}
void ShopLayer::buyGold()
{
	auto tag = 41;
	auto shop_bg = (Sprite*)_shopLayer->getChildByTag(40);
	for (int i = 0; i < 5; i++)
	{
		auto imageView = (ui::ImageView*)(shop_bg->getChildByTag(tag++));
		auto goldLabel = Label::createWithCharMap("white_font.png", 25, 29, '0');
		goldLabel->setString(StringUtils::format("%d", RMB[i]));
		imageView->addChild(goldLabel);
		goldLabel->setPosition(100.0f, 33.0f);
	}
}