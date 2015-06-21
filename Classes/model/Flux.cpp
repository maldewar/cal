#include "Flux.h"
#include "Unit.h"
#include "../util/CMath.h"

Flux::Flux() : Entity(), ContactComponent() {
  m_state = FLUX_STATE_ACTIVE;
  m_width = 0.15;
  m_height = 0.15;
  m_arrowAngle = 0;
  m_timer = new Timer(3);
  m_target = new b2Vec2(0, 0);
  m_waitingForAuto = false;
  m_isAuto = false;
  setAutoId();
}

Flux::~Flux() {
  m_isSelected      = false;
}

int Flux::getType() {
  return ENTITY_TYPE_FLUX;
}

Flux* Flux::create() {
  return Flux::create(false);
}

Flux* Flux::create(bool active) {
  Flux *flux = new (std::nothrow) Flux();
  if (flux && flux->init(active))
  {
    flux->autorelease();
    return flux;
  }
  CC_SAFE_DELETE(flux);
  return nullptr;
}

bool Flux::init(bool active)
{
  m_skeletonNode = spine::SkeletonAnimation::createWithFile("skeletons/flux/skeleton.json",
                        "flux/skeleton.atlas");
  if (m_skeletonNode) {
    scheduleUpdate();
    //setScale(PX_TO_M);
    setIsSensor(true);
    addChild(m_skeletonNode);
    m_skeletonNode->setPosition(cocos2d::Point(0,getGroundOffset()));
    m_skeletonNode->setRotation(M_PI_4);
    setScale(getSkeletonScale());
    if (active) {
      activate(0);
    } else {
      deactivate(0);
    }
    return true;
  }
  return false;
}

void Flux::activate(float dt) {
  if (m_state == FLUX_STATE_INACTIVE) {
    m_state = FLUX_STATE_ACTIVE;
  }
}

void Flux::deactivate(float dt) {
  if (m_state == FLUX_STATE_ACTIVE) {
    m_state = FLUX_STATE_INACTIVE;
  }
}

void Flux::setArrowAngle(float angle) {
  m_arrowAngle = angle;
  if (m_skeletonNode) {
    m_skeletonNode->setRotation(360 - CMath::toDeg(angle));
  }
}

void Flux::setTarget(float x, float y) {
  m_target->x = x;
  m_target->y = y;
}

b2Vec2* Flux::getTarget() {
  return m_target;
}

float Flux::getArrowAngle() {
  return m_arrowAngle;
}

void Flux::update(float dt) {
  Entity::update(dt);
  if (m_isSelected && !m_waitingForAuto && !m_isAuto) {
    dispatchUnit();
    m_waitingForAuto = true;
  } else if (m_waitingForAuto && m_timer->step(dt)) {
    dispatchUnit();
    m_waitingForAuto = false;
    if (m_units.size() == 0)
      setAuto(false);
    else
      setAuto(true);
  } else if (m_isAuto && m_timer->step(dt)) {
    dispatchUnit();
    if (m_units.size() == 0)
      setAuto(false);
  }
}

void Flux::select() {
  m_isSelected = true;
  m_waitingForAuto = false;
  setAuto(false);
}

void Flux::deselect() {
  m_isSelected = false;
  m_waitingForAuto = false;
  m_timer->reset();
}

void Flux::sensorReceive(b2Body* body, Entity* receivedEntity) {
  if (receivedEntity &&
      receivedEntity->getType() == ENTITY_TYPE_UNIT) {
    Unit* unit = (Unit*)receivedEntity;
    m_units[unit->getId()] = unit;
  }
}

void Flux::sensorLose(b2Body* body, Entity* lostEntity) {
  if (lostEntity &&
      lostEntity->getType() == ENTITY_TYPE_UNIT) {
    Unit* unit = (Unit*)lostEntity;
    if (m_units.count(unit->getId()))
      m_units.erase(unit->getId());
  }
}

bool Flux::dispatchUnit() {
  if (m_units.size() > 0) {
    std::unordered_map<std::string, Unit*>::iterator it =
      std::next(std::begin(m_units), rand() % m_units.size());
    (*it).second->commandGoTo(m_target->x, m_target->y);
    m_units.erase(it);
    return true;
  }
  return false;
}

void Flux::setAuto(bool isAuto) {
  m_isAuto = isAuto;
  if (m_isAuto)
    cocos2d::log("Setting auto to TRUE");
  else
    cocos2d::log("Setting auto to FALSE");
}
