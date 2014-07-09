#include "ContactComponent.h"
#include "cocos2d.h"

ContactComponent::ContactComponent() {
  m_isSensor = false;
  m_contacts = 0;
  m_sensors  = 0;
}

ContactComponent::~ContactComponent(){
}

void ContactComponent::addContact(b2Body* body, Entity* contactEntity) {
  m_contacts++;
  contactStart(body, contactEntity);
}

void ContactComponent::removeContact(b2Body* body, Entity* contactEntity) {
  m_contacts--;
  contactEnd(body, contactEntity);
}

bool ContactComponent::hasContact() {
  return (m_contacts > 0);
}

void ContactComponent::contactStart(b2Body* body, Entity* contactEntity) {
}

void ContactComponent::contactEnd(b2Body* body, Entity* contactEntity) {
}

void ContactComponent::enterSensor(b2Body* body, Entity* sensorEntity) {
  m_sensors++;
  sensorStart(body, sensorEntity);
}

void ContactComponent::exitSensor(b2Body* body, Entity* sensorEntity) {
  m_sensors--;
  sensorEnd(body, sensorEntity);
}

bool ContactComponent::inSensor() {
  return (m_sensors > 0);
}

bool ContactComponent::isSensor() {
  return m_isSensor;
}

void ContactComponent::setIsSensor(bool isSensor) {
  m_isSensor = isSensor;
}

void ContactComponent::sensorStart(b2Body* body, Entity* sensorEntity) {
}

void ContactComponent::sensorEnd(b2Body* body, Entity* sensorEntity) {
}

void ContactComponent::sensorReceive(b2Body* body, Entity* receivedEntity) {
}

void ContactComponent::sensorLose(b2Body* body, Entity* lostEntity) {
}
