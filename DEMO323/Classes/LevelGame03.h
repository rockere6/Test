#ifndef __LevelGame03_SCENE_H__  
#define __LevelGame03_SCENE_H__  
  
#include "cocos2d.h"  
#include <sstream>  
  
USING_NS_CC;  
  
class LevelGame03 : public cocos2d::CCLayer  
{  
public:  
static cocos2d::CCScene* createScene();  
    virtual bool init();  

    virtual void onEnter();  
    virtual void onExit(); 
	
    ////�жϾ����Ƿ���  
    //bool isInSprite(CCTouch *theTouch,CCSprite *sp);  
      
    ////���  
    //bool ccTouchBegan(CCTouch *pTouch, CCEvent  *pEvent); 
      
    //��Ϸ����  
    void gameover(float dt);  
    //��Ϸʤ��  
    void gamewin(float dt);  
    //void updateMusic(float dt); 
    void menuCloseCallback(CCObject* pSender);  
      
    //��ɫ������  
    void greeCallback(CCObject* pSender);  
    //��ɫ��ť���  
    void redCallback(CCObject* pSender); 
	void winloseCallback(CCObject *pSender);
	void resultCallback(CCObject *pSender);
	void nextCallback(CCObject *pSender);
	void pauseCallback(CCObject *pSender);
	void homeCallback(CCObject *pSender);
	void musicCallback(CCObject *pSender);
    CREATE_FUNC(LevelGame03);  
};  
  
#endif // __LevelGame03_SCENE_H__  