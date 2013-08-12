//
//  PlayingScene.cpp
//  GameFish
//
//  Created by MinhNT on 13/08/05.
//
//
#include <cmath>
#include "Fish.h"
#include "PlayingScene.h"
using namespace cocos2d;
CCScene* PlayingScene::scene()
{
    CCScene * scene = NULL;
    do
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        //        CC_BREAK_IF(! scene);
        
        // 'layer' is an autorelease object
        PlayingScene *layer = PlayingScene::create();
        //        CC_BREAK_IF(! layer);
        
        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlayingScene::init()
{
    bool bRet = false;
    do
    {
        size = CCDirector::sharedDirector()->getWinSize();
        SPEED = size .width * 2 / 480 ;
        CC_BREAK_IF(! CCLayer::init());
        
        //bground
        bground = CCSprite::create("map_water_01_3.png");
        bground->setPosition(ccp(size.width/2, size.height/2));
        this->addChild(bground, 0);
        CCSize sizebground = bground->getContentSize();
        
        CCSprite *bground1 = CCSprite::create("map_water_01_1.png");
        bground1->setPosition(ccp(sizebground.width/2, sizebground.height *3/4));
        bground->addChild(bground1, 2);
        
        CCSprite *bground2 = CCSprite::create("map_water_01_2.png");
        bground2->setPosition(ccp(sizebground.width/2, sizebground.height/5));
        bground->addChild(bground2, 1);
        
        //创建瓦片地图
//        this->setTileMap(CCTMXTiledMap::create("pd_tilemap1.tmx"));
//        _tileMap->setAnchorPoint(ccp(0.5f, 0.5f));        //设置瓦片地图的锚点为屏幕正中间
//        _tileMap->setPosition(ccp(size.width/2, size.height/2));                //设置瓦片地图的位置为屏幕左下角
//        this->setBackground(_tileMap->layerNamed("Layer1"));
//        this->addChild(_tileMap, 2, 0);        //加入场景层
        
        //获取Objects对象层
//        CCLOG("_tileMap %d", _tileMap->retainCount());
//        CCTMXObjectGroup *objects = _tileMap->objectGroupNamed("Objects");
//        CCLOG("_tileMap %d", _tileMap->retainCount());
//        CC_BREAK_IF(!objects);    //如果失败，退出
//        
//        //获取SpawnPoint的字典（包含坐标，高和宽等信息）
//        CCDictionary *spawnPoint = objects->objectNamed("SpawnPoint");
//        CC_BREAK_IF(!spawnPoint);    //如果失败，退出
        
        //分别取x和y坐标的值
        //---------------array fish -----------------------
        _arrayFish = new CCArray();
        _arrayFishRemove = new CCArray();

        _fish_player = new Fish("itm_big_fish_301", 15);
        _fish_player->initWithFile("itm_big_fish_301_boidung_1.png");
        _fish_player->setPosition(ccp(size.width/2, size.height /2));
        _fish_player->setScale(1.0f/2);
        _fish_player->setContentSize(CCSize(_fish_player->getContentSize().width/2,
                                            _fish_player->getContentSize().height/2));
        _fish_player->setNumberImage(6);
        _fish_player->boiDung();
        _fish_player->setHuongDiChuyen(1);
        _fish_player->setIsPlayer(true);
        _arrayFish->addObject(_fish_player);

        _fish_player->setHead(ccp(_fish_player->getPosition().x + _fish_player->getContentSize().width/2,
                                  _fish_player->getPosition().y ));
        this->addChild(_fish_player, 3);
//        this->addFishPlayer();
        
        //------------------time --------------------
        _time_delay = 5;
        _protected_fish_player = true;
        
        //创建摇杆下面部分
        CCSprite *joystick1 = CCSprite::create("control_bg.png");
        joystick1->setAnchorPoint(ccp(0, 0));
        joystick1->setPosition(ccp(5, 5));
        
        CCSprite *joystick2 = CCSprite::create("btn_power_full.png");
        joystick2->setAnchorPoint(ccp(0, 0));
        joystick2->setPosition(ccp(15, 15));
        this->addChild(joystick2, 3);
        //大圆半径
        R=joystick1->getContentSize().width/2;
        //中心点
        O = ccp(R, R);
        //添加进布景
        this->addChild(joystick1, 3);
        
        //创建摇杆上面圆圈部分
        joystick = CCSprite::create("control_center.png");
        //设置位置为摇杆中心点并添加进布景
        joystick->setPosition(ccp(O.x + 5, O.y + 5));
        this->addChild(joystick, 4);
        
        //初始化需要的变量
        isFlying = false;
        speedX = speedY = 0;
        speedMapX = speedMapY = 0;
        //设置可触摸
        this->setTouchEnabled(true);
        
        //每帧要执行的函数
        this->schedule(schedule_selector(PlayingScene::flying));
        
        //----------------add menu-----------------
        CCMenuItemImage * bt_pw = CCMenuItemImage::create("btn_power_center_full.png", "btn_power_center.png",this, menu_selector(PlayingScene::click_bt_Pw));
        bt_pw->setPosition(ccp(size.width * (435.0f/480), size.height - (280.0f/320 * size.height)));
        CCSprite * bg_pw = CCSprite::create("btn_power_bg.png");
        bg_pw->setPosition(ccp(size.width * (435.0f/480), size.height - (280.0f/320 * size.height)));
        this->addChild(bg_pw, 10);
        
        CCMenuItemImage * bt_jump = CCMenuItemImage::create("btn_jump.png", "btn_jump.png",this, menu_selector(PlayingScene::click_bt_Jump));
        bt_jump->setPosition(ccp(size.width * (450.0f/480), size.height - (215.0f/320 * size.height)));
        
        CCMenuItemImage * bt_pass = CCMenuItemImage::create("btn_pass.png", "btn_pass.png",this, menu_selector(PlayingScene::click_bt_Pass));
        bt_pass->setPosition(ccp(size.width * (365.0f/480), size.height - (290.0f/320 * size.height)));
        
        CCMenuItemImage * bt_pause = CCMenuItemImage::create("bg_header_common.png", "bg_header_common.png",this, menu_selector(PlayingScene::click_bt_Pause));
        bt_pause->setPosition(ccp((450.0f/480 * size.width), size.height - (25.0f/320 * size.height)));
        
        CCSprite *image_ox = CCSprite::create("bg_header_common.png");
        image_ox->setPosition(ccp((400.0f/480 * size.width), size.height - (25.0f/320 * size.height)));
        this->addChild(image_ox, 10);
        
        CCSprite *image_3 = CCSprite::create("bg_header_common.png");
        image_3->setPosition(ccp((350.0f/480 * size.width), size.height - (25.0f/320 * size.height)));
        this->addChild(image_3, 10);
        
        menu = CCMenu::create(bt_pw, bt_jump, bt_pass, bt_pause, NULL);
        menu->setPosition(ccp(0, 0));
        this->addChild(menu);
        
        CCSprite *bg_clock = CCSprite::create("btn_clock.png");
        bg_clock->setPosition(ccp((255.0f/480 * size.width), size.height - (25.0f/320 * size.height)));
        this->addChild(bg_clock, 10);
        
        CCSprite *bg_score = CCSprite::create("stageframe.png");
        bg_score->setPosition(ccp((90.0f/480 * size.width), size.height - (25.0f/320 * size.height)));
        this->addChild(bg_score, 10);

        //-----------label--------------
        _lifes = 3;
        _point = 0;
        _numberFish1 = 0;
        _numberFish2 = 0;
        _numberFish3 = 0;

        char strLife[20] = {0};
        sprintf(strLife, "X%i", _lifes);
        _lb_life = CCLabelTTF::create(strLife, "Time new", 25 );
        _lb_life->setColor(ccBLACK);
        _lb_life->setPosition(image_ox->getPosition());
        this->addChild(_lb_life, 10);

        char strPoint[20] = {0};
        sprintf(strPoint, "%i", _point);
        _lb_point = CCLabelTTF::create(strPoint, "Time new", 25 );
        _lb_point->setColor(ccBLACK);
        _lb_point->setPosition(ccp((90.0f/480 * size.width), size.height -
                                   (15.0f/320 * size.height)));
        this->addChild(_lb_point, 10);
        //---------------fish-----------------
        _fish1 = new Fish("itm_small_fish_101", 10);
        _fish1->initWithFile("itm_small_fish_101_1.png");
        _fish1->setNumberImage(3);
        _fish2 = new Fish("itm_medium_fish_201", 20);
        _fish2->initWithFile("itm_medium_fish_201_boidung_1.png");
        _fish2->setNumberImage(6);
        _fish3 = new Fish("itm_big_fish_301", 40);
        _fish3->initWithFile("itm_medium_fish_201_boidung_1.png");
        _fish3->setNumberImage(6);
        //----------------------update------------------------------
        this->schedule(schedule_selector(PlayingScene::updateVitri), 1.0f/3);
        this->schedule(schedule_selector(PlayingScene::update), 1.0f/60);
        this->schedule(schedule_selector(PlayingScene::updateAddFish), 3.0f);
        this->schedule(schedule_selector(PlayingScene::updateRemove), 1.0f/10);
        this->schedule(schedule_selector(PlayingScene::updateLable), 1.0f/10);
        this->schedule(schedule_selector(PlayingScene::updateTime), 1);
        bRet = true;
    } while (0);
    
    return bRet;
}

void PlayingScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch*)pTouches->anyObject();
    CCPoint location = touch->getLocation();
    
    CCRect rect=joystick->boundingBox();
    if (rect.containsPoint(location))
    {
        isFlying=true;
    }
}

void PlayingScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch*)pTouches->anyObject();
    CCPoint location = touch->getLocation();
    
    //判断触摸滑动点是否在摇杆范围内
    bool inRange = pow(O.x - location.x, 2) + pow(O.y - location.y, 2) < pow(R, 2);
    if (isFlying && inRange)
    {
        CCPoint position=_fish_player->getPosition();
        CCPoint pointBg = bground->getPosition();
        joystick->setPosition(location);
        CCSize sizeMap = bground->getContentSize();
        float r = R * 2 / 6;
        float d = R * 2 / 3;
        CCPoint pointPlane = _fish_player->getPosition();
        // len tren
        if(triangleContainPoint(O.x, O.y, O.x - r, O.y + r, O.x  +r, O.y + r, location.x, location.y)
           || CCRectMake(O.x - r, O.y + r, d, d).containsPoint(location))
        {
            speedX=0;
            speedY= SPEED;
        }
        
        //xuong duoi
        else if (triangleContainPoint(O.x, O.y, O.x - r, O.y - r, O.x + r, O.y - r, location.x, location.y)
                 || CCRectMake(O.x - r, O.y - r - d, d, d).containsPoint(location))
        {
            speedX = 0;
            speedY = -SPEED;
        }
        
        //sang trai
        else if (triangleContainPoint(O.x, O.y, O.x - r, O.y + r, O.x - r, O.y - r, location.x, location.y) || CCRectMake(O.x - r - d, O.y - r, d, d).containsPoint(location))
        {
            speedX = -SPEED;
            speedY = 0;
        }
        
        //sang phai
        else if (triangleContainPoint(O.x, O.y, O.x + r, O.y + r, O.x + r, O.y - r, location.x, location.y)
                 || CCRectMake(O.x + r, O.y - r, d, d).containsPoint(location))
        {
            speedX = SPEED;
            speedY = 0;
        }
        
        //phai tren
        else if (location.x - (O.x + r) > 0 && location.y - (O.y + r) > 0)
        {
            speedX=0.7f * SPEED;
            speedY=0.7f * SPEED;
        }
        //trai tren
        else if (location.x - (O.x - r) < 0 && location.y - (O.y + r) > 0)
        {
            speedX=-0.7f * SPEED;
            speedY=0.7f * SPEED;
        }
        
        //trai duoi
        else if (location.x - (O.x - r) < 0 && location.y - (O.y - r) < 0)
        {
            speedX=-0.7f * SPEED;
            speedY=-0.7f * SPEED;
        }
        
        //phai duoi
        else if (location.x - (O.x + r) > 0 && location.y - (O.y - r) < 0)
        {
            speedX=0.7f * SPEED;
            speedY=-0.7f * SPEED;
        }
    }
}

void PlayingScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    isFlying = false;
    joystick->setPosition(ccp(O.x + 5, O.y + 5));
    speedX = speedY = 0;
    speedMapX = speedMapY = 0;
}
void PlayingScene::flying(float dt)
{
    if (isFlying && (speedX != 0 || speedY != 0))
    {
        CCSize sizeMap = bground->getContentSize();
        float scalex = (float)(sizeMap.width - size.width)/size.width   * 1.0f;
        float scaley = (float)(sizeMap.height - size.height)/size.height  * 1.0f;
        //飞机飞行
        CCPoint position=ccp(_fish_player->getPosition().x + speedX, _fish_player->getPosition().y + speedY);
        CCPoint position_tilemap = ccp(bground->getPosition().x - speedX * scalex, bground->getPosition().y - speedY * scaley);
        CCRect rect=CCRectMake(0 + _fish_player->getContentSize().width * _fish_player->getScale() /4,
                               0 + _fish_player->getContentSize().height * _fish_player->getScale() /4,
                               size.width - _fish_player->getContentSize().width / 4 * _fish_player->getScale(),
                               size.height - _fish_player->getContentSize().height / 4 * _fish_player->getScale());
        
        //判断触摸点是否在屏幕内
        if(rect.containsPoint(position))
        {
            _fish_player->setPosition(position);
            bground->setPosition(position_tilemap);
        }
    }
}

float PlayingScene::heronsformula(float x1,float y1,float x2,float y2,float x3,float y3)
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
bool PlayingScene::triangleContainPoint(float x1,float y1,float x2,float y2,float x3,float y3,float px,float py)
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
    return (float)abs((float)s-(float)(s1+s2+s3)) < 0.001f;
}
float PlayingScene::caculateSpeed(float v, float s1, float s2) {
    //return v2
    return  (float)s2 / (s1 + s2) * v;
    //return v1
    //return s1 / (s1 + s2) * v;
}
void PlayingScene::click_bt_Pw(cocos2d::CCObject *pSender) {
    
}
void PlayingScene::click_bt_Jump(cocos2d::CCObject *pSender) {
    
}
void PlayingScene::click_bt_Pass(cocos2d::CCObject *pSender) {
    
}
void PlayingScene::click_bt_Pause(cocos2d::CCObject *pSender) {
    
}
void PlayingScene::updateVitri(float dt) {
    _fish_player->setViTri(_fish_player->getPosition());
    CCObject *i;
    CCARRAY_FOREACH(_arrayFish, i) {
        Fish *f = (Fish*)i;
        f->setViTri(f->getPosition());
        if (f->getHuongDiChuyen() == 0) {
            f->setHead(ccp(f->getPosition().x - f->getContentSize().width/2,
                           f->getPosition().y ));
        }else if (f->getHuongDiChuyen() == 1) {
            f->setHead(ccp(f->getPosition().x + f->getContentSize().width/2,
                           f->getPosition().y ));
        }


    }
}
void PlayingScene::update(float dt) {
    CCObject * i;
    CCARRAY_FOREACH(_arrayFish, i) {
        Fish *f = (Fish*)i;
        //------------------array fish ------di chuyen dung chieu---------------
        CCPoint vitritruoc=f->getViTri();
        CCPoint vitrisau=f->getPosition();
        //neu di chuyen  sang trai va huong di chuyen sang phai
        if(vitrisau.x < vitritruoc.x && f->getHuongDiChuyen()==1)
        {
            f->setHuongDiChuyen(0);
            f->setFlipX(true);
        }
        //neu di chuyen sang phai va huong di chuyen sang trai
        else if(vitrisau.x > vitritruoc.x && f->getHuongDiChuyen()==0) {
            f->setHuongDiChuyen(1);
            f->setFlipX(false);
        }
        //--------------------gap con ca khac -----an hoac bi an----------------
        CCObject *j;
        CCARRAY_FOREACH(_arrayFish, j) {
            Fish *f2 = (Fish*)j;
            if (f->getPoint() != f2->getPoint()) {
                if (f->getPoint() > f2->getPoint()) {
                    int kc = ccpDistance(f->getHead(), f2->getPosition());
                    if (kc < f2->getContentSize().width * f2->getScale() / 2) {
                        if (f2->getPoint() == 20) _numberFish1 = _numberFish1 - 1;
                        else if (f2->getPoint() == 40) _numberFish2 = _numberFish2 - 1;
                        else if (f2->getPoint() == 80) _numberFish3 = _numberFish3 - 1;

                        if (f->isEqual(_fish_player)) {
                            _point = _point + f2->getPoint();
                        }
                        if (f2->isEqual(_fish_player) && _protected_fish_player == false) {
                            f->dopMoi();
                            _lifes --;
                            _arrayFishRemove->addObject(_fish_player);
                            this->addFishPlayer();
                        }else if (!f2->isEqual(_fish_player)) {
                            _arrayFishRemove->addObject(f2);
                            f->dopMoi();
                        }                        }
                }else if (f->getPoint() < f2->getPoint()){
                    int kc = ccpDistance(f2->getHead(), f->getPosition());
                    if (kc < f->getContentSize().width * f->getScale() / 2) {
                        if (f->getPoint() == 20) _numberFish1 = _numberFish1 - 1;
                        else if (f->getPoint() == 40) _numberFish2 = _numberFish2 - 1;
                        else if (f->getPoint() == 80) _numberFish3 = _numberFish3 - 1;


                        if (f2->isEqual(_fish_player)) {
                            _point = _point + f->getPoint();
                        }
                        if (f->isEqual(_fish_player) && _protected_fish_player == false) {
                            _lifes --;
                            _arrayFishRemove->addObject(_fish_player);
                            this->addFishPlayer();
                            f2->dopMoi();
                        }else if (!f->isEqual(_fish_player)) {
                            f2->dopMoi();
                            _arrayFishRemove->addObject(f);
                        }
                    }
                }
            }
        }
    }  
}
void PlayingScene::updateRemove(float dt) {
    CCObject * i;
    CCARRAY_FOREACH(_arrayFishRemove, i) {
        Fish *f = (Fish*)i;
        _arrayFish->removeObject(f);
        this->removeChild(f, true);
    }
}
void PlayingScene::addFish(Fish * fish)
{
	int tm1=0,tm2=3,tmtb=tm2-tm1;
	//set chi so thong minh cho con ca them vao - cai nay lay random  de cho co con ngu co  khon the moi hay :)
	fish->setChiSoThongMinh((rand() % tmtb));
	
	CCSize winsize = bground->getContentSize();
	float maxY=winsize.height - fish->getContentSize().height/2;
	float minY=fish->getContentSize().height/2;
	int rangeY=maxY-minY;
 	float toado1=(float)winsize.width + (fish->getContentSize().width/2);
	float toado2=0-(float)(fish->getContentSize().width*2);
	float resultX = 0;
    
	int checking = CCRANDOM_0_1() + 0.5;
    
	if (checking == 0) {
		resultX = toado1;
		fish->setHuongDiChuyen(0);
		fish->setFlipX(true);//neu con ca chay tu ben phai sang thi quay dau no  lai truoc da
	} else {
		resultX = toado2;
		fish->setHuongDiChuyen(1);	
	}
	fish->setNhom(0);
	fish->setPosition(ccp(resultX,(float)(rand() % rangeY ) + minY));
    fish->setHead(ccp(fish->getPosition().x + fish->getContentSize().width/2,
                      fish->getPosition().y ));
    _arrayFish->addObject(fish);
	//them con ca vao man hinh game
	this->addChild(fish, 0, 10);
    fish->diChuyen();
    fish->boiDung();
}
void PlayingScene::updateAddFish(float dt) {
    if (_numberFish1 < 30) {
        Fish *f = new Fish(_fish1->getName(), _fish1->getPoint());
        f->initWithFile("itm_small_fish_101_1.png");
        f->setNumberImage(_fish1->getNumberImage());
        f->setIsPlayer(false);
        f->setVanToc(45);
        _numberFish1 = _numberFish1 + 1;
        this->addFish(f);

    }
    if (_numberFish2 < 5) {
        Fish *f = new Fish(_fish2->getName(), _fish2->getPoint());
        f->initWithFile("itm_small_fish_101_1.png");
        f->setNumberImage(_fish2->getNumberImage());
         f->setIsPlayer(false);
        f->setVanToc(30);
        _numberFish2 = _numberFish2 + 1;
        this->addFish(f);

    }
    if (_numberFish3 < 3) {
        Fish *f = new Fish(_fish3->getName(), _fish3->getPoint());
        f->initWithFile("itm_small_fish_101_1.png");
        f->setNumberImage(_fish3->getNumberImage());
        f->setIsPlayer(false);
        f->setVanToc(20);
        _numberFish3 = _numberFish3 + 1;
        this->addFish(f);

    }
}
void PlayingScene::updateLable(float dt) {
    char strLife[20] = {0};
    sprintf(strLife, "X%i", _lifes);
    _lb_life->setString(strLife);

    char strPoint[20] = {0};
    sprintf(strPoint, "%i", _point);
    _lb_point->setString(strPoint);

    if (_point > 100) {
        _fish_player->setPoint(30);
        _fish_player->setScale(3.0f/4);
    }
    if (_point > 300) {
        _fish_player->setPoint(45);
        _fish_player->setScale(5.0f/4);
    }
}
void PlayingScene::updateTime(float dt) {
    if (_time_delay > 0) {
        _time_delay = _time_delay - 1;
        _protected_fish_player = true;
    }
    if (_time_delay <= 0)
        _protected_fish_player = false;
}
void PlayingScene::addFishPlayer() {

    _fish_player = new Fish("itm_big_fish_301", 15);
    _fish_player->initWithFile("itm_big_fish_301_boidung_1.png");
    _fish_player->setPosition(ccp(size.width/2, size.height /2));
    _fish_player->setScale(1.0f/2);
    _fish_player->setContentSize(CCSize(_fish_player->getContentSize().width/2,
                                        _fish_player->getContentSize().height/2));
    _fish_player->setNumberImage(6);
    _fish_player->boiDung();
    _fish_player->setHuongDiChuyen(1);
    _fish_player->setIsPlayer(true);
    _arrayFish->addObject(_fish_player);

    _fish_player->setHead(ccp(_fish_player->getPosition().x + _fish_player->getContentSize().width/2,
                              _fish_player->getPosition().y ));
    _time_delay = 5;
    _protected_fish_player = true;
//    CCMoveTo * movedown = CCMoveTo::create(0.5f, ccp(size.width/2, size.height/2));
//    CCMoveTo * moveup = CCMoveTo::create(0.0f, ccp(size.width/2, size.height - 50));
//    CCSequence *sq = CCSequence::create(moveup, movedown, NULL);
//    _fish_player->runAction(movedown);

    this->addChild(_fish_player, 13);

}
