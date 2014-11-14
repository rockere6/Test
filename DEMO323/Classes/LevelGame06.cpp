#include "LevelGame06.h"
#include "LevelGame07.h"
#include "ScrollViewScene.h" 
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;  
using namespace CocosDenshion;
extern bool isMusic;    
static bool isNext = false;
static char count = 1;
static bool flagMusic = false;

CCScene* LevelGame06::createScene()  
{  
    CCScene *scene = CCScene::create();  
    CCLayer *layer = LevelGame06::create();  
    scene->addChild(layer);  
	//scene->autorelease(); 
    return scene;  
}  

void LevelGame06::onEnter()  
{
	CCLayer::onEnter();
	
}

void LevelGame06::onExit()  
{  
	if(isNext ==false)
	{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
    cache->removeSpriteFramesFromFile("level-6.plist");  
	}
	isNext =false;
	CCLayer::onExit(); 
}

bool LevelGame06::init()  
{
	 if ( !CCLayer::init() )  
    {  
        return false;  
    }

	flagMusic = false;

	CCUserDefault::sharedUserDefault()->setIntegerForKey("level_6", 1);
	CCUserDefault::sharedUserDefault()->flush();  
	count = 1;

	CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
    cache->addSpriteFramesWithFile("level-6.plist");
	//cache->addSpriteFramesWithFile("UIResource.plist");		//UIResouce.plist为其他资源也需要的，不要再添加，删除的话在程序退出时

	CCSprite* sprite =CCSprite::createWithSpriteFrameName("background-6.png"); 
	CCSize sprite_size = sprite->getContentSize();
	sprite->setScaleX(size.width/sprite_size.width);
	sprite->setScaleY(size.height/sprite_size.height);
    sprite->setPosition(CCPoint(size.width*0.5,size.height*0.5)); 
	sprite->setTag(98);
    this->addChild(sprite);  
	//天空飘来五个字为line_1
	CCSprite *line1 = CCSprite::createWithSpriteFrameName("line_1.png");
	line1->setPosition(ccp(size.width + 500, size.height -150));
	line1->setTag(99);
	this->addChild(line1, 1);  


//那都不是事为line_2
//！！！！！！！！此处有从左向右漂浮动作，暂时未加
	CCMenuItemImage *pline2 = CCMenuItemImage::create();
	pline2->setNormalSpriteFrame(cache->spriteFrameByName("line_2.png"));
	pline2->setSelectedSpriteFrame(cache->spriteFrameByName("line_2.png"));
	//pline2->initWithTarget(this,menu_selector(LevelGame06::erCallback));
	pline2->setPosition(ccp(size.width +500, size.height - 400));
	pline2->setTag(100);
//儿精灵
//！！！！！！！！！！！！！和line_2一样从左向右动作
//！！！！！！！！！！！！！且可以被点击，点击一定次数消失
	CCMenuItemImage *pItem = CCMenuItemImage::create();
	pItem->setNormalSpriteFrame(cache->spriteFrameByName("er.png"));
	pItem->setSelectedSpriteFrame(cache->spriteFrameByName("er.png"));
	pItem->initWithTarget(this,menu_selector(LevelGame06::erCallback));
	pItem->setPosition(ccp(size.width +1080, size.height - 400));
	CCMenu* pmenu= CCMenu::create(pline2,pItem, NULL);
    pmenu->setPosition(CCPointZero);
	pmenu->setTag(101);  
    this->addChild(pmenu); 


	//定义Move动作  size.height - 150
	CCActionInterval *line1MoveTo = CCMoveTo::create(12,ccp(-600,size.height -150));
	line1->runAction(line1MoveTo);
	

	//姚明图像精灵，用于定时时间到时出现，开始时隐藏
	CCSprite *yaoSprite = CCSprite::createWithSpriteFrameName("yaoming.png");
	yaoSprite->setPosition(ccp(size.width - 160 ,160));
	yaoSprite->setTag(102);
	yaoSprite->setVisible(false);
	this->addChild(yaoSprite,1);
	
 
	CCMenuItemImage *pauseItem = CCMenuItemImage::create();
	pauseItem->setNormalSpriteFrame(cache->spriteFrameByName("pause-1.png"));
	pauseItem->setSelectedSpriteFrame(cache->spriteFrameByName("pause-2.png"));
	pauseItem->initWithTarget(this, menu_selector(LevelGame06::pauseCallback));
	pauseItem->setPosition(CCPoint(size.width-100,size.height*0.9));
    CCMenu *pauseMenu = CCMenu::create(pauseItem, NULL);  
    pauseMenu->setPosition(CCPointZero);  
    pauseMenu->setTag(103); 
    this->addChild(pauseMenu, 1);  


	this->scheduleOnce(schedule_selector(LevelGame06::updateGame),1.5f);
	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("back2.mp3",true);
		flagMusic = true;
	}
	return true;  
}

void LevelGame06::updateGame(float dt)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();  

	CCMenu *pmenu = (CCMenu *)getChildByTag(101);
	CCActionInterval *menuMoveTo1 = CCMoveTo::create(10,ccp(-size.width-1200,0));//-size.width-1200
	pmenu->runAction(menuMoveTo1);
	this->scheduleOnce(schedule_selector(LevelGame06::yaoCallback),12.0f);
}

void LevelGame06::yaoCallback(float dt)
{
	CCSprite *sprite=(CCSprite *)getChildByTag(102);
	sprite->setVisible(true);
	this->scheduleOnce(schedule_selector(LevelGame06::gameover),3.0f);
}

void LevelGame06::erCallback(CCObject* pSender)
{
	count++;
	CCSize size = CCDirector::sharedDirector()->getWinSize();  

	CCMenu *pmenu=(CCMenu *)getChildByTag(101);
	CCPoint menu_size=pmenu->getPosition();
	//pmenu->stopAllActions();
	//if(count<4)
	//{
	//	CCActionInterval *menuMoveTo1= CCMoveTo::create(25*(size.width+1100+menu_size.x)/(size.width+1100),ccp(-size.width-1100,0));
	//	pmenu->runAction(menuMoveTo1);
	//}
	if(count==4)
	{
		pmenu->stopAllActions();
	}
	if(count==5)
	{
		pmenu->setEnabled(false);
		pmenu->setVisible(false);

		CCSprite *line2 = CCSprite::createWithSpriteFrameName("line_2.png");
		line2->setPosition(CCPoint(size.width+500+menu_size.x,size.height - 400));
		line2->setTag(112);

		addChild(line2);
		this->scheduleOnce(schedule_selector(LevelGame06::gamewin),1.0f);
	}
}


void LevelGame06::pauseCallback(CCObject *pSender)
{
	this->pauseSchedulerAndActions();  //暂停yaoming的定时器
	CCSize size = CCDirector::sharedDirector()->getWinSize(); 

	CCSprite *line1 = (CCSprite *)getChildByTag(99);
	line1->pauseSchedulerAndActions();
	CCMenu *pause = (CCMenu *)getChildByTag(103);//暂停再次禁止
	pause->setEnabled(false);
	CCMenu* pmenu = (CCMenu *)getChildByTag(101);//er再次禁止
	pmenu->setEnabled(false);
	pmenu->pauseSchedulerAndActions();


	  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height); 
	layer->setTag(90);

	CCSprite *sp =CCSprite::createWithSpriteFrameName("bg.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  

	CCMenuItemImage *closeItem = CCMenuItemImage::create();
	closeItem->setNormalSpriteFrame(cache->spriteFrameByName("back-1.png"));
	closeItem->setSelectedSpriteFrame(cache->spriteFrameByName("back-2.png"));
	closeItem->initWithTarget(this, menu_selector(LevelGame06::menuCloseCallback));
	closeItem->setPosition(CCPoint(size.width*0.1,80));
	CCMenu *menus = CCMenu::create(closeItem, NULL);  
    menus->setPosition(CCPointZero);
	layer->addChild(menus); 


	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("home-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("home-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame06::homeCallback));
	Item1->setPosition(ccp(size.width*0.5-300, size.height*0.5));
    Item1->setTag(125); 
	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("pause-list-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("pause-list-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame06::winloseCallback));
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
	Item3->initWithTarget(this,menu_selector(LevelGame06::musicCallback));
	Item3->setPosition(ccp(size.width*0.5+300, size.height*0.5));
    Item3->setTag(127); 
	CCMenu* menu= CCMenu::create(Item1,Item2,Item3, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(128);  
    layer->addChild(menu); 

	this->addChild(layer,2);
}

void LevelGame06::homeCallback(CCObject *pSender)
{
	isNext = true;
	if(isNext == true)
	{
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
		cache->removeSpriteFramesFromFile("level-6.plist");  
	}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HelloWorld::scene())); 
}

void LevelGame06::winloseCallback(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, ScrollViewScene::create()));  
}

void LevelGame06::musicCallback(CCObject *pSender)
{
	CCMenu *pmenu=(CCMenu *)getChildByTag(103);
	pmenu->setEnabled(true);
	//if(isMusic == false)
	//	isMusic = true;
	//else
	//	isMusic = false;
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	 CCLayerColor *layer=( CCLayerColor *)getChildByTag(90);
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
}

void LevelGame06::menuCloseCallback(CCObject* pSender)
{
	this->resumeSchedulerAndActions();
	CCSize size = CCDirector::sharedDirector()->getWinSize(); 

	CCLayerColor *layer =(CCLayerColor *)getChildByTag(90);
	removeChild(layer,true);

	CCMenu *pause = (CCMenu *)getChildByTag(103);//暂停再次恢复
	pause->setEnabled(true);

	CCSprite *line1 = (CCSprite *)getChildByTag(99);
	line1->resumeSchedulerAndActions();

	CCMenu* pmenu = (CCMenu *)getChildByTag(101);//er开启
	pmenu->setEnabled(true);
	pmenu->resumeSchedulerAndActions();
}


//void LevelGame06::updateMusic(float dt)
//{
//	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
//}

void LevelGame06::gamewin(float dt)
{
	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->playEffect("win.wav");
		/*scheduleOnce(schedule_selector(LevelGame06::updateMusic),2.5f);*/
	/*	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();*/
	}
	this->pauseSchedulerAndActions();//暂停yaoming定时器
	CCMenu* pmenu=(CCMenu *)getChildByTag(103);
	pmenu->setEnabled(false);

	CCSprite* pline1 = (CCSprite *)getChildByTag(99);//line1消失
	pline1->setVisible(false);



	CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height); 

	CCSprite *sp =CCSprite::create("bg-6-win.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);

	//CCSprite* win_smile =CCSprite::createWithSpriteFrameName("win-smile.png"); 
   // win_smile->setPosition(CCPoint(size.width*0.5-300,size.height*0.5)); 
   // layer->addChild(win_smile);  

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("win-lose-list-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("win-lose-list-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame06::winloseCallback));
	Item1->setPosition(ccp(size.width*0.5-150, size.height*0.5-50));
    Item1->setTag(120); 

	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("result-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("result-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame06::resultCallback));
	Item2->setPosition(ccp(size.width*0.5+100, size.height*0.5-50));
    Item2->setTag(121); 

	CCMenuItemImage *Item3 = CCMenuItemImage::create();
	Item3->setNormalSpriteFrame(cache->spriteFrameByName("next-1.png"));
	Item3->setSelectedSpriteFrame(cache->spriteFrameByName("next-2.png"));
	Item3->initWithTarget(this,menu_selector(LevelGame06::nextCallback));
	Item3->setPosition(ccp(size.width*0.5+350, size.height*0.5-50));
    Item3->setTag(122); 
	CCMenu* menu= CCMenu::create(Item1,Item2,Item3, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(123);  
    layer->addChild(menu); 

	this->addChild(layer,2);
}

void LevelGame06::gameover(float dt)
{
	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->playEffect("lose.wav");
		/*scheduleOnce(schedule_selector(LevelGame06::updateMusic),2.0f);*/
	}
	this->pauseSchedulerAndActions();
	CCMenu* pmenu=(CCMenu *)getChildByTag(103);
	pmenu->setEnabled(false);

	CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height); 
	CCSprite *sp =CCSprite::create("bg-6-lose.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);

	//CCSprite* lose_cry =CCSprite::createWithSpriteFrameName("lose-cry.png"); 
    //lose_cry->setPosition(CCPoint(size.width*0.5-300,size.height*0.5)); 
    //layer->addChild(lose_cry);  

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("win-lose-list-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("win-lose-list-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame06::winloseCallback));
	Item1->setPosition(ccp(size.width*0.5-100, size.height*0.5-50));
    Item1->setTag(130); 
	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("result-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("result-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame06::resultCallback));
	Item2->setPosition(ccp(size.width*0.5+300, size.height*0.5-50));
    Item2->setTag(131); 
	CCMenu* menu= CCMenu::create(Item1,Item2, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(132);  
    layer->addChild(menu); 

	this->addChild(layer,2);
}

void LevelGame06::resultCallback(CCObject *pSender)
{
		isNext = true;
	if(isNext == true)
	{
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
		cache->removeSpriteFramesFromFile("level-6.plist");  
	}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LevelGame06::createScene()));  
}

void LevelGame06::nextCallback(CCObject *pSender)
{
	isNext = true;
	if(isNext == true)
	{
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
		cache->removeSpriteFramesFromFile("level-6.plist");  
	}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LevelGame07::createScene()));  
}