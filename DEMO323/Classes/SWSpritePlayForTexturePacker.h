#ifndef __Holdtail__SWSpritePlayForTexturePacker__  
#define __Holdtail__SWSpritePlayForTexturePacker__  
  
#include <iostream>  
#include "cocos2d.h"  
  
using namespace cocos2d;  
  
class SWSpritePlayForTexturePacker:public cocos2d::CCSprite{  
public:  
    //ʵ��������ͼƬ����  
    static SWSpritePlayForTexturePacker *createPlay(const char *fileName,int startCount,int allCount,float sprit,bool isrun);  
private:  
    //��ʼ��  
    void playInit(const char *fileName,int startCount,int allCount,float sprit,bool isrun);  
    //����Ķ�̬����  �ļ����� �ļ���ʼλ�� �ļ�֡��  �����ٶ�  �Ƿ�ѭ��  
    void createAnimate(const char *fileName,int startCount,int allCount,float sprit,bool isrun);  
      
};  
#endif /* defined(__Holdtail__SWSpritePlayForTexturePacker__) */ 