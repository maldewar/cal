#include "AIComponent.h"
#include "cocos2d.h"
#include "../util/CMath.h"

float AIComponent::s_afoot_timeout = 0.1f;
float AIComponent::s_afoot_angular_velocity_tolerance = 7.0f;
//static float s_afoot_linear_velocity_tolerance = 5.0f;

AIComponent::AIComponent() {
  m_disturbedDuration = 0.3;
  m_disturbedLapse = m_disturbedDuration;

  m_afoot_timeout = 0;
  m_afoot_marked = false;
  m_state = AI_STATE_LOOSE;
  m_substate = AI_SUBSTATE_FALL;
  m_body = nullptr;
  m_canJump = true;
  m_lastPosition = new b2Vec2(0,0);
  m_rightDirection = true;
  m_touchGround = false;

  m_tween          = false;
  m_tweenCount     = 0;
  m_tweenDuration  = 0;
  m_tweenNextSubstate = 0;

  m_cmd = nullptr;
}

AIComponent::~AIComponent(){
}

void AIComponent::setBody(b2Body* body) {
  m_body = body;
}

void AIComponent::setAfoot() {
  m_afoot_marked = true;
  m_touchGround = true;
  m_afoot_timeout = 0;
}

void AIComponent::setLoose() {
  if (m_body) {
    setState(AI_STATE_LOOSE);
    m_afoot_marked = false;
    m_touchGround = false;
    cancelTween();
  }
}

bool AIComponent::isAfoot() {
  return (m_afoot_marked || m_state == AI_STATE_AFOOT);
}

bool AIComponent::isLoose() {
  return (m_state == AI_STATE_LOOSE);
}

void AIComponent::update(float dt) {
  if (m_body == nullptr)
    return;
  if (m_state == AI_STATE_LOOSE) {
    if (m_afoot_marked) {
      m_afoot_timeout += dt;
      if (m_afoot_timeout > s_afoot_timeout) {
        if (abs(m_body->GetAngularVelocity()) <= s_afoot_angular_velocity_tolerance) {
          setState(AI_STATE_AFOOT);
          m_afoot_marked = false;
        } else {
          setSubstate(AI_SUBSTATE_ROLL);
        }
      }
    }
  } else {
    // STATE AFOOT
    if (m_cmd && m_disturbedLapse >= m_disturbedDuration) {
      m_cmd->update(dt, m_body);
    } else {
      m_disturbedLapse += dt;
    }
  }
  // TODO: get angle from gravity
  if (m_touchGround && (m_lastPosition->x != m_body->GetPosition().x ||
      m_lastPosition->y != m_body->GetPosition().y)) {
    float angle = CMath::getAngleOffset(CMath::getAngle(m_lastPosition->x,
                                                        m_lastPosition->y,
                                                        m_body->GetPosition().x,
                                                        m_body->GetPosition().y),
                                        M_PI_2);
    float distance = CMath::getDistance(m_lastPosition->x,
                                        m_lastPosition->y,
                                        m_body->GetPosition().x,
                                        m_body->GetPosition().y);
    if (distance > 0.0001f) {
      if (m_rightDirection && angle < 0) {
        onDirectionChange(false);
      } else if (!m_rightDirection && angle > 0) {
        onDirectionChange(true);
      }
    }
  }
  if (m_tween) {
    m_tweenCount += dt;
    if (m_tweenCount >= m_tweenDuration) {
      setSubstate(m_tweenNextSubstate);
      cancelTween();
    }
  }
  /*
  if (m_state == AI_STATE_AFOOT && m_substate == AI_SUBSTATE_STILL) {
    b2Vec2 vel = m_body->GetLinearVelocity();
    float desiredVel = 0.09f;
    //float velChange = desiredVel - vel.x;
    //float force = m_body->GetMass() * velChange / (1/60.0); //f = mv/t
    //m_body->ApplyForce( b2Vec2(force,0), m_body->GetWorldCenter(), true);
    float velChange = desiredVel - vel.x;
    float impulse = m_body->GetMass() * velChange; //disregard time factor
    m_body->ApplyLinearImpulse( b2Vec2(impulse,0), m_body->GetWorldCenter(), true);
  }
  */
  m_lastPosition->x = m_body->GetPosition().x;
  m_lastPosition->y = m_body->GetPosition().y;

  //Execute Command
  //if (m_cmd) {
  //  m_cmd->Update(dt, m_body);
  //}
}

void AIComponent::setState(int state) {
  switch(state) {
    case AI_STATE_LOOSE:
      if (m_body) {
        m_body->SetFixedRotation(false);
      }
      setSubstate(AI_SUBSTATE_FALL);
      break;
    case AI_STATE_AFOOT:
      if (m_body) {
        m_body->SetTransform(m_body->GetPosition(), 0);
        m_body->SetFixedRotation(true);
        float angle = atan2(m_body->GetWorld()->GetGravity().y, m_body->GetWorld()->GetGravity().x);
        m_body->SetTransform(m_body->GetPosition(), angle + M_PI_2);
      }
      // TODO: check impact force, angular-linear velocity to stand or still.
      if (m_substate_stand_duration > 0) {
        setSubstate(AI_SUBSTATE_STAND);
      } else {
        setSubstate(AI_SUBSTATE_STILL);
      }
      break;
  }
  onStateChange(state, m_substate);
  m_state = state;
}

void AIComponent::setSubstate(int substate) {
  switch(substate) {
    case AI_SUBSTATE_STAND:
      setTween(m_substate_stand_duration, AI_SUBSTATE_STILL);
      break;
    case AI_SUBSTATE_STILL:
      cancelTween();
      break;
    case AI_SUBSTATE_WALK:
      cancelTween();
      break;
  }
  onSubstateChange(substate);
  m_substate = substate;
}

void AIComponent::setTween(float duration, int nextSubstate) {
  m_tweenDuration = duration;
  m_tweenCount = 0;
  m_tweenNextSubstate = nextSubstate;
  m_tween = true;
}

void AIComponent::cancelTween() {
  m_tween = false;
}

void AIComponent::onStateChange(int state, int substate) {
}

void AIComponent::onSubstateChange(int substate) {
}

void AIComponent::onDirectionChange(bool isRight) {
  m_rightDirection = isRight;
}

void AIComponent::pushCommand(AIComponentCmd *cmd) {
  m_cmd = cmd;
  m_cmds.push(cmd);
}

AIComponentCmd* AIComponent::popCommand() {
  AIComponentCmd* lastCmd = nullptr;
  if (m_cmds.size() > 0) {
    lastCmd = m_cmds.top();
    m_cmds.pop();
    if (m_cmds.size() == 0) {
      m_cmd = nullptr;
    } else {
      m_cmd = m_cmds.top();
    }
  }
  return lastCmd;
}

void AIComponent::disturb() {
  if (m_cmd) {
    m_cmd->correct();
  }
  m_disturbedLapse = 0;
}

void AIComponent::commandWander() {
  AIComponentWanderCmd* cmd = new AIComponentWanderCmd();
  pushCommand(cmd);
}

void AIComponent::commandWander(b2Body* target) {
}

void AIComponent::commandWander(b2Vec2* target) {
}

void AIComponent::setSubstateStandDuration(float duration) {
  m_substate_stand_duration = duration;
}
