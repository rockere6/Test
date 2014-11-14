#ifndef PERSONLAYER_H
#define PERSONLAYER_H

#include "cocos2d.h"

USING_NS_CC;

const int AIRPERSON=747;

class PersonLayer :
	public CCLayer
{
public:

	PersonLayer(void);
	
	~PersonLayer(void);

	static PersonLayer* create();

	virtual bool init();

	void MoveTo(CCPoint location);

	void Blowup(int passScore);

	void RemovePerson();

public:

	static PersonLayer* sharedPerson;

	bool isAlive;

	int score;
};

#endif