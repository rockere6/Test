 
#include "ScorllMainLayer07.h"  
#include "SimpleAudioEngine.h"  
#include "LevelGame07.h"
  
using namespace CocosDenshion;  
  
ScorllMainLayer07::ScorllMainLayer07()  
{  
}  
  
ScorllMainLayer07::~ScorllMainLayer07()  
{  
}  
  
bool ScorllMainLayer07::init()  
{  
    bool bRet = false;  
      
    do {  
        CCSize size = CCDirector::sharedDirector()->getWinSize();   
          
 int isLevelOn = CCUserDefault::sharedUserDefault()->getIntegerForKey("level_7");
	if(isLevelOn)
	{
		CCMenuItemImage *pCloseItem1 = CCMenuItemImage::create(
                                        "level-7-unlocked.png",
                                        "level-7-unlocked.png",
                                        this,
                                        menu_selector(ScorllMainLayer07::menuCloseCallback01));
    
		pCloseItem1->setPosition(ccp(size.width*0.5,size.height*0.5));

		CCMenu* pMenu = CCMenu::create(pCloseItem1, NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu, 1);
	}
	else{
		CCSprite *pCloseItem1 = CCSprite::create("level-7-locked.png");
		pCloseItem1->setPosition(ccp(size.width*0.5,size.height*0.5));
		this->addChild(pCloseItem1,1);
	}
   
        bRet = true;  
    } while (0);  
      
    return bRet;  
}  
  
void ScorllMainLayer07::menuCloseCallback01(CCObject* pSender){  
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5,LevelGame07::createScene()));  
}  
