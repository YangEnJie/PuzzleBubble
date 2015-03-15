#ifndef TOUCH_LAYER_H_
#define TOUCH_LAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class TouchLayer : public Layer
{
public:
	CREATE_FUNC(TouchLayer);
	virtual bool init();
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
	CC_SYNTHESIZE(bool, _touchEnable, TouchEnable);

};







#endif


