#ifndef LevelGame06_H
#define LevelGame06_H

#include "cocos2d.h"  
//#include <sstream>  

USING_NS_CC; 

class LevelGame06 : public cocos2d::CCLayer  
{  

public:  
    static cocos2d::CCScene* createScene();  
    virtual bool init();  

	 // 触摸事件相关 
    virtual void onEnter();  
    virtual void onExit();  

	//void updateMusic(float dt);

//	bool isInSprite(CCTouch *theTouch,CCSprite *sp);
//	bool ccTouchBegan(CCTouch *pTouch, CCEvent  *pEvent);  
//    void ccTouchMoved(CCTouch *pTouch, CCEvent  *pEvent);  
//  void ccTouchEnded(CCTouch *pTouch, CCEvent  *pEvent);  
//    void ccTouchCancelled(CCTouch *pTouch, CCEvent  *pEvent);  
    //  
	void updateGame(float dt);
	void yaoCallback(float dt);
    ////游戏结束  
    void gameover(float dt);  
    ////游戏胜利  
    void gamewin(float dt);  
      
   
	void erCallback(CCObject* pSender);
	//void yaomingCallback(CCObject *pSender);

	void menuCloseCallback(CCObject* pSender); 
	void winloseCallback(CCObject *pSender);
	void resultCallback(CCObject *pSender);
	void nextCallback(CCObject *pSender);
	void pauseCallback(CCObject *pSender);
	void homeCallback(CCObject *pSender);
	void musicCallback(CCObject *pSender);
    CREATE_FUNC(LevelGame06);  
};  

#endif