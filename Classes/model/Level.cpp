#include "Level.h"
#include "Unit.h"
#include "../util/CMath.h"

Level::Level() : Entity() {
  m_state = LEVEL_STATE_ACTIVE;
  m_level = 0;
  m_armature = nullptr;
}

Level::~Level() {
}

int Level::getType() {
  return ENTITY_TYPE_LEVEL;
}

Level* Level::create(std::string armature) {
  return Level::create(armature, false);
}

Level* Level::create(std::string armature, bool active) {
  Level *level = new (std::nothrow) Level();
  if (level && level->init(armature, active))
  {
    level->autorelease();
    return level;
  }
  CC_SAFE_DELETE(level);
  return nullptr;
}

bool Level::init(std::string armature, bool active)
{
  if (!armature.empty())
    m_armature = cocostudio::Armature::create(armature);
  if (m_armature) {
    m_armature->getAnimation()->playWithIndex(LEVEL_ANIM_ACTIVE);
    scheduleUpdate();
    addChild(m_armature);
    setScale(PX_TO_M);
  }
  if (active) {
    activate();
  } else {
    deactivate();
  }
  return true;
}

int Level::getLevel() {
  return m_level;
}

void Level::setLevel(int level) {
  m_level = level;
}

std::string Level::getTitle() {
  return m_title;
}

void Level::setTitle(std::string title) {
  m_title = title;
}

void Level::activate() {
  if (m_state == LEVEL_STATE_INACTIVE) {
    m_state = LEVEL_STATE_ACTIVE;
    if (m_armature) {
      m_armature->getAnimation()->playWithIndex(LEVEL_ANIM_ACTIVE);
    }
  }
}

void Level::deactivate() {
  if (m_state == LEVEL_STATE_ACTIVE) {
    m_state = LEVEL_STATE_INACTIVE;
    if (m_armature) {
      m_armature->getAnimation()->playWithIndex(LEVEL_ANIM_INACTIVE);
    }
  }
}

bool Level::isActive() {
  if (m_state == LEVEL_STATE_ACTIVE)
    return true;
  return false;
}

void Level::update(float dt) {
  Entity::update(dt);
}

void Level::select() {
  //getWorldLevelLayer()->getWorldLevelScene()->selectCtrl(CTRL_LEVEL, this);
  CCLOG("SELECTED LEVEL %d", m_level);
}
