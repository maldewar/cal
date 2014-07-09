#include "WorldLevelCtrlLayer.h"
#include "ui/UILayout.h"
#include "ui/UILayoutParameter.h"
#include "platform/CCDevice.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool WorldLevelCtrlLayer::init()
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
    m_scene = nullptr;

    setUILayer();
    return true;
}

void WorldLevelCtrlLayer::settingsBtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    if (m_currentAction != nullptr && !m_currentAction->isPlaying()) {
      //pushState(State::SettingsMenu);
    }
  }
}

void WorldLevelCtrlLayer::returnBtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    if (m_currentAction != nullptr && !m_currentAction->isPlaying()) {
      Director::getInstance()->popScene();
    }
  }
}

void WorldLevelCtrlLayer::pauseBtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    if (m_currentAction != nullptr && !m_currentAction->isPlaying()) {
      if (m_scene) {
        m_scene->togglePause();
      }
    }
  }
}

void WorldLevelCtrlLayer::setUILayer() {
  Layer* uiLayer = Layer::create();
  this->addChild(uiLayer, 3);

  ui::Layout* uiLayout = static_cast<ui::Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile(WorldLevelCtrlLayer::GAME_MENU_JSON));
  uiLayer->addChild(uiLayout);

  //Containers
  ui::Layout* borderButtons = static_cast<ui::Layout*>(uiLayout->getChildByName("border_buttons"));
  ui::Layout* _btnSettings = static_cast<ui::Layout*>(borderButtons->getChildByName("_btn_settings"));
  ui::Layout* _btnPause = static_cast<ui::Layout*>(borderButtons->getChildByName("_btn_pause"));
  ui::Layout* returnButton = static_cast<ui::Layout*>(uiLayout->getChildByName("return_button"));
  ui::Layout* _btnReturn = static_cast<ui::Layout*>(returnButton->getChildByName("_btn_return"));

  double visibleWidthRatio = m_visibleSize.width / m_winSize.width;
  borderButtons->setSizePercent(Size(visibleWidthRatio, 1));
  returnButton->setSizePercent(Size(visibleWidthRatio, 1));

  m_settingsBtn = static_cast<ui::Button*>(_btnSettings->getChildByName("btn_settings"));
  m_returnBtn = static_cast<ui::Button*>(_btnReturn->getChildByName("btn_return"));
  m_pauseChk = static_cast<ui::CheckBox*>(_btnPause->getChildByName("btn_pause"));

  scaleWidget(_btnSettings, Align::TopRight);
  scaleWidget(_btnPause, Align::TopLeft);
  scaleWidget(_btnReturn, Align::BottomRight);

  m_settingsBtn->addTouchEventListener(CC_CALLBACK_2(WorldLevelCtrlLayer::settingsBtnCallback, this));
  m_returnBtn->addTouchEventListener(CC_CALLBACK_2(WorldLevelCtrlLayer::returnBtnCallback, this));
  m_pauseChk->addTouchEventListener(CC_CALLBACK_2(WorldLevelCtrlLayer::pauseBtnCallback, this));

  pushState(State::GameMenu);

}

void WorldLevelCtrlLayer::setTouchEnabled(bool enabled) {
  m_settingsBtn->setTouchEnabled(enabled);
  m_returnBtn->setTouchEnabled(enabled);
  m_pauseChk->setTouchEnabled(enabled);
}

void WorldLevelCtrlLayer::pushState(State state) {
  CCLOG("Pushing state %d", state);
  if (!m_states.empty()) {
    playAnimationOut(m_states.top());
  }
  if ( m_states.empty() || state != m_states.top()) {
    m_states.push(state);
    playAnimationIn(state);
  }
  /*if (m_states.size() > 1) {
    playStateAnimation("return_button_in");
  }*/
}

void WorldLevelCtrlLayer::popState() {
  if (!m_states.empty()) {
    playAnimationOut(m_states.top());
    m_states.pop();
    if (!m_states.empty()) {
      playAnimationIn(m_states.top());
    }
  }
  /*if (m_states.size() == 1) {
    playStateAnimation("return_button_out");
  }*/
}

void WorldLevelCtrlLayer::playAnimationIn(State state) {
  switch (state) {
    case State::GameMenu:
      playStateAnimation("border_buttons_in");
      playStateAnimation("return_button_in");
      break;
    /*
    case State::SettingsMenu:
      playStateAnimation("setting_options_in");
      break;
    case State::ContinueMenu:
      break;
    */
  }
}

void WorldLevelCtrlLayer::playAnimationOut(State state) {
  switch (state) {
    case State::GameMenu:
      playStateAnimation("border_buttons_out");
      playStateAnimation("return_button_out");
      break;
    /*
    case State::SettingsMenu:
      playStateAnimation("settings_options_out");
      break;
    case State::ContinueMenu:
      break;
    */
  }
}

void WorldLevelCtrlLayer::playStateAnimation(std::string name) {
  m_currentAction = cocostudio::ActionManagerEx::getInstance()->getActionByName(WorldLevelCtrlLayer::GAME_MENU_JSON, name.c_str());/*
  m_currentAction->play();
  if (m_currentAction->isPlaying())
    log("Animatiooooon is playing");
  else
    log("Animation is NOOOOOT playing");
  */
  m_currentAction->play(CallFunc::create(this, callfunc_selector(WorldLevelCtrlLayer::finishStateAnimation)));
  //cocostudio::ActionManagerEx::getInstance()->playActionByName(WorldLevelCtrlLayer::MAIN_MENU_JSON, name.c_str());
  /*
  cocostudio::ActionManagerEx::getInstance()->playActionByName(WorldLevelCtrlLayer::MAIN_MENU_JSON,
                                                   name.c_str(),
                                                   CallFunc::create(std::bind(&WorldLevelCtrlLayer::finishStateAnimation, this)));
  */
  /*cocostudio::ActionManagerEx::getInstance()->playActionByName(WorldLevelCtrlLayer::MAIN_MENU_JSON,
                                                   name.c_str(),
                                                   CallFunc::create(this, callfunc_selector(WorldLevelCtrlLayer::finishStateAnimation)));*/
  /*
  m_animCount++;
  cocostudio::ActionManagerEx::getInstance()->playActionByName(WorldLevelCtrlLayer::MAIN_MENU_JSON,
                                                   name.c_str(),
                                                   CCCallFunc::create(this, callfunc_selector(WorldLevelCtrlLayer::finishStateAnimation)));
  */
}

void WorldLevelCtrlLayer::finishStateAnimation() {
  //m_animCount--;
  /*if (m_animCount == 0) {
    setState(m_currentState);
  }*/
}

void WorldLevelCtrlLayer::scaleWidget(ui::Widget* widget, const Align align) {
  int dpi = Device::getDPI();
  int minDPI = 96;
  int maxDPI = 240;
  if (dpi < minDPI || dpi > maxDPI)
    return;
  float minScale = 0.4;
  float maxScale = 0.75;
  float scale = (dpi - minDPI) * (maxScale - minScale) / (float)(maxDPI - minDPI) + minScale;
  Size contentSize = widget->getContentSize();
  CCLOG("SCALE %f SIZEX:%f SIZEY:%f", scale, contentSize.width, contentSize.height);
  float positionX = contentSize.width - (scale * contentSize.width);
  float positionY = contentSize.height - (scale * contentSize.height);
  widget->setScale(scale);
  // margin (left, top, right, bottom)
  switch(align) {
    case Align::TopLeft:
      widget->getLayoutParameter()->setMargin(ui::Margin(0,-positionY,0,0));
      break;
    case Align::TopRight:
      widget->getLayoutParameter()->setMargin(ui::Margin(0,-positionY,-positionX,0));
      break;
    case Align::BottomLeft:
      break;
    case Align::BottomRight:
      widget->getLayoutParameter()->setMargin(ui::Margin(0,0,-positionX,0));
      break;
  }
}

void WorldLevelCtrlLayer::setScene(WorldLevelScene* scene) {
  m_scene = scene;
}
