 
#ifndef ScrollView_ScrollView_h  
#define ScrollView_ScrollView_h  
  
#include "cocos2d.h"  
  
USING_NS_CC;  
  
// ��Ļ�ߴ�  
const float WINDOW_WIDTH = 1280.0f;  
const float WINDOW_HEIGHT = 720.0f;  
  
// �������  
const int TOUCH_DELTA = 20;  
  
class ScrollView: public CCLayer//,public CCTargetedTouchDelegate  
{  
private:  
    // ���µ�  
    CCPoint m_TouchDownPoint;  
    // ̧��� ���ʹ���ж��Ƿ�Ϊ����¼�  
    CCPoint m_TouchUpPoint;  
    // ��ǰ������  
    CCPoint m_TouchCurPoint;  
      
private:  
    // ��ҳ��  
    int m_Page;  
    // ��ǰ��ʾҳ  
    int m_CurPage;  
      
private:  
    // �洢����ҳ��  
    CCArray *m_PageLayer;  
      
private:  
    // ��תҳ  
    void goToPage();  
      
public:  
    ScrollView();  
    ~ScrollView();  
      
    virtual bool init();  
      
    CREATE_FUNC(ScrollView);  
  
public:  
    // ��ʼ�����  
    virtual void onEnter();  
    virtual void onExit();  
      
    // �����¼����  
    bool ccTouchBegan(CCTouch *pTouch, CCEvent  *pEvent);  
    void ccTouchMoved(CCTouch *pTouch, CCEvent  *pEvent);  
    void ccTouchEnded(CCTouch *pTouch, CCEvent  *pEvent);  
    void ccTouchCancelled(CCTouch *pTouch, CCEvent  *pEvent);  
      
public:  
    // ���ҳ  
    void addPage(CCLayer *pPageLayer);  
    //����������תҳ��  
    void gotoUserChoosePage(int _isToOrBack);  
  
};  
  
#endif 