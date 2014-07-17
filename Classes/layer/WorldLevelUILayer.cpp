#include "WorldLevelUILayer.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"
#include "ui/UILayout.h"
#include "../scene/WorldLevelScene.h"
#include "../HelloWorldScene.h"

USING_NS_CC;

char* WorldLevelUILayer::GAME_MENU_JSON = "GameMenu.json";

// on "init" you need to initialize your instance
bool WorldLevelUILayer::init()
{
  if ( !UILayer::init() ) {
    return false;
  }
  setUILayer();
  return true;
}

void WorldLevelUILayer::settingsBtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    if (m_currentAction != nullptr && !m_currentAction->isPlaying()) {
      //pushState(State::SettingsMenu);
    }
  }
}

void WorldLevelUILayer::returnBtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    if (m_currentAction != nullptr && !m_currentAction->isPlaying()) {
      //Director::getInstance()->popScene();
      Scene* mainScene = HelloWorld::createScene();
      Director::getInstance()->replaceScene(mainScene);
    }
  }
}

void WorldLevelUILayer::pauseBtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    if (m_currentAction != nullptr && !m_currentAction->isPlaying()) {
      if (m_scene) {
        m_scene->togglePause();
      }
    }
  }
}

void WorldLevelUILayer::setUILayer() {
  Layer* uiLayer = Layer::create();
  this->addChild(uiLayer, 3);

  ui::Layout* uiLayout = static_cast<ui::Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile(WorldLevelUILayer::GAME_MENU_JSON));
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

  m_settingsBtn->addTouchEventListener(CC_CALLBACK_2(WorldLevelUILayer::settingsBtnCallback, this));
  m_returnBtn->addTouchEventListener(CC_CALLBACK_2(WorldLevelUILayer::returnBtnCallback, this));
  m_pauseChk->addTouchEventListener(CC_CALLBACK_2(WorldLevelUILayer::pauseBtnCallback, this));

  pushState(State::GameMenu);

}

void WorldLevelUILayer::playAnimationIn(int state) {
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

void WorldLevelUILayer::playAnimationOut(int state) {
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

void WorldLevelUILayer::playStateAnimation(std::string name) {
  m_currentAction = cocostudio::ActionManagerEx::getInstance()->getActionByName(WorldLevelUILayer::GAME_MENU_JSON, name.c_str());
  m_currentAction->play(CallFunc::create(this, callfunc_selector(WorldLevelUILayer::finishStateAnimation)));
}

void WorldLevelUILayer::finishStateAnimation() {
}
