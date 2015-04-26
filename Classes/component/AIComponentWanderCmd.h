#ifndef __AI_COMPONENT_WANDER_CMD_H__
#define __AI_COMPONENT_WANDER_CMD_H__

#include "Box2D/Box2D.h"

#include "AIComponentCmd.h"

class AIComponentWanderCmd : public AIComponentCmd
{
public:
  enum WanderType {
    None,
    Point,
    Body
  };

private:
  WanderType m_wanderType;
  float m_maxDistance;
  b2Vec2* m_around;
  b2Body* m_aroundBody;
  float m_maxSpeed;
  float m_maxForce;
  /**
   * Current Walk status.
   */
  Walk m_currentWalkStatus;
  /**
   * Helper var for the duration
   * of a walk status.
   */
  float m_currentWalkDuration;
  /**
   * Helper var for the lapse
   * of a walk status.
   */
  float m_currentWalkLapse;
  /**
   * Probability for staying.
   */
  float m_stayBias;
  /**
   * Probability for moving to the right.
   */
  float m_moveRightBias;
  /**
   * Probability for moving to the left.
   */
  float m_moveLeftBias;
  /**
   * If != 0 tells the next direction to take,
   * not randomly.
   */
  int m_sureNextDirection;

public:
  /**
   * Class constructor.
   */
  AIComponentWanderCmd();
  AIComponentWanderCmd(b2Vec2 *target);
  AIComponentWanderCmd(b2Body *target);
  void setMaxDistance(float maxDistance);
  void setMaxSpeed(float maxSpeed);
  void setMaxForce(float maxForce);
  Walk getNextWalk();
  void onDirectionChange(int direction);
  virtual void update(float dt, b2Body * body);

};

#endif // __AI_COMPONENT_WANDER_CMD_H__
