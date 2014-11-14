#ifndef __LevelGame04_SCENE_H__  
#define __LevelGame04_SCENE_H__  
  
#include "cocos2d.h"  
#include <sstream>  
  
USING_NS_CC;  
  
class LevelGame04 : public cocos2d::CCLayer  
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

      //void updateMusic(float dt);  
    //游戏结束  
    void gameover(float dt);  
    //游戏胜利  
    void gamewin(float dt);  
	//void updateGame(float dt);

    //判断精灵是否点击  
   // bool isInSprite(CCTouch *theTouch,CCSprite *sp);
	//点击
	//bool ccTouchBegan(CCTouch *pTouch, CCEvent  *pEvent);
      
    //MENU图标中的ME回调 
    void meCallback(CCObject* pSender);  
    //clickME回调 
    void clickmeCallback(CCObject* pSender); 

	void menuCloseCallback(CCObject* pSender);  
	void winloseCallback(CCObject *pSender);
	void resultCallback(CCObject *pSender);
	void nextCallback(CCObject *pSender);
	void pauseCallback(CCObject *pSender);
	void homeCallback(CCObject *pSender);
	void musicCallback(CCObject *pSender);

    CREATE_FUNC(LevelGame04);  
};  
  
#endif // __LevelGame04_SCENE_H__  