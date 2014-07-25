#include "Exit.h"
#include "Unit.h"
#include "../util/CMath.h"

Exit::Exit() : Entity(), ContactComponent() {
  m_state = 0;
  m_units = 0;
  m_capacity = 0;
  m_open = false;
  m_openTimer = 5000;
  m_state = 0;
  m_armature = nullptr;
  m_transition = false;
  m_width = 0.4f;
  m_height = 0.4f;
}

Exit::~Exit() {
}

int Exit::getType() {
  return ENTITY_TYPE_EXIT;
}

Exit* Exit::create()
{
  Exit *exit = new (std::nothrow) Exit();
  if (exit && exit->init())
  {
    exit->autorelease();
    return exit;
  }
  CC_SAFE_DELETE(exit);
  return nullptr;
}

bool Exit::init(void)
{
  m_armature = cocostudio::Armature::create("exit");
  if (m_armature) {
    addChild(m_armature);
    setScale(PX_TO_M);
    setIsSensor(true);
    scheduleUpdate();
    return true;
  }
  return false;
}

/*
std::string Exit::getDescription() const
{
    return StringUtils::format("<Exit | Tag = %d>", _tag);
}
*/

void Exit::setCapacity(int capacity) {
  if (capacity >= 0)
    m_capacity = capacity;
}

int Exit::getCapacity() {
  return m_capacity;
}

int Exit::getUnits() {
  return m_units;
}

void Exit::open(float dt) {
  unschedule(schedule_selector(Exit::open));
  if (m_state == EXIT_STATE_CLOSED) {
    if (m_armature) {
      m_armature->getAnimation()->playWithIndex(EXIT_ANIM_OPENING);
    }
    m_state = EXIT_STATE_OPENING;
    schedule(schedule_selector(Exit::open), 1);
  } else if (m_state == EXIT_STATE_OPENING) {
    m_state = EXIT_STATE_OPEN;
    m_transition = false;
  }
}

void Exit::close(float dt) {
  unschedule(schedule_selector(Exit::close));
  if (m_state == EXIT_STATE_OPEN) {
    if (m_armature) {
      m_armature->getAnimation()->playWithIndex(EXIT_ANIM_CLOSING);
    }
    m_state = EXIT_STATE_CLOSING;
    schedule(schedule_selector(Exit::close), 1);
  } else if (m_state == EXIT_STATE_CLOSING) {
    m_state = EXIT_STATE_CLOSED;
    m_transition = false;
  }
}

void Exit::setOpen(bool isOpen) {
  if (isOpen)
    open(0);
  else
    close(0);
}

void Exit::setOpenTimer(int openTimer) {
  m_openTimer = openTimer;
}

void Exit::update(float dt) {
  Entity::update(dt);
  if (m_state == EXIT_STATE_CLOSED) {
    if (!m_transition && m_units != m_capacity) {
      schedule(schedule_selector(Exit::open), (float)m_openTimer/1000);
      m_transition = true;
    }
    return;
  } else if (m_state == EXIT_STATE_OPEN) {
    /*
    if (m_units != m_capacity && !m_transition) {
      schedule(schedule_selector(Exit::spawnUnit), (float)m_interval/1000, m_capacity, 0);
      m_transition = true;
    } else {
      unscheduleUpdate();
    }
    */
    return;
  }
}

void Exit::sensorReceive(b2Body* body, Entity* receivedEntity) {
  if (receivedEntity) {
    if (receivedEntity->getType() == ENTITY_TYPE_UNIT) {
      Unit* unit = dynamic_cast<Unit*>(receivedEntity);
      unit->remove(false);
    }
  }
}
