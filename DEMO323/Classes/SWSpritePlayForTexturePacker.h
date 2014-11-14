#ifndef __Holdtail__SWSpritePlayForTexturePacker__  
#define __Holdtail__SWSpritePlayForTexturePacker__  
  
#include <iostream>  
#include "cocos2d.h"  
  
using namespace cocos2d;  
  
class SWSpritePlayForTexturePacker:public cocos2d::CCSprite{  
public:  
    //实例化传入图片名称  
    static SWSpritePlayForTexturePacker *createPlay(const char *fileName,int startCount,int allCount,float sprit,bool isrun);  
private:  
    //初始化  
    void playInit(const char *fileName,int startCount,int allCount,float sprit,bool isrun);  
    //精灵的动态表现  文件名称 文件开始位置 文件帧数  精灵速度  是否循环  
    void createAnimate(const char *fileName,int startCount,int allCount,float sprit,bool isrun);  
      
};  
#endif /* defined(__Holdtail__SWSpritePlayForTexturePacker__) */ 