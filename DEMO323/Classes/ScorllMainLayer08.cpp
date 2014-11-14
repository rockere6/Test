#include "ScorllMainLayer08.h"  
#include "SimpleAudioEngine.h"  
#include "LevelGame08.h"
  
using namespace CocosDenshion;  
  
ScorllMainLayer08::ScorllMainLayer08()  
{  
}  
  
ScorllMainLayer08::~ScorllMainLayer08()  
{  
}  
  
bool ScorllMainLayer08::init()  
{  
    bool bRet = false;  
      
    do {  
        CCSize size = CCDirector::sharedDirector()->getWinSize();  
       
    
	//�ڹؿ�ѡ������IF�ж�level_8�Ƿ�Ϊ1
	//Ϊ1�򴴽�����ͼƬ��Ϊ0�򴴽�Ϊ����ͼƬ
	
	int isLevelOn = CCUserDefault::sharedUserDefault()->getIntegerForKey("level_8");
	//int isLevelOn = 1;

	if(isLevelOn)
	{
		CCMenuItemImage *pCloseItem1 = CCMenuItemImage::create(
                                        "level-8-unlocked.png",
                                        "level-8-unlocked.png",
                                        this,
                                        menu_selector(ScorllMainLayer08::menuCloseCallback01));
    
	pCloseItem1->setPosition(ccp(size.width*0.5,size.height*0.5));

    CCMenu* pMenu = CCMenu::create(pCloseItem1, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
	}
	else{
		CCSprite *pCloseItem1 = CCSprite::create("level-8-locked.png");
		pCloseItem1->setPosition(ccp(size.width*0.5,size.height*0.5));
		this->addChild(pCloseItem1,1);
	}
        bRet = true;  
    } while (0);  
      
    return bRet;  
}  
  
void ScorllMainLayer08::menuCloseCallback01(CCObject* pSender){  
	
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5,LevelGame08::createScene()));  
}  
