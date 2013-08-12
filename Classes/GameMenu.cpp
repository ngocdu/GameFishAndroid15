//
//  GameMenu.cpp
//  GameFish
//
//  Created by MinhNT on 13/08/05.
//
//
#include "MapLoading.h"
#include "GameMenu.h"
using namespace cocos2d;
CCScene* GameMenu::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameMenu *layer = GameMenu::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool GameMenu::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!CCLayer::init());
        this->setTouchEnabled(true);
        size = CCDirector::sharedDirector()->getWinSize();
        //bg round
        CCSprite *bground = CCSprite::create("bg_menu.png");
        bground->setPosition(ccp(size.width/2, size.height/2));
        this->addChild(bground);
        CCSprite * feedingfrenzy = CCSprite::create("gamename.png");
        feedingfrenzy->setPosition(ccp(size.width/2, size.height - (40.0f/320 * size.height)));
        this->addChild(feedingfrenzy);
        //menu
        CCMenuItemImage * story_mode = CCMenuItemImage::create("btn_story_mode.png", "btn_story_mode.png",this, menu_selector(GameMenu::click_bt_story_mode));
        story_mode->setPosition(ccp(size.width/2, size.height - (100.0f/320 * size.height)));
        CCMenuItemImage * time_attack = CCMenuItemImage::create("btn_time_attack.png", "btn_time_attack.png",this, menu_selector(GameMenu::click_bt_time_attack));
        time_attack->setPosition(ccp(size.width/2 , size.height - (150.0f/320 * size.height)));
        CCMenuItemImage * more = CCMenuItemImage::create("btn_more.PNG", "btn_more.PNG",this, menu_selector(GameMenu::click_bt_more));
        more->setPosition(ccp(size.width/2 - (1.0f/13 * size.width), size.height - (192.0f/320 * size.height)));
        CCMenuItemImage * option = CCMenuItemImage::create("btn_option.png", "btn_option.png",this, menu_selector(GameMenu::click_bt_option));
        option->setPosition(ccp((265.0f/480 * size.width), size.height - (215.0f/320 * size.height)));
        CCMenuItemImage * high_score = CCMenuItemImage::create("btn_highscore.png", "btn_highscore.png",this, menu_selector(GameMenu::click_bt_high_score));
        high_score->setPosition(ccp((300.0f/480 * size.width), size.height - (260.0f/320 * size.height)));

        CCMenuItemImage * rate_game = CCMenuItemImage::create("btn_rategame.png", "btn_rategame.png",this, menu_selector(GameMenu::click_bt_rate_game));
        rate_game->setPosition(ccp((310.0f/480 * size.width), size.height - (290.0f/320 * size.height)));
        menu = CCMenu::create(story_mode, time_attack, more, high_score, rate_game, option, NULL);
        menu->setPosition(ccp(0, 0));
        this->addChild(menu);
        
        bRet=true;
        
    } while(0);
    
    return bRet;
}
void GameMenu::click_bt_story_mode(cocos2d::CCObject *pSender) {
    CCDirector::sharedDirector()->replaceScene(MapLoading::scene());
}
void GameMenu::click_bt_time_attack(cocos2d::CCObject *pSender) {
    CCDirector::sharedDirector()->replaceScene(MapLoading::scene());
}
void GameMenu::click_bt_high_score(cocos2d::CCObject *pSender) {
    
}
void GameMenu::click_bt_more(cocos2d::CCObject *pSender) {
    
}
void GameMenu::click_bt_option(cocos2d::CCObject *pSender) {
    
}
void GameMenu::click_bt_rate_game(cocos2d::CCObject *pSender) {
    
}