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
  m_wheelCtrl = WheelCtrl::create(m_scene);
  m_wheelCtrl->setPosition(Vec2(m_winSize.width / 2, m_winSize.height / 2));
  addChild(m_wheelCtrl);
  m_showingTime = 0.34f;
  m_cooldownTime = 0.5f;
  m_isFollowingCtrl = true;
  m_isPausingCtrl = true;
  m_ratioToCancel = 0.5f;
  m_isCancelled = false;
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
  if (getState() == State::Active) {
    Touch* touch = touches[0];
    Point screenPos = touch->getLocationInView();
    m_isCancelled = checkIsCancelled(screenPos);
    if (m_isCancelled) {
        m_wheelCtrl->cancel();
    } else {
      float angle = CMath::getAngle(m_center->x, m_center->y, screenPos.x, 1080 - screenPos.y);
      m_wheelCtrl->setTargetAngle(angle);
    }
  }
}

void GravityCtrlLayer::onBeginCtrlTouch(Entity* entity) {
  replaceState(State::Active);
  m_wheelCtrl->show();
}

void GravityCtrlLayer::onEndCtrlTouch() {
  if (!m_wheelCtrl->isCancelled()) {
    m_wheelCtrl->applyTargetAngle();
  }
  m_wheelCtrl->hide();
  replaceState(State::Inactive);
}

void GravityCtrlLayer::onCancelCtrlTouch() {
  m_wheelCtrl->hide();
  replaceState(State::Inactive);
}

bool GravityCtrlLayer::checkIsCancelled(cocos2d::Point& screenPosition) {
  cocos2d::Size screenSize = Director::getInstance()->getWinSize();
  Vec2 center = Vec2(screenSize.width/2, screenSize.height/2);
  Vec2 touch = Vec2(screenPosition.x, screenPosition.y);
  float distance = center.distance(touch);
  if (distance < screenSize.width * m_ratioToCancel / 2)
    return false;
  else
    return true;
}
