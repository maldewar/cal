#include "HelloWorldScene.h"
#include "LevelScene.h"
#include "layer/WorldLevelLayer.h"
#include "scene/WorldLevelScene.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"
#include "ui/UILayout.h"
#include "ui/UILayoutParameter.h"

USING_NS_CC;

char* HelloWorld::MAIN_MENU_JSON = "MainMenu.json";

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    m_visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    m_winSize = Director::getInstance()->getWinSize();

    m_animCount = 0;
    //m_inTransition = false;
    m_currentAction = nullptr;

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    /*
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    auto changeSceneBtn = MenuItemImage::create("CloseNormal.png",
                                                "CloseSelected.png",
                                                CC_CALLBACK_1(HelloWorld::changeSceneCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + m_visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    changeSceneBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    changeSceneBtn->setPosition(m_winSize.width / 2, m_winSize.height / 2);*/

    // create menu, it's an autorelease object
    //auto menu = Menu::create(closeItem, NULL);
    //menu->setPosition(Vec2::ZERO);
    //this->addChild(menu, 1);
    //this->addChild(changeSceneBtn, 2);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    //auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    //label->setPosition(Vec2(origin.x + m_visibleSize.width/2,
    //                        origin.y + m_visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    //this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("ui/bg_main.png");
    // position the sprite on the center of the screen
    //sprite->setPosition(Vec2(m_visibleSize.width/2 + origin.x, m_visibleSize.height/2 + origin.y));
    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);
    //setUILayer();
    return true;
}

void HelloWorld::onEnter() {
  Layer::onEnter();
  setUILayer();
  scheduleUpdate();
  CCLOG("CALLING ON ENTER.");
}

void HelloWorld::startBtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    if (m_currentAction != nullptr && !m_currentAction->isPlaying()) {
      //Director::getInstance()->replaceScene( WorldLevelLayer::scene() );
      //Director::sharedDirector()->pushScene(WorldLevelLayer::scene());
      Director::getInstance()->replaceScene(WorldLevelScene::create(""));
      /*
      auto newScene = LevelScene::createScene();
      Director::getInstance()->setDepthTest(true);
      Director::getInstance()->replaceScene(CCTransitionFade::create(0.5,newScene));
      */
      //Director::getInstance()->replaceScene(CCTransitionPageTurn::create(0.5,newScene));
      //TransitionScene *transition = TransitionPageTurn::create(3.0f, newScene, false);
    }
  }
}

void HelloWorld::continueBtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
}

void HelloWorld::settingsBtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    if (m_currentAction != nullptr && !m_currentAction->isPlaying()) {
      pushState(State::SettingsMenu);
    }
  }
}

void HelloWorld::returnBtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    if (m_currentAction != nullptr && !m_currentAction->isPlaying()) {
      popState();
    }
  }
}

/*
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::changeSceneCallback(Ref* pSender) {
  auto newScene = LevelScene::createScene();
  Director::getInstance()->setDepthTest(true);

  Director::getInstance()->replaceScene(CCTransitionFade::create(0.5,newScene));
  //Director::getInstance()->replaceScene(CCTransitionPageTurn::create(0.5,newScene));

  //TransitionScene *transition = TransitionPageTurn::create(3.0f, newScene, false);
  
}*/

void HelloWorld::setUILayer() {
  Layer* uiLayer = Layer::create();
  this->addChild(uiLayer, 3);

  ui::Layout* uiLayout = static_cast<ui::Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile(HelloWorld::MAIN_MENU_JSON));
  uiLayer->addChild(uiLayout);

  //Containers
  ui::Layout* borderButtons = static_cast<ui::Layout*>(uiLayout->getChildByName("border_buttons"));
  ui::Layout* _btnSettings = static_cast<ui::Layout*>(borderButtons->getChildByName("_btn_settings"));
  ui::Layout* returnButton = static_cast<ui::Layout*>(uiLayout->getChildByName("return_button"));
  ui::Layout* _btnReturn = static_cast<ui::Layout*>(returnButton->getChildByName("_btn_return"));
  ui::Layout* mainOptions = static_cast<ui::Layout*>(uiLayout->getChildByName("main_options"));
  ui::Layout* settingsOptions = static_cast<ui::Layout*>(uiLayout->getChildByName("settings_options"));
  ui::Layout* settingsPanel = static_cast<ui::Layout*>(settingsOptions->getChildByName("settings_panel"));

  double visibleWidthRatio = m_visibleSize.width / m_winSize.width;
  borderButtons->setSizePercent(Size(visibleWidthRatio, 1));
  returnButton->setSizePercent(Size(visibleWidthRatio, 1));

  m_startBtn = static_cast<ui::Button*>(mainOptions->getChildByName("btn_start"));
  m_continueBtn = static_cast<ui::Button*>(mainOptions->getChildByName("btn_continue"));
  m_settingsBtn = static_cast<ui::Button*>(_btnSettings->getChildByName("btn_settings"));
  m_settingsApplyBtn = static_cast<ui::Button*>(settingsPanel->getChildByName("btn_settings_apply"));
  m_returnBtn = static_cast<ui::Button*>(_btnReturn->getChildByName("btn_return"));
  m_musicChk = static_cast<ui::CheckBox*>(borderButtons->getChildByName("btn_music"));
  m_soundChk = static_cast<ui::CheckBox*>(borderButtons->getChildByName("btn_sound"));

  m_startBtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::startBtnCallback, this));
  m_continueBtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::continueBtnCallback, this));
  m_settingsBtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::settingsBtnCallback, this));
  m_returnBtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::returnBtnCallback, this));

  pushState(State::MainMenu);
  
  //cocostudio::ActionManagerEx::getInstance()->playActionByName("MainMenu.json", "setting_options_in");
  //cocostudio::ActionManagerEx::getInstance()->playActionByName("MainMenu.json", "main_options_in");
  //cocostudio::ActionManagerEx::getInstance()->playActionByName("MainMenu.json", "border_buttons_in");
  //cocostudio::ActionManagerEx::getInstance()->playActionByName("MainMenu.json", "return_button_in");

}

/*
void HelloWorld::setState(State state) {
  if (m_currentState != state) {
    bool callSetState = false;
    switch(m_currentState) {
      case State::MainMenu:
        break;
      case State::SettingsMenu:
        break;
      case State::ContinueMenu:
        break;
      default:
        callSetState = true;
    }
    m_inTransition = true;
    m_currentState = state;
    if (callSetState) {
      setState(m_currentState);
    }
  } else {
    if (m_inTransition) {
      switch(m_currentState) {
        case State::MainMenu:
          playStateAnimation("main_options_in");
          playStateAnimation("border_buttons_in");
          break;
        case State::SettingsMenu:
          break;
        case State::ContinueMenu:
          break;
      }
      m_inTransition == false;
    }
  }
};
*/

void HelloWorld::setTouchEnabled(bool enabled) {
  m_startBtn->setTouchEnabled(enabled);
  m_continueBtn->setTouchEnabled(enabled);
  m_settingsBtn->setTouchEnabled(enabled);
  m_settingsApplyBtn->setTouchEnabled(enabled);
  m_returnBtn->setTouchEnabled(enabled);
  m_musicChk->setTouchEnabled(enabled);
  m_soundChk->setTouchEnabled(enabled);
}

void HelloWorld::pushState(State state) {
  CCLOG("Pushing state %d", state);
  if (!m_states.empty()) {
    CCLOG("  m_states is NOT EMPTY.");
    playAnimationOut(m_states.top());
  } else {
    CCLOG("  m_states is EMPTY.");
  }
  if ( m_states.empty() || state != m_states.top()) {
    m_states.push(state);
    playAnimationIn(state);
  }
  if (m_states.size() > 1) {
    playStateAnimation("return_button_in");
  }
}

void HelloWorld::popState() {
  if (!m_states.empty()) {
    playAnimationOut(m_states.top());
    m_states.pop();
    if (!m_states.empty()) {
      playAnimationIn(m_states.top());
    }
  }
  if (m_states.size() == 1) {
    playStateAnimation("return_button_out");
  }
}

void HelloWorld::playAnimationIn(State state) {
  CCLOG(" Calling playAnimationIn %d", state);
  switch (state) {
    case State::MainMenu:
      playStateAnimation("main_options_in");
      playStateAnimation("border_buttons_in");
      break;
    case State::SettingsMenu:
      playStateAnimation("setting_options_in");
      break;
    case State::ContinueMenu:
      break;
  }
}

void HelloWorld::playAnimationOut(State state) {
  switch (state) {
    case State::MainMenu:
      playStateAnimation("main_options_out");
      playStateAnimation("border_buttons_out");
      break;
    case State::SettingsMenu:
      playStateAnimation("settings_options_out");
      break;
    case State::ContinueMenu:
      break;
  }
}

void HelloWorld::playStateAnimation(std::string name) {
  CCLOG("  loading animation file:%s action:%s", HelloWorld::MAIN_MENU_JSON, name.c_str());
  m_currentAction = cocostudio::ActionManagerEx::getInstance()->getActionByName(HelloWorld::MAIN_MENU_JSON, name.c_str());
  /*
  m_currentAction->play();
  if (m_currentAction->isPlaying())
    log("Animatiooooon is playing");
  else
    log("Animation is NOOOOOT playing");
  */
  CCLOG("  playStateAnimation %s", name.c_str());
  m_currentAction->play(CallFunc::create(this, callfunc_selector(HelloWorld::finishStateAnimation)));
  CCLOG("  currentAction set.");
  //cocostudio::ActionManagerEx::getInstance()->playActionByName(HelloWorld::MAIN_MENU_JSON, name.c_str());
  /*
  cocostudio::ActionManagerEx::getInstance()->playActionByName(HelloWorld::MAIN_MENU_JSON,
                                                   name.c_str(),
                                                   CallFunc::create(std::bind(&HelloWorld::finishStateAnimation, this)));
  */
  /*cocostudio::ActionManagerEx::getInstance()->playActionByName(HelloWorld::MAIN_MENU_JSON,
                                                   name.c_str(),
                                                   CallFunc::create(this, callfunc_selector(HelloWorld::finishStateAnimation)));*/
  /*
  m_animCount++;
  cocostudio::ActionManagerEx::getInstance()->playActionByName(HelloWorld::MAIN_MENU_JSON,
                                                   name.c_str(),
                                                   CCCallFunc::create(this, callfunc_selector(HelloWorld::finishStateAnimation)));
  */
}

void HelloWorld::finishStateAnimation() {
  //m_animCount--;
  /*if (m_animCount == 0) {
    setState(m_currentState);
  }*/
}
