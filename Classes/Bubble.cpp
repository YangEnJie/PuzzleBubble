#include "Bubble.h"
#include "GameConst.h"
#include "cocostudio/CocoStudio.h"


using namespace cocostudio;

Bubble::Bubble()//���캯����ʼ��
{
	_flag = false;
	_type = BUBBLE_TYPE_UNKNOW;
	_isSame = false;
	_isPass = false;
	_isMove = false;
	_isDie = false;
}

Bubble::~Bubble()
{

}

Bubble * Bubble::initWithType(BubbleType type) //���ݴ���������������������
{
	Bubble *pRet = Bubble::create();
	pRet->setType(type);
	pRet->initWithSpriteFrameName(getStringByType(type));






	return pRet;
}



std::string Bubble::getStringByType(BubbleType type) //��ͬ���ͻ�ȡ��ͬ��ͼƬ��Դ
{
	std::string pRet;
	switch (type) {
	case BUBBLE_TYPE1:
	case BUBBLE_TYPE2:
	case BUBBLE_TYPE3:
	case BUBBLE_TYPE4:
	case BUBBLE_TYPE5:
	case BUBBLE_TYPE6:
	case BUBBLE_TYPE7:
		pRet = StringUtils::format(BUBBLE_NAME.c_str(), (int)type);
		break;
	case BUBBLE_TYPE_COLOR:
		pRet = BUBBLE_COLOR_NAME;
		break;
	default:
		break;
	}
	return pRet;
}