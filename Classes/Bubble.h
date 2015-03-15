#ifndef BUBBLE_H_
#define BUBBLE_H_

#include "cocos2d.h"
#include "GameEnum.h"
USING_NS_CC;
//泡泡类，包含类型和自己所在的一行是否是左缺的状态
class Bubble : public Sprite
{
public:
	Bubble();
	~Bubble();
	static Bubble *initWithType(BubbleType type = BUBBLE_TYPE1);
	CREATE_FUNC(Bubble);
	CC_SYNTHESIZE(BubbleType, _type, Type);//泡泡的类型
	CC_SYNTHESIZE(bool, _isSame, IsSame); //判断是否是统一类型的
	CC_SYNTHESIZE(bool, _isPass, IsPass); //判断是否路过
	CC_SYNTHESIZE(bool, _flag, Flag);//是否是左缺的状态
	CC_SYNTHESIZE(bool, _isMove, IsMove); //是否移动过
	CC_SYNTHESIZE(bool, _isDie, IsDie);
private:
	static std::string getStringByType(BubbleType type);
};

#endif /* defined(__paopaolong__PaoPao__) */