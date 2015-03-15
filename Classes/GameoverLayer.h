#ifndef GAMEOVER_LAYER_H_
#define GAMEOVER_LAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class GameoverLayer : public LayerColor
{
public:
	CREATE_FUNC(GameoverLayer);
	virtual bool init();
private:
	void menuOverCallBack(Ref* Psender);
	void menuStartCallBack(Ref* Psender);

};







#endif