#include "WorldActLayer.h"
#include "WorldLevelUILayer.h"
#include "../util/b2dJson.h"
#include "../util/b2dJsonImage.h"
#include "../util/QueryCallbacks.h"
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

WorldActLayer* WorldActLayer::create(int act, std::string filename) {
  WorldActLayer* worldLevelLayer = new (std::nothrow) WorldActLayer();
  if (worldLevelLayer && worldLevelLayer->init(act, filename)) {
    worldLevelLayer->autorelease();
    return worldLevelLayer;
  }
  CC_SAFE_DELETE(worldLevelLayer);
  return nullptr;
}

bool WorldActLayer::init(int act, std::string filename) {
  m_act = act;
  m_filename = filename;
  return BasicRUBELayer::init();
}

string WorldActLayer::getFilename() {
    return m_filename;
}

// Override superclass to set different starting offset
Point WorldActLayer::initialWorldOffset()
{
    // If you are not sure what to set the starting position as, you can
    // pan and zoom the scene until you get the right fit, and then set
    // a breakpoint in the draw or update methods to see what the values
    // of [self scale] and [self position] are.
    //
    // For the images.json scene, I did this on my iPad in landscape (1024x768)
    // and came up with a value of 475,397 for the position. Since the
    // offset is measured in pixels, we need to set this as a percentage of
    // the current screen height instead of a fixed value, to get the same
    // result on different devices.
    // 
    //Size s = Director::getInstance()->getWinSize();
    //return cocos2d::Vec2(0,0);
    //return CCPointMake( s.width * (475 / 1024.0), s.height * (397 / 768.0) );
    // TODO: use cameras
    return getCenteredPosition(0, 0);
}


// Override superclass to set different starting scale
float WorldActLayer::initialWorldScale()
{
    Size s = Director::getInstance()->getWinSize();
    //return s.height / 35; //screen will be 35 physics units high
    return s.height/4;
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

void WorldActLayer::onBodyTouchBegan(b2Body* body, b2Fixture* fixture) {
  if (fixture->IsSensor()) {
    void* userData;
    userData = body->GetUserData();
    if (userData) {
      Level* level = (Level*)userData;
      if (level->isActive() && level->getLevel() > 0) {
        cocos2d::Director::getInstance()->replaceScene(WorldLevelScene::create(m_act, level->getLevel()));
      }
    }
  }
}

void WorldActLayer::onWorldTouchBegan(b2Vec2& position) {
}
