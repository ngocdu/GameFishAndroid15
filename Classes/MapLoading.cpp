//
//  MapLoading.cpp
//  GameFish
//
//  Created by MinhNT on 13/08/05.
//
//
#include "GameMenu.h"
#include "MapLoading.h"
using namespace cocos2d;
CCScene* MapLoading::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MapLoading *layer = MapLoading::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool MapLoading::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!CCLayer::init());
        this->setTouchEnabled(true);
        size = CCDirector::sharedDirector()->getWinSize();
        //bg round
        CCSprite *bground = CCSprite::create("bg_maploading.png");
        bground->setPosition(ccp(size.width/2, size.height/2));
        this->addChild(bground);
        
        CCSprite * bt_level = CCSprite::create("btn_level.png");
        bt_level->setPosition(ccp(size.width/2 + 1.0f/22 * size.width, size.height - (300.0f/320 * size.height)));
        this->addChild(bt_level);
        
        CCSprite * map_hd = CCSprite::create("map-hd.png");
        map_hd->setPosition(ccp(size.width/2 , size.height/2));
        this->addChild(map_hd);
        
        //menu
        CCMenuItemImage * back = CCMenuItemImage::create("btn_back_loading.png", "btn_back_loading.png",this, menu_selector(MapLoading::click_bt_back));
        back->setPosition(ccp(size.width * 40/480, size.height - (295.0f/320 * size.height)));
       
        menu = CCMenu::create(back, NULL);
        menu->setPosition(ccp(0, 0));
        this->addChild(menu);
        
        bRet=true;
        
    } while(0);
    
    return bRet;
}
void MapLoading::click_bt_back(cocos2d::CCObject *pSender) {
    CCDirector::sharedDirector()->replaceScene(GameMenu::scene());
}
