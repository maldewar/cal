#include "LevelScene.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"
#include "ui/UILayout.h"

USING_NS_CC;

Scene* LevelScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LevelScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LevelScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getWinSize();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    /*
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(LevelScene::menuCloseCallback, this));
    auto changeSceneBtn = MenuItemImage::create("CloseNormal.png",
                                                "CloseSelected.png",
                                                CC_CALLBACK_1(LevelScene::changeSceneCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    changeSceneBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    changeSceneBtn->setPosition(winSize.width / 2, winSize.height / 2);

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    this->addChild(changeSceneBtn, 2);*/

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "LevelScene" splash screen"
    auto sprite = Sprite::create("ui/bg_main.png");
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

// LOADING UI LAYOUT FROM JSON.
/*
    Layer* m_pLayer = Layer::create();
    this->addChild(m_pLayer, 2);

    ui::Layout* m_pLayout = static_cast<ui::Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("CalaverasMainMenu_1.json"));
    m_pLayer->addChild(m_pLayout);
    cocostudio::ActionManagerEx::getInstance()->playActionByName("CalaverasMainMenu_1.json", "Animation0");
*/
    

    return true;
}
