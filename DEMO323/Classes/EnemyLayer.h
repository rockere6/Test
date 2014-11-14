#ifndef ENEMYLAYER_H
#define ENEMYLAYER_H

#include "cocos2d.h"
#include "Enemy.h"

USING_NS_CC;

const int SOAP_MAXLIFE=1;//soap
const int JUHUA_MAXLIFE=1;//juhua

class EnemyLayer :
	public CCLayer
{
public:
	EnemyLayer(void);
	~EnemyLayer(void);

	CREATE_FUNC(EnemyLayer);
	virtual bool init();

	void addSoap(float dt);
	void soapMoveFinished(CCNode* pSender);
	void soapBlowup(Enemy* enemy1);
	void removeSoap(CCNode* pTarget, void* data);
	void removeAllSoap();

	void addJuhua(float dt);
	void juhuaMoveFinished(CCNode* pSender);
	void juhuaBlowup(Enemy* enemy2);
	void removeJuhua(CCNode* pTarget, void* data);
	void removeAllJuhua();
	void removeAllEnemy();

	CCArray* m_pAllSoap;
	CCArray* m_pAllJuhua;

private:
	CCSpriteFrame* soapSpriteFrame;
	CCSpriteFrame* juhuaSpriteFrame;

};

#endif