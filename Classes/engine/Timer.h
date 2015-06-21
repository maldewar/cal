#ifndef _TIMER_H_
    #define _TIMER_H_

#include "cocos2d.h"

class Timer {
private:
  float m_duration;
  float m_lapse;

public:
  /**
   * Constructor.
   * @param duration Time between intervals in seconds.
   */
  Timer(float duration);
  bool step(float delta);
  void reset();
};

#endif
