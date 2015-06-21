#include "Entry.h"
#include "Unit.h"
#include "../util/CMath.h"

Entry::Entry() : Entity() {
  m_state = 0;
  m_units = 0;
  m_capacity = 0;
  m_open = false;
  m_openTimer = 5000;
  m_forceMinDistance = 0.0f;
  m_forceMaxDistance = 0.0f;
  m_forceMaxAngle = 0.0f;
  m_forceMinAngularImpulse = 0.0f;
  m_forceMaxAngularImpulse = 0.0f;
  m_state = 0;
  m_armature = nullptr;
  m_transition = false;
  m_width = 0.2f;
  m_height = 0.075f;
  setAutoId();
}

Entry::~Entry() {
}

int Entry::getType() {
  return ENTITY_TYPE_ENTRY;
}

Entry* Entry::create()
{
  Entry *entry = new (std::nothrow) Entry();
  if (entry && entry->init())
  {
    entry->autorelease();
    return entry;
  }
  CC_SAFE_DELETE(entry);
  return nullptr;
}

bool Entry::init(void)
{
  m_armature = cocostudio::Armature::create("entry");
  if (m_armature) {
    addChild(m_armature);
    setScale(PX_TO_M);
    scheduleUpdate();
    return true;
  }
  return false;
}

/*
std::string Entry::getDescription() const
{
    return StringUtils::format("<Entry | Tag = %d>", _tag);
}
*/

void Entry::setCapacity(int capacity) {
    if (capacity >= 0)
        m_capacity = capacity;
}

int Entry::getCapacity() {
    return m_capacity;
}

int Entry::getUnits() {
    return m_units;
}

void Entry::open(float dt) {
  unschedule(schedule_selector(Entry::open));
  if (m_state == ENTRY_STATE_CLOSED) {
    if (m_armature) {
      m_armature->getAnimation()->playWithIndex(ENTRY_ANIM_OPENING);
    }
    m_state = ENTRY_STATE_OPENING;
    schedule(schedule_selector(Entry::open), 1);
  } else if (m_state == ENTRY_STATE_OPENING) {
    m_state = ENTRY_STATE_OPEN;
    m_transition = false;
  }
}

void Entry::close(float dt) {
  unschedule(schedule_selector(Entry::close));
  if (m_state == ENTRY_STATE_OPEN) {
    if (m_armature) {
      m_armature->getAnimation()->playWithIndex(ENTRY_ANIM_CLOSING);
    }
    m_state = ENTRY_STATE_CLOSING;
    schedule(schedule_selector(Entry::close), 1);
  } else if (m_state == ENTRY_STATE_CLOSING) {
    m_state = ENTRY_STATE_CLOSED;
    m_transition = false;
  }
}

void Entry::setOpen(bool isOpen) {
  if (isOpen)
    open(0);
  else
    close(0);
}

void Entry::setOpenTimer(int openTimer) {
  m_openTimer = openTimer;
}

void Entry::setInterval(int interval) {
  if (interval >= 0) {
    m_interval = interval;
  }
}

int Entry::getInterval() {
  return m_interval;
}

void Entry::setForceMinDistance(float distance) {
  m_forceMinDistance = distance;
}

float Entry::getForceMinDistance() {
  return m_forceMinDistance;
}

void Entry::setForceMaxDistance(float distance) {
  m_forceMaxDistance = distance;
}

float Entry::getForceMaxDistance() {
  return m_forceMaxDistance;
}

void Entry::setForceMaxAngle(float angle) {
  m_forceMaxAngle = angle;
}

float Entry::getForceMaxAngle() {
  return m_forceMaxAngle;
}

void Entry::setForceMinAngularImpulse(float angularImpulse) {
  m_forceMinAngularImpulse = angularImpulse;
}

float Entry::getForceMinAngularImpulse() {
    return m_forceMinAngularImpulse;
}

void Entry::setForceMaxAngularImpulse(float angularImpulse) {
    m_forceMaxAngularImpulse = angularImpulse;
}

float Entry::getForceMaxAngularImpulse() {
    return m_forceMaxAngularImpulse;
}

void Entry::update(float dt) {
  Entity::update(dt);
  if (m_state == ENTRY_STATE_CLOSED) {
    if (!m_transition && m_units != m_capacity) {
      schedule(schedule_selector(Entry::open), (float)m_openTimer/1000);
      m_transition = true;
    }
    return;
  } else if (m_state == ENTRY_STATE_OPEN) {
    if (m_units != m_capacity && !m_transition) {
      schedule(schedule_selector(Entry::spawnUnit), (float)m_interval/1000, m_capacity - 1, 0);
      m_transition = true;
    } else {
      unscheduleUpdate();
    }
    return;
  }
}

void Entry::spawnUnit(float dt) {
  Unit* newUnit = Unit::create(true, true);
  newUnit->getBody()->SetTransform(getBody()->GetPosition(), 0);
  newUnit->getBody()->ApplyLinearImpulse( getRandomForce(), newUnit->getBody()->GetWorldCenter(), true);
  float angularImpulse = CMath::random(m_forceMinAngularImpulse, m_forceMaxAngularImpulse);
  angularImpulse = m_forceMinAngularImpulse - m_forceMaxAngularImpulse/2 + angularImpulse;
  newUnit->getBody()->ApplyAngularImpulse(angularImpulse, true);
  newUnit->update(0);
  newUnit->scheduleUpdate();
  getWorldLevelLayer()->addChild(newUnit);
  m_armature->getAnimation()->playWithIndex(ENTRY_ANIM_RELEASE);
  m_units += 1;
}

b2Vec2 Entry::getRandomForce() {
    b2Vec2 force;
    float angle = getBody()->GetAngle() - M_PI_2;
    if (m_forceMaxAngle > 0 || m_forceMaxDistance > 0) {
        float randomAngle = CMath::random(0.0f, m_forceMaxAngle);
        angle = angle - m_forceMaxAngle/2 + randomAngle;
        float randomDistance = CMath::random(m_forceMinDistance, m_forceMaxDistance);
        force.x = cos(angle) * randomDistance;
        force.y = sin(angle) * randomDistance;
    } else {
        force.x = 0;
        force.y = 0;
    }
    return force;
}
