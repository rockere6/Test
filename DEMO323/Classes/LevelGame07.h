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

	 // �����¼���� 
    virtual void onEnter();  
    virtual void onExit();   
    
	void winGame(float dt);

	void updateGame(float dt);
    ////��Ϸ����  
    void gameover(float dt);  
    ////��Ϸʤ��  
    void gamewin(float dt);  
    //���ٶ��¼�
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