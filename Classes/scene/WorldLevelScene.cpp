#include <math.h>
#include "WorldLevelScene.h"
#include "cocostudio/CocoStudio.h"

WorldLevelScene::WorldLevelScene() {
  m_worldLevelUILayer = nullptr;
  m_worldLevelDebugLayer = nullptr;
  m_paused = false;
  m_debug = true;
  m_gravityAngle = -M_PI_2;
}

WorldLevelScene::~WorldLevelScene() {
}

WorldLevelScene* WorldLevelScene::create(std::string filename) {
  WorldLevelScene* worldLevelScene = new (std::nothrow) WorldLevelScene();
  if (worldLevelScene && worldLevelScene->init()) {
    worldLevelScene->autorelease();
    return worldLevelScene;
  }
  CC_SAFE_DELETE(worldLevelScene);
  return nullptr;
}

bool WorldLevelScene::init(void) {
  cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("sprite/entry/entry.pvr",
    "sprite/entry/entry.plist", "entry.ExportJson");
  cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("sprite/unit/unit.pvr",
    "sprite/unit/unit.plist","unit.ExportJson");
  cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("sprite/gravitron/gravitron.pvr",
    "sprite/gravitron/gravitron.plist", "gravitron.ExportJson");
  //Background Layer
  BackgroundLayer* bgLayer = BackgroundLayer::create();
  //addChild(bgLayer, 0);

  //World Layer
  WorldLevelLayer* layer = WorldLevelLayer::create();
  layer->enableDebugDraw(false);
  addWorldLevelLayer(layer);

  //World Debug Layer
  if (m_debug) {
    CCLOG("ADDING DEBUG LAYER");
    m_worldLevelDebugLayer = WorldLevelDebugLayer::create();
    m_worldLevelDebugLayer->setScene(this);
    addChild(m_worldLevelDebugLayer, 4);
    CCLOG("DEBUG LAYER ADDED");
  }

  //World UI Layer
  WorldLevelUILayer* uiLayer = WorldLevelUILayer::create();
  m_worldLevelUILayer = uiLayer;
  uiLayer->setScene(this);
  addChild(uiLayer, 3);

  return true;
}

void WorldLevelScene::pause(bool pause) {
  m_paused = pause;
  for (auto layer : m_worldLevelLayers) {
    if (m_paused) {
      pauseChildrenRecursive(layer, true);
    } else {
      pauseChildrenRecursive(layer, false);
    }
  }
}

void WorldLevelScene::togglePause() {
  pause(!m_paused);
}

void WorldLevelScene::toggleDebug() {
  
}

void WorldLevelScene::addWorldLevelLayer(WorldLevelLayer* worldLevelLayer) {
  m_worldLevelLayers.push_back(worldLevelLayer);
  addChild(worldLevelLayer, 1);
  worldLevelLayer->enableDebugDraw(m_debug);
  float xGravity = cos(m_gravityAngle) * 6;
  float yGravity = sin(m_gravityAngle) * 6;
  worldLevelLayer->getWorld()->SetGravity(b2Vec2(xGravity, yGravity));
  worldLevelLayer->setWorldLevelScene(this);
}

void WorldLevelScene::pauseChildrenRecursive(cocos2d::Node* node, bool pause) {
  if (pause) {
    node->pauseSchedulerAndActions();
  } else {
    node->resumeSchedulerAndActions();
  }
  for (auto child : node->getChildren()) {
    pauseChildrenRecursive(child, pause);
  }
}

void WorldLevelScene::setGravityAngle(float angle) {
  m_gravityAngle = angle;
  float xGravity = cos(m_gravityAngle) * 6;
  float yGravity = sin(m_gravityAngle) * 6;
  for (auto worldLevelLayer : m_worldLevelLayers) {
    worldLevelLayer->getWorld()->SetGravity(b2Vec2(xGravity, yGravity));
    for (b2Body* b = worldLevelLayer->getWorld()->GetBodyList(); b; b = b->GetNext()) {
      b->SetAwake(true);
    }
  }
}

bool WorldLevelScene::isDebugEnable() {
  return m_debug;
}

void WorldLevelScene::enableDebug(bool debug) {
  m_debug = debug;
  for (auto worldLevelLayer : m_worldLevelLayers) {
    worldLevelLayer->enableDebugDraw(m_debug);
  }
}
