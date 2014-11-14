 
#ifndef __Holdtail__ScorllMainLayer02__  
#define __Holdtail__ScorllMainLayer02__  
  
#include <iostream>  
#include "cocos2d.h"  
  
USING_NS_CC;  
  
class ScorllMainLayer02: public CCLayer  
{  
public:  
    ScorllMainLayer02();  
    ~ScorllMainLayer02();  
      
    virtual bool init();  
      
    CREATE_FUNC(ScorllMainLayer02);  
      
    void menuCloseCallback01(CCObject* pSender);       
};  
  
#endif /* defined(__Holdtail__ScorllMainLayer0101__) */  