#ifndef __AI_COMPONENT_H__
#define __AI_COMPONENT_H__

#include <stack>
#include "Box2D/Box2D.h"

#include "AIComponentWanderCmd.h"
#include "AIComponentGoToCmd.h"

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
  float m_disturbedDuration;
  float m_disturbedLapse;
  float m_afoot_timeout;
  bool m_afoot_marked;
  float m_loose_timeout;
  bool m_loose_marked;
  int m_state;
  int m_substate;
  b2Body* m_body;
  bool m_canJump;
  b2Vec2* m_lastPosition;
  int m_direction;
  bool m_touchGround;

  bool m_tween;
  float m_tweenCount;
  float m_tweenDuration;
  int m_tweenNextSubstate;

  float m_substate_stand_duration;
  static float s_afoot_angular_velocity_tolerance;
  static float s_afoot_timeout;
  static float s_loose_timeout;

  AIComponentCmd* m_cmd;
  std::stack<AIComponentCmd*> m_cmds;
  int m_animation;

public:
  /**
   * Class constructor.
   */
  AIComponent(void);
  ~AIComponent(void);
  void setAfoot();
  void setLoose();
  bool isAfoot();
  bool isLoose();
  void setSubstateStandDuration(float duration);
  virtual void setBody(b2Body* body);
  virtual void update(float dt);
  virtual void onStateChange(int state, int substate);
  virtual void onSubstateChange(int substate);
  virtual void onDirectionChange(int direction);
  virtual void pushCommand(AIComponentCmd *cmd);
  virtual AIComponentCmd* popCommand();
  virtual void disturb();
  virtual void commandWander();
  virtual void commandWander(b2Body* target);
  virtual void commandWander(b2Vec2* target);
  virtual void commandGoTo(float x, float y);
  int getAnimation();

protected:
  virtual void setState(int state);
  virtual void setSubstate(int substate);
  virtual void setTween(float duration, int nextSubstate);
  virtual void cancelTween();

};

#endif // __AI_COMPONENT_H__
