#include "AISystem.h"
#include <cocos2d.h>

AISystem::AISystem(float gravityAngle) {
  m_gravityAngle = gravityAngle;
}

void AISystem::registerComponent(std::string id, AIComponent* component) {
  cocos2d::log("Registering AIComponent with id: %s", id.c_str());
  if (m_components.count(id) == 0) {
    m_components.insert(std::make_pair(id, component));
  }
}

void AISystem::deregisterComponent(std::string id) {
  if (m_components.count(id) > 0) {
    m_components.erase(id);
  }
}

void AISystem::setGravityAngle(float gravityAngle) {
  m_gravityAngle = gravityAngle;
  for (auto component : m_components) {
    component.second->disturb();
  }
}
