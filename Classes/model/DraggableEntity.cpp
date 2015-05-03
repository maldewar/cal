#include "DraggableEntity.h"

DraggableEntity::DraggableEntity() : Entity(), DraggableComponent() {
}

DraggableEntity::~DraggableEntity() {
}

int DraggableEntity::getType() {
  return ENTITY_TYPE_DRAGGABLE;
}

void DraggableEntity::setBody(b2Body* body) {
  Entity::setBody(body);
  DraggableComponent::setBody(body);
}

DraggableEntity* DraggableEntity::create() {
  return DraggableEntity::create(false);
}

DraggableEntity* DraggableEntity::create(bool active) {
  DraggableEntity *draggableEntity = new (std::nothrow) DraggableEntity();
  if (draggableEntity && draggableEntity->init(active))
  {
    draggableEntity->autorelease();
    return draggableEntity;
  }
  CC_SAFE_DELETE(draggableEntity);
  return nullptr;
}

bool DraggableEntity::init(bool active)
{
  setActive(active);
  scheduleUpdate();
  return true;
}

void DraggableEntity::update(float dt) {
  Entity::update(dt);
}

void DraggableEntity::select(cocos2d::Touch* touch) {
  cocos2d::log("SELECTING draggable entity.");
  getWorldLevelLayer()->setNavigationEnabled(false);
  getWorldLevelLayer()->addTouchListener(this);
  createMouseJoint(getWorldLevelLayer()->getWorld(),
                   getWorldLevelLayer()->screenToWorld(touch->getLocation()),
                   touch);
}

bool DraggableEntity::onMoveTouchEvent(cocos2d::Touch* touch) {
  cocos2d::log(" onMoveTouchEvent");
  moveMouseJoint(getWorldLevelLayer()->screenToWorld(touch->getLocation()));
  return false;
}

bool DraggableEntity::onEndTouchEvent(cocos2d::Touch* touch) {
  cocos2d::log("onEndTouchEvent");
  getWorldLevelLayer()->setNavigationEnabled(true);
  destroyMouseJoint(getWorldLevelLayer()->getWorld());
  return true;
}
