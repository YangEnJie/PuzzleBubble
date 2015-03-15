#ifndef SHOP_LAYER_H_
#define SHOP_LAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class ShopLayer : public LayerColor
{
public:
	CREATE_FUNC(ShopLayer);
	virtual bool init();
	void menuReturnCallBack(Ref* pSender);
	void buyGold();

	Node* _shopLayer;

};




#endif