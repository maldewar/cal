#include "ContactSystem.h"
#include "../model/Entity.h"
#include "../component/ContactComponent.h"

ContactSystem::ContactSystem() : b2ContactListener() {
}

void ContactSystem::BeginContact(b2Contact* contact) {
  void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
  void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
  if (bodyAUserData) {
    if (contact->GetFixtureB()->IsSensor()) {
      CCLOG("Entering sensor area.");
    } else {
      Entity* entityA = (Entity*)bodyAUserData;
      if (entityA->getType() == ENTITY_TYPE_UNIT) {
        ContactComponent* contactComponent = dynamic_cast<ContactComponent*>(entityA);
        contactComponent->addContact();
      }
    }
  }
  if (bodyBUserData) {
    if (contact->GetFixtureA()->IsSensor()) {
      CCLOG("Entering sensor area.");
    } else {
      Entity* entityB = (Entity*)bodyBUserData;
      if (entityB->getType() == ENTITY_TYPE_UNIT) {
        ContactComponent* contactComponent = dynamic_cast<ContactComponent*>(entityB);
        contactComponent->addContact();
      }
    }
  }
}

void ContactSystem::EndContact(b2Contact* contact) {
  void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
  void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
  if (bodyAUserData) {
    Entity* entityA = (Entity*)bodyAUserData;
    if (contact->GetFixtureB()->IsSensor()) {
      CCLOG("Leaving sensor area.");
    } else {
      if (entityA->getType() == ENTITY_TYPE_UNIT) {
        ContactComponent* contactComponent = dynamic_cast<ContactComponent*>(entityA);
        contactComponent->removeContact();
      }
    }
  }
  if (bodyBUserData) {
    Entity* entityB = (Entity*)bodyBUserData;
    if (contact->GetFixtureA()->IsSensor()) {
      CCLOG("Leaving sensor area.");
    } else {
      if (entityB->getType() == ENTITY_TYPE_UNIT) {
        ContactComponent* contactComponent = dynamic_cast<ContactComponent*>(entityB);
        contactComponent->removeContact();
      }
    }
  }
}
