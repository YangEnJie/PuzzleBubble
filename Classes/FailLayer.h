#ifndef FAIL_LAYER_H_
#define FAIL_LAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class FailLayer : public LayerColor
{
public:
	CREATE_FUNC(FailLayer);
	virtual bool init();
private:
	void menuAffirmCallBack(Ref* Psender);
	void menuCancelCallBack(Ref* Psender);

};







#endif