#include "ScrollViewScene.h"  
#include "ScrollView.h"  
#include "ScorllMainLayer01.h"  
#include "ScorllMainLayer02.h" 
#include "ScorllMainLayer03.h" 
#include "ScorllMainLayer04.h" 
#include "ScorllMainLayer05.h" 
#include "ScorllMainLayer06.h" 
#include "ScorllMainLayer07.h" 
#include "ScorllMainLayer08.h" 
#include "HelloWorldScene.h"  
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
//using namespace CocosDenshion;  
//声明静态变量  
extern bool isMusic;  
static bool flagMusic = false;


static ScrollView *scrollView;  
  
static ScrollViewScene *sc;  
  
ScrollViewScene *ScrollViewScene::sharedSC(){  
    if(sc != NULL){  
        return sc;  
    }  
    return  NULL;  
}  
  
ScrollViewScene::ScrollViewScene()  
{  
      
}  
  
  
bool ScrollViewScene::init()  
{  
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
    sc = this;  
      
    bool bRet = false;  
      
    do {  
        CC_BREAK_IF(!CCScene::init());  
        scrollView = ScrollView::create();  
          
        for (int i=0; i<8; ++i) {  
            if (0==i) {  
                ScorllMainLayer01 *layer = ScorllMainLayer01::create();  
                layer->setTag(i);  
                scrollView->addPage(layer);  
            }else if(1==i){  
                ScorllMainLayer02 *layer = ScorllMainLayer02::create();  
                layer->setTag(i);  
                scrollView->addPage(layer);  
            }else if(2==i){  
                ScorllMainLayer03 *layer = ScorllMainLayer03::create();  
                layer->setTag(i);  
                scrollView->addPage(layer);  
            }else if(3==i){  
                ScorllMainLayer04 *layer = ScorllMainLayer04::create();  
                layer->setTag(i);  
                scrollView->addPage(layer);  
            }else if(4==i){  
                ScorllMainLayer05 *layer = ScorllMainLayer05::create();  
                layer->setTag(i);  
                scrollView->addPage(layer);  
            }else if(5==i){  
                ScorllMainLayer06 *layer = ScorllMainLayer06::create();  
                layer->setTag(i);  
                scrollView->addPage(layer);  
            }else if(6==i){  
                ScorllMainLayer07 *layer = ScorllMainLayer07::create();  
                layer->setTag(i);  
                scrollView->addPage(layer);  
            }else if(7==i){  
                ScorllMainLayer08 *layer = ScorllMainLayer08::create();  
                layer->setTag(i);  
                scrollView->addPage(layer);  
			}
              
        }  
          
    CCSize size = CCDirector::sharedDirector()->getWinSize();  

    CCSprite* pSprite = CCSprite::create("list-bg.png");
	pSprite->setPosition(ccp(size.width/2 , size.height/2));
	this->addChild(pSprite, 0);

        //初始化信息 
          
        //下面的星星  
        CCSprite* sprite1 =CCSprite::create("dots-1.png"); 
        sprite1->setPosition(ccp(size.width*0.5-280,size.height*0.12));  
        addChild(sprite1);  
		CCSprite* sprite2 =CCSprite::create("dots-1.png"); 
        sprite2->setPosition(ccp(size.width*0.5-200,size.height*0.12));  
        addChild(sprite2);  
        CCSprite* sprite3 =CCSprite::create("dots-1.png"); 
        sprite3->setPosition(ccp(size.width*0.5-120,size.height*0.12));  
        addChild(sprite3);  
        CCSprite* sprite4 =CCSprite::create("dots-1.png"); 
        sprite4->setPosition(ccp(size.width*0.5-40,size.height*0.12));  
        addChild(sprite4);  
        CCSprite* sprite5 =CCSprite::create("dots-1.png"); 
        sprite5->setPosition(ccp(size.width*0.5+40,size.height*0.12));  
        addChild(sprite5);    
        CCSprite* sprite6 =CCSprite::create("dots-1.png"); 
        sprite6->setPosition(ccp(size.width*0.5+120,size.height*0.12));  
        addChild(sprite6);  
        CCSprite* sprite7 =CCSprite::create("dots-1.png"); 
        sprite7->setPosition(ccp(size.width*0.5+200,size.height*0.12));  
        addChild(sprite7); 
		CCSprite* sprite8 =CCSprite::create("dots-1.png"); 
        sprite8->setPosition(ccp(size.width*0.5+280,size.height*0.12));  
        addChild(sprite8); 
          
		CCSprite* sprite =CCSprite::create("dots-2.png"); 
        sprite->setPosition(ccp(size.width*0.5-280,size.height*0.12));  
        sprite->setTag(888);  
        addChild(sprite);  
          
          
	/*CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "back-1.png",
                                        "back-2.png",
                                        this,
                                        menu_selector(ScrollViewScene::menuCloseCallback)); */
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create();
	pCloseItem->setNormalSpriteFrame(cache->spriteFrameByName("back-1.png"));
	pCloseItem->setSelectedSpriteFrame(cache->spriteFrameByName("back-2.png"));
	pCloseItem->initWithTarget(this,menu_selector(ScrollViewScene::menuCloseCallback));
	pCloseItem->setPosition(ccp(size.width*0.1,size.height*0.1));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
          
        this->addChild(scrollView);  
        bRet = true;  
    } while (0);  

	if(isMusic == true)
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("back1.mp3",true);
		flagMusic = true;
	}      

    return bRet;  
}  
  
void ScrollViewScene::menuCloseCallback(CCObject* pSender){  
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HelloWorld::scene()));  
}  