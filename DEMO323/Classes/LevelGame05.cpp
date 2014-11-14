#include "LevelGame05.h"
#include "LevelGame06.h"
#include "ScrollViewScene.h" 
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC; 
using namespace CocosDenshion;
static bool isNext =false;
extern bool isMusic;  

static char count=9;
static bool isDouble=false;
static bool isMatch=false;
static char lastItemIndex=0;
static char curItemIndex=0;
static bool isFinish=true;
static bool isKillSchedule=false;
static bool flagMusic = false;

CCScene* LevelGame05::createScene()  
{  
    CCScene *scene = CCScene::create();  
    CCLayer *layer = LevelGame05::create();  
    scene->addChild(layer);  
	//scene->autorelease(); 
    return scene;  
}  

bool LevelGame05::init() 
{
	if ( !CCLayer::init() )  
    {  
        return false;  
    }
//isNext = false;
	flagMusic = false;

	CCUserDefault::sharedUserDefault()->setIntegerForKey("level_5", 1);
	CCUserDefault::sharedUserDefault()->flush();  
	count=9;
	isDouble=false;
	isMatch=false;
	lastItemIndex=0;//1-9
	curItemIndex=0;//1-9
	isFinish=true;
	isKillSchedule=false;

	CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
    cache->addSpriteFramesWithFile("level-5.plist");

	
	CCSprite* sprite =CCSprite::createWithSpriteFrameName("background-5.png"); 
	CCSize sprite_size = sprite->getContentSize();
	sprite->setScaleX(size.width/sprite_size.width);
	sprite->setScaleY(size.height/sprite_size.height);
    sprite->setPosition(CCPoint(size.width*0.5,size.height*0.5)); 
	sprite->setTag(90);
    this->addChild(sprite);  

	CCMenuItemImage *pItem1 = CCMenuItemImage::create();
	pItem1->setNormalSpriteFrame(cache->spriteFrameByName("poker.png"));
	pItem1->setSelectedSpriteFrame(cache->spriteFrameByName("poker.png"));
	pItem1->initWithTarget(this,menu_selector(LevelGame05::ItemCallback1));
	pItem1->setPosition(ccp(size.width*0.5, size.height*0.5+200));
    pItem1->setTag(91); 

	CCMenuItemImage *pItem2 = CCMenuItemImage::create();
	pItem2->setNormalSpriteFrame(cache->spriteFrameByName("poker.png"));
	pItem2->setSelectedSpriteFrame(cache->spriteFrameByName("poker.png"));
	pItem2->initWithTarget(this,menu_selector(LevelGame05::ItemCallback2));
	pItem2->setPosition(ccp(size.width*0.5+200, size.height*0.5+200));
    pItem2->setTag(92); 

	CCMenuItemImage *pItem3 = CCMenuItemImage::create();
	pItem3->setNormalSpriteFrame(cache->spriteFrameByName("poker.png"));
	pItem3->setSelectedSpriteFrame(cache->spriteFrameByName("poker.png"));
	pItem3->initWithTarget(this,menu_selector(LevelGame05::ItemCallback3));
	pItem3->setPosition(ccp(size.width*0.5+400, size.height*0.5+200));
    pItem3->setTag(93); 

	CCMenuItemImage *pItem4 = CCMenuItemImage::create();
	pItem4->setNormalSpriteFrame(cache->spriteFrameByName("poker.png"));
	pItem4->setSelectedSpriteFrame(cache->spriteFrameByName("poker.png"));
	pItem4->initWithTarget(this,menu_selector(LevelGame05::ItemCallback4));
	pItem4->setPosition(ccp(size.width*0.5, size.height*0.5));
    pItem4->setTag(94); 

	CCMenuItemImage *pItem5 = CCMenuItemImage::create();
	pItem5->setNormalSpriteFrame(cache->spriteFrameByName("poker.png"));
	pItem5->setSelectedSpriteFrame(cache->spriteFrameByName("poker.png"));
	pItem5->initWithTarget(this,menu_selector(LevelGame05::ItemCallback5));
	pItem5->setPosition(ccp(size.width*0.5+200, size.height*0.5));
    pItem5->setTag(95); 

	CCMenuItemImage *pItem6 = CCMenuItemImage::create();
	pItem6->setNormalSpriteFrame(cache->spriteFrameByName("poker.png"));
	pItem6->setSelectedSpriteFrame(cache->spriteFrameByName("poker.png"));
	pItem6->initWithTarget(this,menu_selector(LevelGame05::ItemCallback6));
	pItem6->setPosition(ccp(size.width*0.5+400, size.height*0.5));
    pItem6->setTag(96); 

	CCMenuItemImage *pItem7 = CCMenuItemImage::create();
	pItem7->setNormalSpriteFrame(cache->spriteFrameByName("poker.png"));
	pItem7->setSelectedSpriteFrame(cache->spriteFrameByName("poker.png"));
	pItem7->initWithTarget(this,menu_selector(LevelGame05::ItemCallback7));
	pItem7->setPosition(ccp(size.width*0.5, size.height*0.5-200));
    pItem7->setTag(97); 

	CCMenuItemImage *pItem8 = CCMenuItemImage::create();
	pItem8->setNormalSpriteFrame(cache->spriteFrameByName("poker.png"));
	pItem8->setSelectedSpriteFrame(cache->spriteFrameByName("poker.png"));
	pItem8->initWithTarget(this,menu_selector(LevelGame05::ItemCallback8));
	pItem8->setPosition(ccp(size.width*0.5+200, size.height*0.5-200));
    pItem8->setTag(98); 

	CCMenuItemImage *pItem9 = CCMenuItemImage::create();
	pItem9->setNormalSpriteFrame(cache->spriteFrameByName("poker.png"));
	pItem9->setSelectedSpriteFrame(cache->spriteFrameByName("poker.png"));
	pItem9->initWithTarget(this,menu_selector(LevelGame05::ItemCallback9));
	pItem9->setPosition(ccp(size.width*0.5+400, size.height*0.5-200));
    pItem9->setTag(99); 

	CCMenu* pmenu= CCMenu::create(pItem1,pItem2,pItem3,pItem4,pItem5,
						pItem6,pItem7,pItem8,pItem9,NULL);
    pmenu->setPosition(CCPointZero);
	pmenu->setTag(100);  
	//pmenu->setEnabled(false);
    this->addChild(pmenu); 

	CCMenuItemImage *pauseItem = CCMenuItemImage::create();
		pauseItem->setNormalSpriteFrame(cache->spriteFrameByName("pause-1.png"));
		pauseItem->setSelectedSpriteFrame(cache->spriteFrameByName("pause-2.png"));
		pauseItem->initWithTarget(this, menu_selector(LevelGame05::pauseCallback));
		pauseItem->setPosition(CCPoint(size.width-100,size.height*0.9));
    CCMenu *pauseMenu = CCMenu::create(pauseItem, NULL);  
   pauseMenu->setPosition(CCPointZero);  
   pauseMenu->setTag(101); 
    this->addChild(pauseMenu, 1);  

	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("back2.mp3",true);
		flagMusic = true;
	}
	return true;  
}


void LevelGame05::onExit()
{
	if(isNext == false)
	{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
 cache->removeSpriteFramesFromFile("level-5.plist");  
	}
	if(isKillSchedule == false)
	{
		unschedule(schedule_selector(LevelGame05::updateGame));
	}
	isNext =true;
 CCLayer::onExit(); 
}

void LevelGame05::updateGame(float dt)
{
	if(isMatch == true)
	{
		count=count - 2;
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();

		CCMenu *pmenu=(CCMenu *)getChildByTag(100);
		pmenu->removeChildByTag(90+lastItemIndex);
		pmenu->removeChildByTag(90+curItemIndex);
	}
	else
	{
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
		CCMenu *pmenu=(CCMenu *)getChildByTag(100);
		CCMenuItemImage *Item1=(CCMenuItemImage *)pmenu->getChildByTag(90+lastItemIndex);
		CCMenuItemImage *Item2=(CCMenuItemImage *)pmenu->getChildByTag(90+curItemIndex);
		Item1->setNormalSpriteFrame(cache->spriteFrameByName("poker.png"));
		Item1->setSelectedSpriteFrame(cache->spriteFrameByName("poker.png"));
		Item2->setNormalSpriteFrame(cache->spriteFrameByName("poker.png"));
		Item2->setSelectedSpriteFrame(cache->spriteFrameByName("poker.png"));
	}
	isFinish = true;
	lastItemIndex = 0;
}

void LevelGame05::ItemCallback1(CCObject *pSender)
{
	if(lastItemIndex!=1&&isFinish==true)
	{
	 
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();

		CCMenu *pmenu=(CCMenu *)getChildByTag(100);
		CCMenuItemImage *Item1=(CCMenuItemImage *)pmenu->getChildByTag(91);
		Item1->setNormalSpriteFrame(cache->spriteFrameByName("face_1.png"));
		Item1->setSelectedSpriteFrame(cache->spriteFrameByName("face_1.png"));

	if(isDouble == false)
	{
		isDouble=true;
		lastItemIndex = 1;
	}
	else
	{
		isDouble = false;
		isFinish = false;
		curItemIndex=1;
		if(lastItemIndex == 9)
		{
			isMatch = true;
		}
		else
		{
			isMatch =false;
		}
		this->scheduleOnce(schedule_selector(LevelGame05::updateGame),0.3f);
	}
	}
	
	//Item1->setNormalSpriteFrame(cache->spriteFrameByName("poker.png"));
	//Item1->setSelectedSpriteFrame(cache->spriteFrameByName("poker.png"));
}


void LevelGame05::ItemCallback2(CCObject *pSender)
{
	if(lastItemIndex!=2&&isFinish==true)
	{
		 CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();

		CCMenu *pmenu=(CCMenu *)getChildByTag(100);
		CCMenuItemImage *Item1=(CCMenuItemImage *)pmenu->getChildByTag(92);
		Item1->setNormalSpriteFrame(cache->spriteFrameByName("face_2.png"));
		Item1->setSelectedSpriteFrame(cache->spriteFrameByName("face_2.png"));

		if(isDouble == false)
		{
			isDouble=true;
			lastItemIndex = 2;
		}
		else
		{
			isDouble = false;
			isFinish = false;
			curItemIndex=2;
			if(lastItemIndex == 8)
			{
				isMatch = true;
			}
			else
			{
				isMatch =false;
			}
			this->scheduleOnce(schedule_selector(LevelGame05::updateGame),0.3f);
		}
	}
}

void LevelGame05::ItemCallback3(CCObject *pSender)
{
	if(lastItemIndex!=3&&isFinish==true)
	{
		 CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();

		CCMenu *pmenu=(CCMenu *)getChildByTag(100);
		CCMenuItemImage *Item1=(CCMenuItemImage *)pmenu->getChildByTag(93);
		Item1->setNormalSpriteFrame(cache->spriteFrameByName("face_3.png"));
		Item1->setSelectedSpriteFrame(cache->spriteFrameByName("face_3.png"));

		if(isDouble == false)
		{
			isDouble=true;
			lastItemIndex = 3;
		}
		else
		{
			isDouble = false;
			isFinish = false;
			curItemIndex=3;
			if(lastItemIndex == 7)
			{
				isMatch = true;
			}
			else
			{
				isMatch =false;
			}
			this->scheduleOnce(schedule_selector(LevelGame05::updateGame),0.3f);
		}
	}
}

void LevelGame05::ItemCallback4(CCObject *pSender)
{
	if(lastItemIndex!=4&&isFinish==true)
	{
		 CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();

		CCMenu *pmenu=(CCMenu *)getChildByTag(100);
		CCMenuItemImage *Item1=(CCMenuItemImage *)pmenu->getChildByTag(94);
		Item1->setNormalSpriteFrame(cache->spriteFrameByName("face_4.png"));
		Item1->setSelectedSpriteFrame(cache->spriteFrameByName("face_4.png"));

		if(isDouble == false)
		{
			isDouble=true;
			lastItemIndex = 4;
		}
		else
		{
			isDouble = false;
			isFinish = false;
			curItemIndex=4;
			if(lastItemIndex == 6)
			{
				isMatch = true;
			}
			else
			{
				isMatch =false;
			}
			this->scheduleOnce(schedule_selector(LevelGame05::updateGame),0.3f);
		}
	}
}

void LevelGame05::ItemCallback5(CCObject *pSender)
{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	if(count == 1)
	{
		CCMenu *pmenu=(CCMenu *)getChildByTag(100);
		CCMenuItemImage *Item=(CCMenuItemImage *)pmenu->getChildByTag(95);
		Item->setNormalSpriteFrame(cache->spriteFrameByName("face_5.png"));
		Item->setSelectedSpriteFrame(cache->spriteFrameByName("face_5.png"));
		pmenu->setEnabled(false);
		this->scheduleOnce(schedule_selector(LevelGame05::gameover),1.0f);
	}
	else{
	if(lastItemIndex!=5&&isFinish==true)
	{
		CCMenu *pmenu=(CCMenu *)getChildByTag(100);
		CCMenuItemImage *Item1=(CCMenuItemImage *)pmenu->getChildByTag(95);
		Item1->setNormalSpriteFrame(cache->spriteFrameByName("face_5.png"));
		Item1->setSelectedSpriteFrame(cache->spriteFrameByName("face_5.png"));

		if(isDouble == false)
		{
			isDouble=true;
			lastItemIndex = 5;
		}
		else
		{
			isDouble = false;
			isFinish = false;
			curItemIndex=5;
				isMatch =false;
			this->scheduleOnce(schedule_selector(LevelGame05::updateGame),0.3f);
		}
	}
	}
}

void LevelGame05::ItemCallback6(CCObject *pSender)
{
	if(lastItemIndex!=6&&isFinish==true)
	{
		 CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();

		CCMenu *pmenu=(CCMenu *)getChildByTag(100);
		CCMenuItemImage *Item1=(CCMenuItemImage *)pmenu->getChildByTag(96);
		Item1->setNormalSpriteFrame(cache->spriteFrameByName("face_4.png"));
		Item1->setSelectedSpriteFrame(cache->spriteFrameByName("face_4.png"));

		if(isDouble == false)
		{
			isDouble=true;
			lastItemIndex = 6;
		}
		else
		{
			isDouble = false;
			isFinish = false;
			curItemIndex=6;
			if(lastItemIndex == 4)
			{
				isMatch = true;
			}
			else
			{
				isMatch =false;
			}
			this->scheduleOnce(schedule_selector(LevelGame05::updateGame),0.3f);
		}
	}	
}

void LevelGame05::ItemCallback7(CCObject *pSender)
{
	if(lastItemIndex!=7&&isFinish==true)
	{
		 CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();

		CCMenu *pmenu=(CCMenu *)getChildByTag(100);
		CCMenuItemImage *Item1=(CCMenuItemImage *)pmenu->getChildByTag(97);
		Item1->setNormalSpriteFrame(cache->spriteFrameByName("face_3.png"));
		Item1->setSelectedSpriteFrame(cache->spriteFrameByName("face_3.png"));

		if(isDouble == false)
		{
			isDouble=true;
			lastItemIndex = 7;
		}
		else
		{
			isDouble = false;
			isFinish = false;
			curItemIndex=7;
			if(lastItemIndex == 3)
			{
				isMatch = true;
			}
			else
			{
				isMatch =false;
			}
			this->scheduleOnce(schedule_selector(LevelGame05::updateGame),0.3f);
		}
	}
}

void LevelGame05::ItemCallback8(CCObject *pSender)
{
	if(lastItemIndex!=8&&isFinish==true)
	{
		 CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();

		CCMenu *pmenu=(CCMenu *)getChildByTag(100);
		CCMenuItemImage *Item1=(CCMenuItemImage *)pmenu->getChildByTag(98);
		Item1->setNormalSpriteFrame(cache->spriteFrameByName("face_2.png"));
		Item1->setSelectedSpriteFrame(cache->spriteFrameByName("face_2.png"));

		if(isDouble == false)
		{
			isDouble=true;
			lastItemIndex = 8;
		}
		else
		{
			isDouble = false;
			isFinish = false;
			curItemIndex=8;
			if(lastItemIndex == 2)
			{
				isMatch = true;
			}
			else
			{
				isMatch =false;
			}
			this->scheduleOnce(schedule_selector(LevelGame05::updateGame),0.3f);
		}
	}
}

void LevelGame05::ItemCallback9(CCObject *pSender)
{
	if(lastItemIndex!=9&&isFinish==true)
	{
		 CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();

		CCMenu *pmenu=(CCMenu *)getChildByTag(100);
		CCMenuItemImage *Item1=(CCMenuItemImage *)pmenu->getChildByTag(99);
		Item1->setNormalSpriteFrame(cache->spriteFrameByName("face_1.png"));
		Item1->setSelectedSpriteFrame(cache->spriteFrameByName("face_1.png"));

		if(isDouble == false)
		{
			isDouble=true;
			lastItemIndex = 9;
		}
		else
		{
			isDouble = false;
			isFinish = false;
			curItemIndex=9;
			if(lastItemIndex == 1)
			{
				isMatch = true;
			}
			else
			{
				isMatch =false;
			}
			this->scheduleOnce(schedule_selector(LevelGame05::updateGame),0.3f);
		}
	}
}

//void LevelGame05::updateMusic(float dt)
//{
//	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
//}

void LevelGame05::gameover(float dt)
{
	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->playEffect("lose.wav");
	/*	scheduleOnce(schedule_selector(LevelGame05::updateMusic),2.0f);*/
	}
	CCMenu *pausemenu=(CCMenu *)getChildByTag(101);
	pausemenu->setEnabled(false);
	   CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height); 
	layer->setTag(70);
	CCSprite *sp =CCSprite::create("bg-5-lose.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);

	//CCSprite* lose_cry =CCSprite::createWithSpriteFrameName("lose-cry.png"); 
 //   lose_cry->setPosition(CCPoint(size.width*0.5-300,size.height*0.5)); 
 //   layer->addChild(lose_cry); 
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCMenuItemImage *Item0 = CCMenuItemImage::create();
	Item0->setNormalSpriteFrame(cache->spriteFrameByName("win-smile.png"));
	Item0->setSelectedSpriteFrame(cache->spriteFrameByName("win-smile.png"));
	Item0->initWithTarget(this,menu_selector(LevelGame05::simleCallback));
	Item0->setPosition(ccp(size.width*0.5-400, size.height*0.5));
    Item0->setTag(109); 
	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("win-lose-list-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("win-lose-list-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame05::winloseCallback));
	Item1->setPosition(ccp(size.width*0.5, size.height*0.5-50));
    Item1->setTag(110); 
	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("result-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("result-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame05::resultCallback));
	Item2->setPosition(ccp(size.width*0.5+300, size.height*0.5-50));
    Item2->setTag(111); 
	CCMenu* menu= CCMenu::create(Item0,Item1,Item2, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(112);  
    layer->addChild(menu); 

	this->addChild(layer,2);
}

void LevelGame05::pauseCallback(CCObject *pSender)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height); 
	layer->setTag(80);

	CCMenu *pmenu=(CCMenu *)getChildByTag(100);//9¸ö²Ëµ¥Ïî½ûÖ¹
	pmenu->setEnabled(false);
	CCMenu *pause=(CCMenu *)getChildByTag(101);//101ÊÇÔÝÍ£ÔÙ´Î½ûÖ¹
	pause->setEnabled(false);

	CCSprite *sp =CCSprite::createWithSpriteFrameName("bg.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  

	CCMenuItemImage *closeItem = CCMenuItemImage::create();
    closeItem->setNormalSpriteFrame(cache->spriteFrameByName("back-1.png"));
    closeItem->setSelectedSpriteFrame(cache->spriteFrameByName("back-2.png"));
    closeItem->initWithTarget(this, menu_selector(LevelGame05::menuCloseCallback));
	closeItem->setPosition(CCPoint(size.width*0.1,80));
    CCMenu *menus = CCMenu::create(closeItem, NULL);  
    menus->setPosition(CCPointZero);  
    layer->addChild(menus); 


	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("home-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("home-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame05::homeCallback));
	Item1->setPosition(ccp(size.width*0.5-300, size.height*0.5));
    Item1->setTag(125); 
	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("pause-list-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("pause-list-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame05::winloseCallback));
	Item2->setPosition(ccp(size.width*0.5, size.height*0.5));
    Item2->setTag(126); 
	CCMenuItemImage *Item3 = CCMenuItemImage::create();
	if(isMusic == true)
	{
		Item3->setNormalSpriteFrame(cache->spriteFrameByName("pause-music.png"));
	//	Item3->setSelectedSpriteFrame(cache->spriteFrameByName("close-pause-music.png"));
	}
	else
	{
		Item3->setNormalSpriteFrame(cache->spriteFrameByName("close-pause-music.png"));
		//Item3->setSelectedSpriteFrame(cache->spriteFrameByName("pause-music.png"));
	}
	Item3->initWithTarget(this,menu_selector(LevelGame05::musicCallback));
	Item3->setPosition(ccp(size.width*0.5+300, size.height*0.5));
    Item3->setTag(127); 
	CCMenu* menu= CCMenu::create(Item1,Item2,Item3, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(128);  
    layer->addChild(menu); 

	this->addChild(layer,2);
}

void LevelGame05::menuCloseCallback(CCObject* pSender)
{ 
	CCLayerColor *layer =(CCLayerColor *)getChildByTag(80);
	removeChild(layer,true);
	CCMenu *pmenu=(CCMenu *)getChildByTag(100);
	pmenu->setEnabled(true);
	CCMenu *pause=(CCMenu *)getChildByTag(101);
	pause->setEnabled(true);
}


void LevelGame05::winloseCallback(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, ScrollViewScene::create()));  
}

void LevelGame05::homeCallback(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HelloWorld::scene()));  
}

void LevelGame05::musicCallback(CCObject *pSender)
{
	CCMenu *pmenu=(CCMenu *)getChildByTag(101);
	pmenu->setEnabled(true);
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	 CCLayerColor *layer=( CCLayerColor *)getChildByTag(80);
	if(isMusic == true)
	{
		isMusic = false;
		/*CCDirector::sharedDirector()->end();*/
		CCMenu* pMenu = (CCMenu *)layer->getChildByTag(128);
		CCMenuItemImage *Item = (CCMenuItemImage *)pMenu->getChildByTag(127);
		Item->setNormalSpriteFrame(cache->spriteFrameByName("close-pause-music.png"));
		if(flagMusic == true)
			SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
	else
	{
		isMusic =true;
		CCMenu* pMenu = (CCMenu *)layer->getChildByTag(128);
		CCMenuItemImage *Item = (CCMenuItemImage *)pMenu->getChildByTag(127);
		Item->setNormalSpriteFrame(cache->spriteFrameByName("pause-music.png"));
		if(flagMusic == true)
		{
			SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		}
		else
		{
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("back2.mp3",true);
			flagMusic = true;
		}
	}
	//removeChildByTag(80);

}

void LevelGame05::resultCallback(CCObject *pSender)
{
	isNext = true;
	if(isNext == true)
	{
			CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
			cache->removeSpriteFramesFromFile("level-5.plist");  
	}
	isKillSchedule=true;
	if(isKillSchedule == true)
	{
		unschedule(schedule_selector(LevelGame05::updateGame));
	}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LevelGame05::createScene()));  
}

void LevelGame05::simleCallback(CCObject *pSender)
{
	this->scheduleOnce(schedule_selector(LevelGame05::gamewin),1.0f);
	//gamewin();
}


void LevelGame05::gamewin(float dt)
{
	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->playEffect("win.wav");
		/*scheduleOnce(schedule_selector(LevelGame05::updateMusic),2.5f);*/
	/*	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();*/
	}
	CCSprite* sprite=(CCSprite *)getChildByTag(90);
	sprite->setVisible(false);
	CCLayerColor *layerc =(CCLayerColor *)getChildByTag(80);
	removeChild(layerc,true);
	CCMenu *pmenu=(CCMenu *)getChildByTag(100);//yi_normal½ûÖ¹
	pmenu->setVisible(true);
	CCMenu *pause=(CCMenu *)getChildByTag(101);//105ÊÇÔÝÍ£ÔÙ´Î½ûÖ¹
	pause->setVisible(true);
	CCMenu *pause1=(CCMenu *)getChildByTag(101);//105ÊÇÔÝÍ£½ûÖ¹
	pause1->setEnabled(false);

	CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height); 
		
	CCSprite *sp =CCSprite::create("bg-5-win.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);

	//CCSprite* win_smile =CCSprite::createWithSpriteFrameName("win-smile.png"); 
   // win_smile->setPosition(CCPoint(size.width*0.5-300,size.height*0.5)); 
    //layer->addChild(win_smile);  


	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("win-lose-list-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("win-lose-list-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame05::winloseCallback));
	Item1->setPosition(ccp(size.width*0.5-150, size.height*0.5-50));
    Item1->setTag(120); 

	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("result-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("result-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame05::resultCallback));
	Item2->setPosition(ccp(size.width*0.5+100, size.height*0.5-50));
    Item2->setTag(121); 

	CCMenuItemImage *Item3 = CCMenuItemImage::create();
	Item3->setNormalSpriteFrame(cache->spriteFrameByName("next-1.png"));
	Item3->setSelectedSpriteFrame(cache->spriteFrameByName("next-2.png"));
	Item3->initWithTarget(this,menu_selector(LevelGame05::nextCallback));
	Item3->setPosition(ccp(size.width*0.5+350, size.height*0.5-50));
    Item3->setTag(122); 
	CCMenu* menu= CCMenu::create(Item1,Item2,Item3, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(123);  
    layer->addChild(menu); 

	this->addChild(layer,3);
}

void LevelGame05::nextCallback(CCObject *pSender)
{
	isNext = true;
	if(isNext == true)
	{
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
		cache->removeSpriteFramesFromFile("level-5.plist");  
	}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LevelGame06::createScene()));  
}