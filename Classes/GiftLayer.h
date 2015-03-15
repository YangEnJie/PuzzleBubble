#ifndef GIFT_LAYER_H_
#define GIFT_LAYER_H_

#include "cocos2d.h"


USING_NS_CC;

class GiftLayer : public LayerColor
{
public:
	CREATE_FUNC(GiftLayer);
	virtual bool init();
	bool isGameScene = false;
private:
	Node* _giftNode;
	void getButtonCallBack(Ref* Pesender);
	void returnButtonCallBack(Ref* Pesender);

};















#endif