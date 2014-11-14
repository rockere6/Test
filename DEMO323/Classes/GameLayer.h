#ifndef GAMELAYER_H
#define GAMELAYER_H

#include "cocos2d.h"
#include "EnemyLayer.h"
#include "PersonLayer.h"
#include "NoTouchLayer.h"
//#include "ControlLayer.h"

USING_NS_CC;

//const int MAX_SCORE=9;

class GameLayer :
	public CCLayer
{
public:

	GameLayer(void);

	~GameLayer(void);

	CREATE_FUNC(GameLayer);

	virtual bool init();
	virtual void onExit(); 

	//void backgroundMove(float dt);

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	void registerWithTouchDispatcher();

	void update(float dt);

	void menuPauseCallback(CCObject* pSender);
	void menuSoapCallback(CCObject* pSender);

	void menuCloseCallback(CCObject* pSender);
	void winloseCallback(CCObject *pSender);
	void resultCallback(CCObject *pSender);
	/*void nextCallback(CCObject *pSender);*/
	void homeCallback(CCObject *pSender);
	void musicCallback(CCObject *pSender);
	void updateScore(int score);
	void gamewin(float dt);
	void gameover();

	//void menuBigBoomCallback(CCObject* pSender);

	//void updateBigBoomItem(int bigBoomCount);

	//virtual void keyBackClicked();//Android·µ»Ø¼ü

	//static Level getCurLevel();
	int score;
	CCLabelTTF *scoreItem;
	CCMenuItemImage* pPauseItem;
	CCMenuItemImage* pSoapItem;
	NoTouchLayer* noTouchLayer;
private:
	CCSprite* background1;
	//CCSprite* background2;

	PersonLayer* personLayer;
	//BulletLayer* bulletLayer;
	//MutiBulletsLayer* mutiBulletsLayer;
	//ControlLayer* controlLayer;
	//UFOLayer* ufoLayer;
	EnemyLayer* enemyLayer;

	//CCMenu* menuBigBoom;
	//CCLabelBMFont* bigBoomCountItem;

	
	//int bigBoomCount;
	//static Level level;
};

#endif