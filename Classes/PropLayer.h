#ifndef PROP_LAYER_H_
#define PROP_LAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class PropLayer : public Layer
{
public:
	CREATE_FUNC(PropLayer);
	virtual bool init();
	CC_SYNTHESIZE(float, _time, Time);
	void AddScoreLabel(int var);
	void setCannonAngle(Point target);
	void setCannonAction(Point target);
	void setBombNum();
	void setColorBubbleNum();

	Node* _propLayer;

private:

	
	void timeCallFunc();
	void menuBombCallBack(Ref* Psender);
	void menuHourglassCallBack(Ref* Psender);
	void menuPauseCallBack(Ref* Psender);
	void menuColorBubbleCallBack(Ref* Psender);
	void update(float delta);
};





#endif