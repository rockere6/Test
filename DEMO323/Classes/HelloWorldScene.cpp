#include "HelloWorldScene.h"  
#include "ScrollViewScene.h" 
#include "SimpleAudioEngine.h"
  
USING_NS_CC;  
using namespace CocosDenshion;
 bool isMusic=true;  
static bool flagMusic = false;

CCScene* HelloWorld::scene()  
{  
    // 'scene' is an autorelease object  
    CCScene *scene = CCScene::create();  
      
    // 'layer' is an autorelease object  
    HelloWorld *layer = HelloWorld::create();  
  
    // add layer as a child to scene  
    scene->addChild(layer);  
  
    // return the scene  
    return scene;  
}  
  
// on "init" you need to initialize your instance  
bool HelloWorld::init()  
{  
    //////////////////////////////  
    // 1. super init first  
    if ( !CCLayer::init() )  
    {  
        return false;  
    } 
	this->setKeypadEnabled(true);

    flagMusic = false;


	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("back1.mp3",true);
		flagMusic = true;
	}
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();  
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();  
	
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache(); 
	cache->addSpriteFramesWithFile("UIResource.plist");
    /////////////////////////////  
    // 2. add a menu item with "X" image, which is clicked to quit the program  
    //    you may modify it.  
      
      
    //加入背景 
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* pSprite =CCSprite::createWithSpriteFrameName("start-bg.png");  
    pSprite->setPosition(ccp(size.width*0.5,size.height*0.5));  
    addChild(pSprite);  
      
    CCSprite* pSprite1 =CCSprite::create("zimu.png");  
    pSprite1->setPosition(ccp(size.width*0.5,size.height*0.5));  
	pSprite1->setVisible(false);
	pSprite1->setTag(100);
	addChild(pSprite1);
	
/*	//字幕界面的退出按钮
	CCMenuItemImage *pCloseItem1 = CCMenuItemImage::create();
	pCloseItem1->setNormalSpriteFrame(cache->spriteFrameByName("exit-1.png"));
	pCloseItem1->setSelectedSpriteFrame(cache->spriteFrameByName("exit-2.png"));
	pCloseItem1->initWithTarget(this,menu_selector(HelloWorld::menuCloseCallback));
	pCloseItem1->setPosition(ccp(size.width*0.8,80));
    CCMenu* pMenu1 = CCMenu::create(pCloseItem1,NULL);
    pMenu1->setPosition(CCPointZero);
	pMenu1->setTag(151);
	pMenu1->setVisible(false);
    this->addChild(pMenu1, 2);  */

  /*   CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "play-1.png",
                                        "play-2.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback)); */

	CCMenuItemImage *pCloseItem = CCMenuItemImage::create();
	pCloseItem->setNormalSpriteFrame(cache->spriteFrameByName("play-1.png"));
	pCloseItem->setSelectedSpriteFrame(cache->spriteFrameByName("play-2.png"));
	pCloseItem->initWithTarget(this,menu_selector(HelloWorld::menuCloseCallback));
	pCloseItem->setPosition(ccp(size.width*0.5,size.height*0.5-160));

	/*CCMenuItemImage *pBackItem = CCMenuItemImage::create(
                                        "back-1.png",
                                        "back-2.png",
                                        this,
                                        menu_selector(HelloWorld::menuClose)); */
    CCMenuItemImage *pBackItem = CCMenuItemImage::create();
	pBackItem->setNormalSpriteFrame(cache->spriteFrameByName("back-1.png"));
	pBackItem->setSelectedSpriteFrame(cache->spriteFrameByName("back-2.png"));
	pBackItem->initWithTarget(this,menu_selector(HelloWorld::menuClose));
	pBackItem->setPosition(ccp(size.width*0.1,80));

	CCMenuItemImage *pInforItem = CCMenuItemImage::create();
	pInforItem->setNormalSpriteFrame(cache->spriteFrameByName("information-1.png"));
	pInforItem->setSelectedSpriteFrame(cache->spriteFrameByName("information-2.png"));
	pInforItem->initWithTarget(this,menu_selector(HelloWorld::InforCallback));
	pInforItem->setPosition(ccp(size.width*0.8,80));


	CCMenuItemImage *pMusicItem = CCMenuItemImage::create();
	if(isMusic == true)
	{
	pMusicItem->setNormalSpriteFrame(cache->spriteFrameByName("music.png"));
	}
	else
	{
		//SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		pMusicItem->setNormalSpriteFrame(cache->spriteFrameByName("close-music.png"));
	}
	/*pMusicItem->setSelectedSpriteFrame(cache->spriteFrameByName("close-music.png"));*/
	//pMusicItem->setSelectedSpriteFrame(cache->spriteFrameByName("music.png"));
	pMusicItem->initWithTarget(this,menu_selector(HelloWorld::musicClose));
	pMusicItem->setTag(151);
	pMusicItem->setPosition(ccp(size.width*0.9,80));
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem,pBackItem,pMusicItem,pInforItem,NULL);
    pMenu->setPosition(CCPointZero);
	pMenu->setTag(150);
    this->addChild(pMenu, 1);

	//关闭音乐
	
      
    return true;  
}  
  

void HelloWorld::musicClose(CCObject *pSender)
{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	if(isMusic == true)
	{
		isMusic = false;
		/*CCDirector::sharedDirector()->end();*/
		CCMenu* pMenu = (CCMenu *)getChildByTag(150);
		CCMenuItemImage *Item = (CCMenuItemImage *)pMenu->getChildByTag(151);
		Item->setNormalSpriteFrame(cache->spriteFrameByName("close-music.png"));
		if(flagMusic == true)
			SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
	else
	{
		isMusic =true;
		CCMenu* pMenu = (CCMenu *)getChildByTag(150);
		CCMenuItemImage *Item = (CCMenuItemImage *)pMenu->getChildByTag(151);
		Item->setNormalSpriteFrame(cache->spriteFrameByName("music.png"));
		if(flagMusic == true)
		{
			SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		}
		else
		{
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("back1.mp3",true);
			flagMusic = true;

		}
	}
	//CCDirector::sharedDirector()->end();
}

void HelloWorld::menuCloseCallback(CCObject* pSender)  
{  
    //Director::getInstance()->end();  
    //实现  
  CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, ScrollViewScene::create()));  
 
 // CCScene *pScene = HistoryGame01::createScene();
 //CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, pScene));  
    //释放没有用到过的缓冲  
    //CCTextureCache::sharedTextureCache()->removeUnusedTextures();  
}  

void HelloWorld::menuClose(CCObject *pSender)
{
	SimpleAudioEngine::sharedEngine()->end();
	CCDirector::sharedDirector()->end();
}

void HelloWorld::keyBackClicked()
{
	SimpleAudioEngine::sharedEngine()->end();
	CCDirector::sharedDirector()->end();
}

void HelloWorld::InforCallback(CCObject *pSender)
{
	CCSprite* pSprite1 = (CCSprite* )getChildByTag(100);
	pSprite1->setVisible(true);

	CCMenu* pMenu = (CCMenu* )getChildByTag(150);
	pMenu->setVisible(false);


	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache(); 
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCMenuItemImage *pCloseItem1 = CCMenuItemImage::create();
	pCloseItem1->setNormalSpriteFrame(cache->spriteFrameByName("exit-1.png"));
	pCloseItem1->setSelectedSpriteFrame(cache->spriteFrameByName("exit-2.png"));
	pCloseItem1->initWithTarget(this,menu_selector(HelloWorld::resultCallback));
	pCloseItem1->setPosition(ccp(size.width*0.9,80));
    CCMenu* pMenu1 = CCMenu::create(pCloseItem1,NULL);
    pMenu1->setPosition(CCPointZero);
	pMenu1->setTag(151);
    this->addChild(pMenu1); 
}

void HelloWorld::resultCallback(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HelloWorld::scene()));
}