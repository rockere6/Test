 
#ifndef __Holdtail__ScorllMainLayer01__  
#define __Holdtail__ScorllMainLayer01__  
  
#include <iostream>  
#include "cocos2d.h"  
  
USING_NS_CC;  
  
class ScorllMainLayer01: public CCLayer  
{  
public:  
    ScorllMainLayer01();  
    ~ScorllMainLayer01();  
      
    virtual bool init();  
      
    CREATE_FUNC(ScorllMainLayer01);  
      
    void menuCloseCallback01(CCObject* pSender);     
};  
  
#endif /* defined(__Holdtail__ScorllMainLayer0101__) */  