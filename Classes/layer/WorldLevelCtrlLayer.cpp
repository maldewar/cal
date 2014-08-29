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
  m_showingTime = 0;

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
      pushState(State::Waiting);
    }
  }
}

void WorldLevelCtrlLayer::beginCtrlTouch(Entity* entity) {
  pushState(State::Showing);
  m_touchTime = 0;
  m_entity = entity;
  onBeginCtrlTouch();
}

void WorldLevelCtrlLayer::endCtrlTouch() {
  onEndCtrlTouch();
}

void WorldLevelCtrlLayer::cancelCtrlTouch() {
  onCancelCtrlTouch();
}

void WorldLevelCtrlLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) {
  if (getState() == State::Showing && m_touchTime < m_showingTime) {
    popState();
    cancelCtrlTouch();
  } else if(getState() == State::Waiting) {
    popState(2);
    endCtrlTouch();
  }
}

void WorldLevelCtrlLayer::onBeginCtrlTouch() {
}

void WorldLevelCtrlLayer::onEndCtrlTouch() {
}

void WorldLevelCtrlLayer::onCancelCtrlTouch() {
}
