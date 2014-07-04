#include "ContactComponent.h"
#include "cocos2d.h"

ContactComponent::ContactComponent() {
  m_contacts = 0;
}

ContactComponent::~ContactComponent(){
}

void ContactComponent::addContact() {
  m_contacts++;
  if (m_contacts == 1) {
    contactStart();
  }
}

void ContactComponent::removeContact() {
  m_contacts--;
  if (m_contacts == 0) {
    contactEnd();
  }
}

bool ContactComponent::hasContact() {
  return (m_contacts > 0);
}

void ContactComponent::contactStart() {
}

void ContactComponent::contactEnd() {
}
