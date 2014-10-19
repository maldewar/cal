#ifndef __AI_COMPONENT_CMD_H__
#define __AI_COMPONENT_CMD_H__

#include <Box2D/Box2D.h>

const int AI_CMD_STAY   = 0;
const int AI_CMD_SEEK  = 1;
const int AI_CMD_FOLLOW = 2;

class AIComponentCmd
{
protected:
  int m_type;

public:
  /**
   * Class constructor.
   */
  AIComponentCmd();
  ~AIComponentCmd(void);
  int GetType();
  virtual void Update(float dt, b2Body *body);

};

#endif // __AI_COMPONENT_CMD_H__
