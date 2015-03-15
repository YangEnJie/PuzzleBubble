#include "StartScene.h"
#include "GameScene.h"
#include "TurnplateLayer.h"
#include "UserData.h"
#include "GameConst.h"
#include "ui/CocosGUI.h"
#include "ShopLayer.h"
#include "GiftLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace cocostudio::timeline;
using namespace CocosDenshion;

StartLayer::StartLayer()
{
	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic("main_music.mp3", true);
}

StartLayer::~StartLayer()
{
	
}

Scene* StartLayer::scene()
{
    Scene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = Scene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        StartLayer *layer = StartLayer::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	setReal(Vec2(-0.5f, 0.5f));
	_startNode = CSLoader::createNode("StartLayer.csb");
	addChild(_startNode);
	_startNode->setTag(50);

	auto buttonStart = (ui::Button*)_startNode->getChildByTag(3);
	buttonStart->addClickEventListener(CC_CALLBACK_1(StartLayer::menuNewGameCallback, this));

	auto buttonEnd = (ui::Button*)_startNode->getChildByTag(4);
	buttonEnd->addClickEventListener(CC_CALLBACK_1(StartLayer::menuCloseCallback, this));


	auto shopImageView = (ui::ImageView*)_startNode->getChildByTag(79);
	shopImageView->addClickEventListener(CC_CALLBACK_1(StartLayer::menuShopCallBack, this));

	auto goldImageView = (ui::ImageView*)_startNode->getChildByTag(81);
	goldImageView->addClickEventListener(CC_CALLBACK_1(StartLayer::menuShopCallBack, this));

	auto goldBg = (Sprite*)_startNode->getChildByTag(87);
	auto goldLabel = (ui::TextBMFont*)goldBg->getChildByTag(107);
	goldLabel->setString(StringUtils::format("%d", UserData::getInstance()->getGold()));


	auto giftImageView = (ui::ImageView*)_startNode->getChildByTag(80);
	giftImageView->addClickEventListener(CC_CALLBACK_1(StartLayer::menuGiftCallBack, this));

	auto turnImageView = (ui::ImageView*)_startNode->getChildByTag(61);
	turnImageView->addClickEventListener(CC_CALLBACK_1(StartLayer::menuTurnCallBack, this));

	auto armature = (Armature*)_startNode->getChildByTag(10);
	armature->getAnimation()->play("Animation1");
	
	armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(StartLayer::movementCall, this));

	SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/bgm.mp3", true);

	auto armatureLogo = (Armature*)_startNode->getChildByTag(13);
	_disPoint = armatureLogo->getPosition();

	
	auto volToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(StartLayer::menuVolCallBack, this), MenuItemImage::create("Start/vol.png", "Start/vol.png"), MenuItemImage::create("Start/vol_1.png", "Start/vol_1.png"), nullptr);
	auto menu = Menu::create(volToggle,nullptr);
	this->addChild(menu);
	menu->setPosition(470.0f, 890.0f);



	return true;
}

void StartLayer::menuCloseCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("Music/Click.mp3");
	UserData::getInstance()->saveData();
    Director::getInstance()->end();
	exit(0);
}

void StartLayer::menuNewGameCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("Music/Click.mp3");
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	Director::getInstance()->pushScene(GameScene::create());
}

void StartLayer::menuShopCallBack(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("Music/Click.mp3");
	auto shopLayer = ShopLayer::create();
	addChild(shopLayer);
}

void StartLayer::menuGiftCallBack(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("Music/Click.mp3");
	auto giftLayer = GiftLayer::create();
	addChild(giftLayer);
}
void StartLayer::menuTurnCallBack(Ref* psender)
{
	SimpleAudioEngine::getInstance()->playEffect("Music/Click.mp3");
	auto turnPlate = TurnplateLayer::create();
	this->addChild(turnPlate);
}
void StartLayer::movementCall(Armature * armature, MovementEventType type, const std::string &name)
{
	if (type == COMPLETE){
		
		if (name == "Animation1")
		{
			haveRun = true;
			scheduleUpdate();
			armature->getAnimation()->play("Animation1_Copy1");
			auto moveActionBoy = MoveBy::create(1.5f, Vec2(-5, 15));
			auto seqBoy = Sequence::create(moveActionBoy, moveActionBoy->reverse(), nullptr);
			auto repeatBoy = RepeatForever::create(seqBoy);
			auto spriteBoy = (Sprite*)_startNode->getChildByTag(12);
			spriteBoy->runAction(repeatBoy);

			auto moveActionCat = MoveBy::create(1.5f, Vec2(15, 8));
			auto seqCat = Sequence::create(moveActionCat, moveActionCat->reverse(), nullptr);
			auto repeatCat = RepeatForever::create(seqCat);
			auto spriteCat = (Sprite*)_startNode->getChildByTag(41);
			spriteCat->runAction(repeatCat);


			auto moveActionArm = MoveBy::create(1.5f, Vec2(8, 8));
			auto seqArm = Sequence::create(moveActionArm, moveActionArm->reverse(), nullptr);
			auto repeatArm = RepeatForever::create(seqArm);
			armature->runAction(repeatArm);
		}
	}
}
void StartLayer::update(float delta)
{
	auto ball = (Sprite*)_startNode->getChildByTag(43);
	ball->setPosition(ball->getPosition().x + getReal().x * 20, ball->getPosition().y + getReal().y * 20);
	if (ball->getPosition().x <= BUBBLE_RADIUS)
	{
		setReal((_disPoint - ball->getPosition()).getNormalized());
	}
	if (ball->getPosition().x >= _disPoint.x && ball->getPosition().y >= _disPoint.y)
	{
		ball->removeAllChildren();
		auto scale = ScaleTo::create(0.5f, 1.3f);
		ball->runAction(scale);
		unscheduleUpdate();
		ball->setPosition(_disPoint);
		auto armatureLogo = (Armature*)_startNode->getChildByTag(13);
		armatureLogo->getAnimation()->play("Animation1");
		armatureLogo->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(StartLayer::movementLogoCall,this));
	}

}
void StartLayer::movementLogoCall(Armature * armature, MovementEventType type, const std::string &name)
{

	if (type == COMPLETE){
		if (name == "Animation1")
		{
			armature->getAnimation()->play("Animation2");
// 
// 			if (!UserData::getInstance()->getHaveRaffle())
// 			{
// 				auto turnPlate = TurnplateLayer::create();
// 				this->addChild(turnPlate);
// 				
// 			}
		}
	}
}
void StartLayer::menuVolCallBack(Ref* pSender)
{

}