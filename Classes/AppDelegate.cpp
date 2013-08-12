//
//  GameFishAppDelegate.cpp
//  GameFish
//
//  Created by MinhNT on 13/07/29.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"
#include "Joystick.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "GameMenu.h"
#include "MapLoading.h"
#include "PlayingScene.h"
using namespace cocos2d;
USING_NS_CC;
using namespace CocosDenshion;
typedef struct tagResource
{
    cocos2d::CCSize size;
    char directory[100];
}Resource;
static Resource smallResource  =  { cocos2d::CCSizeMake(480, 320),   "iPhone" };
static Resource mediumResource =  { cocos2d::CCSizeMake(960, 640),  "iPhone_hd"   };
static Resource largeResource  =  { cocos2d::CCSizeMake(2048, 1536), "ipadhd" };
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(480, 320);
AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
//    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    //--------------------------------------------------------------------------
    std::vector<std::string> searchPath = CCFileUtils::sharedFileUtils()->getSearchPaths();;
    // initialize director
//    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);
    // Set the design resolution
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
    CCSize frameSize = pEGLView->getFrameSize();
    // In this demo, we select resource according to the frame's height.
    // If the resource size is different from design resolution size, you need to set contentScaleFactor.
    // We use the ratio of resource's height to the height of design resolution,
    // this can make sure that the resource's height could fit for the height of design resolution.
    // if the frame's height is larger than the height of medium resource size, select large resource.
    if (frameSize.height > mediumResource.size.height)
    {
            searchPath.push_back(largeResource.directory);
            pDirector->setContentScaleFactor(largeResource.size.height/designResolutionSize.height);
    }
    // if the frame's height is larger than the height of small resource size, select medium resource.
    else if (frameSize.height > smallResource.size.height)
    {
            searchPath.push_back(mediumResource.directory);
            pDirector->setContentScaleFactor(mediumResource.size.height/designResolutionSize.height);
    }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
    else
    {
            searchPath.push_back(smallResource.directory);
            pDirector->setContentScaleFactor(smallResource.size.height/designResolutionSize.height);
     }
    
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
    //--------------------------------------------------------------------------
    
    // create a scene. it's an autorelease object
//    CCScene *pScene = HelloWorld::scene();
    //CCScene *pScene = Joystick::scene();
//    CCScene *pScene = GameMenu::scene();
//    CCScene *pScene = MapLoading::scene();
    CCScene *pScene = PlayingScene::scene();
    // run
    pDirector->runWithScene(pScene);

    //-----------***************************************************************
    // initialize director
//    CCDirector *pDirector = CCDirector::sharedDirector();
//    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
//
//    CCSize designSize = CCSizeMake(480, 320);
//    CCSize resourceSize = CCSizeMake(480, 320);
//    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
//
//    std::vector<std::string> resDirOrders;
//
//    TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
//    if (platform == kTargetIphone || platform == kTargetIpad)
//    {
//        std::vector<std::string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
////        searchPaths.insert(searchPaths.begin(), "Published-iOS");
//        searchPaths.insert(searchPaths.begin(), "Resources");
//        CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
//
//        if (screenSize.height > 768)
//        {
//            resourceSize = CCSizeMake(2048, 1536);
//            resDirOrders.push_back("resources-ipadhd");
//        }
//        else if (screenSize.height > 640)
//        {
//            resourceSize = CCSizeMake(1536, 768);
//            resDirOrders.push_back("resources-ipad");
//        }else if (screenSize.height > 320)
//        {
//            resourceSize = CCSizeMake(960, 640);
////            resDirOrders.push_back("resources-iphonehd");
////            searchPaths.push_back("resources-iphonehd");
//            resDirOrders.push_back("iPhone_hd");
//
//        }
//        else
//        {
////            resDirOrders.push_back("resources-iphone");
////            searchPaths.push_back("resources-iphone");
//            resDirOrders.push_back("iPhone");
//        }
//        CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
//    }
//    else if (platform == kTargetAndroid || platform == kTargetWindows)
//    {
//
//        if (screenSize.width > 720)
//        {
//            resourceSize = CCSizeMake(960, 640);
//            resDirOrders.push_back("iPhone_hd");
//        }
//        else if (screenSize.width > 568)
//        {
//            resourceSize = CCSizeMake(720, 480);
//            resDirOrders.push_back("iPhone_hd");
//        }
//        else
//        {
//            resourceSize = CCSizeMake(568, 320);
//            resDirOrders.push_back("iPhone_hd");
//        }
//    }
//
//    CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);
//    pDirector->setContentScaleFactor(resourceSize.width/designSize.width);
//
//    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);
//    
//    // turn on display FPS
//    pDirector->setDisplayStats(true);
//    
//    // set FPS. the default value is 1.0/60 if you don't call this
//    pDirector->setAnimationInterval(1.0 / 60);
////
////    ScriptingCore* sc = ScriptingCore::getInstance();
////    sc->addRegisterCallback(register_all_cocos2dx);
////    sc->addRegisterCallback(register_all_cocos2dx_extension);
////    sc->addRegisterCallback(register_all_cocos2dx_extension_manual);
////    sc->addRegisterCallback(register_cocos2dx_js_extensions);
////    sc->addRegisterCallback(register_CCBuilderReader);
////    sc->addRegisterCallback(jsb_register_chipmunk);
////    sc->addRegisterCallback(jsb_register_system);
////
////    sc->start();
////
////    CCScriptEngineProtocol *pEngine = ScriptingCore::getInstance();
////    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
////    ScriptingCore::getInstance()->runScript("main.js");
//    
//    CCScene *pScene = PlayingScene::scene();
//    //    // run
//    pDirector->runWithScene(pScene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
