#include "LevelGame08.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

extern bool isMusic;  
static bool flagMusic =false;

LevelGame08::LevelGame08(void)
{
	_welcomeLayer=NULL;
}

LevelGame08::~LevelGame08(void)
{
}

CCScene* LevelGame08::createScene()  
{  
    CCScene *scene = CCScene::create();  
    CCLayer *layer = LevelGame08::create();  
    scene->addChild(layer);  
	//scene->autorelease(); 
    return scene;  
} 

bool LevelGame08::init()
{

	CCUserDefault::sharedUserDefault()->setIntegerForKey("level_8", 1);
	CCUserDefault::sharedUserDefault()->flush();	
	flagMusic = false;
	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("back2.mp3",true);
		flagMusic = true;
	}

	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		_welcomeLayer=WelcomeLayer::create();
		CC_BREAK_IF(!_welcomeLayer);
		this->addChild(_welcomeLayer);
		bRet=true;
	} while (0);

	return bRet;
}