#include "LevelGame07.h"
#include "ScrollViewScene.h" 
#include "HelloWorldScene.h"
#include "LevelGame08.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;  
using namespace CocosDenshion;
extern bool isMusic;  
static bool isNext = false;
static int  shakeCnt;
static bool flagMusic = false;


CCScene* LevelGame07::createScene()  
{  
    CCScene *scene = CCScene::create();  
    CCLayer *layer = LevelGame07::create();  
    scene->addChild(layer);  
	//scene->autorelease(); 
    return scene;  
}  

void LevelGame07::onEnter()  
{
	CCLayer::onEnter();
	
}

void LevelGame07::onExit()  
{  
	if(isNext ==false)
	{
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
		cache->removeSpriteFramesFromFile("level-7.plist");  
	}
	isNext =false;
	CCLayer::onExit(); 
}

bool LevelGame07::init()  
{
	 if ( !CCLayer::init() )  
    {  
        return false;  
    }
	CCUserDefault::sharedUserDefault()->setIntegerForKey("level_7", 1);
	CCUserDefault::sharedUserDefault()->flush();  
	shakeCnt = 0; 
	setAccelerometerEnabled(true);

	flagMusic = false;

    CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
    cache->addSpriteFramesWithFile("level-7.plist");

	CCSprite* sprite =CCSprite::createWithSpriteFrameName("background-7-1.png"); 
    sprite->setPosition(CCPoint(size.width*0.5,size.height*0.5)); 
	sprite->setTag(100);
    this->addChild(sprite);

	CCSprite* sprite1 =CCSprite::createWithSpriteFrameName("background-7-2.png"); 
    sprite1->setPosition(CCPoint(size.width*0.5,size.height*0.5)); 
	sprite1->setTag(101);
	sprite1->setVisible(false);
    this->addChild(sprite1);

	//屌丝和妹纸
	CCSprite* diaosi =CCSprite::createWithSpriteFrameName("yuehui.png"); 
    diaosi->setPosition(CCPoint(size.width*0.5,size.height*0.3)); 
	diaosi->setTag(99);
	diaosi->setVisible(false);
    this->addChild(diaosi);
	//sun
	CCSprite *sun = CCSprite::createWithSpriteFrameName("sun.png");
	sun->setPosition(ccp(size.width*0.15, size.height-200));
	sun->setTag(102);
	this->addChild(sun,1);  
	//moon
	CCSprite *moon = CCSprite::createWithSpriteFrameName("moon.png");
	moon->setPosition(ccp(-size.width*0.15, size.height-200));
	moon->setTag(103);
	this->addChild(moon,1); 


	//定义sun 的Move动作 
	CCActionInterval *sunMoveTo = CCMoveTo::create(10,ccp(size.width+200,size.height -250));
	sun->runAction(sunMoveTo);
	this->scheduleOnce(schedule_selector(LevelGame07::updateGame),10.5f); 
	
	//pause按钮
	CCMenuItemImage *pauseItem = CCMenuItemImage::create();
	pauseItem->setNormalSpriteFrame(cache->spriteFrameByName("pause-1.png"));
	pauseItem->setSelectedSpriteFrame(cache->spriteFrameByName("pause-2.png"));
	pauseItem->initWithTarget(this, menu_selector(LevelGame07::pauseCallback));
	pauseItem->setPosition(CCPoint(size.width-100,size.height*0.9));
    CCMenu *pauseMenu = CCMenu::create(pauseItem, NULL);  
    pauseMenu->setPosition(CCPointZero);  
    pauseMenu->setTag(104); 
    this->addChild(pauseMenu, 1);  

	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("back2.mp3",true);
		flagMusic = true;
	}
	 
	return true;  
}

void LevelGame07::didAccelerate(CCAcceleration* pAccelerationValue)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize(); 
	CCSprite* diaosi = (CCSprite *)getChildByTag(99);
	float x = pAccelerationValue->x;
	float y = pAccelerationValue->y;
	float z = pAccelerationValue->z;
	float all = x*x + y*y + z*z;
	
	//CCPoint diaosi_position=diaosi->getPosition();

	if(all < 1.2)
 {
	if(shakeCnt>12)
	{
		//this->pauseSchedulerAndActions();
		this->unschedule(schedule_selector(LevelGame07::updateGame));
		this->unschedule(schedule_selector(LevelGame07::gameover));

		CCSprite* beijing1 = (CCSprite *)getChildByTag(100);	
		beijing1->setVisible(false);

		//sun动作暂停
		CCSprite *pSun = (CCSprite *)getChildByTag(102);
		pSun->pauseSchedulerAndActions();
		pSun->setVisible(false);
		//moon动作暂停 
		CCSprite* pMoon = (CCSprite *)getChildByTag(103);
		pMoon->pauseSchedulerAndActions();
		pMoon->setVisible(false);

		//background-7-2出场
		CCSprite* beijing2 = (CCSprite *)getChildByTag(101);
		beijing2->setVisible(true);

		//和妹纸约会去喽
		CCSprite* diaosi = (CCSprite *)getChildByTag(99);
		diaosi->setVisible(true);

		CCActionInterval *yuehuiMoveTo = CCMoveTo::create(8,ccp(size.width,size.height*0.3));
		diaosi->runAction(yuehuiMoveTo);
		this->scheduleOnce(schedule_selector(LevelGame07::gamewin),9.0f); 
		setAccelerometerEnabled(false);
		shakeCnt = 0;
	}
/*	CCPoint diaosi_position=diaosi->getPosition();
		if(diaosi_position.x == size.width){
			gamewin(1);
		}    */
		
 }
	else if(all > 3)
 {
	 shakeCnt++;
	}

}


/*void LevelGame07::winGame(float dt)
{	
	CCSize size = CCDirector::sharedDirector()->getWinSize(); 
	CCSprite* diaosi = (CCSprite *)getChildByTag(99);
	CCPoint diaosi_position=diaosi->getPosition();
	while(diaosi_position.x != size.width){
		diaosi_position=diaosi->getPosition();
	}
	gamewin(1);

}  */ 
void LevelGame07::updateGame(float dt)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();  

	CCSprite *pmoon = (CCSprite *)getChildByTag(103);
	CCActionInterval *moonMoveTo = CCMoveTo::create(10,ccp(size.width+200,size.height-250));
	pmoon->runAction(moonMoveTo);
	this->scheduleOnce(schedule_selector(LevelGame07::gameover),12.0f);
}




void LevelGame07::pauseCallback(CCObject *pSender)
{
	this->pauseSchedulerAndActions();  //暂停定时器
	CCSize size = CCDirector::sharedDirector()->getWinSize(); 
	//sun动作暂停
	CCSprite *pSun = (CCSprite *)getChildByTag(102);
	pSun->pauseSchedulerAndActions();
	//moon动作暂停 
	CCSprite* pMoon = (CCSprite *)getChildByTag(103);
	pMoon->pauseSchedulerAndActions();
	//屌丝暂停
	CCSprite* diaosi = (CCSprite *)getChildByTag(99);
	diaosi->pauseSchedulerAndActions();
	//暂停再次禁止
	CCMenu *pause = (CCMenu *)getChildByTag(104);
	pause->setEnabled(false);
	  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height); 
	layer->setTag(105);

	CCSprite *sp =CCSprite::createWithSpriteFrameName("bg.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  

	CCMenuItemImage *closeItem = CCMenuItemImage::create();
	closeItem->setNormalSpriteFrame(cache->spriteFrameByName("back-1.png"));
	closeItem->setSelectedSpriteFrame(cache->spriteFrameByName("back-2.png"));
	closeItem->initWithTarget(this, menu_selector(LevelGame07::menuCloseCallback));
	closeItem->setPosition(CCPoint(size.width*0.1,80));
	CCMenu *menus = CCMenu::create(closeItem, NULL);  
    menus->setPosition(CCPointZero);
	layer->addChild(menus); 


	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("home-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("home-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame07::homeCallback));
	Item1->setPosition(ccp(size.width*0.5-300, size.height*0.5));
    Item1->setTag(106); 
	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("pause-list-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("pause-list-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame07::winloseCallback));
	Item2->setPosition(ccp(size.width*0.5, size.height*0.5));
    Item2->setTag(107); 
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
	Item3->initWithTarget(this,menu_selector(LevelGame07::musicCallback));
	Item3->setPosition(ccp(size.width*0.5+300, size.height*0.5));
    Item3->setTag(108); 
	CCMenu* menu= CCMenu::create(Item1,Item2,Item3, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(109);  
    layer->addChild(menu); 

	this->addChild(layer,2);
}

void LevelGame07::homeCallback(CCObject *pSender)
{
	isNext = true;
	if(isNext == true)
	{
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
		cache->removeSpriteFramesFromFile("level-7.plist");  
	}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HelloWorld::scene())); 
}

void LevelGame07::winloseCallback(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, ScrollViewScene::create()));  
}

void LevelGame07::musicCallback(CCObject *pSender)
{
	CCMenu *pmenu=(CCMenu *)getChildByTag(104);
	pmenu->setEnabled(true);
	//if(isMusic == false)
	//	isMusic = true;
	//else
	//	isMusic = false;
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	 CCLayerColor *layer=( CCLayerColor *)getChildByTag(105);
	if(isMusic == true)
	{
		isMusic = false;
		/*CCDirector::sharedDirector()->end();*/
		CCMenu* pMenu = (CCMenu *)layer->getChildByTag(109);
		CCMenuItemImage *Item = (CCMenuItemImage *)pMenu->getChildByTag(108);
		Item->setNormalSpriteFrame(cache->spriteFrameByName("close-pause-music.png"));
		if(flagMusic == true)
			SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
	else
	{
		isMusic =true;
		CCMenu* pMenu = (CCMenu *)layer->getChildByTag(109);
		CCMenuItemImage *Item = (CCMenuItemImage *)pMenu->getChildByTag(108);
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
}

void LevelGame07::menuCloseCallback(CCObject* pSender)
{
	this->resumeSchedulerAndActions();
	//sun动作恢复
	CCSprite *pSun = (CCSprite *)getChildByTag(102);
	pSun->resumeSchedulerAndActions();
	//moon动作恢复 
	CCSprite* pMoon = (CCSprite *)getChildByTag(103);
	pMoon->resumeSchedulerAndActions();
	//屌丝动作恢复
	CCSprite* diaosi = (CCSprite *)getChildByTag(99);
	diaosi->resumeSchedulerAndActions();

	CCLayerColor *layer =(CCLayerColor *)getChildByTag(105);
	removeChild(layer,true);
	
	//暂停再次恢复
	CCMenu *pause = (CCMenu *)getChildByTag(104);
	pause->setEnabled(true);
}

void LevelGame07::gamewin(float dt)
{
	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->playEffect("win.wav");
		//scheduleOnce(schedule_selector(LevelGame01::updateMusic),2.5f);
	/*	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();*/
	}
	this->pauseSchedulerAndActions();//暂停定时器

	//暂停键禁止
	CCMenu* pmenu=(CCMenu *)getChildByTag(104);
	pmenu->setEnabled(false);
		
	CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height); 

	CCSprite *sp =CCSprite::create("bg-7-win.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);

	//CCSprite* win_smile =CCSprite::createWithSpriteFrameName("win-smile.png"); 
    //win_smile->setPosition(CCPoint(size.width*0.5-300,size.height*0.5)); 
   // layer->addChild(win_smile);  

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("win-lose-list-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("win-lose-list-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame07::winloseCallback));
	Item1->setPosition(ccp(size.width*0.5-150, size.height*0.5-50));
    Item1->setTag(120); 

	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("result-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("result-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame07::resultCallback));
	Item2->setPosition(ccp(size.width*0.5+100, size.height*0.5-50));
    Item2->setTag(121); 

	CCMenuItemImage *Item3 = CCMenuItemImage::create();
	Item3->setNormalSpriteFrame(cache->spriteFrameByName("next-1.png"));
	Item3->setSelectedSpriteFrame(cache->spriteFrameByName("next-2.png"));
	Item3->initWithTarget(this,menu_selector(LevelGame07::nextCallback));
	Item3->setPosition(ccp(size.width*0.5+350, size.height*0.5-50));
    Item3->setTag(122); 
	CCMenu* menu= CCMenu::create(Item1,Item2,Item3, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(123);  
    layer->addChild(menu); 

	this->addChild(layer,2);
}

void LevelGame07::gameover(float dt)
{
	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->playEffect("lose.wav");
	//	scheduleOnce(schedule_selector(LevelGame01::updateMusic),2.0f);
	}
	this->pauseSchedulerAndActions();
	CCMenu* pmenu=(CCMenu *)getChildByTag(104);
	pmenu->setEnabled(false);

	CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height); 
	CCSprite *sp =CCSprite::create("bg-7-lose.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);

	//CCSprite* lose_cry =CCSprite::createWithSpriteFrameName("lose-cry.png"); 
   // lose_cry->setPosition(CCPoint(size.width*0.5-300,size.height*0.5)); 
   // layer->addChild(lose_cry);  

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("win-lose-list-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("win-lose-list-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame07::winloseCallback));
	Item1->setPosition(ccp(size.width*0.5-100, size.height*0.5-50));
    Item1->setTag(130); 
	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("result-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("result-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame07::resultCallback));
	Item2->setPosition(ccp(size.width*0.5+300, size.height*0.5-50));
    Item2->setTag(131); 
	CCMenu* menu= CCMenu::create(Item1,Item2, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(132);  
    layer->addChild(menu); 

	this->addChild(layer,2);
}

void LevelGame07::resultCallback(CCObject *pSender)
{
	isNext = true;
	if(isNext == true)
	{
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
		cache->removeSpriteFramesFromFile("level-7.plist");  
	}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LevelGame07::createScene()));  
}

void LevelGame07::nextCallback(CCObject *pSender)
{
	isNext = true;
	if(isNext == true)
	{
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
		cache->removeSpriteFramesFromFile("level-7.plist");  
	}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LevelGame08::createScene())); 
}