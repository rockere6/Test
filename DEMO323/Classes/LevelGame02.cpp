#include "LevelGame03.h"
#include "LevelGame02.h"
#include "SWSpritePlayForTexturePacker.h" 
#include "ScrollViewScene.h" 
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;  
static bool isMusic=false;  
static bool isNext =false;
static bool isTouchDelete=false;

CCScene* LevelGame02::createScene()  
{  
    CCScene *scene = CCScene::create();  
    CCLayer *layer = LevelGame02::create();  
    scene->addChild(layer);  
	//scene->autorelease(); 
    return scene;  
}  

bool LevelGame02::init() 
{
	if ( !CCLayer::init() )  
    {  
        return false;  
    }
	isMusic=false;

	CCUserDefault::sharedUserDefault()->setIntegerForKey("level_2", 1);
	CCUserDefault::sharedUserDefault()->flush();

	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("beiershuang.mp3");
    //SimpleAudioEngine::sharedEngine()->preloadEffect( EFFECT_FILE );

    CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
    cache->addSpriteFramesWithFile("level-2.plist");
	//cache->addSpriteFramesWithFile("UIResource.plist");//UIResouce.plist为其他资源也需要的，不要再添加，删除的话在程序退出时

	CCSprite* sprite =CCSprite::createWithSpriteFrameName("background-2.png"); 
	CCSize sprite_size = sprite->getContentSize();
	sprite->setScaleX(size.width/sprite_size.width);
	sprite->setScaleY(size.height/sprite_size.height);
    sprite->setPosition(CCPoint(size.width*0.5,size.height*0.5)); 
	sprite->setTag(98);
    this->addChild(sprite);  

	SWSpritePlayForTexturePacker *sprite_jump = SWSpritePlayForTexturePacker::createPlay("jump",1, 7, 0.1f,true);  
	sprite_jump->setPosition(CCPoint(size.width*0.5, 270));  
    sprite_jump->setTag(99);  
    addChild(sprite_jump);  
	CCSprite *sjump = CCSprite::createWithSpriteFrameName("jump_02.png");
	sjump->setTag(95);
	sjump->setPosition(CCPoint(size.width*0.5, 270));
	sjump->setVisible(false);
	addChild(sjump);

	SWSpritePlayForTexturePacker *sprite_yin = SWSpritePlayForTexturePacker::createPlay("yin",1, 2, 0.1f,true);  
	sprite_yin->setPosition(CCPoint(165, 178));  
    sprite_yin->setTag(100);  
    addChild(sprite_yin); 
	CCSprite *syin = CCSprite::createWithSpriteFrameName("yin_01.png");
	syin->setTag(96);
	syin->setPosition(CCPoint(165, 178));
	syin->setVisible(false);
	addChild(syin);

	SWSpritePlayForTexturePacker *sprite_xiang = SWSpritePlayForTexturePacker::createPlay("xiang",1, 2, 0.1f,true);  
	sprite_xiang->setPosition(CCPoint(size.width-190, 178));  
    sprite_xiang->setTag(101);  
    addChild(sprite_xiang); 
	CCSprite *sxiang = CCSprite::createWithSpriteFrameName("xiang_01.png");
	sxiang->setTag(97);
	sxiang->setPosition(CCPoint(size.width-190, 178));
	sxiang->setVisible(false);
	addChild(sxiang);

		CCMenuItemImage *pauseItem = CCMenuItemImage::create();
		pauseItem->setNormalSpriteFrame(cache->spriteFrameByName("pause-1.png"));
		pauseItem->setSelectedSpriteFrame(cache->spriteFrameByName("pause-2.png"));
		pauseItem->initWithTarget(this, menu_selector(LevelGame02::pauseCallback));
		pauseItem->setPosition(CCPoint(size.width-100,size.height*0.9));
    CCMenu *pauseMenu = CCMenu::create(pauseItem, NULL);  
    pauseMenu->setPosition(CCPointZero);  
    pauseMenu->setTag(105); 
    this->addChild(pauseMenu);  

	//SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("beiershuang.mp3", false);
	/*SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();*/
	this->scheduleOnce(schedule_selector(LevelGame02::updateGame),30.0f);
	return true;  
}

void LevelGame02::onEnter()  
{
	CCLayer::onEnter();
	//SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("beiershuang.mp3");
	
}

void LevelGame02::onExit()  
{  
	if(isNext ==false)
	{
	 
    SimpleAudioEngine::sharedEngine()->end();

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
    cache->removeSpriteFramesFromFile("level-2.plist");  
	}
	isNext =false;
	CCLayer::onExit(); 
}

void LevelGame02::updateGame(float dt)
{
	gameover();
}

void LevelGame02::pauseCallback(CCObject *pSender)
{
	 // 游戏失败  Color4B
	CCMenu *pmenu1=(CCMenu *)getChildByTag(105);//105是暂停再次禁止
	pmenu1->setEnabled(false);
	SWSpritePlayForTexturePacker *sprite_yin=(SWSpritePlayForTexturePacker *)getChildByTag(100);
	sprite_yin->setVisible(false);
	SWSpritePlayForTexturePacker *sprite_xiang=(SWSpritePlayForTexturePacker *)getChildByTag(101);
	sprite_xiang->setVisible(false);
	SWSpritePlayForTexturePacker *sprite_jump=(SWSpritePlayForTexturePacker *)getChildByTag(99);
	sprite_jump->setVisible(false);
	CCSprite *sjump=(CCSprite *)getChildByTag(95);
	sjump->setVisible(true);
	CCSprite *syin=(CCSprite *)getChildByTag(96);
	syin->setVisible(true);
	CCSprite *sxiang=(CCSprite *)getChildByTag(97);
	sxiang->setVisible(true);

	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	//暂停所有的定时器及动作 *****************************
	this->pauseSchedulerAndActions();

    CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height); 
	layer->setTag(90);

	CCSprite *sp =CCSprite::createWithSpriteFrameName("bg.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
	sp->setTag(94);
    layer->addChild(sp);

	
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  

	CCMenuItemImage *closeItem = CCMenuItemImage::create();
    closeItem->setNormalSpriteFrame(cache->spriteFrameByName("back-1.png"));
    closeItem->setSelectedSpriteFrame(cache->spriteFrameByName("back-2.png"));
    closeItem->initWithTarget(this, menu_selector(LevelGame02::menuCloseCallback));
	closeItem->setPosition(CCPoint(size.width*0.1,80));
    CCMenu *menus = CCMenu::create(closeItem, NULL);  
    menus->setPosition(CCPointZero);  
    layer->addChild(menus); 


	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("home-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("home-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame02::homeCallback));
	Item1->setPosition(ccp(size.width*0.5-300, size.height*0.5));
    Item1->setTag(125); 
	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("pause-list-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("pause-list-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame02::winloseCallback));
	Item2->setPosition(ccp(size.width*0.5, size.height*0.5));
    Item2->setTag(126); 
	CCMenuItemImage *Item3 = CCMenuItemImage::create();
	if(isMusic == false)
	{
		Item3->setNormalSpriteFrame(cache->spriteFrameByName("pause-music.png"));
		Item3->setSelectedSpriteFrame(cache->spriteFrameByName("close-pause-music.png"));
	}
	else
	{
		Item3->setNormalSpriteFrame(cache->spriteFrameByName("close-pause-music.png"));
		Item3->setSelectedSpriteFrame(cache->spriteFrameByName("pause-music.png"));
	}
	Item3->initWithTarget(this,menu_selector(LevelGame02::musicCallback));
	Item3->setPosition(ccp(size.width*0.5+300, size.height*0.5));
    Item3->setTag(127); 
	CCMenu* menu= CCMenu::create(Item1,Item2,Item3, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(128);  
    layer->addChild(menu); 

	this->addChild(layer,1);
}

void LevelGame02::menuCloseCallback(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	//恢复所有的定时器及动作
	this->resumeSchedulerAndActions();

	CCLayerColor *layer =(CCLayerColor *)getChildByTag(90);
	removeChild(layer,true);
	CCMenu *pmenu=(CCMenu *)getChildByTag(105);
	pmenu->setEnabled(true);	
	
	CCSprite *sjump=(CCSprite *)getChildByTag(95);
	sjump->setVisible(false);
	CCSprite *syin=(CCSprite *)getChildByTag(96);
	syin->setVisible(false);
	CCSprite *sxiang=(CCSprite *)getChildByTag(97);
	sxiang->setVisible(false);
	SWSpritePlayForTexturePacker *sprite_yin=(SWSpritePlayForTexturePacker *)getChildByTag(100);
	sprite_yin->setVisible(true);
	SWSpritePlayForTexturePacker *sprite_xiang=(SWSpritePlayForTexturePacker *)getChildByTag(101);
	sprite_xiang->setVisible(true);
	SWSpritePlayForTexturePacker *sprite_jump=(SWSpritePlayForTexturePacker *)getChildByTag(99);
	sprite_jump->setVisible(true);

}

void LevelGame02::homeCallback(CCObject *pSender)
{
	isNext = true;
	if(isNext == true)
	{
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
		cache->removeSpriteFramesFromFile("level-2.plist");  
	}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HelloWorld::scene())); 
}

void LevelGame02::winloseCallback(CCObject *pSender)
{
	isNext = true;
	if(isNext == true)
	{
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
		cache->removeSpriteFramesFromFile("level-2.plist");  
	}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, ScrollViewScene::create()));  
}
void LevelGame02::musicCallback(CCObject *pSender)
{
	//CCLayerColor *layer =(CCLayerColor *)getChildByTag(90);
	//removeChild(layer,true);
	removeChildByTag(90);
	if(isMusic == false)
	{
		gamewin();
	}
	
}

void LevelGame02::resultCallback(CCObject *pSender)
{
	isNext =true;
	if(isNext ==true)
	{
		//SimpleAudioEngine::sharedEngine()->end();

		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
		cache->removeSpriteFramesFromFile("level-2.plist");  
	}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LevelGame02::createScene()));  
}

void LevelGame02::nextCallback(CCObject *pSender)
{
	isNext = true;
	if(isNext == true)
	{
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
		cache->removeSpriteFramesFromFile("level-2.plist");  
	}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LevelGame03::createScene()));  
}

void LevelGame02::gamewin()
{
	SimpleAudioEngine::sharedEngine()->playEffect("win.wav");
	CCSprite *sjump=(CCSprite *)getChildByTag(95);
	sjump->setVisible(false);
	CCSprite *syin=(CCSprite *)getChildByTag(96);
	syin->setVisible(false);
	CCSprite *sxiang=(CCSprite *)getChildByTag(97);
	sxiang->setVisible(false);
	CCSprite *spause=(CCSprite *)getChildByTag(105);
	spause->setVisible(false);
	SWSpritePlayForTexturePacker *sprite_yin=(SWSpritePlayForTexturePacker *)getChildByTag(100);
	sprite_yin->setVisible(false);
	SWSpritePlayForTexturePacker *sprite_xiang=(SWSpritePlayForTexturePacker *)getChildByTag(101);
	sprite_xiang->setVisible(false);
	SWSpritePlayForTexturePacker *sprite_jump=(SWSpritePlayForTexturePacker *)getChildByTag(99);
	sprite_jump->setVisible(false);
	CCSprite *sp=(CCSprite *)getChildByTag(98);
	sp->setVisible(false);

	CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height); 

	CCSprite *bg =CCSprite::create("bg-2-win.png");  
    bg->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(bg);

	//CCSprite* win_smile =CCSprite::createWithSpriteFrameName("win-smile.png"); 
    //win_smile->setPosition(CCPoint(size.width*0.5-300,size.height*0.5)); 
    //layer->addChild(win_smile);  

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("win-lose-list-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("win-lose-list-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame02::winloseCallback));
	Item1->setPosition(ccp(size.width*0.5-150, size.height*0.5-50));
    Item1->setTag(120); 

	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("result-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("result-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame02::resultCallback));
	Item2->setPosition(ccp(size.width*0.5+100, size.height*0.5-50));
    Item2->setTag(121); 

	CCMenuItemImage *Item3 = CCMenuItemImage::create();
	Item3->setNormalSpriteFrame(cache->spriteFrameByName("next-1.png"));
	Item3->setSelectedSpriteFrame(cache->spriteFrameByName("next-2.png"));
	Item3->initWithTarget(this,menu_selector(LevelGame02::nextCallback));
	Item3->setPosition(ccp(size.width*0.5+350, size.height*0.5-50));
    Item3->setTag(122); 
	CCMenu* menu= CCMenu::create(Item1,Item2,Item3, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(123);  
    layer->addChild(menu); 

	this->addChild(layer,2);
}

void LevelGame02::gameover()
{
	SimpleAudioEngine::sharedEngine()->playEffect("lose.wav");
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCSprite *spause=(CCSprite *)getChildByTag(105);
	spause->setVisible(false);
	SWSpritePlayForTexturePacker *sprite_yin=(SWSpritePlayForTexturePacker *)getChildByTag(100);
	sprite_yin->setVisible(false);
	SWSpritePlayForTexturePacker *sprite_xiang=(SWSpritePlayForTexturePacker *)getChildByTag(101);
	sprite_xiang->setVisible(false);
	SWSpritePlayForTexturePacker *sprite_jump=(SWSpritePlayForTexturePacker *)getChildByTag(99);
	sprite_jump->setVisible(false);
	CCSprite *sp=(CCSprite *)getChildByTag(98);
	sp->setVisible(false);

	CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height); 

	CCSprite *bg =CCSprite::create("bg-2-lose.png");  
    bg->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(bg);

	//CCSprite* lose_cry =CCSprite::createWithSpriteFrameName("lose-cry.png"); 
    //lose_cry->setPosition(CCPoint(size.width*0.5-300,size.height*0.5)); 
    //layer->addChild(lose_cry);  

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("win-lose-list-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("win-lose-list-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame02::winloseCallback));
	Item1->setPosition(ccp(size.width*0.5-100, size.height*0.5-50));
    Item1->setTag(110); 
	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("result-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("result-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame02::resultCallback));
	Item2->setPosition(ccp(size.width*0.5+250, size.height*0.5-50));
    Item2->setTag(111); 
	CCMenu* menu= CCMenu::create(Item1,Item2, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(112);  
    layer->addChild(menu); 

	this->addChild(layer,2);
}
