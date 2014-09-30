#include "WheelCtrl.h"
#include "../../util/CMath.h"

WheelCtrl::WheelCtrl() : Node() {
  m_state = WHEEL_CTRL_STATE_HIDDEN;
  m_type = WHEEL_CTRL_TYPE_POINTER;
  m_armature = nullptr;
  m_pauseScene = false;
  m_scene = nullptr;
  m_targetAngle = 0;
}

WheelCtrl::~WheelCtrl() {
}

WheelCtrl* WheelCtrl::create(WorldLevelScene* scene, int type)
{
  WheelCtrl *wheelCtrl = new (std::nothrow) WheelCtrl();
  if (wheelCtrl && wheelCtrl->init(scene, type))
  {
    wheelCtrl->autorelease();
    return wheelCtrl;
  }
  CC_SAFE_DELETE(wheelCtrl);
  return nullptr;
}

bool WheelCtrl::init(WorldLevelScene* scene, int type)
{
  m_armature = cocostudio::Armature::create("wheelCtrl");
  //m_armature->setVisible(false);
  setVisible(false);
  m_type = type;
  m_isCancelled = false;
  if (m_armature) {
    addChild(m_armature);
    m_scene = scene;
    scheduleUpdate();
    return true;
  }
  return false;
}

void WheelCtrl::show(bool ease) {
  //m_armature->setVisible(true);
  setVisible(true);
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
  CCLOG("WheelCtrl::show type:%d", m_type);
  switch (m_type) {
    case WHEEL_CTRL_TYPE_SELECT:
      if (ease)
        m_armature->getAnimation()->playWithIndex(WHEEL_CTRL_ANIM_SELECT_SHOWING);
      else
        m_armature->getAnimation()->playWithIndex(WHEEL_CTRL_ANIM_SELECT);
      break;
    case WHEEL_CTRL_TYPE_CURSOR:
      if (ease)
        m_armature->getAnimation()->playWithIndex(WHEEL_CTRL_ANIM_CURSOR_SHOWING);
      else
        m_armature->getAnimation()->playWithIndex(WHEEL_CTRL_ANIM_CURSOR);
      break;
    default:
      if (ease) {
        if (!m_isCancelled)
          m_armature->getAnimation()->playWithIndex(WHEEL_CTRL_ANIM_POINTER_SHOWING);
        else
          m_armature->getAnimation()->playWithIndex(WHEEL_CTRL_ANIM_CIRCLE_SHOWING);
      } else {
        if (!m_isCancelled)
          m_armature->getAnimation()->playWithIndex(WHEEL_CTRL_ANIM_POINTER);
        else
          m_armature->getAnimation()->playWithIndex(WHEEL_CTRL_ANIM_CIRCLE);
      }
  }
  if (isVisible()) {
    CCLOG("WheelCtrl::show is visible");
  } else {
    CCLOG("WheelCtrl::show this is not visible");
  }
}

void WheelCtrl::hide(bool ease) {
  if (m_pauseScene && m_scene) {
    m_scene->pause(false);
  }
  switch (m_type) { 
    case WHEEL_CTRL_TYPE_SELECT:
      if (ease)
        m_armature->getAnimation()->playWithIndex(WHEEL_CTRL_ANIM_SELECT_HIDING);
      else {
        //m_armature->setVisible(false);
        setVisible(false);
        m_armature->getAnimation()->playWithIndex(WHEEL_CTRL_ANIM_SELECT);
      }
      break;
    case WHEEL_CTRL_TYPE_CURSOR:
      if (ease)
        m_armature->getAnimation()->playWithIndex(WHEEL_CTRL_ANIM_CURSOR_HIDING);
      else {
        //m_armature->setVisible(false);
        setVisible(false);
        m_armature->getAnimation()->playWithIndex(WHEEL_CTRL_ANIM_CURSOR);
      }
      break;
    default:
      if (ease) {
        if (!m_isCancelled)
          m_armature->getAnimation()->playWithIndex(WHEEL_CTRL_ANIM_POINTER_HIDING);
        else
          m_armature->getAnimation()->playWithIndex(WHEEL_CTRL_ANIM_CIRCLE_HIDING);
      } else {
        //m_armature->setVisible(false);
        setVisible(false);
        if (!m_isCancelled)
          m_armature->getAnimation()->playWithIndex(WHEEL_CTRL_ANIM_POINTER);
        else
          m_armature->getAnimation()->playWithIndex(WHEEL_CTRL_ANIM_CIRCLE);
      }
  }
}

void WheelCtrl::update(float dt) {
}

void WheelCtrl::setWorldLevelScene(WorldLevelScene* scene) {
  m_scene = scene;
}

void WheelCtrl::setTargetAngle(float angle) {
  if (m_isCancelled) {
    m_isCancelled = false;
    show(false);
  }
  m_armature->setRotation(CC_RADIANS_TO_DEGREES(-angle));
  if (m_scene->gravityAngleRotatesWorld()) {
    m_targetAngle = angle + m_scene->getGravityAngle() + M_PI_2;
  } else {
    m_targetAngle = angle;
  }
}

void WheelCtrl::applyTargetAngle() {
  m_scene->setGravityAngle(m_targetAngle);
  setVisible(false);
}

void WheelCtrl::cancel() {
  m_isCancelled = true;
  m_armature->getAnimation()->playWithIndex(WHEEL_CTRL_ANIM_CIRCLE);
}

bool WheelCtrl::isCancelled() {
  return m_isCancelled;
}

