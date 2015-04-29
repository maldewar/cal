#include "DraggableComponent.h"

DraggableComponent::DraggableComponent() {
  m_active = true;
  m_pinX = 0;
  m_pinY = 0;
  m_mouseJoint = nullptr;
  m_mouseJointGroundBody = nullptr;
  m_mouseJointTouch = nullptr;
}

DraggableComponent::~DraggableComponent() {}

void DraggableComponent::setActive(bool active) {
  m_active = active;
}

bool DraggableComponent::isActive() {
  return m_active;
}

void DraggableComponent::setPinX(float pinX) {
  m_pinX = pinX;
}

float DraggableComponent::getPinX() {
  return m_pinX;
}

void DraggableComponent::setPinY(float pinY) {
  m_pinY = pinY;
}

float DraggableComponent::getPinY() {
  return m_pinY;
}

void DraggableComponent::setBody(b2Body* body) {
  m_body = body;
}

bool DraggableComponent::createMouseJoint(b2World* world, b2Vec2 worldPosition, cocos2d::Touch* touch) {
  if (m_mouseJoint) {
    return false;
  }
  if (!m_mouseJointGroundBody) {
    b2BodyDef bd;
    m_mouseJointGroundBody = world->CreateBody( &bd );
  }
  b2MouseJointDef md;
  md.bodyA = m_mouseJointGroundBody;
  md.bodyB = m_body;
  md.target = worldPosition;
  md.maxForce = 2500.0f * m_body->GetMass();
  m_mouseJoint = (b2MouseJoint*)world->CreateJoint(&md);
  m_body->SetAwake(true);
  m_mouseJointTouch = touch;
  return true;
}

bool DraggableComponent::destroyMouseJoint(b2World* world) {
  world->DestroyJoint(m_mouseJoint);
  m_mouseJoint = NULL;
  m_mouseJointTouch = NULL;
  return true;
}

bool DraggableComponent::moveMouseJoint(b2Vec2 position) {
  if (m_mouseJoint) {
    m_mouseJoint->SetTarget(position);
    return true;
  }
  return false;
}
