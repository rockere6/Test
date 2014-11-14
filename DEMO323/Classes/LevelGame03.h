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
	
    ////判断精灵是否点击  
    //bool isInSprite(CCTouch *theTouch,CCSprite *sp);  
      
    ////点击  
    //bool ccTouchBegan(CCTouch *pTouch, CCEvent  *pEvent); 
      
    //游戏结束  
    void gameover(float dt);  
    //游戏胜利  
    void gamewin(float dt);  
    //void updateMusic(float dt); 
    void menuCloseCallback(CCObject* pSender);  
      
    //绿色按你点击  
    void greeCallback(CCObject* pSender);  
    //红色按钮点击  
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