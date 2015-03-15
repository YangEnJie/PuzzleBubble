#ifndef BUBBLE_LAYER_H_
#define BUBBLE_LAYER_H_

#include "cocos2d.h"
#include "Bubble.h"
#include "GameConst.h"
#include "GameEnum.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"


USING_NS_CC;
using namespace cocostudio;

class BubbleLayer : public Layer
{
public:
		virtual bool init();

		static cocos2d::Scene* scene();

	
	void onTouch(Point target);

	CREATE_FUNC(BubbleLayer);
	virtual void update(float delta);
private:

	Bubble *board[MAX_ROWS][MAX_COLS]; 	 //泡泡棋盘
	Bubble *wait[MAX_WAIT_PAOPAO]; 	    // 等待的泡泡
public:
	Bubble *ready;  // 将会发射的泡泡
private:
	
	CC_SYNTHESIZE(Vec2, real, Real);
	CC_SYNTHESIZE(int, _level, Level);
	bool _havePass = false;

	EventListenerTouchOneByOne* _listener;
	bool initTheBoard(int level = 0);  //初始化关卡
	Bubble *randomPaoPao(); //获取随机泡泡
	Point getPointByRowAndCol(int row, int col); //根据行列及是否左缺确定位置
	Point getRowAndColByPoint(Point target);
	void initWaitPaoPao(); //初始化等待的泡泡
	void initReadyPaoPao(); //初始化准备发射的泡泡
	void setEnable();	//设置触摸有效
	void setDisable();	//设置触摸无效
	bool isCollideBorder();
	bool checCollideBoard();
	void changeWaitToReady();
	void correctReadyPosition();
	bool getFirstRowFlag();
	bool isCircleCollision(Point pos1, float radius1, Point pos2, float radius2);
	void findTheSameBubble(int i, int j, bool flag, BubbleType type);
	void bubbleBlast(int i, int j, bool flag);
	void moveTheBubble(int i, int j, bool flag, float distance);
	void deleteTheSameBubble(int i, int j, bool flag);
	void bubbleAction(Bubble *obj);
	void callbackRemoveBubble(Node *obj);
	void downBubbleActionCallBack(Node *obj);
	void jumpActionCallBack();
	void resetAllPass();
	void checkDownBubble();
	void downBubble();
	void downBubbleAction(Bubble *obj);
	void initBubbleAction(Bubble *obj, int i, int j);
	void gameOver(bool over = false);
	void setReadyAngle(Point target);
	void throwBallAction();
	bool isPass();
	void movementPassCallBack(Armature * armature, MovementEventType type, const std::string &name);
	void moveParantCallBack(Armature * armature, MovementEventType type, const std::string &name);
	void readyAction();

	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

public:

	Vector<Sprite*> _auxiliary;

	void colorBubble();
	void swapBubble();
	void bombBubble();
	void auxiliaryLine(Point tagrat);
};

#endif /* defined(__paopaolong__MainLayer__) */