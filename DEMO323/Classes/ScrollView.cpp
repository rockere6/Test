
#include "ScrollView.h"  
#include "ScrollViewScene.h"  
  
ScrollView::ScrollView()  
{  
    m_Page = 0;  
    m_CurPage = 0;  
    m_PageLayer = CCArray::createWithCapacity(8);  
    m_PageLayer->retain();  
      
    init();  
}  
ScrollView::~ScrollView()  
{  
    m_PageLayer->removeAllObjects();  
    m_PageLayer->release();  
}  
  
bool ScrollView::init()  
{  
    bool bRet = false;  
      
    do {  
        CC_BREAK_IF(!CCLayer::init());  
          
        bRet = true;  
    } while (0);  



   // setTouchEnabled(true);  
    //����Ϊ������Ӧ  kCCTouchesOneByOne
  //  setTouchMode(CCTouch::DispatchMode::ONE_BY_ONE);  
      
  /*  auto myListener = EventListenerTouchOneByOne::create();  
    myListener->CCTouchBegan = CC_CALLBACK_2(ScrollView::onTouchBegan, this);  
    myListener->CCTouchMoved = CC_CALLBACK_2(ScrollView::onTouchMoved, this);  
    myListener->CCTouchEnded = CC_CALLBACK_2(ScrollView::onTouchEnded, this);  
    myListener->CCTouchCancelled = CC_CALLBACK_2(ScrollView::onTouchCancelled, this);  
     */ 
      
    return bRet;  
}  
  
void ScrollView::onEnter()  
{  
   CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);    
   CCLayer::onEnter();
}  
  
void ScrollView::onExit()  
{  
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);  
	CCLayer::onExit();  
}  
  
void ScrollView::goToPage()  
{  
    CCMoveTo *moveTo = CCMoveTo::create(0.2f, CCPoint(-m_CurPage * WINDOW_WIDTH, 0));  
      
    this->runAction(moveTo);  
}  
  
void ScrollView::addPage(cocos2d::CCLayer *pPageLayer)  
{  
    if (pPageLayer) {  
        // ���ó�һҳ��С  
        pPageLayer->setContentSize(CCSize(WINDOW_WIDTH, WINDOW_HEIGHT));  
        pPageLayer->setPosition(CCPoint(WINDOW_WIDTH * m_Page, 0));  
        this->addChild(pPageLayer);  
        // ��ӵ�ҳ  
        m_PageLayer->addObject(pPageLayer);  
        m_Page = m_PageLayer->count();  
    }  
}  
  
//������������ҳ����ת  
void ScrollView::gotoUserChoosePage(int _isToOrBack){  
    if (0 == _isToOrBack) {  
        //��һҳ  
        if (m_CurPage > 0) {  
            --m_CurPage;  
        }  
    }else if(1 == _isToOrBack){  
        //��һҳ  
        if (m_CurPage < (m_Page - 1)) {  
            ++m_CurPage;  
        }  
    }  
      
    // ִ����ת����  
    goToPage();  
}  
  
bool ScrollView::ccTouchBegan(CCTouch *pTouch, CCEvent  *pEvent){  
    m_TouchDownPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());  
    m_TouchCurPoint = m_TouchDownPoint;  
      
    return true;  
}  
void ScrollView::ccTouchMoved(CCTouch *pTouch, CCEvent  *pEvent){  
    // �ƶ�  
    CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());  
    CCPoint posPoint = CCPoint(getPositionX() + touchPoint.x - m_TouchCurPoint.x, getPositionY());  
    setPosition(posPoint);  
    m_TouchCurPoint = touchPoint;  
}  
void ScrollView::ccTouchEnded(CCTouch *pTouch, CCEvent  *pEvent){  
    m_TouchUpPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());  
    // ���㰴�º�̧���ƫ����  
    float offset = (m_TouchUpPoint.x - m_TouchDownPoint.x) * (m_TouchUpPoint.x - m_TouchDownPoint.x) + (m_TouchUpPoint.y - m_TouchDownPoint.y) * (m_TouchUpPoint.y - m_TouchDownPoint.y);  
      
    if (offset < (TOUCH_DELTA * TOUCH_DELTA)) {  
        // ���  
        // ����Layer����Click��Ϣ  
        //((CCLayer*) m_PageLayer->objectAtIndex(m_CurPage))->ccTouchBegan(pTouch, pEvent);  
    }  
    else {  
        // ��������  
        int offset = getPositionX() - m_CurPage * (-WINDOW_WIDTH);  
        //if (offset > WINDOW_WIDTH / 2) {  
        if (offset > 50) {  
            // ��һҳ  
            if (m_CurPage > 0) {  
                --m_CurPage;  
                CCSprite *sprite =  (CCSprite *)ScrollViewScene::sharedSC()->getChildByTag(888);  
                sprite->setPosition(CCPoint(sprite->getPositionX()-80,sprite->getPositionY()));  
            }  
        }  
        //else if (offset < -WINDOW_WIDTH / 2) {  
        else if (offset < -50) {  
            // ��һҳ  
            if (m_CurPage < (m_Page - 1)) {  
                ++m_CurPage;  
                CCSprite *sprite =  (CCSprite *)ScrollViewScene::sharedSC()->getChildByTag(888);  
                sprite->setPosition(CCPoint(sprite->getPositionX()+80,sprite->getPositionY()));  
            }  
        }  
          
        // ִ����ת����  
        goToPage();  
    }  
}  
void ScrollView::ccTouchCancelled(CCTouch *pTouch, CCEvent  *pEvent){  
      
} 