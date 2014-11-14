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
	
    ////�жϾ����Ƿ���  
    //bool isInSprite(CCTouch *theTouch,CCSprite *sp);  
      
    ////���  
    //bool ccTouchBegan(CCTouch *pTouch, CCEvent  *pEvent); 

      //void updateMusic(float dt);  
    //��Ϸ����  
    void gameover(float dt);  
    //��Ϸʤ��  
    void gamewin(float dt);  
	//void updateGame(float dt);

    //�жϾ����Ƿ���  
   // bool isInSprite(CCTouch *theTouch,CCSprite *sp);
	//���
	//bool ccTouchBegan(CCTouch *pTouch, CCEvent  *pEvent);
      
    //MENUͼ���е�ME�ص� 
    void meCallback(CCObject* pSender);  
    //clickME�ص� 
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