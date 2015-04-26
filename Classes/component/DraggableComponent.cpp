#include "DraggableComponent.h"

DraggableComponent::DraggableComponent() {
  m_active = true;
  m_pinX = 0;
  m_pinY = 0;
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
