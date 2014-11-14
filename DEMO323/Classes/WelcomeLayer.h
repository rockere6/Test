#ifndef WELCOMELAYER_H
#define WELCOMELAYER_H

#include "cocos2d.h"

USING_NS_CC;

class WelcomeLayer :
	public CCLayer
{
public:

	WelcomeLayer(void);

	~WelcomeLayer(void);

	virtual bool init();

	CREATE_FUNC(WelcomeLayer);

	void loadingDone(CCNode* pNode);
};
#endif