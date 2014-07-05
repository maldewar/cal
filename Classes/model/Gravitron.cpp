#include "Gravitron.h"
#include "Unit.h"
#include "../util/CMath.h"

Gravitron::Gravitron() : Entity() {
  m_state = GRAVITRON_STATE_ACTIVE;
  m_armature = nullptr;
  m_width = 0.15f;
  m_height = 0.15f;
}

Gravitron::~Gravitron() {
}

int Gravitron::getType() {
  return ENTITY_TYPE_GRAVITRON;
}

Gravitron* Gravitron::create() {
  return Gravitron::create(false);
}

Gravitron* Gravitron::create(bool active) {
  Gravitron *gravitron = new (std::nothrow) Gravitron();
  if (gravitron && gravitron->init(active))
  {
    gravitron->autorelease();
    return gravitron;
  }
  CC_SAFE_DELETE(gravitron);
  return nullptr;
}

bool Gravitron::init(bool active)
{
  m_armature = cocostudio::Armature::create("gravitron");
  if (m_armature) {
    scheduleUpdate();
    addChild(m_armature);
    setScale(PX_TO_M);
    if (active) {
      m_armature->getAnimation()->playWithIndex(GRAVITRON_ANIM_ACTIVE);
    } else {
      m_armature->getAnimation()->playWithIndex(GRAVITRON_ANIM_INACTIVE);
    }
    return true;
  }
  return false;
}

void Gravitron::activate(float dt) {
  if (m_state = GRAVITRON_STATE_INACTIVE) {
    m_state = GRAVITRON_STATE_ACTIVE;
    if (m_armature) {
      m_armature->getAnimation()->playWithIndex(GRAVITRON_ANIM_ACTIVE);
    }
  }
}

void Gravitron::deactivate(float dt) {
  if (m_state = GRAVITRON_STATE_ACTIVE) {
    m_state = GRAVITRON_STATE_INACTIVE;
    if (m_armature) {
      m_armature->getAnimation()->playWithIndex(GRAVITRON_ANIM_INACTIVE);
    }
  }
}

void Gravitron::update(float dt) {
  Entity::update(dt);
}
