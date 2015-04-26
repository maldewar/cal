#ifndef __DRAGGABLE_COMPONENT_H__
#define __DRAGGABLE_COMPONENT_H__

#include "Box2D/Box2D.h"

const int DRAGGABLE_STATE_LOOSE = 0;
const int DRAGGABLE_STATE_AFOOT = 1;

class DraggableComponent
{
protected:
  bool m_active;
  float m_pinX;
  float m_pinY;
  b2Body* m_body;

public:
  /**
   * Class constructor.
   */
  DraggableComponent(void);
  ~DraggableComponent(void);
  void setActive(bool active);
  bool isActive();
  void setPinX(float pinX);
  float getPinX();
  void setPinY(float pinY);
  float getPinY();
  void setBody(b2Body* body);

};

#endif // __DRAGGABLE_COMPONENT_H__
