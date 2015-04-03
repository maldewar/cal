#ifndef _AI_SYSTEM_H_
    #define _AI_SYSTEM_H_

#include <string>
#include <unordered_map>
#include "../component/AIComponent.h"

class AISystem {
private:
  float m_gravityAngle;
  std::unordered_map<std::string, AIComponent*> m_components;
public:
 AISystem(float gravityAngle);

public:
  void registerComponent(std::string id, AIComponent* component);
  void deregisterComponent(std::string id);
  void setGravityAngle(float gravityAngle);

};

#endif
