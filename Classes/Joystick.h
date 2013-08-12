//
//  JoyTick.h
//  GameFish
//
//  Created by MinhNT on 13/07/29.
//
//
#include "cocos2d.h"
#ifndef GameFish_Joystick_h
#define GameFish_Joystick_h
using namespace cocos2d;
class Joystick : public CCLayer
{
public:
    
    virtual bool init();
    CCPoint getVelocity() {return velocity;}
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Joystick);
    
    void updateVelocity(CCPoint point);
    void resetJoystick();
    bool handleLastTouch();
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

private:
    
    CCPoint kCenter;
    CCSprite *thumb;
    bool isPressed;
    
    CCPoint velocity;
    CCSprite *sprite;
};
#endif
