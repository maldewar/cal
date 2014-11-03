#include "ActSceneDef.h"

ActSceneDef::ActSceneDef() : SceneDef() {
  m_act = "";
}

std::string ActSceneDef::getAct() {
  return m_act;
}

void ActSceneDef::setAct(std::string act) {
  m_act = act;
}
