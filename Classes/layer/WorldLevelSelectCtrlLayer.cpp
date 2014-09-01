#include "WorldLevelSelectCtrlLayer.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"
#include "ui/UILayout.h"
#include "../scene/WorldLevelScene.h"
#include "../util/CMath.h"

USING_NS_CC;

WorldLevelSelectCtrlLayer* WorldLevelSelectCtrlLayer::create(WorldLevelScene* scene) {
  WorldLevelSelectCtrlLayer* worldLevelSelectCtrlLayer = new (std::nothrow) WorldLevelSelectCtrlLayer();
  if (worldLevelSelectCtrlLayer && worldLevelSelectCtrlLayer->init(scene)) {
    worldLevelSelectCtrlLayer->autorelease();
    return worldLevelSelectCtrlLayer;
  }
  CC_SAFE_DELETE(worldLevelSelectCtrlLayer);
  return nullptr;
}

bool WorldLevelSelectCtrlLayer::init(WorldLevelScene* scene) {
  if ( !UILayer::init() ) {
    return false;
  }
  setScene(scene);

  // Wheel ctrl
  m_wheelCtrl = WheelCtrl::create(m_scene);
  m_wheelCtrl->setPosition(Vec2(m_winSize.width / 2, m_winSize.height / 2));
  addChild(m_wheelCtrl);

  m_center = new Vec2(m_winSize.width/2, m_winSize.height/2);
  m_touchTime = 0;
  m_showingTime = 0.34f;
  m_ctrl = 0;

  setTouchEnabled(true);
  scheduleUpdate();
  setAnchorPoint(Vec2(0,0));
  pushState(State::Inactive);
  return true;
}

void WorldLevelSelectCtrlLayer::update(float dt) {
  if (getState() == State::Showing) {
    if (m_touchTime < m_showingTime) {
      m_touchTime += dt;
    } else {
      pushState(State::Waiting);
    }
  } else if (getState() == State::Waiting) {
  }
}

void WorldLevelSelectCtrlLayer::playAnimationIn(int state) {
  switch (state) {
    case State::Showing:
      break;
  }
}

void WorldLevelSelectCtrlLayer::playAnimationOut(int state) {
  CCLOG("Animation out %d", state);
  switch (state) {
    case State::Showing:
      if (m_ctrl == CTRL_GRAVITRON) {
        m_wheelCtrl->hide();
      }
      break;
  }
}

void WorldLevelSelectCtrlLayer::playStateAnimation(std::string name) {
  /*
  m_currentAction = cocostudio::ActionManagerEx::getInstance()->getActionByName(WorldLevelSelectCtrlLayer::GAME_MENU_JSON, name.c_str());
  m_currentAction->play(CallFunc::create(this, callfunc_selector(WorldLevelSelectCtrlLayer::finishStateAnimation)));
  */
}

void WorldLevelSelectCtrlLayer::beginCtrlTouch(int ctrl, Entity* entity) {
  pushState(State::Showing);
  m_touchTime = 0;
  m_ctrl = ctrl;
  if (m_ctrl == CTRL_GRAVITRON) {
    m_wheelCtrl->show();
  }
}

void WorldLevelSelectCtrlLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) {
  if (getState() == State::Waiting) {
    Touch* touch = touches[0];
    Point screenPos = touch->getLocationInView();
    if (m_ctrl == CTRL_GRAVITRON) {
      float angle = CMath::GetAngle(m_center->x, m_center->y, screenPos.x, 1080 - screenPos.y);
      m_wheelCtrl->setTargetAngle(angle);
    }
  }
}

void WorldLevelSelectCtrlLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) {
  CCLOG("Touch ended");
  if (getState() == State::Showing && m_touchTime < m_showingTime) {
    popState();
  } else if(getState() == State::Waiting) {
    popState();
    popState();
    if (m_ctrl == CTRL_GRAVITRON) {
      m_wheelCtrl->applyTargetAngle();
    }
  }
}
