#include "UnitManager.h"

static UnitManager* s_sharedUnitManager = nullptr;

UnitManager* UnitManager::getInstance() {
  if (s_sharedUnitManager == nullptr) {
    s_sharedUnitManager = new UnitManager();
    if (!s_sharedUnitManager || !s_sharedUnitManager->init()) {
      CC_SAFE_DELETE(s_sharedUnitManager);
    }
  }
  return s_sharedUnitManager;
}

void UnitManager::destroyInstance() {
  CC_SAFE_RELEASE_NULL(s_sharedUnitManager);
}

UnitManager::UnitManager(void) {
  m_units.clear();
}

UnitManager::~UnitManager(void) {
  m_units.clear();
}

bool UnitManager::init() {
  m_units.clear();
  return true;
}

Unit* UnitManager::spawnUnit() {
  Unit* unit = new (std::nothrow) Unit();
  if (unit) {
    m_units.push_back(unit);
  }
  return unit;
}
