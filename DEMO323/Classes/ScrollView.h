 
#ifndef ScrollView_ScrollView_h  
#define ScrollView_ScrollView_h  
  
#include "cocos2d.h"  
  
USING_NS_CC;  
  
// 屏幕尺寸  
const float WINDOW_WIDTH = 1280.0f;  
const float WINDOW_HEIGHT = 720.0f;  
  
// 触摸误差  
const int TOUCH_DELTA = 20;  
  
class ScrollView: public CCLayer//,public CCTargetedTouchDelegate  
{  
private:  
    // 按下点  
    CCPoint m_TouchDownPoint;  
    // 抬起点 配合使用判断是否为点击事件  
    CCPoint m_TouchUpPoint;  
    // 当前触摸点  
    CCPoint m_TouchCurPoint;  
      
private:  
    // 总页数  
    int m_Page;  
    // 当前显示页  
    int m_CurPage;  
      
private:  
    // 存储所有页层  
    CCArray *m_PageLayer;  
      
private:  
    // 跳转页  
    void goToPage();  
      
public:  
    ScrollView();  
    ~ScrollView();  
      
    virtual bool init();  
      
    CREATE_FUNC(ScrollView);  
  
public:  
    // 初始化相关  
    virtual void onEnter();  
    virtual void onExit();  
      
    // 触摸事件相关  
    bool ccTouchBegan(CCTouch *pTouch, CCEvent  *pEvent);  
    void ccTouchMoved(CCTouch *pTouch, CCEvent  *pEvent);  
    void ccTouchEnded(CCTouch *pTouch, CCEvent  *pEvent);  
    void ccTouchCancelled(CCTouch *pTouch, CCEvent  *pEvent);  
      
public:  
    // 添加页  
    void addPage(CCLayer *pPageLayer);  
    //公开方法跳转页面  
    void gotoUserChoosePage(int _isToOrBack);  
  
};  
  
#endif 