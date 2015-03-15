#ifndef TURNPLATE_LAYER_H_
#define TURNPLATE_LAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class TurnplateLayer : public Layer
{
public:
	CREATE_FUNC(TurnplateLayer);
	virtual bool init();
private:
	Node* _turnplateNode;
	bool _isPress = false;
	void menuRotateCallBack(Ref* Psender);
	void menuReturnCallBack(Ref* Psender);
	void addProps();
};



#endif