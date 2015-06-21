#include "EntityElem.h"

std::unordered_map<int, int> EntityElem::m_ids;

EntityElem::EntityElem() {
  m_id = "";
  m_entity = nullptr;
  m_fixture = nullptr;
  m_touchEnabled = true;
  setAutoId();
}

EntityElem::~EntityElem() {
}

void EntityElem::setId(std::string id) {
  m_id = id;
}

std::string EntityElem::getId() {
  return m_id;
}

int EntityElem::getType() {
  return 0;
}

void EntityElem::setFixture(b2Fixture* fixture) {
  m_fixture = fixture;
  m_fixture->SetUserData(this);
}

b2Fixture* EntityElem::getFixture() {
  return m_fixture;
}

void EntityElem::setEntity(Entity* entity) {
  m_entity = entity;
}

Entity* EntityElem::getEntity() {
  return m_entity;
}

void EntityElem::setTouchEnabled(bool touchEnabled) {
  m_touchEnabled = touchEnabled;
}

bool EntityElem::isTouchEnabled() {
  return m_touchEnabled;
}

void EntityElem::update(float dt)
{
  Node::update(dt);
  /*
  if ( m_fixture ) {
    cocos2d::Vec2 position = cocos2d::Vec2(0,0);
    position.x = m_fixture->GetPosition().x;
    position.y = m_fixture->GetPosition().y;
    setRotation(CC_RADIANS_TO_DEGREES(-m_fixture->GetAngle()));
    setPosition(position);
  }
  */
}

void EntityElem::select() {
}

void EntityElem::select(b2Fixture* fixture) {
}

void EntityElem::select(cocos2d::Touch* touch) {
}

void EntityElem::setAutoId() {
  int type = getType();
  if (m_ids.count(type) == 0) {
    m_ids[type] = 0;
  }
  std::string kind;
  switch(type) {
    default:
      kind = "default_";
  }
  m_id = kind + std::to_string(m_ids[type]);
  m_ids[type]++;
}
