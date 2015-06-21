#include "Timer.h"

Timer::Timer(float duration) {
  if (duration >= 0) {
    m_duration = duration;
  } else {
    m_duration = 0;
  }
  m_lapse = 0;
}

bool Timer::step(float delta) {
  m_lapse += delta;
  if (m_lapse >= m_duration) {
    m_lapse = 0;
    return true;
  }
  return false;
}

void Timer::reset() {
  m_lapse = 0;
}
