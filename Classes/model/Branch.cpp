#include "Branch.h"
#include "Unit.h"
#include "../util/CMath.h"

Branch::Branch() : Entity(), ContactComponent() {
  m_state = BRANCH_STATE_ACTIVE;
  m_angle = 0;
  m_topAngle = 0;
  m_bottomAngle = 0;
  m_motorSpeed = 0;
}

Branch::~Branch() {}

int Branch::getType() {
  return ENTITY_TYPE_BRANCH;
}

Branch* Branch::create() {
  return Branch::create(false);
}

Branch* Branch::create(bool active) {
  Branch *gravitron = new (std::nothrow) Branch();
  if (gravitron && gravitron->init(active))
  {
    gravitron->autorelease();
    return gravitron;
  }
  CC_SAFE_DELETE(gravitron);
  return nullptr;
}

bool Branch::init(bool active)
{
  scheduleUpdate();
  setIsSensor(true);
  if (active) {
    activate(0);
  } else {
    deactivate(0);
  }
  return true;
}

void Branch::activate(float dt) {
  if (m_state == BRANCH_STATE_INACTIVE) {
    m_state = BRANCH_STATE_ACTIVE;
  }
}

void Branch::deactivate(float dt) {
  if (m_state == BRANCH_STATE_ACTIVE) {
    m_state = BRANCH_STATE_INACTIVE;
  }
}

void Branch::update(float dt) {
  Entity::update(dt);
}

void Branch::select(b2Body* body) {
  getWorldLevelLayer()->setNavigationEnabled(false);
  getWorldLevelLayer()->addTouchListener(this);
}

void Branch::addJoint(b2RevoluteJoint* joint) {
  m_joints.push_back(joint);
}

void Branch::setAngle(float angle) {
  m_angle = angle;
}

float Branch::getAngle() {
  return m_angle;
}

void Branch::setTopAngle(float topAngle) {
  m_topAngle = topAngle;
}

float Branch::getTopAngle() {
  return m_topAngle;
}

void Branch::setBottomAngle(float bottomAngle) {
  m_bottomAngle = bottomAngle;
}

float Branch::getBottomAngle() {
  return m_bottomAngle;
}

void Branch::setMotorSpeed(float motorSpeed) {
  m_motorSpeed = motorSpeed;
}

float Branch::getMotorSpeed() {
  return m_motorSpeed;
}

void Branch::applyAngle(float angle) {
  if (angle - M_PI_4 < m_topAngle && angle + M_PI_4 > m_bottomAngle) {
    if (angle > m_topAngle)
      angle = m_topAngle;
    else if (angle < m_bottomAngle)
      angle = m_bottomAngle;
    m_angle = angle;
    if (m_joints.size() > 0)
      m_angle /= m_joints.size();
    float jointAngle = 0;
    for (std::vector<b2RevoluteJoint*>::iterator it = m_joints.begin();
         it != m_joints.end(); ++it) {
      (*it)->SetMaxMotorTorque(m_motorSpeed*20);
      jointAngle = (*it)->GetJointAngle();
      if (m_angle < jointAngle) {
        (*it)->SetMotorSpeed(-m_motorSpeed);
        (*it)->SetLimits(m_angle, m_angle + 0.1);
      } else {
        (*it)->SetMotorSpeed(m_motorSpeed);
        (*it)->SetLimits(m_angle - 0.1, m_angle);
      }
    }
  }
}

void Branch::sensorReceive(b2Body* body, Entity* receivedEntity) {
  if (receivedEntity &&
      receivedEntity->getType() == ENTITY_TYPE_UNIT &&
      m_state == BRANCH_STATE_INACTIVE) {
    activate(0);
  }
}

bool Branch::onEndTouchEvent() {
  float baseAngle = m_body->GetAngle();
  cocos2d::Vec2* startTouch = getWorldLevelLayer()->getWorldLevelScene()->getStartTouch();
  cocos2d::Vec2* endTouch = getWorldLevelLayer()->getWorldLevelScene()->getEndTouch();
  float touchAngle = CMath::getAngle(startTouch->x,
                                     startTouch->y,
                                     endTouch->x,
                                     endTouch->y);
  touchAngle -= baseAngle;
  applyAngle(touchAngle);
  getWorldLevelLayer()->setNavigationEnabled(true);
  return true;
}
