#ifndef ScrollView_ScrollViewScene_h  
#define ScrollView_ScrollViewScene_h  
  
#include "cocos2d.h"  
  
USING_NS_CC;  
  
class ScrollViewScene: public CCScene  
{  
      
public:  
    ScrollViewScene();  
    virtual bool init();  
    CREATE_FUNC(ScrollViewScene);  
      
    void menuCloseCallback(CCObject* pSender);  
      
    static ScrollViewScene *sharedSC();  
};  
  
#endif 