#include "GameoverLayer.h"
#include "StartScene.h"
#include "GameScene.h"
#include "UserData.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocostudio::timeline;

bool GameoverLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->initWithColor(Color4B(0, 0, 0, 100));
	auto gameoverLayer = CSLoader::createNode("GameoverLayer.csb");
	auto frameSize = Director::getInstance()->getVisibleSize();
	gameoverLayer->setContentSize(frameSize);
	ui::Helper::doLayout(gameoverLayer);
	addChild(gameoverLayer);

	auto buttonStart = (ui::Button*)(gameoverLayer->getChildByTag(78));
	buttonStart->addClickEventListener(CC_CALLBACK_1(GameoverLayer::menuStartCallBack, this));

	auto buttonOver = (ui::Button*)(gameoverLayer->getChildByTag(77));
	buttonOver->addClickEventListener(CC_CALLBACK_1(GameoverLayer::menuOverCallBack, this));

	auto scoreText = (ui::TextBMFont*)(gameoverLayer->getChildByTag(106));
	scoreText->setString(StringUtils::format("%d", UserData::getInstance()->getScore()));

	auto bestScoreText = (ui::TextBMFont*)(gameoverLayer->getChildByTag(104));
	bestScoreText->setString(StringUtils::format("%d", UserData::getInstance()->getBestScore()));

	auto goldText = (ui::TextBMFont*)(gameoverLayer->getChildByTag(105));
	goldText->setString(StringUtils::format("%d", UserData::getInstance()->getGold()));



	if (scoreText->getString() == bestScoreText->getString())
	{
		auto recordSprite = (Sprite*)gameoverLayer->getChildByTag(71);
		if (!recordSprite->isVisible())
		{
			recordSprite->setVisible(true);
		}
	}

	return true;
}
void GameoverLayer::menuStartCallBack(Ref* Psender)
{
	Director::getInstance()->replaceScene(GameScene::create());
}

void GameoverLayer::menuOverCallBack(Ref* Psender)
{
	Director::getInstance()->replaceScene(StartLayer::scene());
}