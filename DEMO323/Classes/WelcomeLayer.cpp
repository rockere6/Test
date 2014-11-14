#include "WelcomeLayer.h"
#include "GameScene.h"

WelcomeLayer::WelcomeLayer(void)
{
}

WelcomeLayer::~WelcomeLayer(void)
{
}

bool WelcomeLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		//png加入全局cache中
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("level-8.plist");
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot.plist");

		CCSize winSize=CCDirector::sharedDirector()->getWinSize();

		////加入background
		//CCSprite* background=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		//background->setPosition(ccp(winSize.width/2,winSize.height/2));
		//this->addChild(background);

		////加入copyright
		//CCSprite* copyright=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("shoot_copyright.png"));
		//copyright->setAnchorPoint(ccp(0.5,0));
		//copyright->setPosition(ccp(winSize.width/2,winSize.height/2));
		//this->addChild(copyright);

		//加入loading
		CCSprite* loading=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background_01.png"));
		loading->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(loading);

		CCAnimation* animation=CCAnimation::create();
		animation->setDelayPerUnit(3.0f);
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background_01.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background_02.png"));
		

		CCAnimate* animate=CCAnimate::create(animation);
		CCRepeat* repeat=CCRepeat::create(animate,1);
		CCCallFuncN* repeatdone=CCCallFuncN::create(this,callfuncN_selector(WelcomeLayer::loadingDone));
		CCSequence* sequence=CCSequence::create(repeat,repeatdone,NULL);
		loading->runAction(sequence);
		
		//getHighestHistorySorce();

		//this->setKeypadEnabled(true);

		bRet=true;
	} while (0);

	return bRet;
}

void WelcomeLayer::loadingDone(CCNode* pNode)
{
	CCScene* pScene=GameScene::create();
	//CCTransitionMoveInB *animateScene=CCTransitionMoveInB::create(0.5f,pScene);
	//CCDirector::sharedDirector()->replaceScene(animateScene);
	/*CCDirector::sharedDirector()->end();*/
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5,pScene));  
}