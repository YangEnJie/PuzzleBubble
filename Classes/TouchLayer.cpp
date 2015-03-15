#include "TouchLayer.h"
#include "GameConst.h"
#include "GameScene.h"

bool TouchLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	setTouchEnable(false);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TouchLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	

	

	return true;
}

bool TouchLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	/*
	auto gameScene = (GameScene*)this->getParent();
	BubbleLayer* bubbleLayer = gameScene->_bubbleLayer;
	auto real = (touch->getLocation() - bubbleLayer->ready->getPosition()).getNormalized();
	bubbleLayer->setReal(real);*/
	return getTouchEnable();
	
}

void TouchLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	auto gameScene = (GameScene*)this->getParent();
	BubbleLayer* bubbleLayer = gameScene->_bubbleLayer;
	bubbleLayer->removeChildByTag(100);

	if (touch->getLocation().y <= TOUCH_DOWN * Director::getInstance()->getVisibleSize().height || touch->getLocation().y >= TOUCH_TOP*Director::getInstance()->getVisibleSize().height)
	{
		return;
	}

	auto real = (touch->getLocation() - bubbleLayer->ready->getPosition()).getNormalized();
	bubbleLayer->setReal(real);
	if (real.x <= 0.9 && real.x >= -0.9 && real != Vec2::ZERO && real.y > 0)
	{
		bubbleLayer->auxiliaryLine(touch->getLocation());
		bubbleLayer->setReadyAngle(touch->getLocation());
		gameScene->setCannonAngle(touch->getLocation());
	}
	
}

void TouchLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	auto gameScene = (GameScene*)this->getParent();
	BubbleLayer* bubbleLayer = gameScene->_bubbleLayer;
	bubbleLayer->removeChildByTag(100);
	
	if (touch->getLocation().y <= TOUCH_DOWN * Director::getInstance()->getVisibleSize().height && touch->getLocation().x <= 200)
	{
		gameScene->swapBubble();
	}

	if (touch->getLocation().y <= TOUCH_DOWN * Director::getInstance()->getVisibleSize().height || touch->getLocation().y >= TOUCH_TOP * Director::getInstance()->getVisibleSize().height)
	{
		setTouchEnable(true);
		return;
	}
	auto real = (touch->getLocation() - bubbleLayer->ready->getPosition()).getNormalized();

	if (real.x <= 0.9 && real.x >= -0.9 && real != Vec2::ZERO && real.y > 0)
	{
		gameScene->setCannonAngle(touch->getLocation());
		gameScene->onTouch(touch->getLocation());
		gameScene->_propLayer->setCannonAction(touch->getLocation());
		
	}
	
}

