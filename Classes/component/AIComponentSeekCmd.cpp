#include "cocos2d.h"
#include "AIComponentSeekCmd.h"

AIComponentSeekCmd::AIComponentSeekCmd(b2Vec2 *target) : AIComponentCmd() {
  m_type         = AI_CMD_SEEK;
  m_seeks_body   = false;
  m_target_point = target;
  m_max_speed = 0.02f;
  m_max_force = 0.04f;
}

AIComponentSeekCmd::AIComponentSeekCmd(b2Body *target) : AIComponentCmd() {
  m_type        = AI_CMD_SEEK;
  m_seeks_body  = true;
  m_target_body = target;
}

void AIComponentSeekCmd::SetMaxSpeed(float maxSpeed) {
  m_max_speed = maxSpeed;
}

void AIComponentSeekCmd::SetMaxForce(float maxForce) {
  m_max_force = maxForce;
}

void AIComponentSeekCmd::Update(float dt, b2Body *body) {
  CCLOG("Updating Seek Cmd target:%f,%f", m_target_point->x, m_target_point->y);
}
