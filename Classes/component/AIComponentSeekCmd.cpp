#include "cocos2d.h"
#include "AIComponentSeekCmd.h"
#include "../scene/WorldLevelScene.h"

AIComponentSeekCmd::AIComponentSeekCmd(b2Vec2 *target) : AIComponentCmd() {
  m_type         = AI_CMD_SEEK;
  m_seeks_body   = false;
  m_target_point = target;
  m_max_speed = 2.0f;
  m_max_force = 4.5f;
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
  //CCLOG("Updating Seek Cmd target:%f,%f", m_target_point->x, m_target_point->y);
  m_desire = b2Vec2(m_target_point->x, m_target_point->y) - body->GetPosition();
  m_desire.Normalize();
  m_desire *= m_max_speed;
  m_velocity = body->GetLinearVelocity();
  m_velocity = m_desire - m_velocity;
  if (m_velocity.Length() > m_max_force) {
    m_velocity.Normalize();
    m_velocity *= m_max_force;
  }
  //m_velocity += WorldLevelScene::getGravity();
  CCLOG("Force to apply, x: %f, y: %f", m_velocity.x, m_velocity.y);
  CCLOG("Gravity x:%f y:%f", WorldLevelScene::getGravity().x, WorldLevelScene::getGravity().y);
  //m_velocity += WorldLevelScene::getGravity();
  body->ApplyForceToCenter(m_velocity, true);
}
