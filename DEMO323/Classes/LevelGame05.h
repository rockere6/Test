#ifndef LevelGame05_H
#define LevelGame05_H

#include "cocos2d.h"  
//#include <sstream>  

USING_NS_CC; 

class LevelGame05 : public cocos2d::CCLayer  
{  
public:  
    static cocos2d::CCScene* createScene();  
    virtual bool init();  	
	
/*	virtual void onEnter(); */ 
	virtual void onExit();  

	/*void updateMusic(float dt);*/
	 ////游戏结束  
    void gameover(float dt);  
    //////游戏胜利  
    void gamewin(float dt); 
	void updateGame(float dt);
	void ItemCallback1(CCObject *pSender);
	void ItemCallback2(CCObject *pSender);
	void ItemCallback3(CCObject *pSender);
	void ItemCallback4(CCObject *pSender);
	void ItemCallback5(CCObject *pSender);
	void ItemCallback6(CCObject *pSender);
	void ItemCallback7(CCObject *pSender);
	void ItemCallback8(CCObject *pSender);
	void ItemCallback9(CCObject *pSender);
	void simleCallback(CCObject *pSender);
	void menuCloseCallback(CCObject *pSender);
	void winloseCallback(CCObject *pSender);
	void resultCallback(CCObject *pSender);
	void nextCallback(CCObject *pSender);
	void pauseCallback(CCObject *pSender);
	void homeCallback(CCObject *pSender);
	void musicCallback(CCObject *pSender);
	CREATE_FUNC(LevelGame05); 
};  
  
#endif