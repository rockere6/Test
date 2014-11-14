#include "SWSpritePlayForTexturePacker.h"  
#include "ScrollViewScene.h"  
#include "HelloWorldScene.h"
#include "LevelGame04.h" 
#include "LevelGame05.h" 
#include "SimpleAudioEngine.h"

//#include "CCEventDispatcher.h"  
//#include "CCEventListenerTouch.h"  
  
USING_NS_CC;  
using namespace CocosDenshion;

//static bool isClickGo;  
extern bool isMusic;  
static bool isNext = false;
static bool isFailed = false;
static bool flagMusic = false;
static int isMenu=0;

CCScene* LevelGame04::createScene()  
{  
   // isClickGo = true;  
    CCScene *scene = CCScene::create();  
    CCLayer *layer = LevelGame04::create();  
    scene->addChild(layer);  
    return scene;  
}  


bool LevelGame04::init()  
{  
    if ( !CCLayer::init() )  
    {  
        return false;  
    }  
     isFailed = false; 
	 flagMusic = false;
	isMenu=0;
    //cocos2d-x3.0中的点击事件  
    //auto dispatcher = Director::getInstance()->getEventDispatcher();  
    //auto touchListener = EventListenerTouchOneByOne::create();  
    //touchListener->onTouchBegan = CC_CALLBACK_2(HistoryGame02::onTouchBegan, this);  
    //dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);  
    CCUserDefault::sharedUserDefault()->setIntegerForKey("level_4", 1);
	CCUserDefault::sharedUserDefault()->flush();  
      
    //加入背景  

    CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
    cache->addSpriteFramesWithFile("level-4.plist");
	CCSprite* sprite =CCSprite::createWithSpriteFrameName("background-4.png"); 
	CCSize sprite_size = sprite->getContentSize();
	sprite->setScaleX(size.width/sprite_size.width);
	sprite->setScaleY(size.height/sprite_size.height);
    sprite->setPosition(CCPoint(size.width*0.5,size.height*0.5)); 
	sprite->setTag(98);
    this->addChild(sprite); 
     

   //ClickME图标
    CCMenuItemImage *clickmeItem = CCMenuItemImage::create();
	clickmeItem->setNormalSpriteFrame(cache->spriteFrameByName("clickme_1.png"));
	clickmeItem->setSelectedSpriteFrame(cache->spriteFrameByName("clickme_2.png"));
	clickmeItem->initWithTarget(this,menu_selector(LevelGame04::clickmeCallback));
	clickmeItem->setPosition(ccp(size.width / 2 , size.height / 2));
	CCMenu* pmenu= CCMenu::create(clickmeItem, NULL);
    pmenu->setPosition(CCPointZero);
	pmenu->setTag(100);  
	//pmenu->setEnabled(false);
    this->addChild(pmenu); 

    //ME和NU两个图标
	CCMenuItemImage *meItem = CCMenuItemImage::create();
	meItem->setNormalSpriteFrame(cache->spriteFrameByName("ME.png"));
	meItem->setSelectedSpriteFrame(cache->spriteFrameByName("ME.png"));
	meItem->initWithTarget(this,menu_selector(LevelGame04::meCallback));
	meItem->setPosition(ccp(100, size.height*0.9));
    meItem->setTag(101); 
	CCMenu* meMenu= CCMenu::create(meItem, NULL);
    meMenu->setPosition(CCPointZero);
	meMenu->setTag(103);  
    this->addChild(meMenu,1); 
	CCMenuItemImage *nuItem = CCMenuItemImage::create();
	nuItem->setNormalSpriteFrame(cache->spriteFrameByName("NU.png"));
	nuItem->setSelectedSpriteFrame(cache->spriteFrameByName("NU.png"));
	//yiItem->initWithTarget(this,menu_selector(LevelGame01::yiCallback));
	nuItem->setPosition(ccp(184, size.height*0.9));
	CCMenu* nuMenu= CCMenu::create(nuItem, NULL);
    nuMenu->setPosition(CCPointZero);
	nuMenu->setTag(102);  
    this->addChild(nuMenu,1); 

   // cache->addSpriteFramesWithFile("UIResoure.plist");
	//batch = CCSpriteBatchNode::create("UIResoure.png");
	//this->addChild(batch);
	
	CCMenuItemImage *pauseItem = CCMenuItemImage::create();
	pauseItem->setNormalSpriteFrame(cache->spriteFrameByName("pause-1.png"));
	pauseItem->setSelectedSpriteFrame(cache->spriteFrameByName("pause-2.png"));
	pauseItem->initWithTarget(this, menu_selector(LevelGame04::pauseCallback));
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
  
  
void LevelGame04::menuCloseCallback(CCObject* pSender)
{
	//释放没有用到过的缓冲  
   // CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
  //  cache->removeSpriteFramesFromFile("level-1.plist");  
    //实现  
   // CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, ScrollViewScene::create()));  
	CCLayerColor *layer =(CCLayerColor *)getChildByTag(90);
	removeChild(layer,true);
	CCMenu *pmenu=(CCMenu *)getChildByTag(100);		//clickme重新使能
	pmenu->setEnabled(true);
	CCMenu *pmenu1=(CCMenu *)getChildByTag(104);	//104是pause重新使能
	pmenu1->setEnabled(true);
	CCMenu *pmenu2=(CCMenu *)getChildByTag(103);	//menu重新使能
	pmenu2->setEnabled(true);
}
  
void LevelGame04::clickmeCallback(CCObject* pSender)  
{  
	if(isFailed == false)
	{
    CCSize size = CCDirector::sharedDirector()->getWinSize();  
    SWSpritePlayForTexturePacker *sp_people2 = SWSpritePlayForTexturePacker::createPlay("blow_up",1, 3, 0.1f,true);  
    sp_people2->setPosition(CCPoint(size.width / 2, size.height / 2));  
    sp_people2->setTag(105);  
    addChild(sp_people2);  
	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->playEffect("boom.wav");
		//scheduleOnce(schedule_selector(LevelGame03::updateMusic),2.0f);
	}
    this->scheduleOnce(schedule_selector(LevelGame04::gameover),2.0f);  
	isFailed = true;
	}
}  
  
void LevelGame04::meCallback(CCObject* pSender)  
{  
	isMenu++;	
	if(isMenu == 3)
	{
	CCMenu *pmenu = (CCMenu *)getChildByTag(103);
	//CCFiniteTimeAction *scale = CCScaleTo::create(2.0f,2);
	CCFiniteTimeAction *blick=CCBlink::create(0.5f,10);
	//CCAction *action = CCSpawn::create(scale,blick,NULL);
	pmenu->runAction(blick);
    this->scheduleOnce(schedule_selector(LevelGame04::gamewin), 1.0f);  
	}
}  
 
void LevelGame04::onEnter()  
{  
   //CCDirector* pDirector = CCDirector::sharedDirector();
   //pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);    
   CCLayer::onEnter();
}  
  
void LevelGame04::onExit()  
{  
	//CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	if(isNext == false)
	{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	cache->removeSpriteFramesFromFile("level-4.plist");  
	}
	isNext =false;
	/*CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	cache->removeSpriteFramesFromFile("level-4.plist");  */
	CCLayer::onExit(); 
}

//void LevelGame04::updateMusic(float dt)
//{
//	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
//}
  
void LevelGame04::gameover(float dt)
{
	if(isMusic == true)
	{
		//SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->playEffect("lose.wav");
		/*scheduleOnce(schedule_selector(LevelGame04::updateMusic),2.0f);*/
	}
	  // 游戏失败  Color4B
	CCMenu *pmenu=(CCMenu *)getChildByTag(100);	//clickme禁止
	pmenu->setEnabled(false);
	CCMenu *pause=(CCMenu *)getChildByTag(104);//104是pause禁止
	pause->setEnabled(false);
	CCMenu *pmenu1=(CCMenu *)getChildByTag(103);	//menu禁止
	pmenu1->setEnabled(false);
	//屏蔽爆炸动画
	SWSpritePlayForTexturePacker *p_blowup = (SWSpritePlayForTexturePacker *)getChildByTag(105); 
	p_blowup->setVisible(false);
   
	CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height); 
	CCSprite *sp =CCSprite::create("bg-4-lose.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);

	//CCSprite* lose_cry =CCSprite::createWithSpriteFrameName("lose-cry.png"); 
   // lose_cry->setPosition(CCPoint(size.width*0.5-300,size.height*0.5)); 
   // layer->addChild(lose_cry);  

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("win-lose-list-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("win-lose-list-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame04::winloseCallback));
	Item1->setPosition(ccp(size.width*0.5-150, size.height*0.5-50));
    Item1->setTag(110); 
	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("result-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("result-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame04::resultCallback));
	Item2->setPosition(ccp(size.width*0.5+350, size.height*0.5-50));
    Item2->setTag(111); 
	CCMenu* menu= CCMenu::create(Item1,Item2, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(112);  
    layer->addChild(menu); 

	this->addChild(layer,2);
}

/*void LevelGame04::updateGame(float dt)
{
	gamewin();
}*/

void LevelGame04::gamewin(float dt)
{
	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->playEffect("win.wav");
		/*scheduleOnce(schedule_selector(LevelGame04::updateMusic),2.5f);*/
	/*	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();*/
	}
	 //
//	unschedule(schedule_selector(LevelGame04::updateGame));
	
    CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height); 

	CCMenu *pmenu=(CCMenu *)getChildByTag(100);		//clickme禁止
	pmenu->setEnabled(false);
	CCMenu *pmenu1=(CCMenu *)getChildByTag(103);	//menu禁止
	pmenu1->setEnabled(false);
	CCMenu *pause=(CCMenu *)getChildByTag(104);		//104是pause禁止
	pause->setEnabled(false);

	CCSprite *sp =CCSprite::create("bg-4-win.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);

	//CCSprite* win_smile =CCSprite::createWithSpriteFrameName("win-smile.png"); 
    //win_smile->setPosition(CCPoint(size.width*0.5-300,size.height*0.5)); 
    //layer->addChild(win_smile);  

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("win-lose-list-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("win-lose-list-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame04::winloseCallback));
	Item1->setPosition(ccp(size.width*0.5-150, size.height*0.5-50));
    Item1->setTag(120); 

	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("result-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("result-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame04::resultCallback));
	Item2->setPosition(ccp(size.width*0.5+100, size.height*0.5-50));
    Item2->setTag(121); 

	CCMenuItemImage *Item3 = CCMenuItemImage::create();
	Item3->setNormalSpriteFrame(cache->spriteFrameByName("next-1.png"));
	Item3->setSelectedSpriteFrame(cache->spriteFrameByName("next-2.png"));
	Item3->initWithTarget(this,menu_selector(LevelGame04::nextCallback));
	Item3->setPosition(ccp(size.width*0.5+350, size.height*0.5-50));
    Item3->setTag(122); 
	CCMenu* menu= CCMenu::create(Item1,Item2,Item3, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(123);  
    layer->addChild(menu); 

	this->addChild(layer,2);
}

void LevelGame04::pauseCallback(CCObject *pSender)
{
	 //
    CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height); 
	layer->setTag(90);
	CCMenu *pmenu=(CCMenu *)getChildByTag(100);//clickme禁止
	pmenu->setEnabled(false);
	CCMenu *pmenu1=(CCMenu *)getChildByTag(104);//104是暂停禁止
	pmenu1->setEnabled(false);
	CCMenu *pmenu2=(CCMenu *)getChildByTag(103);//103是menu禁止
	pmenu2->setEnabled(false);

	CCSprite *sp =CCSprite::createWithSpriteFrameName("bg.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);

	
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  

	CCMenuItemImage *closeItem = CCMenuItemImage::create();
	closeItem->setNormalSpriteFrame(cache->spriteFrameByName("back-1.png"));
	closeItem->setSelectedSpriteFrame(cache->spriteFrameByName("back-2.png"));
	closeItem->initWithTarget(this, menu_selector(LevelGame04::menuCloseCallback));
	closeItem->setPosition(CCPoint(size.width*0.1,80));
	CCMenu *menus = CCMenu::create(closeItem, NULL);  
    menus->setPosition(CCPointZero);
	layer->addChild(menus); 


	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("home-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("home-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame04::homeCallback));
	Item1->setPosition(ccp(size.width*0.5-300, size.height*0.5));
    Item1->setTag(125); 
	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("pause-list-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("pause-list-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame04::winloseCallback));
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
	Item3->initWithTarget(this,menu_selector(LevelGame04::musicCallback));
	Item3->setPosition(ccp(size.width*0.5+300, size.height*0.5));
    Item3->setTag(127); 
	CCMenu* menu= CCMenu::create(Item1,Item2,Item3, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(128);  
    layer->addChild(menu); 

	this->addChild(layer,2);
}

void LevelGame04::winloseCallback(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, ScrollViewScene::create()));  
}

void LevelGame04::resultCallback(CCObject *pSender)
{
	isNext = true;
	if(isNext == true)
	{
			CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
			cache->removeSpriteFramesFromFile("level-4.plist"); 
	}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LevelGame04::createScene()));  
}

void LevelGame04::nextCallback(CCObject *pSender)
{
	//CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache(); 
	//cache->removeSpriteFramesFromFile("level-1.plist"); 
	//LevelGame01::onExit(); 
	isNext = true;
	if(isNext == true)
	{
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
		cache->removeSpriteFramesFromFile("level-4.plist");  
	}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LevelGame05::createScene()));
}

void LevelGame04::homeCallback(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HelloWorld::scene()));  
}

void LevelGame04::musicCallback(CCObject *pSender)
{
	CCMenu *pmenu=(CCMenu *)getChildByTag(104);
	pmenu->setEnabled(true);
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
