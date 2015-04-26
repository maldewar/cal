#include "AIComponentCmd.h"
#include "cocos2d.h"
#include "../util/CMath.h"
#include "../scene/WorldLevelScene.h"

AIComponentCmd::AIComponentCmd() {
  m_type = Type::Stay;
  m_animation = 0;
}

AIComponentCmd::~AIComponentCmd() {
}

AIComponentCmd::Type AIComponentCmd::getType() {
  return m_type;
}

void AIComponentCmd::update(float dt, b2Body *body) {
}

void AIComponentCmd::walk(b2Body* body, AIComponentCmd::Walk direction) {
  if (direction == Walk::Right || direction == Walk::Left) {
    body->ApplyLinearImpulse(getDirectionForce(
                             direction,
                             0.1,
                             body->GetLinearVelocity(),
                             body->GetMass()
                           ),
                           body->GetWorldCenter(),
                           true);
  }
}

void AIComponentCmd::correct() {
}

void AIComponentCmd::onDirectionChange(int direction) {
}

int AIComponentCmd::getAnimation() {
  return m_animation;
}

b2Vec2 AIComponentCmd::getDirectionForce(AIComponentCmd::Walk direction,
                                         float desiredVelocity,
                                         b2Vec2 currentVelocity,
                                         float bodyMass) {
  //float directionAngle = WorldLevelScene::getGravityAngle();
  b2Vec2 desiredVelocityVec;
  switch (direction) {
    case AIComponentCmd::Walk::Right:
      desiredVelocityVec = WorldLevelScene::getRightNormal();
      break;
    case AIComponentCmd::Walk::Stop:
      desiredVelocityVec = b2Vec2(0,0);
      break;
    case AIComponentCmd::Walk::Left:
      desiredVelocityVec = WorldLevelScene::getLeftNormal();
      break;
  }
  //b2Vec2 desiredVelocityVec = *CMath::getWorldPointAt(0, 0, desiredVelocity, directionAngle);
  desiredVelocityVec -= currentVelocity;
  desiredVelocityVec *= bodyMass * 0.3;
  return desiredVelocityVec;
}
