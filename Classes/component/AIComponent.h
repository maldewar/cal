#ifndef __AI_COMPONENT_H__
#define __AI_COMPONENT_H__

#include <Box2D/Box2D.h>

const int AI_STATE_LOOSE = 0;
const int AI_STATE_AFOOT = 1;
const int AI_STATE_LOOSE_AFOOT = 2;

const int AI_SUBSTATE_FALL = 0;
const int AI_SUBSTATE_ROLL = 1;

const int AI_SUBSTATE_STAND = 10;
const int AI_SUBSTATE_STILL = 11;
const int AI_SUBSTATE_WALK  = 12;

class AIComponent
{
protected:
  float m_afoot_timeout;
  bool m_afoot_marked;
  int m_state;
  int m_substate;
  b2Body* m_body;
  bool m_canJump;
  b2Vec2* m_lastPosition;
  bool m_rightDirection;
  bool m_touchGround;

  bool m_tween;
  float m_tweenCount;
  float m_tweenDuration;
  int m_tweenNextSubstate;

  float m_substate_stand_duration;
  static float s_afoot_angular_velocity_tolerance;
  static float s_afoot_timeout;

public:
  /**
   * Class constructor.
   */
  AIComponent(void);
  virtual ~AIComponent(void);
  virtual void setBody(b2Body* body);
  virtual void setAfoot();
  virtual void setLoose();
  virtual bool isAfoot();
  virtual bool isLoose();
  virtual void update(float dt);
  virtual void onStateChange(int state, int substate);
  virtual void onSubstateChange(int substate);
  virtual void onDirectionChange(bool isRight);
  void setSubstateStandDuration(float duration);

protected:
  virtual void setState(int state);
  virtual void setSubstate(int substate);
  virtual void setTween(float duration, int nextSubstate);
  virtual void cancelTween();
};

#endif // __AI_COMPONENT_H__
