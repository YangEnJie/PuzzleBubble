#include "FailLayer.h"
#include "GameoverLayer.h"
#include "GameScene.h"
#include "UserData.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocostudio::timeline;

bool FailLayer::init()
{
	if (!LayerColor::init())
	{
		return false;
	}
	this->initWithColor(Color4B(0, 0, 0, 100));
	auto failLayer = CSLoader::createNode("FailLayer.csb");
	auto frameSize = Director::getInstance()->getVisibleSize();
	failLayer->setContentSize(frameSize);
	ui::Helper::doLayout(failLayer);
	addChild(failLayer);

	auto buttonAffirm = (ui::Button*)(failLayer->getChildByTag(86));
	buttonAffirm->addClickEventListener(CC_CALLBACK_1(FailLayer::menuAffirmCallBack, this));

	auto buttonCancel = (ui::Button*)(failLayer->getChildByTag(87));
	buttonCancel->addClickEventListener(CC_CALLBACK_1(FailLayer::menuCancelCallBack, this));

	auto fail_bg = (Sprite*)(failLayer->getChildByTag(80));
	auto rebirthLabel = (ui::TextBMFont*)(fail_bg->getChildByTag(108));
 	rebirthLabel->setString(StringUtils::format("%d", UserData::getInstance()->getRebirth()));
	

	return true;
}
void FailLayer::menuAffirmCallBack(Ref* Psender)
{
	if (UserData::getInstance()->getRebirth() > 0)
	{
		SimpleAudioEngine::getInstance()->playEffect("Music/Fuhuo.mp3");
		auto gamescene = (GameScene*)this->getParent();
		gamescene->mResume();
		UserData::getInstance()->addRebirth(-1);
		gamescene->_propLayer->setTime(60.0f);
		gamescene->removeChild(this);

	}

}

void FailLayer::menuCancelCallBack(Ref* Psender)
{
	auto gameScene = (GameScene*)this->getParent();
	auto gameOverLayer = GameoverLayer::create();
	gameScene->addChild(gameOverLayer);
	removeFromParentAndCleanup(true);
}