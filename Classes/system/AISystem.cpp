#include "AISystem.h"
#include <cocos2d.h>

AISystem::AISystem(float gravityAngle) {
  m_gravityAngle = gravityAngle;
  m_choiceGraph = new ChoiceGraph();
  m_debugDrawEnabled = false;
}

void AISystem::registerComponent(std::string id, AIComponent* component) {
  if (m_components.count(id) == 0) {
    m_components.insert(std::make_pair(id, component));
  }
}

void AISystem::deregisterComponent(std::string id) {
  if (m_components.count(id) > 0) {
    m_components.erase(id);
  }
}

bool AISystem::addWalkableEntity(Entity* entity) {
  return m_choiceGraph->addEntity(entity);
}

void AISystem::setGravityAngle(float gravityAngle) {
  m_gravityAngle = gravityAngle;
  for (auto component : m_components) {
    component.second->disturb();
  }
}

void AISystem::setDebugDrawEnabled(bool debugDrawEnabled) {
  m_debugDrawEnabled = true;
  m_choiceGraph->setDebugDrawEnabled(m_debugDrawEnabled);
}

bool AISystem::isDebugDrawEnabled() {
  return m_debugDrawEnabled;
}

void AISystem::debugDraw() {
  if (m_debugDrawEnabled) {
    cocos2d::DrawPrimitives::setDrawColor4F(255, 255, 255, 1);
    cocos2d::DrawPrimitives::drawLine(cocos2d::Point(0,0), cocos2d::Point(1,1));
  }
}

ChoiceGraph* AISystem::getChoiceGraph() {
  return m_choiceGraph;
}
