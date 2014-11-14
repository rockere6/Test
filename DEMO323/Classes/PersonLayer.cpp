#include "PersonLayer.h"

PersonLayer* PersonLayer::sharedPerson=NULL;//

PersonLayer::PersonLayer(void)
{
	isAlive=true;
	score=0;
}

PersonLayer::~PersonLayer(void)
{
}

PersonLayer* PersonLayer::create() 
{ 
	PersonLayer *pRet = new PersonLayer();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		sharedPerson=pRet;
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

bool PersonLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		
		CCSize winSize=CCDirector::sharedDirector()->getWinSize();

		CCSprite* person=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("person.png"));
		person->setPosition(ccp(winSize.width/2,person->getContentSize().height/2));
		this->addChild(person,0,AIRPERSON);
		
		//CCSequence* sequence=CCSequence::create(blink,CCRepeatForever::create(animate),NULL);
		//plane->runAction(sequence);

		bRet=true;
	} while (0);
	
	return bRet;
}

void PersonLayer::MoveTo(CCPoint location)
{
	//���б߽��ж�
	if(isAlive && !CCDirector::sharedDirector()->isPaused())//�Ѿ���NoTouchLayer��
	{
		CCPoint actualPoint;
		CCSize winSize=CCDirector::sharedDirector()->getWinSize();
		CCSize personSize=this->getChildByTag(AIRPERSON)->getContentSize();
		if (location.x<personSize.width/2)
		{
			location.x=personSize.width/2;
		}
		if (location.x>winSize.width-personSize.width/2)
		{
			location.x=winSize.width-personSize.width/2;
		}
		if (location.y<personSize.height/2)
		{
			location.y=personSize.width/2+10;
		}
		if (location.y>winSize.height-personSize.height/2)
		{
			location.y=winSize.height-personSize.height/2;
		}
		this->getChildByTag(AIRPERSON)->setPosition(location);
	}
}

void PersonLayer::Blowup(int passScore)
{
	if(isAlive)
	{
		isAlive=false;
		score=passScore;
		
		CCCallFunc* removePerson=CCCallFunc::create(this,callfunc_selector(PersonLayer::RemovePerson));
		this->getChildByTag(AIRPERSON)->stopAllActions();
		this->getChildByTag(AIRPERSON)->runAction(removePerson);
	}
}

void PersonLayer::RemovePerson()
{
	this->removeChildByTag(AIRPERSON,true);
	//GameOverScene* pScene=GameOverScene::create(/*score*/);
	//CCTransitionMoveInT* animateScene=CCTransitionMoveInT::create(0.8f,pScene);
	//CCDirector::sharedDirector()->replaceScene(animateScene);
}