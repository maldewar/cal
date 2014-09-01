#include "GravityCtrlLayer.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"
#include "../scene/WorldLevelScene.h"
#include "../util/CMath.h"

USING_NS_CC;

GravityCtrlLayer* GravityCtrlLayer::create(WorldLevelScene* scene) {
  GravityCtrlLayer* gravityCtrlLayer = new (std::nothrow) GravityCtrlLayer();
  if (gravityCtrlLayer && gravityCtrlLayer->init(scene)) {
    gravityCtrlLayer->autorelease();
    return gravityCtrlLayer;
  }
  CC_SAFE_DELETE(gravityCtrlLayer);
  return nullptr;
}

bool GravityCtrlLayer::init(WorldLevelScene* scene) {
  if ( !WorldLevelCtrlLayer::init(scene) ) {
    return false;
  }
  // Wheel ctrl
  m_wheelCtrl = WheelCtrl::create(m_scene);
  m_wheelCtrl->setPosition(Vec2(m_winSize.width / 2, m_winSize.height / 2));
  addChild(m_wheelCtrl);
  m_showingTime = 0.34f;
  m_isFollowingCtrl = true;
  m_isPausingCtrl = true;
  return true;
}

void GravityCtrlLayer::update(float dt) {
  WorldLevelCtrlLayer::update(dt);
}

void GravityCtrlLayer::playAnimationIn(int state) {
  switch (state) {
    case State::Showing:
      m_opacityLayout->setVisible(true);
      break;
  }
}

void GravityCtrlLayer::playAnimationOut(int state) {
  switch (state) {
    case State::Showing:
      m_opacityLayout->setVisible(false);
      m_wheelCtrl->hide();
      break;
  }
}

void GravityCtrlLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) {
  if (getState() == State::Waiting) {
    Touch* touch = touches[0];
    Point screenPos = touch->getLocationInView();
    float angle = CMath::GetAngle(m_center->x, m_center->y, screenPos.x, 1080 - screenPos.y);
    m_wheelCtrl->setTargetAngle(angle);
  }
}

void GravityCtrlLayer::onBeginCtrlTouch() {
  m_wheelCtrl->show();
}

void GravityCtrlLayer::onEndCtrlTouch() {
  m_wheelCtrl->applyTargetAngle();
  m_wheelCtrl->hide();
}

void GravityCtrlLayer::onCancelCtrlTouch() {
  m_wheelCtrl->hide();
}
