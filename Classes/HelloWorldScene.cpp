#include "HelloWorldScene.h"
using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
//        CC_BREAK_IF(! scene);
        
        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
//        CC_BREAK_IF(! layer);
        
        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	size = CCDirector::sharedDirector()->getWinSize();
    bool bRet = false;
    do
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////
        
        CC_BREAK_IF(! CCLayer::init());
        
        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////
        
        // 1. Add a menu item with "X" image, which is clicked to quit the program.
        
        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                              "CloseNormal.png",
                                                              "CloseSelected.png",
                                                              this,
                                                              menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);
        
        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));
        
        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);
        
        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 5);
        
        //bground
        bground = CCSprite::create("nen1.jpg");
        bground->setPosition(ccp(size.width/2, size.height/2)); 
        this->addChild(bground, 3);
        //创建瓦片地图
        this->setTileMap(CCTMXTiledMap::create("pd_tilemap1.tmx"));
        _tileMap->setAnchorPoint(ccp(0.5f, 0.5f));        //设置瓦片地图的锚点为屏幕正中间
        _tileMap->setPosition(ccp(size.width/2, size.height/2));                //设置瓦片地图的位置为屏幕左下角
        this->setBackground(_tileMap->layerNamed("Layer1"));
        this->addChild(_tileMap, 2, TileMapNode);        //加入场景层
        
        //获取Objects对象层
        CCLOG("_tileMap %d", _tileMap->retainCount());
        CCTMXObjectGroup *objects = _tileMap->objectGroupNamed("Objects");
        CCLOG("_tileMap %d", _tileMap->retainCount());
        CC_BREAK_IF(!objects);    //如果失败，退出
        
        //获取SpawnPoint的字典（包含坐标，高和宽等信息）
        CCDictionary *spawnPoint = objects->objectNamed("SpawnPoint");
        CC_BREAK_IF(!spawnPoint);    //如果失败，退出
        
        //分别取x和y坐标的值
        
        plane = CCSprite::create("hartnett.jpg");
        plane->setPosition(ccp(size.width/2, size.height/2));
        plane->setScale(0.3f);
        this->addChild(plane, 3);
        
        //创建摇杆下面部分
        CCSprite *joystick1 = CCSprite::create("joystick1.png");
        //设置透明度，锚点，位置
        joystick1->setOpacity(191);
        joystick1->setAnchorPoint(ccp(0, 0));
        joystick1->setPosition(ccp(0, 0));
        joystick1->setColor(ccWHITE);
        //大圆半径
        R=joystick1->getContentSize().width/2;
        //中心点
        O = ccp(R, R);
        //添加进布景
        this->addChild(joystick1, 3);
        
        //创建摇杆上面圆圈部分
        joystick = CCSprite::create("joystick2.png");
        //设置位置为摇杆中心点并添加进布景
        joystick->setPosition(ccp(O.x, O.y));
        joystick->setColor(ccRED);
        joystick->setScale(0.8f);
        this->addChild(joystick, 4);
        
        //初始化需要的变量
        isFlying = false;
        speedX = speedY = 0;
        speedMapX = speedMapY = 0;
        //设置可触摸
        this->setTouchEnabled(true);
        
        //每帧要执行的函数
        this->schedule(schedule_selector(HelloWorld::flying));
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
    
}

void HelloWorld::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch*)pTouches->anyObject();
    CCPoint location = touch->getLocation();
    
    CCRect rect=joystick->boundingBox();
    if (rect.containsPoint(location))
    {
        isFlying=true;
    }
}

void HelloWorld::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch*)pTouches->anyObject();
    CCPoint location = touch->getLocation();
    
    //判断触摸滑动点是否在摇杆范围内
    bool inRange = pow(O.x - location.x, 2) + pow(O.y - location.y, 2) < pow(R, 2);
    if (isFlying && inRange)
    {
        CCPoint position=plane->getPosition();
        CCPoint pointBg = bground->getPosition();
        joystick->setPosition(location);
        CCSize sizeMap = bground->getContentSize();
        float r = R * 2 / 6;
        float d = R * 2 / 3;
        CCPoint pointPlane = plane->getPosition();
        // len tren
        if(triangleContainPoint(O.x, O.y, O.x - r, O.y + r, O.x  +r, O.y + r, location.x, location.y)
           || CCRectMake(O.x - r, O.y + r, d, d).containsPoint(location))
        {
            speedX=0;
            speedY= 1;
        }
        
        //xuong duoi
        else if (triangleContainPoint(O.x, O.y, O.x - r, O.y - r, O.x + r, O.y - r, location.x, location.y)
                 || CCRectMake(O.x - r, O.y - r - d, d, d).containsPoint(location))
        {
            speedX=0;
            speedY= -1;
        }
        
        //sang trai
        else if (triangleContainPoint(O.x, O.y, O.x - r, O.y + r, O.x - r, O.y - r, location.x, location.y) || CCRectMake(O.x - r - d, O.y - r, d, d).containsPoint(location))
        {
                speedX=-1;
                speedY=0;
        }
        
        //sang phai
        else if (triangleContainPoint(O.x, O.y, O.x + r, O.y + r, O.x + r, O.y - r, location.x, location.y)
                 || CCRectMake(O.x + r, O.y - r, d, d).containsPoint(location))
        {
                speedX=1;
                speedY=0;
        }
        
        //phai tren
        else if (location.x - (O.x + r) > 0 && location.y - (O.y + r) > 0)
        {
            speedX=0.7f;
            speedY=0.7f;
        }
        //trai tren
        else if (location.x - (O.x - r) < 0 && location.y - (O.y + r) > 0)
        {
                speedX=-0.7f;
                speedY=0.7f;
        }
        
        //trai duoi
        else if (location.x - (O.x - r) < 0 && location.y - (O.y - r) < 0)
        {
                speedX=-0.7f;
                speedY=-0.7f;
        }
        
        //phai duoi
        else if (location.x - (O.x + r) > 0 && location.y - (O.y - r) < 0)
        {
                speedX=0.7f;
                speedY=-0.7f;
        }
    }
}

void HelloWorld::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    isFlying = false;
    joystick->setPosition(O);
    speedX = speedY = 0;
    speedMapX = speedMapY = 0;
}

void HelloWorld::flying(float dt)
{
    if (isFlying && (speedX != 0 || speedY != 0))
    {
        CCSize sizeMap = bground->getContentSize();
        float scalex = (float)(sizeMap.width-size.width)/size.width  * 1.0f;
        float scaley = (float)(sizeMap.height-size.height)/size.height * 1.0f;
        //飞机飞行
        CCPoint position=ccp(plane->getPosition().x + speedX, plane->getPosition().y + speedY);
        CCPoint position_tilemap = ccp(bground->getPosition().x - speedX * scalex, bground->getPosition().y - speedY * scaley);
        CCRect rect=CCRectMake(0, 0, size.width, size.height);
        
        //判断触摸点是否在屏幕内
        if(rect.containsPoint(position))
        {
            plane->setPosition(position);
            bground->setPosition(position_tilemap);
        }
    }
}

float HelloWorld::heronsformula(float x1,float y1,float x2,float y2,float x3,float y3)
{
    //求边长a
    float a = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    //求边长b
    float b = sqrt(pow(x2 - x3, 2) + pow(y2 - y3, 2));
    //求边长c
    float c = sqrt(pow(x3 - x1, 2) + pow(y3 - y1, 2));
    //求半周长s
    float s = (a + b + c) / 2;
    
    //根据海伦公式返回三角形面积
    return sqrt(s * (s - a) * (s - b) * (s - c));
}  

//判断三个新三角形面积和是否等于原先三角形面积的函数的实现  
bool HelloWorld::triangleContainPoint(float x1,float y1,float x2,float y2,float x3,float y3,float px,float py)  
{  
    //求S1的面积  
    float s1=heronsformula(x1,y1,x2,y2,px,py);  
    //求S2的面积  
    float s2=heronsformula(x2,y2,x3,y3,px,py);  
    //求S3的面积  
    float s3=heronsformula(x3,y3,x1,y1,px,py);  
    //求S的面积  
    float s=heronsformula(x1,y1,x2,y2,x3,y3);  
    
    //返回S是否等于S1,S2,S3的和  
    return abs(s-(s1+s2+s3))<0.001f;  
}
float HelloWorld::caculateSpeed(float v, float s1, float s2) {
    //return v2
    return  (float)s2 / (s1 + s2) * v;
    //return v1
    //return s1 / (s1 + s2) * v;
}
