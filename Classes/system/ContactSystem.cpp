#include "ContactSystem.h"
#include "../model/Entity.h"
#include "../component/ContactComponent.h"

ContactSystem::ContactSystem() : b2ContactListener() {
}

void ContactSystem::BeginContact(b2Contact* contact) {
  void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
  void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
  Entity* entityA = nullptr;
  Entity* entityB = nullptr;
  if (bodyAUserData) {
    entityA = (Entity*)bodyAUserData;
  }
  if (bodyBUserData) {
    entityB = (Entity*)bodyBUserData;
  }
  if (bodyAUserData) {
    if (contact->GetFixtureB()->IsSensor()) {
      if (entityA->getType() == ENTITY_TYPE_UNIT ||
          entityA->getType() == ENTITY_TYPE_GRAVITRON ||
          entityA->getType() == ENTITY_TYPE_EXIT ||
          entityA->getType() == ENTITY_TYPE_FLUX) {
        ContactComponent* contactComponent = dynamic_cast<ContactComponent*>(entityA);
        contactComponent->enterSensor(contact->GetFixtureB()->GetBody(), entityB);
      }
    } else {
      if (entityA->getType() == ENTITY_TYPE_UNIT ||
          entityA->getType() == ENTITY_TYPE_GRAVITRON ||
          entityA->getType() == ENTITY_TYPE_EXIT ||
          entityA->getType() == ENTITY_TYPE_FLUX) {
        ContactComponent* contactComponent = dynamic_cast<ContactComponent*>(entityA);
        contactComponent->addContact(contact->GetFixtureB()->GetBody(), entityB);
        if (contact->GetFixtureA()->IsSensor() && contactComponent->isSensor()) {
          contactComponent->sensorReceive(contact->GetFixtureB()->GetBody(), entityB);
        }
      }
    }
  }
  if (bodyBUserData) {
    if (contact->GetFixtureA()->IsSensor()) {
      if (entityB->getType() == ENTITY_TYPE_UNIT ||
          entityB->getType() == ENTITY_TYPE_GRAVITRON ||
          entityB->getType() == ENTITY_TYPE_EXIT ||
          entityB->getType() == ENTITY_TYPE_FLUX) {
        ContactComponent* contactComponent = dynamic_cast<ContactComponent*>(entityB);
        contactComponent->enterSensor(contact->GetFixtureA()->GetBody(), entityA);
      }
    } else {
      if (entityB->getType() == ENTITY_TYPE_UNIT ||
          entityB->getType() == ENTITY_TYPE_GRAVITRON ||
          entityB->getType() == ENTITY_TYPE_EXIT ||
          entityB->getType() == ENTITY_TYPE_FLUX) {
        ContactComponent* contactComponent = dynamic_cast<ContactComponent*>(entityB);
        contactComponent->addContact(contact->GetFixtureA()->GetBody(), entityA);
        if (contact->GetFixtureB()->IsSensor() && contactComponent->isSensor()) {
          contactComponent->sensorReceive(contact->GetFixtureA()->GetBody(), entityA);
        }
      }
    }
  }
}

void ContactSystem::EndContact(b2Contact* contact) {
  void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
  void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
  Entity* entityA = nullptr;
  Entity* entityB = nullptr;
  if (bodyAUserData) {
    entityA = (Entity*)bodyAUserData;
  }
  if (bodyBUserData) {
    entityB = (Entity*)bodyBUserData;
  }
  if (bodyAUserData) {
    if (contact->GetFixtureB()->IsSensor()) {
      if (entityA->getType() == ENTITY_TYPE_UNIT ||
          entityA->getType() == ENTITY_TYPE_GRAVITRON ||
          entityA->getType() == ENTITY_TYPE_FLUX) {
        ContactComponent* contactComponent = dynamic_cast<ContactComponent*>(entityA);
        contactComponent->exitSensor(contact->GetFixtureB()->GetBody(), entityB);
      }
    } else {
      if (entityA->getType() == ENTITY_TYPE_UNIT ||
          entityA->getType() == ENTITY_TYPE_GRAVITRON ||
          entityA->getType() == ENTITY_TYPE_FLUX) {
        ContactComponent* contactComponent = dynamic_cast<ContactComponent*>(entityA);
        contactComponent->removeContact(contact->GetFixtureB()->GetBody(), entityB);
        if (contact->GetFixtureA()->IsSensor() && contactComponent->isSensor()) {
          contactComponent->sensorLose(contact->GetFixtureB()->GetBody(), entityB);
        }
      }
    }
  }
  if (bodyBUserData) {
    if (contact->GetFixtureA()->IsSensor()) {
      if (entityB->getType() == ENTITY_TYPE_UNIT ||
          entityB->getType() == ENTITY_TYPE_GRAVITRON ||
          entityB->getType() == ENTITY_TYPE_FLUX) {
        ContactComponent* contactComponent = dynamic_cast<ContactComponent*>(entityB);
        contactComponent->exitSensor(contact->GetFixtureA()->GetBody(), entityA);
      }
    } else {
      if (entityB->getType() == ENTITY_TYPE_UNIT ||
          entityB->getType() == ENTITY_TYPE_GRAVITRON ||
          entityB->getType() == ENTITY_TYPE_FLUX) {
        ContactComponent* contactComponent = dynamic_cast<ContactComponent*>(entityB);
        contactComponent->removeContact(contact->GetFixtureA()->GetBody(), entityA);
        if (contact->GetFixtureB()->IsSensor() && contactComponent->isSensor()) {
          CCLOG("sensor lose");
          contactComponent->sensorLose(contact->GetFixtureA()->GetBody(), entityA);
        }
      }
    }
  }
}
