#include "Entity.h"

Entity::Entity() {
  m_body = nullptr;
}

Entity::~Entity() {
}

void Entity::setBody(b2Body* body) {
  m_body = body;
}

void Entity::update(float dt)
{
    Node::update(dt);
    cocos2d::Point pos = cocos2d::CCPointMake(0, 0);
    float angle = 0;
    if ( m_body ) {
        //need to rotate image local center by body angle
        b2Vec2 localPos( pos.x, pos.y );
        b2Rot rot( m_body->GetAngle() );
        localPos = b2Mul(rot, localPos) + m_body->GetPosition();
        pos.x = localPos.x;
        pos.y = localPos.y;
        angle += -m_body->GetAngle();
    }
    setRotation( CC_RADIANS_TO_DEGREES(angle) );
    setPosition( pos );
}
