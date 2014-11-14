#ifndef LevelGame08_H
#define LevelGame08_H

#include "cocos2d.h"  
#include "WelcomeLayer.h"
//#include <sstream>  

USING_NS_CC; 

class LevelGame08 : public cocos2d::CCLayer 
{
	public:  
		LevelGame08(void);

	~LevelGame08(void);

	virtual bool init();
     static cocos2d::CCScene* createScene(); 
	 CREATE_FUNC(LevelGame08);
public:
	WelcomeLayer* _welcomeLayer;
};

#endif