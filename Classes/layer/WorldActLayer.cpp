#include "WorldActLayer.h"

#include <spine/spine-cocos2dx.h>

#include "WorldLevelUILayer.h"
#include "../model/ImageNode.h"
#include "../model/ImageBody.h"
#include "../model/Level.h"
#include "../factory/EntityFactory.h"
#include "../manager/StorageManager.h"
#include "../scene/WorldLevelScene.h"

using namespace std;
using namespace cocos2d;

WorldActLayer::WorldActLayer() : BasicRUBELayer() {
  m_debugDrawEnabled = true;
  m_rotationEnabled = true;
}

WorldActLayer* WorldActLayer::create(int act, WorldLayerDef* worldLayerDef) {
  WorldActLayer* worldLevelLayer = new (std::nothrow) WorldActLayer();
  if (worldLevelLayer && worldLevelLayer->init(act, worldLayerDef)) {
    worldLevelLayer->autorelease();
    return worldLevelLayer;
  }
  CC_SAFE_DELETE(worldLevelLayer);
  return nullptr;
}

bool WorldActLayer::init(int act, WorldLayerDef* worldLayerDef) {
  m_act = act;
  return BasicRUBELayer::init(nullptr, worldLayerDef);
}

// This is called after the Box2D world has been loaded, and while the b2dJson information
// is still available to do extra loading. Here is where we load the images.
void WorldActLayer::afterLoadProcessing(b2dJson* json) {
  // Process bodies
  std::vector<b2Body*> b2Bodies;
  json->getAllBodies(b2Bodies);
  int currentAct = StorageManager::getInstance()->getAct();
  int currentLevel = -1;
  if (m_act >= currentAct) {
    currentLevel = StorageManager::getInstance()->getLevel();
  }
  for (int i = 0; i < b2Bodies.size(); i++) {
    if (json->hasCustomString(b2Bodies[i], "category")) {
      std::string category = json->getCustomString(b2Bodies[i], "category");
      if (category.compare("level") == 0) {
        Level* level = EntityFactory::getInstance()->getLevel(json, b2Bodies[i]);
        if (currentLevel == -1 || level->getLevel() <= currentLevel)
          level->activate();
        addChild(level);
      }
    }
  }

  BasicRUBELayer::afterLoadProcessing(json);
}

// Remove one body and any images is had attached to it from the layer
void WorldActLayer::removeBodyFromWorld(b2Body* body) {
  m_world->DestroyBody(body);
}

void WorldActLayer::onBodyTouchBegan(std::vector<b2Body*> bodies, std::vector<b2Fixture*> fixtures) {
  b2Fixture* fixture = fixtures[0];
  b2Body* body = bodies[0];
  if (fixture->IsSensor()) {
    void* userData;
    userData = body->GetUserData();
    if (userData) {
      Level* level = (Level*)userData;
      if (level->isActive() && level->getLevel() > 0) {
        cocos2d::log("Getting act %d, level %d", m_act, level->getLevel());
        cocos2d::Director::getInstance()->replaceScene(WorldLevelScene::create(m_act, level->getLevel()));
      }
    }
  }
}

void WorldActLayer::onWorldTouchBegan(b2Vec2& position) {
}
