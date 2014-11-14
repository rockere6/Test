#include "EnemyLayer.h"

EnemyLayer::EnemyLayer(void)
{
	soapSpriteFrame=NULL;
	juhuaSpriteFrame=NULL;

	m_pAllSoap=CCArray::create();
	m_pAllSoap->retain();
	m_pAllJuhua=CCArray::create();
	m_pAllJuhua->retain();
}

EnemyLayer::~EnemyLayer(void)
{
	m_pAllSoap->release();
	m_pAllSoap=NULL;
	m_pAllJuhua->release();
	m_pAllJuhua=NULL;
}

bool EnemyLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		soapSpriteFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("soap.png");
		juhuaSpriteFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("juhua.png");

		this->schedule(schedule_selector(EnemyLayer::addSoap),3.0f);
		this->schedule(schedule_selector(EnemyLayer::addJuhua),1.0f);

		bRet=true;
	} while (0);
	return bRet;
}

void EnemyLayer::addSoap(float dt)
{
	Enemy* enemy1=Enemy::create();
	enemy1->bindSprite(CCSprite::createWithSpriteFrame(soapSpriteFrame),SOAP_MAXLIFE);

	CCSize enemy1Size=enemy1->getSprite()->getContentSize();
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	int minX=enemy1Size.width*0.5;
	int maxX=winSize.width-enemy1Size.width/2;
	int rangeX=maxX-minX;
	int actualX=(rand()%rangeX)+minX;

	enemy1->setPosition(ccp(actualX,winSize.height+enemy1Size.height/2));
	this->addChild(enemy1);
	this->m_pAllSoap->addObject(enemy1);

	float minDuration = 2.0;
	float maxDuration = 4.0;

	int rangeDuration=maxDuration-minDuration;
	int actualDuration=(rand()%rangeDuration)+minDuration;

	CCFiniteTimeAction* actionMove=CCMoveTo::create(actualDuration,ccp(actualX,0-enemy1->getSprite()->getContentSize().height/2));
	CCFiniteTimeAction* actionDone=CCCallFuncN::create(this,callfuncN_selector(EnemyLayer::soapMoveFinished));

	CCSequence* sequence=CCSequence::create(actionMove,actionDone,NULL);
	enemy1->runAction(sequence);

}

void EnemyLayer::soapMoveFinished(CCNode* pSender)
{
	Enemy* enmey1=(Enemy*)pSender;
	this->removeChild(enmey1,true);
	this->m_pAllSoap->removeObject(enmey1);
}

void EnemyLayer::removeSoap(CCNode* pTarget, void* data)
{
	Enemy* enemy1=(Enemy*)data;
	if (enemy1!=NULL)
	{
		m_pAllSoap->removeObject(enemy1);
		this->removeChild(enemy1,true);
	}
}

void EnemyLayer::soapBlowup(Enemy* enemy1)
{
	CCCallFuncND* removeSoap=CCCallFuncND::create(this,callfuncND_selector(EnemyLayer::removeSoap),(void*)enemy1);
	//CCSequence* sequence=CCSequence::create(animate,removeEnemy1,NULL);
	enemy1->getSprite()->runAction(removeSoap);
}

void EnemyLayer::removeAllSoap()
{
	CCObject* obj;
	CCARRAY_FOREACH(m_pAllSoap,obj)
	{
		Enemy* enemy1=(Enemy*)obj;
		if (enemy1->getLife()>0)
		{
			soapBlowup(enemy1);
		}
	}
}

void EnemyLayer::addJuhua(float dt)
{
	Enemy* enemy2=Enemy::create();
	enemy2->bindSprite(CCSprite::createWithSpriteFrame(juhuaSpriteFrame),JUHUA_MAXLIFE);

	CCSize enemy2Size=enemy2->getSprite()->getContentSize();
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	int minX=enemy2Size.width*0.5;
	int maxX=winSize.width-enemy2Size.width/2;
	int rangeX=maxX-minX;
	int actualX=(rand()%rangeX)+minX;

	enemy2->setPosition(ccp(actualX,winSize.height+enemy2Size.height/2));
	this->addChild(enemy2);
	this->m_pAllJuhua->addObject(enemy2);

	float minDuration =2.0;
	float maxDuration = 4.0;

	int rangeDuration=maxDuration-minDuration;
	int actualDuration=(rand()%rangeDuration)+minDuration;

	CCFiniteTimeAction* actionMove=CCMoveTo::create(actualDuration,ccp(actualX,0-enemy2->getSprite()->getContentSize().height/2));
	CCFiniteTimeAction* actionDone=CCCallFuncN::create(this,callfuncN_selector(EnemyLayer::juhuaMoveFinished));

	CCSequence* sequence=CCSequence::create(actionMove,actionDone,NULL);
	enemy2->runAction(sequence);
}

void EnemyLayer::juhuaMoveFinished(CCNode* pSender)
{
	Enemy* enmey2=(Enemy*)pSender;
	this->removeChild(enmey2,true);
	this->m_pAllJuhua->removeObject(enmey2);
}

void EnemyLayer::juhuaBlowup(Enemy* enemy2)
{
	CCCallFuncND* removeJuhua=CCCallFuncND::create(this,callfuncND_selector(EnemyLayer::removeJuhua),(void*)enemy2);
	enemy2->getSprite()->runAction(removeJuhua);
}

void EnemyLayer::removeJuhua(CCNode* pTarget, void* data)
{
	Enemy* enemy2=(Enemy*)data;
	if (enemy2!=NULL)
	{
		m_pAllJuhua->removeObject(enemy2);
		this->removeChild(enemy2,true);
	}
}

void EnemyLayer::removeAllJuhua()
{
	CCObject* obj;
	CCARRAY_FOREACH(m_pAllJuhua,obj)
	{
		Enemy* enemy2=(Enemy*)obj;
		if (enemy2->getLife()>0)
		{
			juhuaBlowup(enemy2);
		}
	}
}

void EnemyLayer::removeAllEnemy()
{
	removeAllSoap();
	removeAllJuhua();
}