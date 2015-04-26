#include "Unit.h"
#include "../manager/UnitManager.h"
#include "../factory/BodyFactory.h"

Unit::Unit() : Entity(), ContactComponent(), AIComponent() {
  m_isLost = false;
  m_width = 0.3f;
  m_height = 0.3f;
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

bool Unit::isLost() {
  return m_isLost;
}

void Unit::setIsLost(bool isLost) {
  m_isLost = isLost;
}

void Unit::remove(bool isLost) {
  this->setIsLost(isLost);
  getWorldLevelLayer()->removeChild(this, true);
}

bool Unit::init(void) {
  m_skeletonNode = spine::SkeletonAnimation::createWithFile("skeletons/unit/skeleton.json",
                                                            "unit/skeleton.atlas");
  if (m_skeletonNode) {
    randomSkin();
    scheduleUpdate();
    addChild(m_skeletonNode);
    m_skeletonNode->setPosition(cocos2d::Point(0,getGroundOffset()));
    setScale(getSkeletonScale());
    return true;
  }
  return false;
}

void Unit::update(float dt) {
  if (AIComponent::m_animation != Entity::m_animation) {
    setAnimation(AIComponent::m_animation);
  }
  Entity::update(dt);
  AIComponent::update(dt);
}

void Unit::select() {
  getWorldLevelLayer()->getWorldLevelScene()->selectCtrl(CTRL_SELECT, this);
}

void Unit::contactStart(b2Body* body, Entity* contactEntity) {
  if (hasContact() && !isAfoot())
    setAfoot();
}

void Unit::contactEnd(b2Body* body, Entity* contactEntity) {
  if (!hasContact() && isAfoot())
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
  /*
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
  */
}

void Unit::onDirectionChange(int direction) {
  Entity::onDirectionChange(direction);
  AIComponent::onDirectionChange(direction);
}

void Unit::setAnimation(int animation) {
  m_skeletonNode->setBonesToSetupPose();
  m_skeletonNode->setSlotsToSetupPose();
  switch(animation) {
    case ENTITY_ANIM_STAND:
      m_skeletonNode->setAnimation(0, "still", true);
      break;
    case ENTITY_ANIM_WALK:
      m_skeletonNode->setAnimation(0, "walk", true);
      break;
    case ENTITY_ANIM_FALL:
      m_skeletonNode->setAnimation(0, "fall", true);
      break;
  }
  Entity::setAnimation(animation);
}

void Unit::randomSkin() {
  int skinIndex = 0 + (rand() % (int)(3 - 0 + 1));
  switch(skinIndex) {
   case 1:
      m_skeletonNode->setSkin("calavera_b");
      break;
   case 2:
      m_skeletonNode->setSkin("calavera_c");
      break;
   default:
      m_skeletonNode->setSkin("calavera_a");
  }
}
