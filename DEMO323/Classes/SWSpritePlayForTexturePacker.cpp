#include "SWSpritePlayForTexturePacker.h"  
#include "cocos2d.h"  
  
using namespace cocos2d;  
  
SWSpritePlayForTexturePacker *SWSpritePlayForTexturePacker::createPlay(const char *fileName,int startCount,int allCount,float sprit,bool isrun){  
    SWSpritePlayForTexturePacker *spritePlay = new SWSpritePlayForTexturePacker();  
    if(spritePlay && spritePlay->init()/*initWithFile("CloseNormal.png")*/){  
        spritePlay->autorelease();  
        spritePlay->playInit(fileName,startCount,allCount,sprit,isrun);  
        return spritePlay;  
    }  
    return NULL;  
}  
  
//初始化  
void SWSpritePlayForTexturePacker::playInit(const char *fileName,int startCount,int allCount,float sprit,bool isrun){  
    //创建动物的动画  
    createAnimate(fileName,startCount,allCount,sprit,isrun);  
}  
  
void SWSpritePlayForTexturePacker::createAnimate(const char *fileName,int startCount,int allCount,float sprit,bool isrun){  
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();//获取内存中的缓冲图片  
  //  cache->addSpriteFramesWithFile("click_on_the_100_times.plist");
//	CCSpriteBatchNode *batch = CCSpriteBatchNode::create("click_on_the_100_times.png");
//	this->addChild(batch);
//	CCTexture2D *teture = CCTextureCache::
    CCArray *arrypeople = CCArray::create();  
    char str[100]={0};  
    for (int i = startCount; i<=allCount; i++) {  
        if (i<10) {  
            sprintf(str, "%s_0%d.png",fileName,i);  
        }else{  
            sprintf(str, "%s_%d.png",fileName,i);  
        }  
        CCSpriteFrame *frame = cache->spriteFrameByName(str);  
		arrypeople->addObject(frame);  
    }  
    CCAnimation *animationpeople = CCAnimation::createWithSpriteFrames(arrypeople,sprit);  
	animationpeople->createWithSpriteFrames(arrypeople);  
    if (isrun) {  
        animationpeople->setLoops(-1);  
    }else{  
        animationpeople->setLoops(1);  
    }  
      
    //Animate *animatepeople = Animate::create(animationpeople);  
    //this->runAction(RepeatForever::create(animatepeople->reverse()));  
    CCAnimate *animate = CCAnimate::create(animationpeople);  
	//action=CCAnimate::create(animationpeople); 
    this->runAction(animate);  
	
}  