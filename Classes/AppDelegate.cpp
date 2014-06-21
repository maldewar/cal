#include "AppDelegate.h"

#include "cocos2d.h"
//#include "cocostudio/CocoStudio.h"
//#include "extensions/coco-ext.h"

#include "HelloWorldScene.h"
#include "LevelScene.h"
#define COCOS2D_DEBUG 1

USING_NS_CC;

cocos2d::Size AppDelegate::m_smallResource = cocos2d::Size(480, 320);
cocos2d::Size AppDelegate::m_mediumResource = cocos2d::Size(960, 640);
cocos2d::Size AppDelegate::m_largeResource = cocos2d::Size(1280, 800);
cocos2d::Size AppDelegate::m_fullHDResource = cocos2d::Size(1920, 1200);
cocos2d::Size AppDelegate::m_xFullHDResource = cocos2d::Size(2560, 1600);
cocos2d::Size AppDelegate::m_designResolutionSize = cocos2d::Size(1920, 1080);
//Original resource size: 3200x1800

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Calaveras");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    auto screenSize = glview->getFrameSize();

    auto fileUtils = FileUtils::getInstance();
    std::vector<std::string> searchPaths;

    if (screenSize.height <= m_smallResource.height) {
      searchPaths.push_back("small");
      director->setContentScaleFactor(m_smallResource.height/m_designResolutionSize.height);
    } else if (screenSize.height <= m_mediumResource.height) {
      searchPaths.push_back("medium");
      searchPaths.push_back("small");
      director->setContentScaleFactor(m_mediumResource.height/m_designResolutionSize.height);
    } else if (screenSize.height <= m_largeResource.height) {
      searchPaths.push_back("large");
      searchPaths.push_back("medium");
      searchPaths.push_back("small");
      director->setContentScaleFactor(m_largeResource.height/m_designResolutionSize.height);
    } else if (screenSize.height <= m_fullHDResource.height) {
      searchPaths.push_back("fullhd");
      searchPaths.push_back("large");
      searchPaths.push_back("medium");
      searchPaths.push_back("small");
      director->setContentScaleFactor(m_fullHDResource.height/m_designResolutionSize.height);
    } else {
      searchPaths.push_back("xfullhd");
      searchPaths.push_back("fullhd");
      searchPaths.push_back("large");
      searchPaths.push_back("medium");
      searchPaths.push_back("small");
      director->setContentScaleFactor(m_xFullHDResource.height/m_designResolutionSize.height);
    }

    fileUtils->setSearchPaths(searchPaths);

    // Set the design resolution
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    // a bug in DirectX 11 level9-x on the device prevents ResolutionPolicy::NO_BORDER from working correctly
    glview->setDesignResolutionSize(m_designResolutionSize.width, m_designResolutionSize.height, ResolutionPolicy::SHOW_ALL);
#else
    glview->setDesignResolutionSize(m_designResolutionSize.width, m_designResolutionSize.height, ResolutionPolicy::NO_BORDER);
#endif

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

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
