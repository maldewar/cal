#include "LevelSceneDef.h"

LevelSceneDef::LevelSceneDef() : SceneDef() {
  m_unitsRequired = 0;
}

int LevelSceneDef::getUnitsRequired() {
  return m_unitsRequired;
}

void LevelSceneDef::setUnitsRequired(int unitsRequired) {
  m_unitsRequired = unitsRequired;
}
