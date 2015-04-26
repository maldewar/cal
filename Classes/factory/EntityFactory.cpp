#include "EntityFactory.h"
#include "../component/AIComponentWanderCmd.h"

static EntityFactory* s_sharedEntityFactory = nullptr;

EntityFactory* EntityFactory::getInstance() {
  if (s_sharedEntityFactory == nullptr) {
    s_sharedEntityFactory = new EntityFactory();
    if (!s_sharedEntityFactory || !s_sharedEntityFactory->init()) {
      CC_SAFE_DELETE(s_sharedEntityFactory);
    }
  }
  return s_sharedEntityFactory;
}

void EntityFactory::destroyInstance() {
  CC_SAFE_RELEASE_NULL(s_sharedEntityFactory);
}

EntityFactory::EntityFactory(void) {
}

EntityFactory::~EntityFactory(void) {
}

bool EntityFactory::init() {
  return true;
}

Unit* EntityFactory::getUnit(b2dJson* json, b2Body* body) {
  Unit* unit = Unit::create(true);
  unit->setBody(body);
  unit->update(0);
  return unit;
}

Entry* EntityFactory::getEntry(b2dJson* json, b2Body* body) {
  Entry* entry = Entry::create();
  entry->setBody(body);
  entry->setCapacity(json->getCustomInt(body, "capacity", 0));
  entry->setOpen(json->getCustomBool(body, "isOpen", false));
  entry->setOpenTimer(json->getCustomInt(body, "openTime", 1000));
  entry->setInterval(json->getCustomInt(body, "interval", 100));
  entry->setForceMaxAngle(json->getCustomFloat(body, "forceMaxAngle", 0));
  entry->setForceMinDistance(json->getCustomFloat(body, "forceMinDistance", 0));
  entry->setForceMaxDistance(json->getCustomFloat(body, "forceMaxDistance", 0));
  entry->setForceMinAngularImpulse(json->getCustomFloat(body, "forceMinAngularImpulse", 0));
  entry->setForceMaxAngularImpulse(json->getCustomFloat(body, "forceMaxAngularImpulse", 0));
  entry->update(0);
  return entry;
}

Exit* EntityFactory::getExit(b2dJson* json, b2Body* body) {
  Exit* exit = Exit::create();
  exit->setBody(body);
  exit->update(0);
  return exit;
}

Area* EntityFactory::getArea(b2dJson* json, b2Body* body) {
  Area* area = Area::create();
  area->setBody(body);
  return area;
}

Gravitron* EntityFactory::getGravitron(b2dJson* json, b2Body* body) {
  bool active = json->getCustomBool(body, "active", true);
  Gravitron* gravitron = Gravitron::create(active);
  gravitron->setBody(body);
  gravitron->update(0);
  return gravitron;
}

Level* EntityFactory::getLevel(b2dJson* json, b2Body* body) {
  std::string armature = json->getCustomString(body, "armature", "");
  Level* level = Level::create(armature);
  level->setBody(body);
  level->setLevel(json->getCustomInt(body, "level", 0));
  bool isActive = json->getCustomBool(body, "active", false);
  if (isActive)
    level->activate();
  level->update(0);
  return level;
}

Branch* EntityFactory::getBranch(b2dJson* json, b2Body* body) {
  bool isActive = json->getCustomBool(body, "active", false);
  Branch* branch = Branch::create(isActive);
  branch->setAngle(json->getCustomFloat(body, "angle", 0));
  branch->setTopAngle(json->getCustomFloat(body, "topAngle", 0));
  branch->setBottomAngle(json->getCustomFloat(body, "bottomAngle", 0));
  branch->setMotorSpeed(json->getCustomFloat(body, "motorSpeed", 0));
  branch->setBody(body);
  branch->update(0);
  return branch;
}

DraggableEntity* EntityFactory::getDraggableEntity(b2dJson* json, b2Body* body) {
  bool isActive = json->getCustomBool(body, "active", false);
  DraggableEntity* draggableEntity = DraggableEntity::create(isActive);
  draggableEntity->setPinX(json->getCustomFloat(body, "draggablePinX", 0));
  draggableEntity->setPinY(json->getCustomFloat(body, "draggablePinY", 0));
  draggableEntity->setBody(body);
  draggableEntity->update(0);
  return draggableEntity;
}
