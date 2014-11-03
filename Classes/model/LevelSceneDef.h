#ifndef __LEVEL_SCENE_DEF_H__
#define __LEVEL_SCENE_DEF_H__

#include <string>
#include <vector>

#include "SceneDef.h"

class LevelSceneDef : public SceneDef
{
protected:
  int m_unitsRequired;

public:
  /**
   * Class constructor.
   */
  LevelSceneDef(void);
  virtual int getUnitsRequired();
  virtual void setUnitsRequired(int unitsRequired);
};

#endif // __LEVEL_SCENE_DEF_H__
