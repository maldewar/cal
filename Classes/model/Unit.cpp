#include "Unit.h"
#include "../manager/UnitManager.h"
#include "../factory/BodyFactory.h"

Unit::Unit() : Entity(), ContactComponent(), AIComponent() {
  m_armature = nullptr;
  m_width = 0.15f;
  m_height = 0.15f;
  setSubstateStandDuration(0.67f);
}

Unit::~Unit() {
}

int Unit::getType() {
  return ENTITY_TYPE_UNIT;
}

void Unit::setBody(b2Body* body) {
  BodyFactory::getInstance()->randomizeUnitBody(body);
  Entity::setBody(body);
  AIComponent::setBody(body);
}

Unit* Unit::create(bool managed, bool setBody) {
  Unit* unit = nullptr;
  if (managed) {
    unit = UnitManager::getInstance()->spawnUnit();
  } else {
    unit = new (std::nothrow) Unit();
  }
  if (unit && unit->init())
  {
    unit->autorelease();
    if (setBody) {
      unit->setBody(BodyFactory::getInstance()->getBody("unit"));
      unit->update(0);
    }
    return unit;
  }
  CC_SAFE_DELETE(unit);
  return nullptr;
}

bool Unit::init(void) {
  m_armature = cocostudio::Armature::create("unit");
  if (m_armature) {
    setAnimation(UNIT_ANIM_FALL);
    scheduleUpdate();
    addChild(m_armature);
    setScale(PX_TO_M);
    return true;
  }
  return false;
}

void Unit::update(float dt) {
  Entity::update(dt);
  AIComponent::update(dt);
}

void Unit::contactStart(b2Body* body, Entity* contactEntity) {
  if (hasContact() && !isAfoot())
    setAfoot();
}

void Unit::contactEnd(b2Body* body, Entity* contactEntity) {
  if (!hasContact())
    setLoose();
}

void Unit::onStateChange(int state, int substate) {
  /**
  switch(state) {
    case AI_STATE_LOOSE:
      m_armature->getAnimation()->playWithIndex(UNIT_ANIM_FALL);
      break;
    case AI_STATE_AFOOT:
      if (dt > 0.37f) {
        m_armature->getAnimation()->playWithIndex(UNIT_ANIM_ROLL_STOP);
      } else {
        m_armature->getAnimation()->playWithIndex(UNIT_ANIM_FALL_STOP);
      }
      break;
  }
  */
}

void Unit::onSubstateChange(int substate) {
  switch(substate) {
    case AI_SUBSTATE_FALL:
      setAnimation(UNIT_ANIM_FALL);
      break;
    case AI_SUBSTATE_ROLL:
      setAnimation(UNIT_ANIM_ROLL);
      break;
    case AI_SUBSTATE_STAND:
      if (m_substate == AI_SUBSTATE_ROLL) {
        setAnimation(UNIT_ANIM_ROLL_STOP);
      } else {
        setAnimation(UNIT_ANIM_FALL_STOP);
      }
      break;
    case AI_SUBSTATE_STILL:
      if (m_animation == UNIT_ANIM_ROLL_STOP) {
        setAnimation(UNIT_ANIM_STAND_SIDE);
      } else {
        setAnimation(UNIT_ANIM_STAND_FRONT);
      }
      break;
  }
}

void Unit::onDirectionChange(bool isRight) {
  AIComponent::onDirectionChange(isRight);
  if (isRight) {
    m_armature->setScaleX(1);
  } else {
    m_armature->setScaleX(-1);
  }
}

void Unit::setAnimation(int animation) {
  m_armature->getAnimation()->playWithIndex(animation);
  m_animation = animation;
}
