#ifndef __AI_COMPONENT_SEEK_CMD_H__
#define __AI_COMPONENT_SEEK_CMD_H__

#include <Box2D/Box2D.h>

#include "AIComponentCmd.h"

class AIComponentSeekCmd : public AIComponentCmd
{
private:
  bool m_seeks_body;
  b2Vec2 *m_target_point;
  b2Body *m_target_body;
  float m_max_speed;
  float m_max_force;
  b2Vec2 *m_velocity;
  b2Vec2 *m_desire;

public:
  /**
   * Class constructor.
   */
  AIComponentSeekCmd(b2Vec2 *target);
  AIComponentSeekCmd(b2Body *target);
  void SetMaxSpeed(float maxSpeed);
  void SetMaxForce(float maxForce);
  virtual void Update(float dt, b2Body * body);

};

#endif // __AI_COMPONENT_SEEK_CMD_H__
