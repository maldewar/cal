#ifndef __AI_COMPONENT_GO_TO_CMD_H__
#define __AI_COMPONENT_GO_TO_CMD_H__

#include "Box2D/Box2D.h"

#include "AIComponentCmd.h"

class AIComponentGoToCmd : public AIComponentCmd
{
private:
  //GoToType m_goToType;
  float m_maxDistance;
  b2Vec2* m_target;
  float m_maxSpeed;
  float m_maxForce;

public:
  /**
   * Class constructor.
   */
  AIComponentGoToCmd(b2Vec2* target);
  void setMaxSpeed(float maxSpeed);
  void setMaxForce(float maxForce);
  virtual void update(float dt, b2Body * body);

};

#endif // __AI_COMPONENT_GO_TO_CMD_H__
