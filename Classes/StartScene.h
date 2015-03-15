#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocostudio;

class StartLayer : public cocos2d::Layer
{
public:

	StartLayer();
	~StartLayer();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
	void menuNewGameCallback(Ref* pSender);
	void menuShopCallBack(Ref* pSender);
	void menuVolCallBack(Ref* pSender);
	void menuGiftCallBack(Ref* pSender);
	void menuTurnCallBack(Ref* psender);

	void movementCall(Armature * armature, MovementEventType type, const std::string &name);
	void movementLogoCall(Armature * armature, MovementEventType type, const std::string &name);
	void update(float delta);

	Node * _startNode;

	bool haveRun = false;

	CREATE_FUNC(StartLayer);
	CC_SYNTHESIZE(Vec2, real, Real);
	Vec2 _disPoint;

};

#endif  // __HELLOWORLD_SCENE_H__