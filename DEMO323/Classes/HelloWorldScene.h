#ifndef __HELLOWORLD_SCENE_H__  
#define __HELLOWORLD_SCENE_H__  
  
#include "cocos2d.h"  
  
class HelloWorld : public cocos2d::CCLayer  
{  
public:  
    // there's no 'id' in cpp, so we recommend returning the class instance pointer  
    static cocos2d::CCScene* scene();  
  
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone  
    virtual bool init();    
    
	void keyBackClicked();
    // a selector callback  
    void menuCloseCallback(CCObject* pSender);  
	void menuClose(CCObject* pSender); 
    void musicClose(CCObject* pSender);
	void InforCallback(CCObject* pSender);
	void resultCallback(CCObject *pSender);
    // implement the "static create()" method manually  
    CREATE_FUNC(HelloWorld);  
};  
  
#endif // __HELLOWORLD_SCENE_H__ 