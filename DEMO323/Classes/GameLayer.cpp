#include "GameLayer.h"
#include "ScrollViewScene.h" 
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

extern bool isMusic; 
static bool isNext = false;
static bool isSucessful=false;
static bool flagMusic = false;
//static int sscore=0;

GameLayer::GameLayer(void)
{
	background1=NULL;
	//controlLayer=NULL;
	personLayer = NULL;
	enemyLayer = NULL;
	noTouchLayer=NULL;
	scoreItem=NULL;
	pPauseItem=NULL;
	score=0;

}

GameLayer::~GameLayer(void)
{
}

void GameLayer::onExit()  
{  
//	
//	//if(isNext ==false)
//	//{
//		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
//		cache->removeSpriteFramesFromFile("level-8.plist");  
//	//}
	isNext = false;
	CCLayer::onExit();  
}

bool GameLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		flagMusic = false;
		isSucessful=false;
		////初始化level
		//level=EASY;

		////加载background Music
		//if (!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		//{
		//	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.mp3",true);
		//}

		//加载background1
		CCSize winSize=CCDirector::sharedDirector()->getWinSize();
		background1=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background-8.png"));
		CCSize sprite_size = background1->getContentSize();
		background1->setScaleX(winSize.width/sprite_size.width);
		background1->setScaleY(winSize.height/sprite_size.height);
		background1->setPosition(ccp(winSize.width/2,winSize.height/2));
		background1->setTag(150);
		this->addChild(background1);

		//加入PauseMenu
		pPauseItem = CCMenuItemImage::create();
		pPauseItem->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("pause-1.png"));
		pPauseItem->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("pause-2.png"));
		pPauseItem->initWithTarget(this, menu_selector(GameLayer::menuPauseCallback));
		pPauseItem->setPosition(CCPoint(winSize.width-100,winSize.height*0.9));
		CCMenu *pauseMenu = CCMenu::create(pPauseItem, NULL);  
		pauseMenu->setPosition(CCPointZero);  
		this->addChild(pauseMenu);  

		pSoapItem = CCMenuItemImage::create();
		pSoapItem->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("soap.png"));
		pSoapItem->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("soap.png"));
		pSoapItem->initWithTarget(this, menu_selector(GameLayer::menuSoapCallback));
		pSoapItem->setPosition(CCPoint(100,winSize.height*0.9));
    CCMenu *soapMenu = CCMenu::create(pSoapItem, NULL);  
    soapMenu->setPosition(CCPointZero);  
	//soapMenu->setEnabled(false);
    this->addChild(soapMenu);  

	scoreItem = CCLabelTTF::create("0", "Arial",50);
	scoreItem->setColor(ccc3(0,0,0));
    scoreItem->setPosition(CCPoint(100, winSize.height*0.9-70));  
    addChild(scoreItem);  

		////加入personLayer
		this->personLayer = PersonLayer::create();
		this->addChild(personLayer);

		//加入enemyLayer
		this->enemyLayer = EnemyLayer::create();
		this->addChild(enemyLayer);

		////加入controlLayer
		//this->controlLayer=ControlLayer::create();
		//this->addChild(controlLayer);

		//设置可触摸
		this->setTouchEnabled(true);

		//碰撞检测
		this->scheduleUpdate();

		bRet=true;
	} while (0);

	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("back2.mp3",true);
		flagMusic = true;
	}
	return bRet;
}

bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void GameLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if (this->personLayer->isAlive)
	{
		CCPoint beginPoint=pTouch->getLocationInView(); 
		beginPoint=CCDirector::sharedDirector()->convertToGL(beginPoint); 
		//juggle the area of drag 
		CCRect personRect=this->personLayer->getChildByTag(AIRPERSON)->boundingBox();
		personRect.origin.x-=15;
		personRect.origin.y-=15;
		personRect.size.width+=30;
		personRect.size.height+=30;
		if(personRect.containsPoint(this->getParent()->convertTouchToNodeSpace(pTouch))) 
		{ 
			CCPoint endPoint=pTouch->getPreviousLocationInView(); 
			endPoint=CCDirector::sharedDirector()->convertToGL(endPoint); 

			CCPoint offSet =ccpSub(beginPoint,endPoint);
			CCPoint toPoint=ccpAdd(this->personLayer->getChildByTag(AIRPERSON)->getPosition(),offSet); 
			this->personLayer->MoveTo(toPoint); 
		} 
	}
}

void GameLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}

void GameLayer::registerWithTouchDispatcher()
{
	CCDirector *pDirector=CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

void GameLayer::update(float dt)
{
	CCObject *et;

	CCRect personRect=this->personLayer->getChildByTag(AIRPERSON)->boundingBox();
	personRect.origin.x+=30;
	personRect.size.width-=60;
	//soap & airplane CheckCollosion
	CCArray* soapToDelete=CCArray::create();
		soapToDelete->retain();
	CCARRAY_FOREACH(this->enemyLayer->m_pAllSoap,et)
	{
		Enemy* soap=(Enemy*)et;
		if (personRect.intersectsRect(soap->getBoundingBox()))
		{
			if (soap->getLife()==1)
			{
				soap->loseLife();
		/*		bulletsToDelete->addObject(bullet);*/
				soapToDelete->addObject(soap);
				score++;
				/*this->controlLayer->*/updateScore(score);
			}
			if(score ==9)
			{
				enemyLayer->removeAllSoap();
				enemyLayer->unschedule(schedule_selector(EnemyLayer::addSoap));
				enemyLayer->unschedule(schedule_selector(EnemyLayer::addJuhua));
				enemyLayer->schedule(schedule_selector(EnemyLayer::addJuhua),0.35f);
	/*			CCMenu *soapMenu =(CCMenu *)controlLayer->getChildByTag(102);
				soapMenu->setEnabled(true);*/
			}
		}
	}
	CCARRAY_FOREACH(soapToDelete,et)
	{
		Enemy* soap=(Enemy*)et;
		this->enemyLayer->soapBlowup(soap);
	}
	soapToDelete->release();

		//juhua& airplane CheckCollosion
	CCARRAY_FOREACH(this->enemyLayer->m_pAllJuhua,et)
	{
		Enemy* enemy2=(Enemy*)et;
		if (enemy2->getLife()>0)
		{
			if (personRect.intersectsRect(enemy2->getBoundingBox()))
			{
				//卸载所有任务计划
				this->unscheduleAllSelectors();
				this->personLayer->Blowup(score);
				enemyLayer->unscheduleAllSelectors();
				enemyLayer->removeAllSoap();
				enemyLayer->removeAllJuhua();
		/*		schedule(schedule_selector(EnemyLayer::addSoap),3.0f);
		this->schedule(schedule_selector(EnemyLayer::addJuhua),1.0f);*/
	/*enemyLayer->unschedule(schedule_selector(EnemyLayer::addJuhua));*/
				/*controlLayer->*/
				gameover();
		return;
			}
		}
	}
}


void GameLayer::menuSoapCallback(CCObject* pSender)
{
	if(score==9&&isSucessful == false)
	{
		CCObject *et;
		score++;
		updateScore(score);
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCFiniteTimeAction* actionMove=CCMoveTo::create(3.0f,ccp(100,-100));
	/*CCFiniteTimeAction* actionDone=CCCallFuncN::create(this,callfuncN_selector(ControlLayer::gamewin));
*/
	/*CCSequence* sequence=CCSequence::create(actionMove,actionDone,NULL);*/
	pSoapItem->runAction(actionMove);
	enemyLayer->unschedule(schedule_selector(EnemyLayer::addJuhua));
	CCARRAY_FOREACH(this->enemyLayer->m_pAllJuhua,et)
	{
		Enemy* enemy2=(Enemy*)et;
		enemy2->stopAllActions();
	}
	scheduleOnce(schedule_selector(GameLayer::gamewin),3.0f);
	}
}



void GameLayer::menuPauseCallback(CCObject* pSender)
{
	/*CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3");*/
	if(!CCDirector::sharedDirector()->isPaused())
	{
		CCDirector::sharedDirector()->pause();

	CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height); 
	layer->setTag(90);
	//CCMenu *pmenu=(CCMenu *)getChildByTag(101);//pause禁止
	//pmenu->setEnabled(false);
	//CCMenu *pmenu1=(CCMenu *)getChildByTag(102);//soap禁止
	//pmenu1->setEnabled(false);

	CCSprite *sp =CCSprite::createWithSpriteFrameName("bg.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);

		
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  

	CCMenuItemImage *closeItem = CCMenuItemImage::create();
    closeItem->setNormalSpriteFrame(cache->spriteFrameByName("back-1.png"));
    closeItem->setSelectedSpriteFrame(cache->spriteFrameByName("back-2.png"));
    closeItem->initWithTarget(this, menu_selector(GameLayer::menuCloseCallback));
	closeItem->setPosition(CCPoint(size.width*0.1,80));
    CCMenu *menus = CCMenu::create(closeItem, NULL);  
    menus->setPosition(CCPointZero);  
    layer->addChild(menus); 


	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("home-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("home-2.png"));
	Item1->initWithTarget(this,menu_selector(GameLayer::homeCallback));
	Item1->setPosition(ccp(size.width*0.5-300, size.height*0.5));
    Item1->setTag(125); 
	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("pause-list-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("pause-list-2.png"));
	Item2->initWithTarget(this,menu_selector(GameLayer::winloseCallback));
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
	Item3->initWithTarget(this,menu_selector(GameLayer::musicCallback));
	Item3->setPosition(ccp(size.width*0.5+300, size.height*0.5));
    Item3->setTag(127); 
	CCMenu* menu= CCMenu::create(Item1,Item2,Item3, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(128);  
    layer->addChild(menu,2); 

	this->addChild(layer,2);

	noTouchLayer=NoTouchLayer::create();
	this->addChild(noTouchLayer);
	}
}

void GameLayer::updateScore(int score)
{
	if (score>=0/* && score<=MAX_SCORE*/)
	{
		/*sscore = score;*/
		CCString* strScore=CCString::createWithFormat("%d",score);
		scoreItem->setString(strScore->m_sString.c_str());
	}
}

void GameLayer::menuCloseCallback(CCObject* pSender)
{
	CCLayerColor *layer =(CCLayerColor *)getChildByTag(90);
	removeChild(layer,true);
	//CCMenu *pmenu=(CCMenu *)getChildByTag(101);//pause
	//pmenu->setEnabled(true);
	
	CCDirector::sharedDirector()->resume();
	this->removeChild(noTouchLayer,true);
}


void GameLayer::winloseCallback(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, ScrollViewScene::create()));  
	CCDirector::sharedDirector()->resume();
	this->removeChild(noTouchLayer,true);
}

void GameLayer::homeCallback(CCObject *pSender)
{

	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HelloWorld::scene()));  
	CCDirector::sharedDirector()->resume();
	this->removeChild(noTouchLayer,true);
}

void GameLayer::musicCallback(CCObject *pSender)
{
	//	CCMenu *pmenu=(CCMenu *)getChildByTag(101);
	//pmenu->setEnabled(true);
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

	//if(score==9)
	//{
	//	CCMenu *pmenu1=(CCMenu *)getChildByTag(102);//soap
	//	pmenu1->setEnabled(true);
	//}
		//	CCDirector::sharedDirector()->resume();
		//this->removeChild(noTouchLayer,true);
}

void GameLayer::resultCallback(CCObject *pSender)
{
	//isNext = true;
	//if(isNext == true)
	//{
	//	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	//	cache->removeSpriteFramesFromFile("level-8.plist");  
	//}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, GameScene::create()));  
				CCDirector::sharedDirector()->resume();
		this->removeChild(noTouchLayer,true);
}


void GameLayer::gamewin(float dt)
{
	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->playEffect("win.wav");
		//scheduleOnce(schedule_selector(LevelGame01::updateMusic),2.5f);
	/*	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();*/
	}
	
	//if(!CCDirector::sharedDirector()->isPaused())
	//{
		//this->getParent()->personLayer->removeChildByTag(747);
	/*	pPauseItem->setVisible(false);*/
		//CCMenu *pmenu=(CCMenu *)getChildByTag(101);//pause
		//pmenu->setEnabled(false);
	//EnemyLayer* enemy=(EnemyLayer*)((GameLayer)(this->getParent())->getChildByTag(10));
	pPauseItem->setVisible(false);
	enemyLayer->unschedule(schedule_selector(EnemyLayer::addJuhua));
	enemyLayer->removeAllJuhua();
	CCSize size = CCDirector::sharedDirector()->getWinSize();  
	CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height);

	CCSprite *sp =CCSprite::create("bg-8-win.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);

	//CCSprite* win_smile =CCSprite::createWithSpriteFrameName("win-smile.png"); 
   // win_smile->setPosition(CCPoint(size.width*0.5-300,size.height*0.5)); 
    //layer->addChild(win_smile);  

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("win-lose-list-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("win-lose-list-2.png"));
	Item1->initWithTarget(this,menu_selector(GameLayer::winloseCallback));
	Item1->setPosition(ccp(size.width*0.5-20, size.height*0.5-60));
    Item1->setTag(120); 

	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("result-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("result-2.png"));
	Item2->initWithTarget(this,menu_selector(GameLayer::resultCallback));
	Item2->setPosition(ccp(size.width*0.5+320, size.height*0.5-60));
    Item2->setTag(121); 

	//CCMenuItemImage *Item3 = CCMenuItemImage::create();
	//Item3->setNormalSpriteFrame(cache->spriteFrameByName("next-1.png"));
	//Item3->setSelectedSpriteFrame(cache->spriteFrameByName("next-2.png"));
	//Item3->initWithTarget(this,menu_selector(LevelGame01::nextCallback));
	//Item3->setPosition(ccp(size.width*0.5+600, size.height*0.5));
 //   Item3->setTag(122); 
	CCMenu* menu= CCMenu::create(Item1,Item2, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(123);  
    layer->addChild(menu); 

	this->addChild(layer,2);
	//	noTouchLayer=NoTouchLayer::create();
	//	this->addChild(noTouchLayer);
	//}
}

void GameLayer::gameover()
{
	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->playEffect("lose.wav");
	//	scheduleOnce(schedule_selector(LevelGame01::updateMusic),2.0f);
	}	
	pPauseItem->setVisible(false);
	isSucessful = true;
	CCSize size = CCDirector::sharedDirector()->getWinSize();  
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 200), size.width, size.height); 

	CCSprite *sp =CCSprite::create("bg-8-lose.png");  
    sp->setPosition(CCPoint(size.width*0.5, size.height*0.5));  
    layer->addChild(sp);

	//CCSprite* lose_cry =CCSprite::createWithSpriteFrameName("lose-cry.png"); 
    //lose_cry->setPosition(CCPoint(size.width*0.5-300,size.height*0.5)); 
    //layer->addChild(lose_cry);  

	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	CCMenuItemImage *Item1 = CCMenuItemImage::create();
	Item1->setNormalSpriteFrame(cache->spriteFrameByName("win-lose-list-1.png"));
	Item1->setSelectedSpriteFrame(cache->spriteFrameByName("win-lose-list-2.png"));
	Item1->initWithTarget(this,menu_selector(GameLayer::winloseCallback));
	Item1->setPosition(ccp(size.width*0.5-100, size.height*0.5-70));
    Item1->setTag(110); 
	CCMenuItemImage *Item2 = CCMenuItemImage::create();
	Item2->setNormalSpriteFrame(cache->spriteFrameByName("result-1.png"));
	Item2->setSelectedSpriteFrame(cache->spriteFrameByName("result-2.png"));
	Item2->initWithTarget(this,menu_selector(GameLayer::resultCallback));
	Item2->setPosition(ccp(size.width*0.5+200, size.height*0.5-70));
    Item2->setTag(111); 
	CCMenu* menu= CCMenu::create(Item1,Item2, NULL);
    menu->setPosition(CCPointZero);
	menu->setTag(112);  
    layer->addChild(menu); 

	this->addChild(layer,2);
	//	noTouchLayer=NoTouchLayer::create();
	//	this->addChild(noTouchLayer);
	//}
}