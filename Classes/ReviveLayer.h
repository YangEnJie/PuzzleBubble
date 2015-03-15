#ifndef REVIVE_LAYER_H_
#define REVIVE_LAYER_H_

#include "cocos2d.h"

USING_NS_CC;


class ReviveLayer : public LayerColor
{
public:
	CREATE_FUNC(ReviveLayer);
	virtual bool init();

private:
	void menuOverCallBack(Ref* Psender);

};






#endif