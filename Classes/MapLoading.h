//
//  MapLoading.h
//  GameFish
//
//  Created by MinhNT on 13/08/05.
//
//

#ifndef GameFish_MapLoading_h
#define GameFish_MapLoading_h

#include "cocos2d.h"
using namespace cocos2d;
class MapLoading : public CCLayer
{
public:
    
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(MapLoading);
    
    void click_bt_back(CCObject* pSender);
private:
    CCSize size;
    CCMenu *menu;
    
};



#endif
