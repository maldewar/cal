#include "BasicUILayer.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"
#include "ui/UILayout.h"
#include "../scene/MainMenuScene.h"
#include "../scene/ActMenuScene.h"

USING_NS_CC;

char* BasicUILayer::BASIC_UI_JSON = "Basic.json";

BasicUILayer* BasicUILayer::create(int sceneType) {
  BasicUILayer* basicUILayer = new (std::nothrow) BasicUILayer();
  if (basicUILayer && basicUILayer->init(sceneType)) {
    basicUILayer->autorelease();
    return basicUILayer;
  }
  CC_SAFE_DELETE(basicUILayer);
  return nullptr;
}

bool BasicUILayer::init(int sceneType)
{
  if ( !UILayer::init() ) {
    return false;
  }
  m_sceneType = sceneType;
  return true;
}

void BasicUILayer::onEnter() {
  CCLOG("BasicUILayer::onEnter");
  UILayer::onEnter();
  setUILayer();
  scheduleUpdate();
}

void BasicUILayer::onExit() {
  CCLOG("BasicUILayer::onExit");
  unscheduleUpdate();
  stopAllActions();
  m_currentAction->stop(); // TODO, stop all actions, not just the last one
  unscheduleAllSelectors();
  cocostudio::ActionManagerEx::getInstance()->releaseActions();
  cocostudio::ActionManagerEx::destroyInstance();
  cocostudio::GUIReader::destroyInstance();
  UILayer::onExit();
}

void BasicUILayer::returnBtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    if (m_currentAction != nullptr && !m_currentAction->isPlaying()) {
      switch(m_sceneType) {
        case SceneType::Act:
          {
            MainMenuScene* mainScene = MainMenuScene::create();
            Director::getInstance()->replaceScene(mainScene);
          }
          break;
        case SceneType::Level:
          {
            ActMenuScene* actScene = ActMenuScene::create();
            Director::getInstance()->replaceScene(actScene);
          }
          break;
      }
    }
  }
}

void BasicUILayer::setUILayer() {
  Layer* uiLayer = Layer::create();
  this->addChild(uiLayer, 3);

  ui::Layout* uiLayout = static_cast<ui::Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile(BasicUILayer::BASIC_UI_JSON));
  uiLayer->addChild(uiLayout);

  //Containers
  ui::Layout* borderButtons = static_cast<ui::Layout*>(uiLayout->getChildByName("border_buttons"));
  //ui::Layout* _btnSettings = static_cast<ui::Layout*>(borderButtons->getChildByName("_btn_settings"));
  //ui::Layout* _btnPause = static_cast<ui::Layout*>(borderButtons->getChildByName("_btn_pause"));
  ui::Layout* returnButton = static_cast<ui::Layout*>(uiLayout->getChildByName("return_button"));
  ui::Layout* _btnReturn = static_cast<ui::Layout*>(returnButton->getChildByName("_btn_return"));

  double visibleWidthRatio = m_visibleSize.width / m_winSize.width;
  borderButtons->setSizePercent(Size(visibleWidthRatio, 1));
  returnButton->setSizePercent(Size(visibleWidthRatio, 1));

  m_returnBtn = static_cast<ui::Button*>(_btnReturn->getChildByName("btn_return"));

  //scaleWidget(_btnSettings, Align::TopRight);
  //scaleWidget(_btnPause, Align::TopLeft);
  scaleWidget(_btnReturn, Align::BottomRight);

  m_returnBtn->addTouchEventListener(CC_CALLBACK_2(BasicUILayer::returnBtnCallback, this));

  pushState(0);

}

void BasicUILayer::playAnimationIn(int state) {
  playStateAnimation("return_button_in");
}

void BasicUILayer::playAnimationOut(int state) {
  playStateAnimation("return_button_out");
}

void BasicUILayer::playStateAnimation(std::string name) {
  m_currentAction = cocostudio::ActionManagerEx::getInstance()->getActionByName(BasicUILayer::BASIC_UI_JSON, name.c_str());
  m_currentAction->play(CallFunc::create(this, callfunc_selector(BasicUILayer::finishStateAnimation)));
}
