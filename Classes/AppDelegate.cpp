#include "AppDelegate.h"

#include "cocos2d.h"
#include "manager/ConfigurationManager.h"
#include "cocostudio/CocoStudio.h"

#include "scene/MainMenuScene.h"
#include "manager/StorageManager.h"
#include "LevelScene.h"
#define COCOS2D_DEBUG 1

USING_NS_CC;

cocos2d::Size AppDelegate::m_smallResource = cocos2d::Size(480, 320);
cocos2d::Size AppDelegate::m_mediumResource = cocos2d::Size(960, 640);
cocos2d::Size AppDelegate::m_largeResource = cocos2d::Size(1280, 800);
cocos2d::Size AppDelegate::m_fullHDResource = cocos2d::Size(1920, 1080);
cocos2d::Size AppDelegate::m_xFullHDResource = cocos2d::Size(2560, 1600);
cocos2d::Size AppDelegate::m_4KResource = cocos2d::Size(3840, 2160);

cocos2d::Size AppDelegate::m_designResolutionSize = cocos2d::Size(1920, 1080);

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Calaveras");
        //glview->setFrameSize(640, 480);
        glview->setFrameSize(480, 270);
        //glview->setFrameSize(960, 540);
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    auto screenSize = glview->getFrameSize();

    auto fileUtils = FileUtils::getInstance();
    std::vector<std::string> searchPaths;

    if (screenSize.height <= m_mediumResource.height) {
      cocos2d::log("!!!!! resolution medium");
      searchPaths.push_back("medium");
      searchPaths.push_back("md");
      director->setContentScaleFactor(m_mediumResource.height/m_designResolutionSize.height);
    } else if (screenSize.height <= m_largeResource.height) {
      cocos2d::log("!!!!! resolution large");
      searchPaths.push_back("large");
      searchPaths.push_back("medium");
      searchPaths.push_back("lg");
      searchPaths.push_back("md");
      director->setContentScaleFactor(m_largeResource.height/m_designResolutionSize.height);
    } else if (screenSize.height <= m_fullHDResource.height) {
      cocos2d::log("!!!!! resolution fullhd");
      searchPaths.push_back("fullhd");
      searchPaths.push_back("large");
      searchPaths.push_back("medium");
      searchPaths.push_back("fhd");
      searchPaths.push_back("lg");
      searchPaths.push_back("md");
      director->setContentScaleFactor(m_fullHDResource.height/m_designResolutionSize.height);
    } else if (screenSize.height <= m_xFullHDResource.height) {
      cocos2d::log("!!!!! resolution xfullhd");
      searchPaths.push_back("xfullhd");
      searchPaths.push_back("fullhd");
      searchPaths.push_back("large");
      searchPaths.push_back("medium");
      searchPaths.push_back("xfhd");
      searchPaths.push_back("fhd");
      searchPaths.push_back("lg");
      searchPaths.push_back("md");
      director->setContentScaleFactor(m_xFullHDResource.height/m_designResolutionSize.height);
    } else {
      cocos2d::log("!!!!! resolution 4K");
      searchPaths.push_back("xfullhd");
      searchPaths.push_back("fullhd");
      searchPaths.push_back("large");
      searchPaths.push_back("medium");
      searchPaths.push_back("4k");
      searchPaths.push_back("xfhd");
      searchPaths.push_back("fhd");
      searchPaths.push_back("lg");
      searchPaths.push_back("md");
      director->setContentScaleFactor(m_4KResource.height/m_designResolutionSize.height);
    }

    fileUtils->setSearchPaths(searchPaths);

    // Set the design resolution
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    // a bug in DirectX 11 level9-x on the device prevents ResolutionPolicy::NO_BORDER from working correctly
    glview->setDesignResolutionSize(m_designResolutionSize.width, m_designResolutionSize.height, ResolutionPolicy::SHOW_ALL);
#else
    glview->setDesignResolutionSize(m_designResolutionSize.width, m_designResolutionSize.height, ResolutionPolicy::NO_BORDER);
#endif

    // Initi Storage
    StorageManager::getInstance();

    // create a scene. it's an autorelease object
    auto scene = MainMenuScene::create();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
