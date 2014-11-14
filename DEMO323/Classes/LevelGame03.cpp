#include "HelloWorldScene.h"
#include "LevelGame03.h"
#include "LevelGame04.h"
#include "SWSpritePlayForTexturePacker.h"  
#include "ScrollViewScene.h"
#include "SimpleAudioEngine.h"


//#include "CCEventDispatcher.h"  
//#include "CCEventListenerTouch.h"  
  
USING_NS_CC; 
using namespace CocosDenshion;
//static bool isTouchDelete=false;
extern bool isMusic;    
//static bool isClickGo;  
  
//定义一个点击的次数  
int clickCount = 100;  
static bool isNext = false;
static bool isFailed = false;
static bool flagMusic = false;

CCScene* LevelGame03::createScene()  
{  
    //isClickGo = true;  
    CCScene *scene = CCScene::create();  
    CCLayer *layer = LevelGame03::create();  
    scene->addChild(layer);  
    return scene;  
}  
void LevelGame03::onEnter()  
{  
	//CCDirector* pDirector = CCDirector::sharedDirector();
	//pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);   
	
	CCLayer::onEnter();
}  
 
void LevelGame03::onExit()  
{  
	//CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	if(isNext == false)
	{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
    cache->removeSpriteFramesFromFile("level-3.plist"); 
	}
	isNext=false;
	CCLayer::onExit();  
} 
  
bool LevelGame03::init()  
{  
    if ( !CCLayer::init() )  
    {  
        return false;  
    }  
      isFailed = false;
	  flagMusic = false;
    //cocos2d-x3.0中的点击事件  
    //auto dispatcher = Director::getInstance()->getEventDispatcher();  
    //auto touchListener = EventListenerTouchOneByOne::create();  
    //touchListener->onTouchBegan = CC_CALLBACK_2(LevelGame03::onTouchBegan, this);  
    //dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);  
     
	CCUserDefault::sharedUserDefault()->setIntegerForKey("level_3", 1);
	CCUserDefault::sharedUserDefault()->flush();
      
    //加入背景  
	clickCount = 100; 

    CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
    cache->addSpriteFramesWithFile("level-3.plist");
      
    CCSprite* sprite =CCSprite::createWithSpriteFrameName("background-3.png"); 
	CCSize sprite_size = sprite->getContentSize();
	sprite->setScaleX(size.width/sprite_size.width);
	sprite->setScaleY(size.height/sprite_size.height);
    sprite->setPosition(CCPoint(size.width*0.5,size.height*0.5));
	sprite->setTag(106);
    this->addChild(sprite);  

      
    //次数  
    CCString *ns = CCString::createWithFormat("%d",clickCount);  
    CCLabelTTF *scorettf = CCLabelTTF::create(ns->getCString(), "Arial",80);  
    scorettf->setPosition(CCPoint(size.width*0.5+110, size.height*0.5+130));  
    scorettf->setTag(107);  
    addChild(scorettf);  
      
      
    //两个按钮  
	/*CCMenuItemImage *greeItem = CCMenuItemImage::create(
                                        "button_01.png",
                                        "button_02.png",
                                        this,
                                        menu_selector(LevelGame03::greeCallback));*/ 
	//绿色按钮
    CCMenuItemImage *greeItem = CCMenuItemImage::create();
	greeItem->setNormalSpriteFrame(cache->spriteFrameByName("button_01.png"));
	greeItem->setSelectedSpriteFrame(cache->spriteFrameByName("button_02.png"));
	greeItem->initWithTarget(this,menu_selector(LevelGame03::greeCallback));
	greeItem->setPosition(ccp(size.width*0.5-200, size.height*0.5-50));
    greeItem->setTag(108); 

   /*	CCMenuItemImage *redItem = CCMenuItemImage::create(
                                        "button_03.png",
                                        "button_04.png",
                                        this,
                                        menu_selector(LevelGame03::redCallback)); */
    //红色按钮
	CCMenuItemImage *redItem = CCMenuItemImage::create();
	redItem->setNormalSpriteFrame(cache->spriteFrameByName("button_03.png"));
	redItem->setSelectedSpriteFrame(cache->spriteFrameByName("button_04.png"));
	redItem->initWithTarget(this,menu_selector(LevelGame03::redCallback));
	redItem->setPosition(ccp(size.width*0.5+200, size.height*0.5-50));
    redItem->setTag(109);  

    CCMenu* menu= CCMenu::create(greeItem,redItem, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(110);  
    addChild(menu); 

	CCMenuItemImage *pauseItem = CCMenuItemImage::create();
    pauseItem->setNormalSpriteFrame(cache->spriteFrameByName("pause-1.png"));
    pauseItem->setSelectedSpriteFrame(cache->spriteFrameByName("pause-2.png"));
    pauseItem->initWithTarget(this, menu_selector(LevelGame03::pauseCallback));
	pauseItem->setPosition(CCPoint(size.width-100,size.height*0.9));

    CCMenu *pauseMenu = CCMenu::create(pauseItem, NULL);  
    pauseMenu->setPosition(CCPointZero);
	pauseMenu->setTag(111);
    this->addChild(pauseMenu, 1);  
      
	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("back2.mp3",true);
		flagMusic = true;
	}
    return true;  
}  
  
 

//暂停回调函数
void LevelGame03::pauseCallback(CCObject *pSender)
{
	CCMenu *pmenu=(CCMenu *)getChildByTag(110);//绿色和红色按钮禁止
	pmenu->setEnabled(false);
	CCMenu *pmenu1=(CCMenu *)getChildByTag(111);//暂停按钮再次禁止
	pmenu1->setEnabled(false);

	CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height);
	layer->setTag(112);

	//显示bg背景
	CCSprite *sp =CCSprite::createWithSpriteFrameName("bg.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	CCMenuItemImage *closeItem = CCMenuItemImage::create();
	closeItem->setNormalSpriteFrame(cache->spriteFrameByName("back-1.png"));
	closeItem->setSelectedSpriteFrame(cache->spriteFrameByName("back-2.png"));
	closeItem->initWithTarget(this, menu_selector(LevelGame03::menuCloseCallback));
	closeItem->setPosition(CCPoint(size.width*0.1,80));
	CCMenu *backmenus = CCMenu::create(closeItem, NULL);  
    backmenus->setPosition(CCPointZero);
	layer->addChild(backmenus);

	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("home-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("home-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame03::homeCallback));
	Item1->setPosition(ccp(size.width*0.5-300, size.height*0.5));
    Item1->setTag(113); 
	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("pause-list-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("pause-list-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame03::winloseCallback));
	Item2->setPosition(ccp(size.width*0.5, size.height*0.5));
    Item2->setTag(114); 
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
	Item3->initWithTarget(this,menu_selector(LevelGame03::musicCallback));
	Item3->setPosition(ccp(size.width*0.5+300, size.height*0.5));
    Item3->setTag(115); 
	CCMenu* menus= CCMenu::create(Item1,Item2,Item3, NULL);
    menus->setPosition(CCPointZero);
	menus->setTag(116);  
    layer->addChild(menus); 

	this->addChild(layer,2);

}

void LevelGame03::menuCloseCallback(CCObject *pSender)
{
	CCLayerColor *layer =(CCLayerColor *)getChildByTag(112);
	removeChild(layer,true);

	CCMenu *pmenu=(CCMenu *)getChildByTag(110);//绿色和红色按钮开启
	pmenu->setEnabled(true);
	CCMenu *pmenu1=(CCMenu *)getChildByTag(111);//暂停按钮再次开启
	pmenu1->setEnabled(true);
}

void LevelGame03::homeCallback(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HelloWorld::scene()));  
}

void LevelGame03::winloseCallback(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, ScrollViewScene::create()));  
}

void LevelGame03::resultCallback(CCObject *pSender)
{
	isNext = true;
	if(isNext == true)
	{
			CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
    cache->removeSpriteFramesFromFile("level-3.plist"); 
	}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LevelGame03::createScene())); 
}
void LevelGame03::musicCallback(CCObject *pSender)
{
		//removeChildByTag(112);
	CCMenu *pmenu=(CCMenu *)getChildByTag(111);
	pmenu->setEnabled(true);

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	 CCLayerColor *layer=( CCLayerColor *)getChildByTag(112);
	if(isMusic == true)
	{
		isMusic = false;
		/*CCDirector::sharedDirector()->end();*/
		CCMenu* pMenu = (CCMenu *)layer->getChildByTag(116);
		CCMenuItemImage *Item = (CCMenuItemImage *)pMenu->getChildByTag(115);
		Item->setNormalSpriteFrame(cache->spriteFrameByName("close-pause-music.png"));
		if(flagMusic == true)
			SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
	else
	{
		isMusic =true;
		CCMenu* pMenu = (CCMenu *)layer->getChildByTag(116);
		CCMenuItemImage *Item = (CCMenuItemImage *)pMenu->getChildByTag(115);
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

void LevelGame03::nextCallback(CCObject *pSender)
{
		isNext = true;
	if(isNext == true)
	{
		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
		cache->removeSpriteFramesFromFile("level-3.plist");  
	}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LevelGame04::createScene()));  
}


void LevelGame03::greeCallback(CCObject* pSender)  
{  
    //绿色按钮点击  
    //当绿色按你点击的时候数字减1  
    clickCount--;  
    //更新显示的数据  
    CCString *ns = CCString::createWithFormat("%d",clickCount);  
    CCLabelTTF * score = (CCLabelTTF *)getChildByTag(107);  
    score->setString(ns->getCString());  
      
    //判断当clickCount等于0的时候  
    if (0 >= clickCount) {  
        this->scheduleOnce(schedule_selector(LevelGame03::gamewin), 0.1f);  
    }  
      
    //判断当数字小于20的时候开始随机交换两个按你的位置  
    if (clickCount<20) {  
        CCSize size = CCDirector::sharedDirector()->getWinSize();  
        //定义两个位置  
        int speed = CCRANDOM_0_1()*10;  
        if (speed%2 == 0) {  
            CCMenu *gree = (CCMenu *)getChildByTag(110)->getChildByTag(108);  
            gree->setPosition(CCPoint(size.width*0.5-200, size.height*0.5-50));  
              
            CCMenu *red = (CCMenu *)getChildByTag(110)->getChildByTag(109);  
            red->setPosition(CCPoint(size.width*0.5+200, size.height*0.5-50));  
        }else{  
            CCMenu *gree = (CCMenu *)getChildByTag(110)->getChildByTag(108);  
            gree->setPosition(CCPoint(size.width*0.5+200, size.height*0.5-50));  
              
            CCMenu *red = (CCMenu *)getChildByTag(110)->getChildByTag(109);  
            red->setPosition(CCPoint(size.width*0.5-200, size.height*0.5-50));  
        }  
    }  
}  
void LevelGame03::redCallback(CCObject* pSender)  
{  
	if(isFailed == false)
	{
    CCSize size = CCDirector::sharedDirector()->getWinSize();  
    SWSpritePlayForTexturePacker *sp_people2 = SWSpritePlayForTexturePacker::createPlay("blow_up",1, 3, 0.07f,true);  
    sp_people2->setPosition(CCPoint(size.width*0.5+150, size.height*0.5-50));  
    sp_people2->setTag(105);  
    addChild(sp_people2);  
	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->playEffect("boom.wav");
		//scheduleOnce(schedule_selector(LevelGame03::updateMusic),2.0f);
	}
    this->scheduleOnce(schedule_selector(LevelGame03::gameover), 1.0f);  
	isFailed =true;
	}
}  
  
//void LevelGame03::updateMusic(float dt)
//{
//	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
//}
  
void LevelGame03::gameover(float dt)
{  
	if(isMusic == true)
	{
		//SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->playEffect("lose.wav");
		/*scheduleOnce(schedule_selector(LevelGame03::updateMusic),2.0f);*/
	}
    
	//使爆炸动画停止
	SWSpritePlayForTexturePacker *sprite_yin=(SWSpritePlayForTexturePacker *)getChildByTag(105);
	sprite_yin->setVisible(false);

	//分别使背景、红绿按钮、暂停按钮不可见
    CCSprite *spss = (CCSprite *)getChildByTag(106);  
    spss->setVisible(false);  
  
	CCMenu *pmenu=(CCMenu *)getChildByTag(110);
	pmenu->setVisible(false);

	CCMenu *pmenu1=(CCMenu *)getChildByTag(111);
	pmenu1->setVisible(false);

	

    CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height);  
	
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();

	CCSprite *sp =CCSprite::create("bg-3-lose.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);
    
	//CCSprite* lose_cry =CCSprite::createWithSpriteFrameName("lose-cry.png"); 
    //lose_cry->setPosition(CCPoint(size.width*0.5-300,size.height*0.5)); 
    //layer->addChild(lose_cry);  
	
	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("win-lose-list-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("win-lose-list-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame03::winloseCallback));
	Item1->setPosition(ccp(size.width*0.5-150, size.height*0.5-50));
    Item1->setTag(117); 

	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("result-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("result-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame03::resultCallback));
	Item2->setPosition(ccp(size.width*0.5+300, size.height*0.5-50));
    Item2->setTag(118); 

	CCMenu* menu= CCMenu::create(Item1,Item2, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(119);  
    layer->addChild(menu); 
     
    this->addChild(layer);  
      
      
}  
  
void LevelGame03::gamewin(float dt){  
  
	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->playEffect("win.wav");
		/*scheduleOnce(schedule_selector(LevelGame03::updateMusic),2.5f);*/
	/*	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();*/
	}
	//分别使背景、红绿按钮、暂停按钮不可见
    CCSprite *spss = (CCSprite *)getChildByTag(106);  
    spss->setVisible(false);  
  
	CCMenu *pmenu=(CCMenu *)getChildByTag(110);
	pmenu->setVisible(false);

	CCMenu *pmenu1=(CCMenu *)getChildByTag(111);
	pmenu1->setVisible(false);

    CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height);  

    CCSprite *sp =CCSprite::create("bg-3-win.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);
      
	//CCSprite* win_smile =CCSprite::createWithSpriteFrameName("win-smile.png"); 
    //win_smile->setPosition(CCPoint(size.width*0.5-300,size.height*0.5)); 
    //layer->addChild(win_smile);  

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("win-lose-list-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("win-lose-list-2.png"));
	Item1->initWithTarget(this,menu_selector(LevelGame03::winloseCallback));
	Item1->setPosition(ccp(size.width*0.5-150, size.height*0.5-50));
    Item1->setTag(119); 

	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("result-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("result-2.png"));
	Item2->initWithTarget(this,menu_selector(LevelGame03::resultCallback));
	Item2->setPosition(ccp(size.width*0.5+100, size.height*0.5-50));
    Item2->setTag(120); 

	CCMenuItemImage *Item3 = CCMenuItemImage::create();
	Item3->setNormalSpriteFrame(cache->spriteFrameByName("next-1.png"));
	Item3->setSelectedSpriteFrame(cache->spriteFrameByName("next-2.png"));
	Item3->initWithTarget(this,menu_selector(LevelGame03::nextCallback));
	Item3->setPosition(ccp(size.width*0.5+350, size.height*0.5-50));
    Item3->setTag(121); 
	CCMenu* menu= CCMenu::create(Item1,Item2,Item3, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(122);  
    layer->addChild(menu); 
      
    this->addChild(layer);  
}  
