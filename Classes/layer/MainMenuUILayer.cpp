#include "MainMenuUILayer.h"
#include "../scene/WorldLevelScene.h"
#include "../scene/ActMenuScene.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"
#include "ui/UILayout.h"
#include "ui/UILayoutParameter.h"

USING_NS_CC;

char* MainMenuUILayer::MAIN_MENU_JSON = "MainMenu.json";

MainMenuUILayer::MainMenuUILayer() {
}

MainMenuUILayer::~MainMenuUILayer() {
}

MainMenuUILayer* MainMenuUILayer::create() {
  MainMenuUILayer* mainMenuUILayer = new (std::nothrow) MainMenuUILayer();
  if (mainMenuUILayer && mainMenuUILayer->init()) {
    mainMenuUILayer->autorelease();
    return mainMenuUILayer;
  }
  CC_SAFE_DELETE(mainMenuUILayer);
  return nullptr;
}

// on "init" you need to initialize your instance
bool MainMenuUILayer::init()
{
  if ( !Layer::init() )
  {
      return false;
  }
  m_visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  m_winSize = Director::getInstance()->getWinSize();
  m_animCount = 0;
  m_currentAction = nullptr;
  //setUILayer();
  return true;
}

void MainMenuUILayer::onEnter() {
  CCLOG("MainMenuUILayer::onEnter");
  Layer::onEnter();
  setUILayer();
  scheduleUpdate();
}

void MainMenuUILayer::onExit() {
  CCLOG("MainMenuUILayer::onExit");
  unscheduleUpdate();
  stopAllActions();
  m_currentAction->stop(); // TODO: stop all actions, not just the last one
  unscheduleAllSelectors();
  cocostudio::ActionManagerEx::getInstance()->releaseActions();
  cocostudio::ActionManagerEx::destroyInstance();
  cocostudio::GUIReader::destroyInstance();
  Layer::onExit();
}

void MainMenuUILayer::startBtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    if (m_currentAction != nullptr && !m_currentAction->isPlaying()) {
      //Director::getInstance()->replaceScene( WorldLevelLayer::scene() );
      //Director::sharedDirector()->pushScene(WorldLevelLayer::scene());
      //Director::getInstance()->replaceScene(WorldLevelScene::create(0,1));
      Director::getInstance()->replaceScene(ActMenuScene::create());
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

void MainMenuUILayer::continueBtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
}

void MainMenuUILayer::settingsBtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    if (m_currentAction != nullptr && !m_currentAction->isPlaying()) {
      pushState(State::SettingsMenu);
    }
  }
}

void MainMenuUILayer::returnBtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    if (m_currentAction != nullptr && !m_currentAction->isPlaying()) {
      popState();
    }
  }
}

void MainMenuUILayer::setUILayer() {
  CCLOG("MainMenuUILayer::setUILayer 1");
  Layer* uiLayer = Layer::create();
  this->addChild(uiLayer, 3);

  ui::Layout* uiLayout = static_cast<ui::Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile(MainMenuUILayer::MAIN_MENU_JSON));
  uiLayer->addChild(uiLayout);
  CCLOG("MainMenuUILayer::setUILayer 2");

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
  CCLOG("MainMenuUILayer::setUILayer 3");

  m_startBtn = static_cast<ui::Button*>(mainOptions->getChildByName("btn_start"));
  m_continueBtn = static_cast<ui::Button*>(mainOptions->getChildByName("btn_continue"));
  m_settingsBtn = static_cast<ui::Button*>(_btnSettings->getChildByName("btn_settings"));
  m_settingsApplyBtn = static_cast<ui::Button*>(settingsPanel->getChildByName("btn_settings_apply"));
  m_returnBtn = static_cast<ui::Button*>(_btnReturn->getChildByName("btn_return"));
  m_musicChk = static_cast<ui::CheckBox*>(borderButtons->getChildByName("btn_music"));
  m_soundChk = static_cast<ui::CheckBox*>(borderButtons->getChildByName("btn_sound"));
  CCLOG("MainMenuUILayer::setUILayer 4");

  m_startBtn->addTouchEventListener(CC_CALLBACK_2(MainMenuUILayer::startBtnCallback, this));
  m_continueBtn->addTouchEventListener(CC_CALLBACK_2(MainMenuUILayer::continueBtnCallback, this));
  m_settingsBtn->addTouchEventListener(CC_CALLBACK_2(MainMenuUILayer::settingsBtnCallback, this));
  m_returnBtn->addTouchEventListener(CC_CALLBACK_2(MainMenuUILayer::returnBtnCallback, this));
  CCLOG("MainMenuUILayer::setUILayer 5");

  pushState(State::MainMenu);

}

void MainMenuUILayer::setTouchEnabled(bool enabled) {
  m_startBtn->setTouchEnabled(enabled);
  m_continueBtn->setTouchEnabled(enabled);
  m_settingsBtn->setTouchEnabled(enabled);
  m_settingsApplyBtn->setTouchEnabled(enabled);
  m_returnBtn->setTouchEnabled(enabled);
  m_musicChk->setTouchEnabled(enabled);
  m_soundChk->setTouchEnabled(enabled);
}

void MainMenuUILayer::pushState(State state) {
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

void MainMenuUILayer::popState() {
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

void MainMenuUILayer::playAnimationIn(State state) {
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

void MainMenuUILayer::playAnimationOut(State state) {
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

void MainMenuUILayer::playStateAnimation(std::string name) {
  CCLOG("  loading animation file:%s action:%s", MainMenuUILayer::MAIN_MENU_JSON, name.c_str());
  m_currentAction = cocostudio::ActionManagerEx::getInstance()->getActionByName(MainMenuUILayer::MAIN_MENU_JSON, name.c_str());
  CCLOG("  playStateAnimation %s", name.c_str());
  m_currentAction->play(CallFunc::create(this, callfunc_selector(MainMenuUILayer::finishStateAnimation)));
  CCLOG("  currentAction set.");
}

void MainMenuUILayer::finishStateAnimation() {
  //m_animCount--;
  /*if (m_animCount == 0) {
    setState(m_currentState);
  }*/
}
