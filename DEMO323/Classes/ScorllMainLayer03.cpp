 
#include "ScorllMainLayer03.h"  
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "LevelGame03.h"


using namespace CocosDenshion;  
  
ScorllMainLayer03::ScorllMainLayer03()  
{  
}  
  
ScorllMainLayer03::~ScorllMainLayer03()  
{  
}  
  
bool ScorllMainLayer03::init()  
{  
    bool bRet = false;  
      
    do {  
        CCSize size = CCDirector::sharedDirector()->getWinSize();  
        
     int isLevelOn = CCUserDefault::sharedUserDefault()->getIntegerForKey("level_3");
	if(isLevelOn)
	{
		CCMenuItemImage *pCloseItem1 = CCMenuItemImage::create(
                                        "level-3-unlocked.png",
                                        "level-3-unlocked.png",
                                        this,
                                        menu_selector(ScorllMainLayer03::menuCloseCallback01));
    
	pCloseItem1->setPosition(ccp(size.width*0.5,size.height*0.5));

    CCMenu* pMenu = CCMenu::create(pCloseItem1, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
	}
	else{
		CCSprite *pCloseItem1 = CCSprite::create("level-3-locked.png");
		pCloseItem1->setPosition(ccp(size.width*0.5,size.height*0.5));
		this->addChild(pCloseItem1,1);
	}
   
        bRet = true;  
    } while (0);  
      
    return bRet;  
}  
  
void ScorllMainLayer03::menuCloseCallback01(CCObject* pSender){  
   // CCLog("SS");  
	//CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HelloWorld::scene()));  
  //CCScene *pScene = HistoryGame01::createScene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LevelGame03::createScene()));  
}  
