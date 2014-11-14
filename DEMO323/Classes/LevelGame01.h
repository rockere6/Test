#ifndef LevelGame01_H
#define LevelGame01_H

#include "cocos2d.h"  
//#include <sstream>  

USING_NS_CC; 

class LevelGame01 : public cocos2d::CCLayer  
{  
private:  
    // 按下点  
    CCPoint m_TouchDownPoint;  
    // 抬起点 配合使用判断是否为点击事件  
    CCPoint m_TouchUpPoint;  
    // 当前触摸点  
    CCPoint m_TouchCurPoint; 
public:  
     static cocos2d::CCScene* createScene();  
    virtual bool init();  

	 // 触摸事件相关 
    virtual void onEnter();  
    virtual void onExit();  
	bool isInSprite(CCTouch *theTouch,CCSprite *sp);
	bool ccTouchBegan(CCTouch *pTouch, CCEvent  *pEvent);  
    void ccTouchMoved(CCTouch *pTouch, CCEvent  *pEvent);  
    void ccTouchEnded(CCTouch *pTouch, CCEvent  *pEvent);  
    void ccTouchCancelled(CCTouch *pTouch, CCEvent  *pEvent);  
    //  
	void updateGame(float dt);
	/*void updateMusic(float dt);*/
    ////游戏结束  
    void gameover();  
    ////游戏胜利  
    void gamewin();  
      
    void menuCloseCallback(CCObject* pSender); 
	void wangnimaCallback(CCObject* pSender);
	void duCallback(CCObject *pSender);
	void yiCallback(CCObject *pSender);

	void winloseCallback(CCObject *pSender);
	void resultCallback(CCObject *pSender);
	void nextCallback(CCObject *pSender);
	void pauseCallback(CCObject *pSender);
	void homeCallback(CCObject *pSender);
	void musicCallback(CCObject *pSender);
    CREATE_FUNC(LevelGame01);  
};  

#endif