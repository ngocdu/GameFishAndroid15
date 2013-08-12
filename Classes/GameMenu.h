//
//  GameMenu.h
//  GameFish
//
//  Created by MinhNT on 13/08/05.
//
//

#ifndef GameFish_GameMenu_h
#define GameFish_GameMenu_h
#include "cocos2d.h"
using namespace cocos2d;
class GameMenu : public CCLayer
{
public:
    
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(GameMenu);
    
    void click_bt_story_mode(CCObject* pSender);
    void click_bt_time_attack(CCObject* pSender);
    void click_bt_more(CCObject* pSender);
    void click_bt_option(CCObject* pSender);
    void click_bt_high_score(CCObject* pSender);
    void click_bt_rate_game(CCObject* pSender);
   private:
    CCSize size;
    CCMenu *menu;
};
#endif
