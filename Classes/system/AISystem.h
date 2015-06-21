#ifndef _AI_SYSTEM_H_
    #define _AI_SYSTEM_H_

#include <string>
#include <unordered_map>
#include <cocos2d.h>
#include "../engine/ChoiceGraph.h"
#include "../component/AIComponent.h"

class ChoiceGraph;

class AISystem {
private:
  bool m_debugDrawEnabled;
  float m_gravityAngle;
  ChoiceGraph* m_choiceGraph;
  std::unordered_map<std::string, AIComponent*> m_components;

public:
 AISystem(float gravityAngle);

public:
  void registerComponent(std::string id, AIComponent* component);
  void deregisterComponent(std::string id);
  bool addWalkableEntity(Entity* entity);
  void setGravityAngle(float gravityAngle);
  void setDebugDrawEnabled(bool debugDrawEnabled);
  bool isDebugDrawEnabled();
  void debugDraw();
  ChoiceGraph* getChoiceGraph();

};

#endif
