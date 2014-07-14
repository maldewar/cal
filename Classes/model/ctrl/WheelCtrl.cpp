#include "WheelCtrl.h"
#include "../../util/CMath.h"

WheelCtrl::WheelCtrl() : Node() {
  m_state = WHEEL_CTRL_STATE_HIDDEN;
  m_armature = nullptr;
  m_pauseScene = false;
  m_scene = nullptr;
  m_targetAngle = 0;
}

WheelCtrl::~WheelCtrl() {
}

WheelCtrl* WheelCtrl::create(WorldLevelScene* scene)
{
  WheelCtrl *wheelCtrl = new (std::nothrow) WheelCtrl();
  if (wheelCtrl && wheelCtrl->init(scene))
  {
    wheelCtrl->autorelease();
    return wheelCtrl;
  }
  CC_SAFE_DELETE(wheelCtrl);
  return nullptr;
}

bool WheelCtrl::init(WorldLevelScene* scene)
{
  m_armature = cocostudio::Armature::create("wheelCtrl");
  m_armature->setVisible(false);
  if (m_armature) {
    addChild(m_armature);
    m_scene = scene;
    scheduleUpdate();
    return true;
  }
  return false;
}

void WheelCtrl::show() {
  m_armature->setVisible(true);
  if (m_scene) {
    if (m_scene->gravityAngleRotatesWorld()) {
      m_armature->setRotation(-CC_RADIANS_TO_DEGREES(-M_PI_2));
    } else {
      m_armature->setRotation(-CC_RADIANS_TO_DEGREES(m_scene->getGravityAngle()));
    }
    if (m_pauseScene) {
      m_scene->pause(true);
    }
  }
  m_armature->getAnimation()->playWithIndex(WHEEL_CTRL_ANIM_SHOWING);
}

void WheelCtrl::hide() {
  if (m_pauseScene && m_scene) {
    m_scene->pause(false);
  }
  m_armature->getAnimation()->playWithIndex(WHEEL_CTRL_ANIM_HIDING);
}

void WheelCtrl::update(float dt) {
}

void WheelCtrl::setWorldLevelScene(WorldLevelScene* scene) {
  m_scene = scene;
}

void WheelCtrl::setTargetAngle(float angle) {
  m_armature->setRotation(CC_RADIANS_TO_DEGREES(-angle));
  if (m_scene->gravityAngleRotatesWorld()) {
    m_targetAngle = angle + m_scene->getGravityAngle() + M_PI_2;
  } else {
    m_targetAngle = angle;
  }
}

void WheelCtrl::applyTargetAngle() {
  CCLOG("Applying angle %f", m_targetAngle);
  m_scene->setGravityAngle(m_targetAngle);
}
