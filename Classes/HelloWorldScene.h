#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

enum
{
    TileMapNode = 0,
};


class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    
    float heronsformula(float x1,float y1,float x2,float y2,float x3,float y3);
    bool triangleContainPoint(float x1,float y1,float x2,float y2,float x3,float y3,float px,float py);
    void flying(float dt);
    float caculateSpeed(float v, float s1, float s2);

    CC_SYNTHESIZE(cocos2d::CCTMXTiledMap*, _tileMap, TileMap);
    CC_SYNTHESIZE(cocos2d::CCTMXLayer*, _background, Background);
    
   
        
private:
    
    CCSize size ;
    cocos2d::CCSprite *joystick;
    cocos2d::CCSprite *bground;
    //中心点O
    cocos2d::CCPoint O;
    //大圆半径
    float R;
    
    cocos2d::CCSprite *plane;
    //飞机飞行的速度分量值
    float speedX;
    float speedY;
    float speedMapX;
    float speedMapY;
    //是否飞行的标志
    bool isFlying;
};

#endif  // __HELLOWORLD_SCENE_H__
