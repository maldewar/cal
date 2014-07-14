#include "WorldLevelCtrlLayer.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"
#include "ui/UILayout.h"
#include "../scene/WorldLevelScene.h"
#include "../util/CMath.h"

USING_NS_CC;

WorldLevelCtrlLayer* WorldLevelCtrlLayer::create(WorldLevelScene* scene) {
  WorldLevelCtrlLayer* worldLevelCtrlLayer = new (std::nothrow) WorldLevelCtrlLayer();
  if (worldLevelCtrlLayer && worldLevelCtrlLayer->init(scene)) {
    worldLevelCtrlLayer->autorelease();
    return worldLevelCtrlLayer;
  }
  CC_SAFE_DELETE(worldLevelCtrlLayer);
  return nullptr;
}

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

void WorldLevelCtrlLayer::update(float dt) {
  if (getState() == State::Showing) {
    if (m_touchTime < m_showingTime) {
      m_touchTime += dt;
    } else {
      pushState(State::Waiting);
    }
  } else if (getState() == State::Waiting) {
  }
}

void WorldLevelCtrlLayer::playAnimationIn(int state) {
  switch (state) {
    case State::Showing:
      m_opacityLayout->setVisible(true);
      break;
  }
}

void WorldLevelCtrlLayer::playAnimationOut(int state) {
  CCLOG("Animation out %d", state);
  switch (state) {
    case State::Showing:
      m_opacityLayout->setVisible(false);
      if (m_ctrl == CTRL_GRAVITRON) {
        m_wheelCtrl->hide();
      }
      break;
  }
}

void WorldLevelCtrlLayer::playStateAnimation(std::string name) {
  /*
  m_currentAction = cocostudio::ActionManagerEx::getInstance()->getActionByName(WorldLevelCtrlLayer::GAME_MENU_JSON, name.c_str());
  m_currentAction->play(CallFunc::create(this, callfunc_selector(WorldLevelCtrlLayer::finishStateAnimation)));
  */
}

void WorldLevelCtrlLayer::beginCtrlTouch(int ctrl, Entity* entity) {
  pushState(State::Showing);
  m_touchTime = 0;
  m_ctrl = ctrl;
  if (m_ctrl == CTRL_GRAVITRON) {
    m_wheelCtrl->show();
  }
}

void WorldLevelCtrlLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) {
  if (getState() == State::Waiting) {
    Touch* touch = touches[0];
    Point screenPos = touch->getLocationInView();
    if (m_ctrl == CTRL_GRAVITRON) {
      float angle = CMath::GetAngle(m_center->x, m_center->y, screenPos.x, 1080 - screenPos.y);
      m_wheelCtrl->setTargetAngle(angle);
    }
  }
}

void WorldLevelCtrlLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) {
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
