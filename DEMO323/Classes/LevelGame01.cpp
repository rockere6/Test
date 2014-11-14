#include "LevelGame01.h"
#include "LevelGame02.h"
#include "ScrollViewScene.h" 
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;  
using namespace CocosDenshion;
extern bool isMusic;  
static bool isTouchDelete=false;
static bool isNext = false;
static bool flagMusic = false;


CCScene* LevelGame01::createScene()  
{  
    CCScene *scene = CCScene::create();  
    CCLayer *layer = LevelGame01::create();  
    scene->addChild(layer);  
	//scene->autorelease(); 
    return scene;  
}  


bool LevelGame01::init()  
{
	 if ( !CCLayer::init() )  
    {  
        return false;  
    }
	flagMusic = false;


    CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
    cache->addSpriteFramesWithFile("level-1.plist");
	//cache->addSpriteFramesWithFile("UIResource.plist");//UIResouce.plist为其他资源也需要的，不要再添加，删除的话在程序退出时

	CCSprite* sprite =CCSprite::createWithSpriteFrameName("background-1.png"); 
	CCSize sprite_size = sprite->getContentSize();
	sprite->setScaleX(size.width/sprite_size.width);
	sprite->setScaleY(size.height/sprite_size.height);
    sprite->setPosition(CCPoint(size.width*0.5,size.height*0.5)); 
	sprite->setTag(98);
    this->addChild(sprite);  

	CCSprite *du_yi = CCSprite::createWithSpriteFrameName("du_yi.png");
	du_yi->setPosition(ccp(size.width/2, size.height/2));
	du_yi->setTag(99);
	this->addChild(du_yi, 1); 

	CCMenuItemImage *pItem = CCMenuItemImage::create();
	pItem->setNormalSpriteFrame(cache->spriteFrameByName("wangnima.png"));
	pItem->setSelectedSpriteFrame(cache->spriteFrameByName("wangnima.png"));
	pItem->initWithTarget(this,menu_selector(LevelGame01::wangnimaCallback));
	pItem->setPosition(ccp(size.width*0.5, size.height*0.5));
    pItem->setTag(100); 
	CCMenu* pmenu= CCMenu::create(pItem, NULL);
    pmenu->setPosition(CCPointZero);
	pmenu->setTag(101);  
	pmenu->setEnabled(false);
    this->addChild(pmenu); 
	



	CCMenuItemImage *duItem = CCMenuItemImage::create();
	duItem->setNormalSpriteFrame(cache->spriteFrameByName("du_normal.png"));
	duItem->setSelectedSpriteFrame(cache->spriteFrameByName("du_down.png"));
	duItem->initWithTarget(this,menu_selector(LevelGame01::duCallback));
	duItem->setPosition(ccp(size.width*0.5-200, 100));
    duItem->setTag(102); 
	CCMenuItemImage *yiItem = CCMenuItemImage::create();
	yiItem->setNormalSpriteFrame(cache->spriteFrameByName("yi_normal.png"));
	yiItem->setSelectedSpriteFrame(cache->spriteFrameByName("yi_down.png"));
	yiItem->initWithTarget(this,menu_selector(LevelGame01::yiCallback));
	yiItem->setPosition(ccp(size.width*0.5+200, 100));
    yiItem->setTag(103); 
	CCMenu* du_yimenu= CCMenu::create(duItem,yiItem, NULL);
    du_yimenu->setPosition(CCPointZero);
	du_yimenu->setTag(104);  
    this->addChild(du_yimenu,1); 
 
		CCMenuItemImage *pauseItem = CCMenuItemImage::create();
		pauseItem->setNormalSpriteFrame(cache->spriteFrameByName("pause-1.png"));
		pauseItem->setSelectedSpriteFrame(cache->spriteFrameByName("pause-2.png"));
		pauseItem->initWithTarget(this, menu_selector(LevelGame01::pauseCallback));
		pauseItem->setPosition(CCPoint(size.width-100,size.height*0.9));
    CCMenu *pauseMenu = CCMenu::create(pauseItem, NULL);  
    pauseMenu->setPosition(CCPointZero);  
    pauseMenu->setTag(105); 
    this->addChild(pauseMenu, 1);  

	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("back2.mp3",true);
		flagMusic = true;
	}
	return true;  
}

void LevelGame01::menuCloseCallback(CCObject* pSender)
{
	//释放没有用到过的缓冲  
   // CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
  //  cache->removeSpriteFramesFromFile("level-1.plist");  
    //实现  
   // CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, ScrollViewScene::create()));  
	CCLayerColor *layer =(CCLayerColor *)getChildByTag(90);
	removeChild(layer,true);
	CCMenu *pmenu=(CCMenu *)getChildByTag(104);//yi_normal禁止
	pmenu->setEnabled(true);
	CCMenu *pmenu1=(CCMenu *)getChildByTag(105);//105是暂停再次禁止
	pmenu1->setEnabled(true);
}

void LevelGame01::wangnimaCallback(CCObject* pSender)
{
	CCMenu *pmenu = (CCMenu *)getChildByTag(101);
	CCFiniteTimeAction *scale = CCScaleTo::create(2.0f,2);
	//CCFiniteTimeAction *delay =CCDelayTime::create(3.0f);
	CCFiniteTimeAction *blick=CCBlink::create(2.0f,30);
	CCAction *action = CCSpawn::create(scale,blick,NULL);
	pmenu->runAction(action);
	this->scheduleOnce(schedule_selector(LevelGame01::updateGame),3.0f);
}

void LevelGame01::updateGame(float dt)
{
	gamewin();
}

void LevelGame01::duCallback(CCObject *pSender)
{
	if(isTouchDelete==false)
	{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this); 
	isTouchDelete=true;
	}
	CCMenu *pmenu=(CCMenu *)getChildByTag(101);  
	pmenu->setEnabled(false);
	gameover();
}

void LevelGame01::yiCallback(CCObject *pSender)
{
	if(isTouchDelete==false)
	{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);  
	isTouchDelete=true;
	}
	CCMenu *pmenu=(CCMenu *)getChildByTag(101);  
	pmenu->setEnabled(false);
	gameover();
}

void LevelGame01::onEnter()  
{  
   CCDirector* pDirector = CCDirector::sharedDirector();
   pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);    
   CCLayer::onEnter();
}  
  
void LevelGame01::onExit()  
{  
	
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	if(isNext =false)
	{
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
		cache->removeSpriteFramesFromFile("level-1.plist");  
	}
	isNext = false;
	CCLayer::onExit();  
}

bool LevelGame01::isInSprite(CCTouch *theTouch,CCSprite *sp){  
    //返回当前触摸位置得OpenGL坐标  
    CCPoint touchPoint = theTouch->getLocation();  
    //将世界坐标转换为当前得父View的本地坐标  
    CCPoint reallyPoint = this->getParent()->convertToNodeSpace(touchPoint);  
    //获取当前基于父View的坐标系  
    CCRect rect = sp->boundingBox();  
    if (rect.containsPoint(reallyPoint)) {  
        //判断是否让用户再点击  
 
            return true;  
    
    }  
    return false;  
}  

bool LevelGame01::ccTouchBegan(CCTouch *pTouch, CCEvent  *pEvent)
{
	m_TouchDownPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());  
    m_TouchCurPoint = m_TouchDownPoint;  
	if(isInSprite(pTouch, (CCSprite *)this->getChildByTag(99)))
		return true; 
	else
		return false;
}


void LevelGame01::ccTouchMoved(CCTouch *pTouch, CCEvent  *pEvent)
{
	CCSprite *sprite =(CCSprite *)getChildByTag(99);
	CCPoint point= sprite->getPosition();
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());  
    CCPoint posPoint = CCPoint(point.x+ touchPoint.x - m_TouchCurPoint.x, point.y);  
    sprite->setPosition(posPoint);  
    m_TouchCurPoint = touchPoint;
}

void LevelGame01::ccTouchEnded(CCTouch *pTouch, CCEvent  *pEvent)
{
	m_TouchUpPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView()); 
	float offset = (m_TouchUpPoint.x - m_TouchDownPoint.x) * (m_TouchUpPoint.x - m_TouchDownPoint.x) + (m_TouchUpPoint.y - m_TouchDownPoint.y) * (m_TouchUpPoint.y - m_TouchDownPoint.y);  
	if(offset>400)
	{
	 
	 CCSprite *sprite = (CCSprite *)getChildByTag(99);
	// CCMenuItemImage *pItem=(CCMenuItemImage *)getChildByTag(100);
	 CCMenu *pMenu = (CCMenu *)getChildByTag(101);
	 CCMenuItemImage *pItem=(CCMenuItemImage *)pMenu->getChildByTag(100);
	 CCSize size1 = sprite->getContentSize();
	 CCSize size2 = pItem->getContentSize();
	 //CCPoint spoint=sprite->getAnchorPoint();
	 //CCPoint mpoint = pMenu->getAnchorPoint();
	 CCSize ssize = CCDirector::sharedDirector()->getWinSize();  
	 float s=sprite->getPositionX();
	 float m=pItem->getPositionX();
	/* if(m_TouchUpPoint.x -m_TouchDownPoint.x>(size1.width/2+size2.width/2))
	 {*/
	 if(s-m>size1.width/2||m-s>size1.width/2)
	 {
		 pMenu->setEnabled(true);
	 }
	 //}
	}
	
}
void LevelGame01::ccTouchCancelled(CCTouch *pTouch, CCEvent  *pEvent)
{
}

void LevelGame01::gameover()
{
	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->playEffect("lose.wav");
	//	scheduleOnce(schedule_selector(LevelGame01::updateMusic),2.0f);
	}

	  // 游戏失败  Color4B
	CCSprite* sprite=(CCSprite *)getChildByTag(98);
	sprite->setVisible(false);
	CCMenu* wangnimamenu=(CCMenu *)getChildByTag(101);
	wangnimamenu->setVisible(false);
	CCMenu* du_yimenu=(CCMenu *)getChildByTag(104);
	du_yimenu->setVisible(false);
	CCMenu *pausemenu=(CCMenu *)getChildByTag(105);
	pausemenu->setVisible(false);
    CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height); 

	CCMenu *pmenu=(CCMenu *)getChildByTag(104);//104是yi_normal禁止
	pmenu->setEnabled(false);
	CCMenu *pause=(CCMenu *)getChildByTag(105);//105是暂停禁止
	pause->setEnabled(false);

	CCSprite *sp =CCSprite::create("bg-1-lose.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);

	//CCSprite* lose_cry =CCSprite::createWithSpriteFrameName("lose-cry.png"); 
   //lose_cry->setPosition(CCPoint(size.width*0.5-300,size.height*0.5)); 
    //layer->addChild(lose_cry);  

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("win-lose-list-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("win-lose-list-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame01::winloseCallback));
	Item1->setPosition(ccp(size.width*0.5, size.height*0.5-50));
    Item1->setTag(110); 
	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("result-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("result-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame01::resultCallback));
	Item2->setPosition(ccp(size.width*0.5+300, size.height*0.5-50));
    Item2->setTag(111); 
	CCMenu* menu= CCMenu::create(Item1,Item2, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(112);  
    layer->addChild(menu); 

	this->addChild(layer,2);
}

//void LevelGame01::updateMusic(float dt)
//{
//	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
//}

void LevelGame01::gamewin()
{
	 //  Color4B
	unschedule(schedule_selector(LevelGame01::updateGame));
	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->playEffect("win.wav");
		//scheduleOnce(schedule_selector(LevelGame01::updateMusic),2.5f);
	/*	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();*/
	}
	
	CCSprite* sprite=(CCSprite *)getChildByTag(98);
	sprite->setVisible(false);
	CCMenu* wangnima=(CCMenu *)getChildByTag(101);
	wangnima->setVisible(false);
	CCMenu* du_yimenu=(CCMenu *)getChildByTag(104);
	du_yimenu->setVisible(false);
    CCMenu *pausemenu=(CCMenu *)getChildByTag(105);
    pausemenu->setVisible(false);

    CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height); 

	CCMenu *pmenu=(CCMenu *)getChildByTag(104);//104是yi_normal
	pmenu->setEnabled(false);
	CCMenu *wangnimamenu=(CCMenu *)getChildByTag(101);//wangnima禁止
	wangnimamenu->setEnabled(false);
	CCMenu *pause=(CCMenu *)getChildByTag(105);//105是暂停禁止
	pause->setEnabled(false);

	CCSprite *sp =CCSprite::create("bg-1-win.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);

	//CCSprite* win_smile =CCSprite::createWithSpriteFrameName("win-smile.png"); 
    //win_smile->setPosition(CCPoint(size.width*0.5-300,size.height*0.5)); 
    //layer->addChild(win_smile);  

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("win-lose-list-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("win-lose-list-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame01::winloseCallback));
	Item1->setPosition(ccp(size.width*0.5-50, size.height*0.5-50));
    Item1->setTag(120); 

	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("result-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("result-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame01::resultCallback));
	Item2->setPosition(ccp(size.width*0.5+200, size.height*0.5-50));
    Item2->setTag(121); 

	CCMenuItemImage *Item3 = CCMenuItemImage::create();
	Item3->setNormalSpriteFrame(cache->spriteFrameByName("next-1.png"));
	Item3->setSelectedSpriteFrame(cache->spriteFrameByName("next-2.png"));
	Item3->initWithTarget(this,menu_selector(LevelGame01::nextCallback));
	Item3->setPosition(ccp(size.width*0.5+450, size.height*0.5-50));
    Item3->setTag(122); 
	CCMenu* menu= CCMenu::create(Item1,Item2,Item3, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(123);  
    layer->addChild(menu); 

	this->addChild(layer,2);
}


void LevelGame01::pauseCallback(CCObject *pSender)
{
	 // 游戏失败  Color4B
    CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height); 
	layer->setTag(90);
	CCMenu *pmenu=(CCMenu *)getChildByTag(104);//yi_normal禁止
	pmenu->setEnabled(false);
	CCMenu *pmenu1=(CCMenu *)getChildByTag(105);//105是暂停再次禁止
	pmenu1->setEnabled(false);

	CCSprite *sp =CCSprite::createWithSpriteFrameName("bg.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);

	
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  

	CCMenuItemImage *closeItem = CCMenuItemImage::create();
    closeItem->setNormalSpriteFrame(cache->spriteFrameByName("back-1.png"));
    closeItem->setSelectedSpriteFrame(cache->spriteFrameByName("back-2.png"));
    closeItem->initWithTarget(this, menu_selector(LevelGame01::menuCloseCallback));
	closeItem->setPosition(CCPoint(size.width*0.1,80));
    CCMenu *menus = CCMenu::create(closeItem, NULL);  
    menus->setPosition(CCPointZero);  
    layer->addChild(menus); 


	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("home-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("home-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame01::homeCallback));
	Item1->setPosition(ccp(size.width*0.5-300, size.height*0.5));
    Item1->setTag(125); 
	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("pause-list-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("pause-list-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame01::winloseCallback));
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
	Item3->initWithTarget(this,menu_selector(LevelGame01::musicCallback));
	Item3->setPosition(ccp(size.width*0.5+300, size.height*0.5));
    Item3->setTag(127); 
	CCMenu* menu= CCMenu::create(Item1,Item2,Item3, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(128);  
    layer->addChild(menu); 

	this->addChild(layer,2);
}

void LevelGame01::winloseCallback(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, ScrollViewScene::create()));  
}

void LevelGame01::resultCallback(CCObject *pSender)
{
	isNext = true;
	if(isNext == true)
	{
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
		cache->removeSpriteFramesFromFile("level-1.plist");  
	}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LevelGame01::createScene()));  
}

void LevelGame01::nextCallback(CCObject *pSender)
{
	isNext = true;
	if(isNext == true)
	{
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
		cache->removeSpriteFramesFromFile("level-1.plist");  
	}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LevelGame02::createScene()));  
}

void LevelGame01::homeCallback(CCObject *pSender)
{
	isNext = true;
	if(isNext == true)
	{
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
		cache->removeSpriteFramesFromFile("level-1.plist");  
	}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HelloWorld::scene()));  
}

void LevelGame01::musicCallback(CCObject *pSender)
{
	CCMenu *pmenu=(CCMenu *)getChildByTag(105);
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
//	removeChildByTag(90);
}
