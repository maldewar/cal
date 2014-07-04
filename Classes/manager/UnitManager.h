#ifndef __UNIT_MANAGER__
#define __UNIT_MANAGER__

#include <vector>

#include "cocos2d.h"
#include "../model/Unit.h"

class UnitManager : public cocos2d::Ref
{
public:
  static UnitManager* getInstance();
  static void destroyInstance();

private:
  UnitManager(void);
  ~UnitManager(void);

public:
  virtual bool init();
  Unit* spawnUnit();

private:
  std::vector<Unit*> m_units;
};

#endif
