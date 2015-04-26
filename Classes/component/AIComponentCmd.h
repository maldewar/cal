#ifndef __AI_COMPONENT_CMD_H__
#define __AI_COMPONENT_CMD_H__

#include "Box2D/Box2D.h"

const int AI_CMD_STAY   = 0;
const int AI_CMD_SEEK  = 1;
const int AI_CMD_FOLLOW = 2;

class AIComponentCmd
{
public:
  enum Type {
    Stay,
    Seek,
    Follow,
    Evade,
    Wander 
  };
  enum Walk {
    Right,
    Stop,
    Left
  };
protected:
  Type m_type;
  int m_animation;

public:
  /**
   * Class constructor.
   */
  AIComponentCmd();
  ~AIComponentCmd(void);
  Type getType();
  virtual void update(float dt, b2Body *body);
  virtual void walk(b2Body* body, Walk direction);
  virtual void correct();
  virtual void onDirectionChange(int direction);
  int getAnimation();

protected:
  virtual b2Vec2 getDirectionForce(AIComponentCmd::Walk direction,
                                  float desiredVelocity,
                                  b2Vec2 currentVelocity,
                                  float bodyMass);

};

#endif // __AI_COMPONENT_CMD_H__
