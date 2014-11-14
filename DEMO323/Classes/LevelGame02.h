#ifndef LevelGame02_H
#define LevelGame02_H

#include "cocos2d.h"  
//#include <sstream>  

USING_NS_CC; 

class LevelGame02 : public cocos2d::CCLayer  
{  
public:  
    static cocos2d::CCScene* createScene();  
    virtual bool init();  	
	
	virtual void onEnter();  
	virtual void onExit();  

	 ////游戏结束  
    void gameover();  
    //////游戏胜利  
    void gamewin(); 
	void updateGame(float dt);

	void menuCloseCallback(CCObject* pSender); 
	void winloseCallback(CCObject *pSender);
	void resultCallback(CCObject *pSender);
	void nextCallback(CCObject *pSender);
	void pauseCallback(CCObject *pSender);
	void homeCallback(CCObject *pSender);
	void musicCallback(CCObject *pSender);
	CREATE_FUNC(LevelGame02); 
};  
  
#endif