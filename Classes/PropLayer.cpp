#include "PropLayer.h"
#include "GameScene.h"
#include "UserData.h"
#include "GameConst.h"
#include "PauseLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocostudio::timeline;
using namespace cocostudio;

enum NodeTag
{
	Tag_time = 100,
	Tag_score,
	tag_bestScore,
	tag_level,
	tag_currentTime
};


bool PropLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	setTime(60);

	_propLayer = CSLoader::createNode("PropLayer.csb");
	auto frameSize = Director::getInstance()->getVisibleSize();
	_propLayer->setContentSize(frameSize);
	ui::Helper::doLayout(_propLayer);
	addChild(_propLayer);

	auto visibleSize = Director::getInstance()->getVisibleSize();


	auto bomb =  (ui::ImageView*)_propLayer->getChildByTag(24);
	bomb->addClickEventListener(CC_CALLBACK_1(PropLayer::menuBombCallBack,this));

	auto bombText = (ui::TextBMFont*)bomb->getChildByTag(152);
	bombText->setString(StringUtils::format("%d", UserData::getInstance()->getBomb()));


	auto hourglass = (ui::ImageView*)_propLayer->getChildByTag(23);
	hourglass->addClickEventListener(CC_CALLBACK_1(PropLayer::menuHourglassCallBack,this));
	auto hourglassText = (ui::TextBMFont*)hourglass->getChildByTag(151);
	hourglassText->setString(StringUtils::format("%d", UserData::getInstance()->getHourglass()));

	auto colorBubble = (ui::ImageView*)_propLayer->getChildByTag(22);
	colorBubble->addClickEventListener(CC_CALLBACK_1(PropLayer::menuColorBubbleCallBack,this));
	auto colorBubbleText = (ui::TextBMFont*)colorBubble->getChildByTag(150);
	colorBubbleText->setString(StringUtils::format("%d", UserData::getInstance()->getColorBubble()));

	auto pauseMenu = (ui::Button*)_propLayer->getChildByTag(36);
	pauseMenu->addClickEventListener(CC_CALLBACK_1(PropLayer::menuPauseCallBack, this));

	scheduleUpdate();
	return true;
}

void PropLayer::setBombNum()
{
	auto bomb = (ui::ImageView*)_propLayer->getChildByTag(24);
	bomb->addClickEventListener(CC_CALLBACK_1(PropLayer::menuBombCallBack, this));
	auto bombText = (ui::TextBMFont*)bomb->getChildByTag(152);
	bombText->setString(StringUtils::format("%d", UserData::getInstance()->getBomb()));

}

void PropLayer::setColorBubbleNum()
{
	auto colorBubble = (ui::ImageView*)_propLayer->getChildByTag(22);
	colorBubble->addClickEventListener(CC_CALLBACK_1(PropLayer::menuColorBubbleCallBack, this));
	auto colorBubbleText = (ui::TextBMFont*)colorBubble->getChildByTag(150);
	colorBubbleText->setString(StringUtils::format("%d", UserData::getInstance()->getColorBubble()));
}

void PropLayer::menuBombCallBack(Ref* Psender)
{
	if (UserData::getInstance()->getBomb() <= 0)
	{
		return;
	}
	//UserData::getInstance()->addBomb(-1);


	auto gameSceme = (GameScene*)this->getParent();
	gameSceme->bombBubble();
}
void PropLayer::menuHourglassCallBack(Ref* Psender)
{
	if (UserData::getInstance()->getHourglass() <= 0)
	{
		return;
	}
	UserData::getInstance()->addHourglass(-1);
	auto hourglass = (ui::ImageView*)_propLayer->getChildByTag(23);
	hourglass->addClickEventListener(CC_CALLBACK_1(PropLayer::menuHourglassCallBack, this));
	auto hourglassText = (ui::TextBMFont*)hourglass->getChildByTag(151);
	hourglassText->setString(StringUtils::format("%d", UserData::getInstance()->getHourglass()));

	auto time = getTime() + HOURGLASSTIME;
	if (time >= 60)
	{	
		time = 60;
	}
	setTime(time);
}

void PropLayer::menuColorBubbleCallBack(Ref* Psender)
{
	if (UserData::getInstance()->getColorBubble() <= 0)
	{
		return;
	}
	//UserData::getInstance()->addColorBubble(-1);


	auto gameSceme = (GameScene*)this->getParent();
	gameSceme->colorBubble();
}
void PropLayer::menuPauseCallBack(Ref* Psender)
{

	auto gameSceme = (GameScene*)this->getParent();
	gameSceme->mPause();
	auto layer = PauseLayer::create();
	gameSceme->addChild(layer);
}

void PropLayer::update(float delta)
{
	setTime(getTime() - 1.0/60.0);

	auto timeLabel = (ui::TextBMFont*)_propLayer->getChildByTag(131);
 	timeLabel->setString(StringUtils::format("%d", (int)getTime()));


	auto loadingBar = (ui::LoadingBar*)_propLayer->getChildByTag(29);
	loadingBar->setPercent(getTime()/60.0 * 100);

	auto armature = (Armature*)loadingBar->getChildByTag(125);
	float wight = loadingBar->getContentSize().width;
	armature->setPosition(211- wight*(1 - getTime() / 60.0), 13);

	auto levelLabel = (ui::TextBMFont*)_propLayer->getChildByTag(122);
	auto level = StringUtils::format("%d", UserData::getInstance()->getLevel());
	auto timeSptite = (Sprite*)_propLayer->getChildByTag(46);

	if (levelLabel->getString() != level)
	{
		levelLabel->setString(level);
	}
	if (getTime() <= 0)
	{
		auto gameSceme = (GameScene*)this->getParent();
		gameSceme->gameOver();
	}
	else if (getTime() <= 5)
	{
		
		auto currentTime = (ui::TextBMFont*)timeSptite->getChildByTag(132);
		if (currentTime->getString() != StringUtils::format("%d", (int)getTime()))
		{
			
			SimpleAudioEngine::getInstance()->playEffect("Music/Clock.mp3");
			currentTime->setString(StringUtils::format("%d", (int)getTime()));
		}
		
		if (!timeSptite->isVisible())
		{
 			auto point = timeSptite->getPosition();
			timeSptite->setPosition(650, point.y);
 			timeSptite->setVisible(true);
			auto moveAction = MoveTo::create(0.5f, point);
			auto speedAction = EaseSineOut::create(moveAction);
			auto callFunc = CallFunc::create(CC_CALLBACK_0(PropLayer::timeCallFunc, this));
			auto seq = Sequence::create(speedAction, callFunc, nullptr);
 			timeSptite->runAction(seq);
		}
	}
	else
	{
		if (timeSptite->isVisible())
		{
			timeSptite->setVisible(false);
		}
	}
}
void PropLayer::AddScoreLabel(int var)
{
	auto scoreLabel = (ui::TextBMFont*)_propLayer->getChildByTag(123);
	UserData::getInstance()->addScore(var);
	scoreLabel->setString(StringUtils::format("%d", UserData::getInstance()->getScore()));
}
void PropLayer::setCannonAngle(Point target)
{
	auto cannon = (Sprite*)_propLayer->getChildByTag(38);
	auto angle = (target - READY_PAOPAO_POS).getAngle(Vec2(0, 1));
	cannon->setRotation(CC_RADIANS_TO_DEGREES(angle));
}
void PropLayer::setCannonAction(Point target)
{
	auto cannon = (Sprite*)_propLayer->getChildByTag(38);
	auto angle = cannon->getRotation();

	auto dir = -10 * (target - READY_PAOPAO_POS).getNormalized();
	auto moveBy = MoveBy::create(0.1f, dir);
	auto seq = Sequence::create(moveBy, moveBy->reverse(), nullptr);
	cannon->runAction(seq);
}
void PropLayer::timeCallFunc()
{
	auto timeSptite = (Sprite*)_propLayer->getChildByTag(46);
	auto time_bg = (Sprite*)timeSptite->getChildByTag(45);
	auto rotateAction = RotateBy::create(1.0f, -360.0f);
	auto repeatAction = RepeatForever::create(rotateAction);
	time_bg->runAction(repeatAction);
}