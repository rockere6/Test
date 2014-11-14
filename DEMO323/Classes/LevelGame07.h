#ifndef LevelGame07_H
#define LevelGame07_H

#include "cocos2d.h"  
//#include <sstream>  

USING_NS_CC; 

class LevelGame07 : public cocos2d::CCLayer  
{  

public:  
    static cocos2d::CCScene* createScene();  
    virtual bool init();  

	 // 触摸事件相关 
    virtual void onEnter();  
    virtual void onExit();   
    
	void winGame(float dt);

	void updateGame(float dt);
    ////游戏结束  
    void gameover(float dt);  
    ////游戏胜利  
    void gamewin(float dt);  
    //加速度事件
	virtual void didAccelerate(CCAcceleration* pAccelerationValue);
   

	void menuCloseCallback(CCObject* pSender); 
	void winloseCallback(CCObject *pSender);
	void resultCallback(CCObject *pSender);
	void nextCallback(CCObject *pSender);
	void pauseCallback(CCObject *pSender);
	void homeCallback(CCObject *pSender);
	void musicCallback(CCObject *pSender);
    CREATE_FUNC(LevelGame07);  
};  

#endif