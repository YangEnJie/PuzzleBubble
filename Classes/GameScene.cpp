#include "GameScene.h"
#include "UserData.h"
#include "GameoverLayer.h"
#include "PauseLayer.h"
#include "FailLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocostudio::timeline;


bool GameScene::init()
{

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bubbles.plist");

	_bg = CSLoader::createNode("Background.csb");
	auto frameSize = Director::getInstance()->getVisibleSize();
	_bg->setContentSize(frameSize);
	ui::Helper::doLayout(_bg);
	addChild(_bg);

	SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/bgm.mp3", true);

	//_touchLayer = TouchLayer::create();
	//addChild(_touchLayer);

	_bubbleLayer = BubbleLayer::create();
	addChild(_bubbleLayer);

	_propLayer = PropLayer::create();
	addChild(_propLayer);








	auto lisenter = EventListenerKeyboard::create();


	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

	return true;
}

void GameScene::operateAllSchedulerAndActions(Node* node, OperateFlag flag)
{
	if (node->isRunning()) {
		switch (flag) {
		case k_Operate_Pause:
			node->pause();
			break;
		case k_Operate_Resume:
			node->resume();
		default:
			break;
		}
		auto children = node->getChildren();
		if (children.size() > 0) {
			for (auto child : children) {
				operateAllSchedulerAndActions(child, flag);
			}
		}
	}
}

void GameScene::mPause()
{
	operateAllSchedulerAndActions(this, k_Operate_Pause);
}

void GameScene::mResume()
{

	operateAllSchedulerAndActions(this, k_Operate_Resume);

}

void GameScene::onTouch(Point target)
{
	_bubbleLayer->onTouch(target);
}
void GameScene::setCannonAngle(Point target)
{
	_propLayer->setCannonAngle(target);
}
void GameScene::setTouchEnable(bool enable)
{
	_touchLayer->setTouchEnable(enable);
}
void GameScene::swapBubble()
{
	_bubbleLayer->swapBubble();
}
void GameScene::bombBubble()
{
	_bubbleLayer->bombBubble();
}
void GameScene::colorBubble()
{
	_bubbleLayer->colorBubble();
}
void GameScene::gameOver(bool over)
{
	UserData::getInstance()->saveData();
	operateAllSchedulerAndActions(this, k_Operate_Pause);

	if (over)
	{
		SimpleAudioEngine::getInstance()->playEffect("Music/Ending.mp3");
		auto overLayer = GameoverLayer::create();
		this->addChild(overLayer);
	}
	else
	{
		SimpleAudioEngine::getInstance()->playEffect("Music/end.mp3");
		auto failLayer = FailLayer::create();
		this->addChild(failLayer);
	}

}
void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode != EventKeyboard::KeyCode::KEY_BACK)
	{
		return;
	}
	operateAllSchedulerAndActions(this, k_Operate_Pause);
	auto pauseLayer = PauseLayer::create();
	addChild(pauseLayer);

}