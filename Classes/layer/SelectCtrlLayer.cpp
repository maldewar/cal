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
  // Wheel ctrl
  m_wheelCtrl = WheelCtrl::create(m_scene);
  m_wheelCtrl->setPosition(Vec2(m_winSize.width / 2, m_winSize.height / 2));
  addChild(m_wheelCtrl);
  //m_showingTime = 0.34f;
  m_isFollowingCtrl = false;
  m_isPausingCtrl = false;
  return true;
}

void SelectCtrlLayer::update(float dt) {
  WorldLevelCtrlLayer::update(dt);
}

void SelectCtrlLayer::playAnimationIn(int state) {
  switch (state) {
    case State::Showing:
      m_opacityLayout->setVisible(true);
      break;
  }
}

void SelectCtrlLayer::playAnimationOut(int state) {
  switch (state) {
    case State::Showing:
      m_opacityLayout->setVisible(false);
      m_wheelCtrl->hide();
      break;
  }
}

void SelectCtrlLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) {
  if (getState() == State::Waiting) {
    Touch* touch = touches[0];
    Point screenPos = touch->getLocationInView();
    float angle = CMath::GetAngle(m_center->x, m_center->y, screenPos.x, 1080 - screenPos.y);
    m_wheelCtrl->setTargetAngle(angle);
  }
}

void SelectCtrlLayer::onBeginCtrlTouch() {
  m_wheelCtrl->show();
}

void SelectCtrlLayer::onEndCtrlTouch() {
  m_wheelCtrl->applyTargetAngle();
  m_wheelCtrl->hide();
}

void SelectCtrlLayer::onCancelCtrlTouch() {
  m_wheelCtrl->hide();
}
