#ifndef PAUSE_LAYER_H_
#define PAUSE_LAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class PauseLayer : public LayerColor
{
public:
	CREATE_FUNC(PauseLayer);
	virtual bool init();
private:
	void menuContinueCallBack(Ref* Psender);
	void menuGetCallBack(Ref* Psender);
	void menuHomeCallBack(Ref* Psender);
};



#endif
