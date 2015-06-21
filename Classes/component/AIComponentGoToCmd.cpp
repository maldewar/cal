#include "cocos2d.h"
#include "AIComponentGoToCmd.h"
#include "../scene/WorldLevelScene.h"
#include "../util/CMath.h"

AIComponentGoToCmd::AIComponentGoToCmd(b2Vec2* target) : AIComponentCmd() {
  m_type     = Type::GoTo;
  m_target   = target;
  m_maxSpeed = 2;
  m_maxForce = 4.5;
}

void AIComponentGoToCmd::setMaxSpeed(float maxSpeed) {
  m_maxSpeed = maxSpeed;
}

void AIComponentGoToCmd::setMaxForce(float maxForce) {
  m_maxForce = maxForce;
}

void AIComponentGoToCmd::update(float dt, b2Body* body) {
  //cocos2d::log("Go To Cmd.");
  /*
  if (m_currentWalkLapse < m_currentWalkDuration) {
    m_currentWalkLapse += dt;
    walk(body, m_currentWalkStatus);
  } else {
    m_currentWalkStatus = getNextWalk();
    m_currentWalkLapse = 0;
    switch(m_currentWalkStatus) {
      case Walk::Left:
      case Walk::Right: {
        m_animation = ENTITY_ANIM_WALK;
        break;
      }
      default: {
        m_animation = ENTITY_ANIM_STAND;
      }
    }
  }
  */
}
