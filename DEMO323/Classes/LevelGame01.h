#ifndef LevelGame01_H
#define LevelGame01_H

#include "cocos2d.h"  
//#include <sstream>  

USING_NS_CC; 

class LevelGame01 : public cocos2d::CCLayer  
{  
private:  
    // ���µ�  
    CCPoint m_TouchDownPoint;  
    // ̧��� ���ʹ���ж��Ƿ�Ϊ����¼�  
    CCPoint m_TouchUpPoint;  
    // ��ǰ������  
    CCPoint m_TouchCurPoint; 
public:  
     static cocos2d::CCScene* createScene();  
    virtual bool init();  

	 // �����¼���� 
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
    ////��Ϸ����  
    void gameover();  
    ////��Ϸʤ��  
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