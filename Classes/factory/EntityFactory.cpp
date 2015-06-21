#include "EntityFactory.h"
#include "../util/CMath.h"


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

void EntityFactory::makeEntity(Entity* entity,
                               b2Body* body, 
                               b2dJson* json) {
  entity->setBody(body);
  if (json) {
    entity->setZOrderTouch(json->getCustomInt(body, "zOrderTouch", 0));
    int zOrderDraw = json->getCustomInt(body, "zOrderDraw", 0);
    entity->setZOrderDraw(zOrderDraw);
    entity->setLocalZOrder(zOrderDraw);
    entity->setSkin(json->getCustomInt(body, "skin", 0));
  }
}

void EntityFactory::makeEntityElem(EntityElem* entityElem,
                                   b2Fixture* fixture,
                                   b2dJson* json) {
  entityElem->setFixture(fixture);
  if (json) {
    entityElem->setTouchEnabled(json->getCustomBool(fixture, "touch", true));
  }
}

b2Fixture* EntityFactory::getByName(std::string name, b2Body* body, b2dJson* json) {
  b2Fixture* result = nullptr;
  for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
    std::string fixtureName = json->getFixtureName(f);
    if (fixtureName.compare(name) == 0) {
      result = f;
      break;
    }
  }
  return result;
}

bool EntityFactory::init() {
  return true;
}

Entity* EntityFactory::getEntity(b2Body* body, b2dJson* json) {
  Entity* entity = new Entity();
  makeEntity(entity, body, json);
  return entity;
}

EntityElem* EntityFactory::getEntityElem(b2Fixture* fixture, b2dJson* json) {
  EntityElem* entityElem = new EntityElem();
  makeEntityElem(entityElem, fixture, json);
  return entityElem;
}

Unit* EntityFactory::getUnit(b2dJson* json, b2Body* body) {
  Unit* unit = Unit::create(true);
  makeEntity(unit, body, json);
  unit->update(0);
  return unit;
}

Entry* EntityFactory::getEntry(b2dJson* json, b2Body* body) {
  Entry* entry = Entry::create();
  makeEntity(entry, body, json);
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
  makeEntity(exit, body, json);
  exit->update(0);
  return exit;
}

Area* EntityFactory::getArea(b2dJson* json, b2Body* body) {
  Area* area = Area::create();
  makeEntity(area, body, json);
  return area;
}

Gravitron* EntityFactory::getGravitron(b2dJson* json, b2Body* body) {
  bool active = json->getCustomBool(body, "active", true);
  Gravitron* gravitron = Gravitron::create(active);
  makeEntity(gravitron, body, json);
  gravitron->update(0);
  return gravitron;
}

Level* EntityFactory::getLevel(b2dJson* json, b2Body* body) {
  std::string armature = json->getCustomString(body, "armature", "");
  Level* level = Level::create(armature);
  makeEntity(level, body, json);
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
  makeEntity(branch, body, json);
  branch->setAngle(json->getCustomFloat(body, "angle", 0));
  branch->setTopAngle(json->getCustomFloat(body, "topAngle", 0));
  branch->setBottomAngle(json->getCustomFloat(body, "bottomAngle", 0));
  branch->setMotorSpeed(json->getCustomFloat(body, "motorSpeed", 0));
  branch->update(0);
  return branch;
}

DraggableEntity* EntityFactory::getDraggableEntity(b2dJson* json, b2Body* body) {
  bool isActive = json->getCustomBool(body, "active", false);
  DraggableEntity* draggableEntity = DraggableEntity::create(isActive);
  makeEntity(draggableEntity, body, json);
  draggableEntity->setPinX(json->getCustomFloat(body, "draggablePinX", 0));
  draggableEntity->setPinY(json->getCustomFloat(body, "draggablePinY", 0));
  draggableEntity->update(0);
  return draggableEntity;
}

Flux* EntityFactory::getFlux(b2dJson* json, b2Body* body) {
  bool isActive = json->getCustomBool(body, "active", true);
  Flux* flux = Flux::create(isActive);
  makeEntity(flux, body, json);
  flux->update(0);
  b2Fixture* fixture = getByName("arrow_fixture", body, json);
  if (fixture) {
    b2PolygonShape* shape = (b2PolygonShape*)fixture->GetShape();
    const b2Vec2 pA = body->GetWorldPoint(shape->GetVertex(0));
    const b2Vec2 pB = body->GetWorldPoint(shape->GetVertex(1));
    const b2Vec2 pC = body->GetWorldPoint(shape->GetVertex(2));
    float angle = CMath::getTriangleAngle(pA.x, pA.y, pB.x, pB.y, pC.x, pC.y);
    flux->setArrowAngle(angle);
    b2Fixture* targetFixture = getByName("direction_fixture", body, json);
    if (targetFixture) {
      b2PolygonShape* targetShape = (b2PolygonShape*)fixture->GetShape();
      const b2Vec2 targetPosition = body->GetWorldPoint(targetShape->GetVertex(0));
      flux->setTarget(targetPosition.x, targetPosition.y);
    }
  }
  return flux;
}
