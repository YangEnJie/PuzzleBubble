#ifndef BUBBLE_H_
#define BUBBLE_H_

#include "cocos2d.h"
#include "GameEnum.h"
USING_NS_CC;
//�����࣬�������ͺ��Լ����ڵ�һ���Ƿ�����ȱ��״̬
class Bubble : public Sprite
{
public:
	Bubble();
	~Bubble();
	static Bubble *initWithType(BubbleType type = BUBBLE_TYPE1);
	CREATE_FUNC(Bubble);
	CC_SYNTHESIZE(BubbleType, _type, Type);//���ݵ�����
	CC_SYNTHESIZE(bool, _isSame, IsSame); //�ж��Ƿ���ͳһ���͵�
	CC_SYNTHESIZE(bool, _isPass, IsPass); //�ж��Ƿ�·��
	CC_SYNTHESIZE(bool, _flag, Flag);//�Ƿ�����ȱ��״̬
	CC_SYNTHESIZE(bool, _isMove, IsMove); //�Ƿ��ƶ���
	CC_SYNTHESIZE(bool, _isDie, IsDie);
private:
	static std::string getStringByType(BubbleType type);
};

#endif /* defined(__paopaolong__PaoPao__) */