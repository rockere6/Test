
#include "ScorllMainLayer02.h"  
#include "SimpleAudioEngine.h"  
#include "LevelGame02.h"
  
using namespace CocosDenshion;  
  
ScorllMainLayer02::ScorllMainLayer02()  
{  
}  
  
ScorllMainLayer02::~ScorllMainLayer02()  
{  
}  
  
bool ScorllMainLayer02::init()  
{  
    bool bRet = false;  
      
    do {  
        CCSize size = CCDirector::sharedDirector()->getWinSize();  
       
    
	//在关卡选择画面用IF判断level_2是否为1
	//为1则创建开锁图片，为0则创建为开锁图片
	
	int isLevelOn = CCUserDefault::sharedUserDefault()->getIntegerForKey("level_2");
	if(isLevelOn)
	{
		CCMenuItemImage *pCloseItem1 = CCMenuItemImage::create(
                                        "level-2-unlocked.png",
                                        "level-2-unlocked.png",
                                        this,
                                        menu_selector(ScorllMainLayer02::menuCloseCallback01));
    
	pCloseItem1->setPosition(ccp(size.width*0.5,size.height*0.5));

    CCMenu* pMenu = CCMenu::create(pCloseItem1, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
	}
	else{
		CCSprite *pCloseItem1 = CCSprite::create("level-2-locked.png");
		pCloseItem1->setPosition(ccp(size.width*0.5,size.height*0.5));
		this->addChild(pCloseItem1,1);
	}
        bRet = true;  
    } while (0);  
      
    return bRet;  
}  
  
void ScorllMainLayer02::menuCloseCallback01(CCObject* pSender){  
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LevelGame02::createScene()));  
}  
