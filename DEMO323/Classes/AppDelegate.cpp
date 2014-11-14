#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
	
	//匹配分辨率
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1280,720,kResolutionNoBorder);

	//预加载背景音乐和音效  加载地方要在刚进入
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("back2.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("back1.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("button.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("win.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("lose.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("boom.wav");
    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
