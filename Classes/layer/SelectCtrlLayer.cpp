#include "SelectCtrlLayer.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"
#include "../scene/WorldLevelScene.h"
#include "../util/CMath.h"

USING_NS_CC;

SelectCtrlLayer* SelectCtrlLayer::create(WorldLevelScene* scene) {
  SelectCtrlLayer* selectCtrlLayer = new (std::nothrow) SelectCtrlLayer();
  if (selectCtrlLayer && selectCtrlLayer->init(scene)) {
    selectCtrlLayer->autorelease();
    return selectCtrlLayer;
  }
  CC_SAFE_DELETE(selectCtrlLayer);
  return nullptr;
}

bool SelectCtrlLayer::init(WorldLevelScene* scene) {
  if ( !WorldLevelCtrlLayer::init(scene) ) {
    return false;
  }
  m_selectCtrl = WheelCtrl::create(m_scene, WHEEL_CTRL_TYPE_SELECT);
  m_cursorCtrl = WheelCtrl::create(m_scene, WHEEL_CTRL_TYPE_CURSOR);
  addChild(m_selectCtrl);
  addChild(m_cursorCtrl);
  m_showingTime = 0.34f;
  m_cooldownTime = 0.5f;
  m_isFollowingCtrl = false;
  m_isPausingCtrl = true;
  m_isFadeToBlackCtrl = false;
  return true;
}

void SelectCtrlLayer::update(float dt) {
  WorldLevelCtrlLayer::update(dt);
  if (m_state == State::Active) {
    m_selectCtrl->setRotation(m_selectCtrl->getRotation() + 0.7f);
    m_cursorCtrl->setRotation(m_cursorCtrl->getRotation() + 2.0f);
  }
}

void SelectCtrlLayer::playAnimationIn(int state) {
}

void SelectCtrlLayer::playAnimationOut(int state) {
  switch (state) {
    case State::Showing:
      m_selectCtrl->setRotation(0);
      m_cursorCtrl->setRotation(0);
      m_selectCtrl->hide();
      m_cursorCtrl->hide();
      break;
  }
}

void SelectCtrlLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event){
  Touch* touch = touches[0];
  Point screenPos = touch->getLocation();
  m_cursorCtrl->setPosition(screenPos);
}

void SelectCtrlLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event){
  Touch* touch = touches[0];
  Point screenPos = touch->getLocation();
  m_cursorCtrl->setPosition(screenPos);
}

void SelectCtrlLayer::onBeginCtrlTouch() {
  m_selectCtrl->show();
  m_cursorCtrl->show();
  Point p = m_scene->worldToScreen(m_entity->getBody()->GetPosition());
  p.y = Director::getInstance()->getWinSize().height - p.y;
  m_selectCtrl->setPosition(p);
}

void SelectCtrlLayer::onEndCtrlTouch() {
  m_selectCtrl->hide();
  m_cursorCtrl->hide();
}

void SelectCtrlLayer::onCancelCtrlTouch() {
  m_selectCtrl->hide();
  m_cursorCtrl->hide();
}
