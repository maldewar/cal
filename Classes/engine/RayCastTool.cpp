#include "RayCastTool.h"
#include "../util/CMath.h"

RayCastTool::RayCastTool(float rayLength) : b2RayCastCallback() {
  m_rayLength        = rayLength;
  m_start            = new b2Vec2();
  m_startTemp        = new cocos2d::Vec2();
  m_end              = new b2Vec2();
  m_endTemp          = new cocos2d::Vec2();
  m_objectType       = 0;
  m_objectTypeFilter = 0;
  m_entity           = nullptr;
};

void RayCastTool::RayCast(b2World* world, float x, float y, float gravityAngle) {
  RayCast(world, x, y, gravityAngle, m_rayLength);
};

void RayCastTool::RayCast(b2World* world, float x, float y, float gravityAngle, float distance) {
  m_hasContact = false;
  m_start->Set(x, y);
  m_startTemp->x = x;
  m_startTemp->y = y;
  m_endTemp = CMath::getPointAt(m_startTemp, distance, gravityAngle);
  m_end->Set(m_endTemp->x, m_endTemp->y);
  m_objectType = 0;
  world->RayCast(this, *m_start, *m_end);
};

float32 RayCastTool::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) {
  m_entity = static_cast<Entity*>(fixture->GetBody()->GetUserData());
  if ((m_objectTypeFilter > 0 && m_entity->getType() != m_objectTypeFilter) || fraction < 0.00001)
    return -1;
  m_hasContact = true;
  m_objectType = m_entity->getType();
  m_end->x = point.x;
  m_end->y = point.y;
  m_endTemp->x = point.x;
  m_endTemp->y = point.y;
  return fraction;
};

bool RayCastTool::HasContact() {
    return m_hasContact;
};

void RayCastTool::SetFilter(int type) {
    m_objectTypeFilter = type;
};

void RayCastTool::ClearFilter() {
    m_objectTypeFilter = 0;
};

cocos2d::Vec2* RayCastTool::GetStart() {
  return m_startTemp;
};

b2Vec2* RayCastTool::GetWorldStart() {
  return m_start;
}

cocos2d::Vec2* RayCastTool::GetEnd() {
    return m_endTemp;
};

b2Vec2* RayCastTool::GetWorldEnd() {
  return m_end;
}

int RayCastTool::GetObjectType() {
    return m_objectType;
};
