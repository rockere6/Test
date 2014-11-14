#include "ScorllMainLayer01.h"  
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "LevelGame01.h"


using namespace CocosDenshion;  
  
ScorllMainLayer01::ScorllMainLayer01()  
{  
}  
  
ScorllMainLayer01::~ScorllMainLayer01()  
{  
}  
  
bool ScorllMainLayer01::init()  
{  
    bool bRet = false;  
      
    do {  
        CCSize size = CCDirector::sharedDirector()->getWinSize();  
        //初始化信息  
        //SpriteFrameCache *cache = SpriteFrameCache::getInstance();  
        //cache->addSpriteFramesWithFile("level_image.plist");  
          
	CCMenuItemImage *pCloseItem1 = CCMenuItemImage::create(
                                        "level-1-unlocked.png",
                                        "level-1-unlocked.png",
                                        this,
                                        menu_selector(ScorllMainLayer01::menuCloseCallback01));
    
	pCloseItem1->setPosition(ccp(size.width*0.5,size.height*0.5));

    CCMenu* pMenu = CCMenu::create(pCloseItem1, NULL);
    pMenu->setPosition(CCPointZero);
	
    this->addChild(pMenu, 1);
   
        bRet = true;  
    } while (0);  
      
    return bRet;  
}  
  
void ScorllMainLayer01::menuCloseCallback01(CCObject* pSender){  
   // CCLog("SS");  
	//CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HelloWorld::scene()));  
  //CCScene *pScene = HistoryGame01::createScene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LevelGame01::createScene()));  
}  
//void ScorllMainLayer01::menuCloseCallback02(CCObject* pSender){  
//	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LevelGame03::createScene()));  
//}  
//void ScorllMainLayer01::menuCloseCallback03(CCObject* pSender){  
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LevelGame01::createScene()));  
//}  
//void ScorllMainLayer01::menuCloseCallback04(CCObject* pSender){  
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LevelGame02::createScene()));     
//} 