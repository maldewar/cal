#include "cocos2d.h"
#include "AIComponentWanderCmd.h"
#include "../scene/WorldLevelScene.h"
#include "../util/CMath.h"

AIComponentWanderCmd::AIComponentWanderCmd() : AIComponentCmd() {
  m_type = Type::Wander;
  m_wanderType = WanderType::None;
  m_maxSpeed = 2;
  m_maxForce = 4.5;
  m_currentWalkStatus   = Walk::Stop;
  m_currentWalkDuration = 0;
  m_currentWalkLapse    = 0;
  m_stayBias      = 0.33;
  m_moveRightBias = 0.33;
  m_moveLeftBias  = 0.33;
}

AIComponentWanderCmd::AIComponentWanderCmd(b2Vec2 *target) : AIComponentCmd() {
  m_type         = Type::Wander;
  m_wanderType   = WanderType::Point;
  m_around       = target;
  m_aroundBody   = nullptr;
}

AIComponentWanderCmd::AIComponentWanderCmd(b2Body *target) : AIComponentCmd() {
  m_type         = Type::Wander;
  m_wanderType   = WanderType::Body;
  m_around       = nullptr;
  m_aroundBody   = target;
}

void AIComponentWanderCmd::setMaxSpeed(float maxSpeed) {
  m_maxSpeed = maxSpeed;
}

void AIComponentWanderCmd::setMaxForce(float maxForce) {
  m_maxForce = maxForce;
}

AIComponentCmd::Walk AIComponentWanderCmd::getNextWalk() {
  float chance      = CMath::random(0, 1);
  float chanceRange = m_stayBias;
  cocos2d::log("chance: %f", chance);
  cocos2d::log("chanceRange: %f", chanceRange);
  if (chance < chanceRange) {
    //TODO: get duration based on stay animation.
    m_currentWalkDuration = 2;
    cocos2d::log("WALK STOP.");
    return Walk::Stop;
  } else {
    //TODO: randomize walking time.
    m_currentWalkDuration = 2;
    chanceRange += m_moveRightBias;
    cocos2d::log("chanceRange: %f", chanceRange);
    if (chance < chanceRange) {
      cocos2d::log("WALK RIGHT.");
      return Walk::Right;
    } else {
      cocos2d::log("WALK LEFT.");
      return Walk::Left;
    }
  }
}

void AIComponentWanderCmd::update(float dt, b2Body* body) {
  if (m_currentWalkLapse < m_currentWalkDuration) {
    m_currentWalkLapse += dt;
    walk(body, m_currentWalkStatus);
  } else {
    m_currentWalkStatus = getNextWalk();
    m_currentWalkLapse = 0;
  }
  //CCLOG("Updating Wander Cmd target:%f,%f", m_target_point->x, m_target_point->y);
  /*
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
  */
}
