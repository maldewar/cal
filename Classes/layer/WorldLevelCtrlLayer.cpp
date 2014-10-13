#include "WorldLevelCtrlLayer.h"
#include "ui/UILayout.h"
#include "../scene/WorldLevelScene.h"
#include "../util/CMath.h"

USING_NS_CC;
bool WorldLevelCtrlLayer::init(WorldLevelScene* scene) {
  if ( !UILayer::init() ) {
    return false;
  }
  setScene(scene);
  // Opacity layout.
  m_opacityLayout = ui::Layout::create();
  m_opacityLayout->setSize(Size(1920, 1080));
  m_opacityLayout->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
  m_opacityLayout->setBackGroundColor(Color3B(0, 0, 0));
  m_opacityLayout->setOpacity(128);
  m_opacityLayout->setTouchEnabled(false);
  m_opacityLayout->setVisible(false);
  addChild(m_opacityLayout);

  m_center = new Vec2(m_winSize.width/2, m_winSize.height/2);
  m_touchTime = 0;
  m_afterHidingTime = 0;
  m_cooldownTime = 0;
  m_lastTriggerTime = 0;
  m_showingTime = 0;
  m_hidingTime = 0;
  m_isFadeToBlackCtrl = true;
  m_isLockingCtrl = true;
  m_isFollowingCtrl = false;
  m_isPausingCtrl = false;

  setTouchEnabled(true);
  scheduleUpdate();
  setAnchorPoint(Vec2(0,0));
  pushState(State::Inactive);
  return true;
}

void WorldLevelCtrlLayer::update(float dt) {
  if (getState() == State::Showing) {
    if (m_touchTime < m_showingTime) {
      m_touchTime += dt;
    } else {
      replaceState(State::Active);
    }
  }
  if (getState() == State::Hiding) {
    if (m_afterHidingTime < m_hidingTime) {
      m_hidingTime += dt;
    } else {
      replaceState(State::Inactive);
    }
  }
  if (m_cooldownTime > 0 && m_lastTriggerTime < m_cooldownTime) {
    m_lastTriggerTime += dt;
  }
}

void WorldLevelCtrlLayer::beginCtrlTouch(Entity* entity) {
  if (m_cooldownTime == 0 || m_lastTriggerTime > m_cooldownTime) {
    replaceState(State::Showing);
    m_touchTime = 0;
    m_entity = entity;
    onBeginCtrlTouch(m_entity);
    if (m_isFadeToBlackCtrl) {
      m_opacityLayout->setVisible(true);
    }
    m_scene->onBeginCtrl(this);
  }
}

void WorldLevelCtrlLayer::endCtrlTouch() {
  onEndCtrlTouch();
  if (m_isFadeToBlackCtrl) {
    m_opacityLayout->setVisible(false);
  }
  m_scene->onEndCtrl(this);
  m_lastTriggerTime = 0;
}

void WorldLevelCtrlLayer::cancelCtrlTouch() {
  onCancelCtrlTouch();
  if (m_isFadeToBlackCtrl) {
    m_opacityLayout->setVisible(false);
  }
  m_scene->onCancelCtrl(this);
}

void WorldLevelCtrlLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) {
  if (getState() == State::Showing && m_touchTime < m_showingTime) {
    replaceState(State::Inactive);
    m_scene->onCancelCtrl(this);
    cancelCtrlTouch();
  } else if(getState() == State::Active) {
    replaceState(State::Hiding);
    m_afterHidingTime = 0;
    m_scene->onEndCtrl(this);
    endCtrlTouch();
  }
}

bool WorldLevelCtrlLayer::isFadeToBlackCtrl() {
  return m_isFadeToBlackCtrl;
}

void WorldLevelCtrlLayer::setFadeToBlackCtrl(bool isFadeToBlackCtrl) {
  m_isFadeToBlackCtrl = isFadeToBlackCtrl;
}

bool WorldLevelCtrlLayer::isLockingCtrl() {
  return m_isLockingCtrl;
}

void WorldLevelCtrlLayer::setLockingCtrl(bool isLockingCtrl) {
  m_isLockingCtrl = isLockingCtrl;
}

bool WorldLevelCtrlLayer::isFollowingCtrl() {
  return m_isFollowingCtrl;
}

void WorldLevelCtrlLayer::setFollowingCtrl(bool isFollowingCtrl) {
  m_isFollowingCtrl = isFollowingCtrl;
}

bool WorldLevelCtrlLayer::isPausingCtrl() {
  return m_isPausingCtrl;
}

void WorldLevelCtrlLayer::setPausingCtrl(bool isPausingCtrl) {
  m_isPausingCtrl = isPausingCtrl;
}

Entity* WorldLevelCtrlLayer::getEntity() {
  return m_entity;
}

void WorldLevelCtrlLayer::onBeginCtrlTouch(Entity* entity) {
}

void WorldLevelCtrlLayer::onEndCtrlTouch() {
}

void WorldLevelCtrlLayer::onCancelCtrlTouch() {
}
