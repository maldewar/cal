#ifndef __AI_COMPONENT_CMD_H__
#define __AI_COMPONENT_CMD_H__

#include "Box2D/Box2D.h"

class AIComponentCmd
{
public:
  enum Type {
    Stay,
    Seek,
    GoTo,
    Follow,
    Evade,
    Wander 
  };
  enum Walk {
    Right,
    Stop,
    Left
  };
  enum Awareness {
    None,
    Evade_,
    Seek_
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
  /**
   * Applies a force to make the body walk.
   * @param body Body of the entity to apply the force to.
   * @param direction Enum for the pulling direction.
   */
  virtual void walk(b2Body* body, Walk direction);
  virtual void correct();
  virtual void onDirectionChange(int direction);
  int getAnimation();
  /**
   * Evaluates the command's goal.
   * @return 1 if the goal is met.
   */
  virtual float getCompleteness();
  /**
   * Enumeration for awareness.
   * @return int Enumaration for entities found.
   */
  virtual int getAwareness();

protected:
  virtual b2Vec2 getDirectionForce(AIComponentCmd::Walk direction,
                                  float desiredVelocity,
                                  b2Vec2 currentVelocity,
                                  float bodyMass);

};

#endif // __AI_COMPONENT_CMD_H__
