//
//  PlayingScene.h
//  GameFish
//
//  Created by MinhNT on 13/08/05.
//
//

#ifndef GameFish_PlayingScene_h
#define GameFish_PlayingScene_h
#include "Fish.h"
#include "cocos2d.h"
USING_NS_CC;

class PlayingScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    // implement the "static node()" method manually
    CREATE_FUNC(PlayingScene);
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    
    float heronsformula(float x1,float y1,float x2,float y2,float x3,float y3);
    bool triangleContainPoint(float x1,float y1,float x2,float y2,float x3,float y3,float px,float py);
    void flying(float dt);
    float caculateSpeed(float v, float s1, float s2);
    
    CC_SYNTHESIZE(cocos2d::CCTMXTiledMap*, _tileMap, TileMap);
    CC_SYNTHESIZE(cocos2d::CCTMXLayer*, _background, Background);
    
//    CC_SYNTHESIZE(CCArray *, _arrayFish, ArrayFish);
    
    //--------------------------------------------------------------------------
    void click_bt_Pw(CCObject* pSender);
    void click_bt_Pass(CCObject* pSender);
    void click_bt_Jump(CCObject* pSender);
    void click_bt_Pause(CCObject* pSender);
    
    //---------------update-----------------------------------------------------
    void updateVitri(float dt);
    void update(float dt);
    void updateAddFish(float dt);
    void updateRemove(float dt);
    void updateLable(float dt);
    void updateTime(float dt);
    //---------------add fish---------------------------------------------------
    void addFish(Fish * fish);
    void addFishPlayer();
    
private:
    int SPEED ;
    CCSize size ;
    cocos2d::CCSprite *joystick;
    cocos2d::CCSprite *bground;
    //中心点O
    cocos2d::CCPoint O;
    //大圆半径
    float R;
    //飞机飞行的速度分量值
    float speedX;
    float speedY;
    float speedMapX;
    float speedMapY;
    //是否飞行的标志
    bool isFlying;
    //-------------------------------
    CCMenu *menu;
    //-------------fish-------
    Fish *_fish_player;
    Fish *_fish1;
    Fish *_fish2;
    Fish *_fish3;
    //------------array fish
    CCArray * _arrayFish;
    CCArray * _arrayFishRemove;
    int _numberFish1;
    int _numberFish2;
    int _numberFish3;
    //label point , time
    int _lifes;
    int _point;
    int _time_delay;
    bool _protected_fish_player;
    CCLabelTTF *_lb_point;
    CCLabelTTF *_lb_time;
    CCLabelTTF *_lb_life;
};
#endif
