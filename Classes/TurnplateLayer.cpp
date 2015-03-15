#include "TurnplateLayer.h"
#include "StartScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "UserData.h"

using namespace cocostudio::timeline;

bool TurnplateLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_turnplateNode = CSLoader::createNode("TurnplateLayer.csb");
	auto frameSize = Director::getInstance()->getVisibleSize();
	_turnplateNode->setContentSize(frameSize);
	ui::Helper::doLayout(_turnplateNode);

	addChild(_turnplateNode);

	auto rotateMenu = (ui::Button*)_turnplateNode->getChildByTag(16);
	rotateMenu->addClickEventListener(CC_CALLBACK_1(TurnplateLayer::menuRotateCallBack, this));

	auto returnMenu = (ui::Button*)_turnplateNode->getChildByTag(33);
	returnMenu->addClickEventListener(CC_CALLBACK_1(TurnplateLayer::menuReturnCallBack, this));

	return true;

}

void TurnplateLayer::menuRotateCallBack(Ref* Pesender)
{
 	if (UserData::getInstance()->getHaveRaffle() || _isPress)
 	{
 		return;
 	}
	_isPress = true;
	auto turnplate = (Sprite*)_turnplateNode->getChildByTag(20);
	auto angle = 720.0f + (int)(CCRANDOM_0_1()*6) * 60;
	auto action = RotateBy::create(2.0f, angle);
	auto sineOut = EaseSineOut::create(action);
	auto callfunc = CallFunc::create(CC_CALLBACK_0(TurnplateLayer::addProps,this));
	auto seq = Sequence::create(sineOut, callfunc, nullptr);
	turnplate->runAction(seq);
	UserData::getInstance()->setHaveRaffle(true);
}
void TurnplateLayer::menuReturnCallBack(Ref* Psender)
{

	this->removeFromParentAndCleanup(true);
}
void TurnplateLayer::addProps()
{
	auto turnplate = (Sprite*)_turnplateNode->getChildByTag(20);
	int angle = (int)turnplate->getRotation() % 360;
	switch (angle)
	{
	case 0  : UserData::getInstance()->addRebirth(1); break;
	case 60 : UserData::getInstance()->addGold(20); break;
	case 120: UserData::getInstance()->addColorBubble(1); break;
	case 180: UserData::getInstance()->addHourglass(1); break;
	case 240: UserData::getInstance()->addBomb(1); break;
	case 300: UserData::getInstance()->addGold(10); break;
	default:
		break;
	}
	_isPress = false;
	CCLOG("%d", angle);
}
