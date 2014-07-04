#include "ContactSystem.h"
#include "../model/Entity.h"
#include "../component/ContactComponent.h"

ContactSystem::ContactSystem() : b2ContactListener() {
}

void ContactSystem::BeginContact(b2Contact* contact) {
  void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
  void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
  if (bodyAUserData) {
    Entity* entityA = (Entity*)bodyAUserData;
    if (entityA->getType() == ENTITY_TYPE_UNIT) {
      ContactComponent* contactComponent = dynamic_cast<ContactComponent*>(entityA);
      contactComponent->addContact();
    }
  }
  if (bodyBUserData) {
    Entity* entityB = (Entity*)bodyBUserData;
    if (entityB->getType() == ENTITY_TYPE_UNIT) {
      ContactComponent* contactComponent = dynamic_cast<ContactComponent*>(entityB);
      contactComponent->addContact();
    }
  }
}

void ContactSystem::EndContact(b2Contact* contact) {
  void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
  void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
  if (bodyAUserData) {
    Entity* entityA = (Entity*)bodyAUserData;
    if (entityA->getType() == ENTITY_TYPE_UNIT) {
      ContactComponent* contactComponent = dynamic_cast<ContactComponent*>(entityA);
      contactComponent->removeContact();
    }
  }
  if (bodyBUserData) {
    Entity* entityB = (Entity*)bodyBUserData;
    if (entityB->getType() == ENTITY_TYPE_UNIT) {
      ContactComponent* contactComponent = dynamic_cast<ContactComponent*>(entityB);
      contactComponent->removeContact();
    }
  }
}
