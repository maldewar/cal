#include "Entity.h"

Entity::Entity() {
  m_id = "";
  m_worldLayer = nullptr;
  m_body = nullptr;
  m_width = 0;
  m_height = 0;
}

Entity::~Entity() {
}

void Entity::setId(std::string id) {
  m_id = id;
}

std::string Entity::getId() {
  return m_id;
}

int Entity::getType() {
  return 0;
}

void Entity::setBody(b2Body* body) {
  m_body = body;
  m_body->SetUserData(this);
}

b2Body* Entity::getBody() {
  return m_body;
}

void Entity::setWorldLevelLayer(WorldLevelLayer* worldLevelLayer) {
  m_worldLayer = worldLevelLayer;
}

WorldLevelLayer* Entity::getWorldLevelLayer() {
  return m_worldLayer;
}

void Entity::update(float dt)
{
  Node::update(dt);
  if ( m_body ) {
    /*
    cocos2d::Point pos = cocos2d::CCPointMake(0, 0);
    float angle = 0;
    //need to rotate image local center by body angle
    b2Vec2 localPos( pos.x, pos.y );
    b2Rot rot( m_body->GetAngle() );
    localPos = b2Mul(rot, localPos) + m_body->GetPosition();
    pos.x = localPos.x;
    pos.y = localPos.y;
    angle += -m_body->GetAngle();
    setRotation( CC_RADIANS_TO_DEGREES(angle) );
    setPosition( pos );
    */
    cocos2d::Vec2 position = cocos2d::Vec2(0,0);
    position.x = m_body->GetPosition().x;
    position.y = m_body->GetPosition().y;
    setRotation(CC_RADIANS_TO_DEGREES(-m_body->GetAngle()));
    setPosition(position);
  }
}

void Entity::select() {
}
