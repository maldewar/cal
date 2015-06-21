#include "WorldLevelLayer.h"
#include "WorldLevelUILayer.h"
#include "../util/b2dJson.h"
#include "../util/b2dJsonImage.h"
#include "../util/QueryCallbacks.h"
#include "../model/ImageNode.h"
#include "../model/ImageBody.h"
#include "../factory/BodyFactory.h"
#include "../factory/EntityFactory.h"

#include <spine/spine-cocos2dx.h>

using namespace std;
using namespace cocos2d;

WorldLevelLayer::WorldLevelLayer() : BasicRUBELayer() {
  m_unitCount = 0;
  m_worldScene = nullptr;
  m_controlGrabbed = false;
  m_rayCastTool = new RayCastTool(10.0f);
  m_rayCastTool->SetFilter(ENTITY_TYPE_AREA);
  m_unitLayer = Layer::create();
  m_areaLayer = Layer::create();
  m_assetLayer = Layer::create();
  BasicRUBELayer::addChild(m_assetLayer, 3);
  BasicRUBELayer::addChild(m_areaLayer, 2);
  BasicRUBELayer::addChild(m_unitLayer, 1);
  m_contactSystem = nullptr;
  m_AISystem = nullptr;
  m_touchedEntity = nullptr;
}

WorldLevelLayer* WorldLevelLayer::create(WorldLevelScene* parent,
                                         WorldLayerDef* worldLayerDef) {
  WorldLevelLayer* worldLevelLayer = new (std::nothrow) WorldLevelLayer();
  if (worldLevelLayer && worldLevelLayer->init(parent, worldLayerDef)) {
    worldLevelLayer->autorelease();
    return worldLevelLayer;
  }
  CC_SAFE_DELETE(worldLevelLayer);
  return nullptr;
}

bool WorldLevelLayer::init(WorldLevelScene* parent, WorldLayerDef* worldLayerDef) {
  m_AISystem = new AISystem(parent->getGravityAngle());
  m_AISystem->setDebugDrawEnabled(true);
  if (m_AISystem->isDebugDrawEnabled()) {
    this->addChild(m_AISystem->getChoiceGraph()->getDrawNode());
  }
  if (BasicRUBELayer::init(parent, worldLayerDef)) {
    m_filename = worldLayerDef->getPath();
    return true;
  }
  return false;
}

int WorldLevelLayer::getUnitCount() {
  return m_unitCount;
}

void WorldLevelLayer::removeUnit(int count, bool isLost) {
  m_unitCount--;
  if (m_isMain) {
    m_worldScene->removeUnit(count, isLost);
  }
}

void WorldLevelLayer::addUnit(int count) {
  m_unitCount++;
  if (m_isMain) {
    m_worldScene->addUnit(count);
  }
}

void WorldLevelLayer::setDataOnFixtures(b2dJson* json, b2Body* body, Entity* parent) {
  for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
    if (json->hasCustomString(f, "category")) {
      std::string category = json->getCustomString(f, "category");
      if (category.compare("default") == 0) {
        EntityElem* entityElem = EntityFactory::getInstance()->getEntityElem(f, json);
        entityElem->setEntity(parent);
      }
    }
  }
}

// This is called after the Box2D world has been loaded, and while the b2dJson information
// is still available to do extra loading. Here is where we load the images.
void WorldLevelLayer::afterLoadProcessing(b2dJson* json)
{
  BasicRUBELayer::afterLoadProcessing(json);
  BodyFactory::getInstance()->setWorld(m_world);
  m_contactSystem = new ContactSystem();
  m_world->SetContactListener(m_contactSystem);
  // Process bodies
  std::vector<b2Body*> b2Bodies;
  json->getAllBodies(b2Bodies);
  for (int i = 0; i < b2Bodies.size(); i++) {
    if (json->hasCustomString(b2Bodies[i], "category")) {
      std::string category = json->getCustomString(b2Bodies[i], "category");
      if (category.compare("entry") == 0) {
        Entry* entry = EntityFactory::getInstance()->getEntry(json, b2Bodies[i]);
        addChild(entry);
      } else if (category.compare("exit") == 0) {
        Exit* exit = EntityFactory::getInstance()->getExit(json, b2Bodies[i]);
        addChild(exit);
      }else if (category.compare("unit") == 0) {
        Unit* unit = EntityFactory::getInstance()->getUnit(json, b2Bodies[i]);
        addChild(unit);
        addUnit(1);
      } else if (category.compare("area") == 0) {
        Area* area = EntityFactory::getInstance()->getArea(json, b2Bodies[i]);
        addChild(area);
        m_AISystem->addWalkableEntity(area);
      } else if (category.compare("gravitron") == 0) {
        Gravitron* gravitron = EntityFactory::getInstance()->getGravitron(json, b2Bodies[i]);
        addChild(gravitron);
      } else if (category.compare("branch") == 0) {
        if (json->hasCustomString(b2Bodies[i], "m_id")) {
          Branch* branch = EntityFactory::getInstance()->getBranch(json, b2Bodies[i]);
          std::string _id = json->getCustomString(b2Bodies[i], "m_id");
          m_branches.insert(std::make_pair(_id, branch));
          addChild(branch);
        }
      } else if (category.compare("flux") == 0) {
        Flux* flux = EntityFactory::getInstance()->getFlux(json, b2Bodies[i]);
        setDataOnFixtures(json, b2Bodies[i], flux);
        addChild(flux);
      }else if (category.compare("draggable") == 0) {
        DraggableEntity* draggableEntity =
          EntityFactory::getInstance()->getDraggableEntity(json, b2Bodies[i]);
        addChild(draggableEntity);
      }
      BodyFactory::getInstance()->addBodyDef(category, b2Bodies[i]);
    }
  }
  for (int i = 0; i < b2Bodies.size(); i++) {
    if (json->hasCustomString(b2Bodies[i], "belongsToCategory")) {
      std::string belongsToCategory = json->getCustomString(b2Bodies[i], "belongsToCategory");
      std::string belongsToId = json->getCustomString(b2Bodies[i], "belongsToId", "");
      int belongsToIndex = json->getCustomInt(b2Bodies[i], "belongsToIndex", 0);
      if (belongsToCategory.compare("branch") == 0) {
        if (m_branches.count(belongsToId) > 0) {
          void* bodyUserData  = b2Bodies[i]->GetUserData();
          if (!bodyUserData) {
            Entity* branchEntity = EntityFactory::getInstance()->getEntity(b2Bodies[i], json);
            addChild(branchEntity);
          }
          m_branches[belongsToId]->addBody(b2Bodies[i], belongsToIndex);
        }
      }
    }
  }

  std::vector<b2Joint*> b2Joints;
  json->getAllJoints(b2Joints);
  for (int i = 0; i < b2Joints.size(); i++) {
    if (json->hasCustomString(b2Joints[i], "category")) {
      std::string category = json->getCustomString(b2Joints[i], "category");
      if (category.compare("branch") == 0) {
        if (json->hasCustomString(b2Joints[i], "m_id")) {
          std::string _id = json->getCustomString(b2Joints[i], "m_id");
          std::map<std::string, Branch*>::iterator it;
          it = m_branches.find(_id);
          if (it != m_branches.end()) {
            it->second->addJoint((b2RevoluteJoint*)b2Joints[i]);
          }
        }
      }
    }
  }
}

void WorldLevelLayer::addChild(Node* node) {
  Entity* entity = dynamic_cast<Entity*>(node);
  if (entity) {
    entity->setWorldLevelLayer(this);
    if (entity->getType() == ENTITY_TYPE_UNIT) {
      Unit* unit = static_cast<Unit*>(entity);
      unit->commandWander();
      m_unitLayer->addChild(node);
      m_AISystem->registerComponent(unit->getId(), unit);
      return;
    } else if (entity->getType() == ENTITY_TYPE_AREA) {
      m_areaLayer->addChild(node);
      return;
    }
  }
  m_assetLayer->addChild(node);
}

void WorldLevelLayer::removeChild(Node* node, bool cleanup) {
  Entity* entity = dynamic_cast<Entity*>(node);
  if (entity) {
    if (entity->getType() == ENTITY_TYPE_UNIT) {
      m_deletedEntities.push_back(entity);
      //entity->unscheduleUpdate();
      //entity->unscheduleAllCallbacks();
      //m_unitLayer->removeChild(node, cleanup);
      //removeBodyFromWorld(entity->getBody());
      //node->removeFromParent();
      return;
    } else if (entity->getType() == ENTITY_TYPE_AREA) {
      m_areaLayer->removeChild(node, cleanup);
      return;
    }
  }
  m_assetLayer->removeChild(node, cleanup);
}

void WorldLevelLayer::setWorldLevelScene(WorldLevelScene* worldLevelScene) {
  m_worldScene = worldLevelScene;
}

WorldLevelScene* WorldLevelLayer::getWorldLevelScene() {
  return m_worldScene;
}

void WorldLevelLayer::setParentScene(BaseScene* parent) {
  BaseLayer::setParentScene(parent);
  m_worldScene = static_cast<WorldLevelScene*>(parent);
}

// This method should undo anything that was done by afterLoadProcessing, and make sure
// to call the superclass method so it can do the same
void WorldLevelLayer::clear()
{
  /*
    for (set<ImageInfo*>::iterator it = m_imageInfos.begin(); it != m_imageInfos.end(); ++it) {
        ImageInfo* imgInfo = *it;
        removeChild(imgInfo->sprite, true);
    }
    m_imageInfos.clear();
    
    BasicRUBELayer::clear();
  */
}

// Standard Cocos2d method. Call the super class to step the physics world, and then
// move the images to match the physics body positions
void WorldLevelLayer::update(float dt)
{
  if (m_deletedEntities.size() > 0) {
    vector<Entity*>::iterator entityIt = m_deletedEntities.begin();
    while (entityIt != m_deletedEntities.end()) {
      removeBodyFromWorld((*entityIt)->getBody());
      if ((*entityIt)->getType() == ENTITY_TYPE_UNIT) {
        m_unitLayer->removeChild((*entityIt), true);
      } else if ((*entityIt)->getType() == ENTITY_TYPE_AREA) {
        m_areaLayer->removeChild((*entityIt), true);
      } else {
        m_assetLayer->removeChild((*entityIt), true);
      }
      entityIt = m_deletedEntities.erase(entityIt);
    }
  }
  BasicRUBELayer::update(dt);
}

// Remove one body and any images is had attached to it from the layer
void WorldLevelLayer::removeBodyFromWorld(b2Body* body)
{
  m_world->DestroyBody(body);
  /*
    
    //go through the image info array and remove all sprites that were attached to the body we just deleted
    vector<ImageInfo*> imagesToRemove;
    for (set<ImageInfo*>::iterator it = m_imageInfos.begin(); it != m_imageInfos.end(); ++it) {
        ImageInfo* imgInfo = *it;
        if ( imgInfo->body == body ) {
            removeChild(imgInfo->sprite, true);
            imagesToRemove.push_back(imgInfo);
        }
    }
    
    //also remove the infos for those images from the image info array
    for (int i = 0; i < imagesToRemove.size(); i++)
        m_imageInfos.erase( imagesToRemove[i] );
  */
}

/*
void WorldLevelLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event) {
  BasicRUBELayer::onTouchesBegan(touches, event);
  if (touches.size() == 1) {
    Touch * touch = touches[0];
    m_worldScene->setTouch(touch);
  }
}

void WorldLevelLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) {
  if (!m_controlGrabbed) {
    BasicRUBELayer::onTouchesMoved(touches, unused_event);
    Touch* touch = touches[0];
    m_worldScene->setTouch(touch);
    Point screenPos = touch->getLocation();
    b2Vec2 worldPos = screenToWorld(screenPos);
    m_rayCastTool->RayCast(m_world, worldPos.x, worldPos.y, getWorldLevelScene()->getGravityAngle());
  }
}

void WorldLevelLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) {
  m_worldScene->setTouch(nullptr);
  if (!m_navigationEnabled) {
    BasicRUBELayer::onTouchesEnded(touches, unused_event);
    return;
  }
}
*/

void WorldLevelLayer::onBodyTouchBegan(std::vector<b2Body*> bodies, std::vector<b2Fixture*> fixtures) {
  int index = getTouchedBody(bodies);
  if (index < 0)
    return;
  b2Body* body = bodies[index];
  b2Fixture* fixture = fixtures[index];
  switch(body->GetType()) {
    case b2_staticBody:
      void* bodyUserData;
      bodyUserData  = body->GetUserData();
      if (bodyUserData) {
        Entity* entity = (Entity*)bodyUserData;
        switch(entity->getType()) {
          case ENTITY_TYPE_AREA:
            CCLOG("Area touched.");
            break;
          case ENTITY_TYPE_GRAVITRON:
            entity->select();
            break;
        }
        m_touchedEntity = entity;
      } else {
        m_touchedEntity = nullptr;
      }
      break;
    case b2_kinematicBody:
    case b2_dynamicBody:
      void* dynamicBodyUserData;
      dynamicBodyUserData = body->GetUserData();
      if (dynamicBodyUserData) {
        Entity* entity = (Entity*)dynamicBodyUserData;
        switch(entity->getType()) {
          case ENTITY_TYPE_UNIT:
            entity->select();
            break;
          case ENTITY_TYPE_GRAVITRON:
            entity->select();
            break;
          case ENTITY_TYPE_BRANCH:
            entity->select(body);
            break;
          case ENTITY_TYPE_DRAGGABLE:
            entity->select(getWorldLevelScene()->getStartTouch());
            break;
          case ENTITY_TYPE_FLUX:
            if (entity->isValidTouch(fixture)) {
              entity->select();
            }
            break;
        }
        m_touchedEntity = entity;
      } else {
        m_touchedEntity = nullptr;
      }
      break;
  }
}

void WorldLevelLayer::onBodyTouchEnded() {
  if (m_touchedEntity) {
    m_touchedEntity->deselect();
  }
}

void WorldLevelLayer::onWorldTouchBegan(b2Vec2& position) {
}

AISystem* WorldLevelLayer::getAISystem() {
  return m_AISystem;
}

void WorldLevelLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event) {
  if (m_isMain && touches.size() == 1) {
    m_worldScene->setStartTouch(touches[0]);
    std::map<std::string, Entity*>::iterator it = m_touchListeners.begin();
    while (it != m_touchListeners.end()){
      if (it->second->onStartTouchEvent(touches[0])) {
        it = m_touchListeners.erase(it);
      } else {
        ++it;
      }
    }
  }
  BasicRUBELayer::onTouchesBegan(touches, event);
}

void WorldLevelLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) {
  if (m_isMain) {
    std::map<std::string, Entity*>::iterator it = m_touchListeners.begin();
    while (it != m_touchListeners.end()){
      if (it->second->onMoveTouchEvent(touches[0])) {
        it = m_touchListeners.erase(it);
      } else {
        ++it;
      }
    }
  }
}

void WorldLevelLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event) {
  if (m_isMain && touches.size() == 1) {
    m_worldScene->setEndTouch(touches[0]);
    std::map<std::string, Entity*>::iterator it = m_touchListeners.begin();
    while (it != m_touchListeners.end()){
      if (it->second->onEndTouchEvent(touches[0])) {
        it = m_touchListeners.erase(it);
      } else {
        ++it;
      }
    }
  }
  BasicRUBELayer::onTouchesEnded(touches, event);
}

bool WorldLevelLayer::addTouchListener(Entity* entity) {
  std::map<std::string, Entity*>::iterator it = m_touchListeners.find(entity->getId());
  if (it == m_touchListeners.end()) {
    m_touchListeners[entity->getId()] = entity;
    return true;
  }
  return false;
}

bool WorldLevelLayer::removeTouchListener(Entity* entity) {
  std::map<std::string, Entity*>::iterator it = m_touchListeners.find(entity->getId());
  if (it != m_touchListeners.end()) {
    m_touchListeners.erase(it);
    return true;
  }
  return false;
}

int WorldLevelLayer::getTouchedBody(std::vector<b2Body*> bodies) {
  int index = -1;
  int zIndex = -1000;
  for (int i = 0; i < bodies.size(); i++) {
    b2Body* body = bodies[i];
    void* userData = body->GetUserData();
    if (userData) {
      Entity* entity = (Entity*)userData;
      if (entity->getZOrderTouch() >= zIndex) {
        zIndex = entity->getZOrderTouch();
        index = i;
      }
    }
  }
  return index;
}

void WorldLevelLayer::onDraw(const cocos2d::Mat4 &transform, uint32_t flags) {
  Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
  Director::getInstance()->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
  //DrawPrimitives::setDrawColor4F(255, 255, 255, 1);
  //DrawPrimitives::drawLine(*m_rayCastTool->GetStart(), *m_rayCastTool->GetEnd());
  if (m_AISystem->isDebugDrawEnabled()) {
    m_AISystem->debugDraw();
  }
  Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

  BasicRUBELayer::onDraw(transform, flags);
}
