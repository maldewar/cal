#include "WorldLevelScene.h"
#include "cocostudio/CocoStudio.h"

WorldLevelScene::WorldLevelScene() {
  m_worldLevelUILayer = nullptr;
  m_paused = false;
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
  BackgroundLayer* bgLayer = BackgroundLayer::create();
  addChild(bgLayer, 0);
  WorldLevelLayer* layer = WorldLevelLayer::create();
  layer->enableDebugDraw(true);
  addWorldLevelLayer(layer);
  WorldLevelUILayer* uiLayer = WorldLevelUILayer::create();
  m_worldLevelUILayer = uiLayer;
  uiLayer->setScene(this);
  addChild(uiLayer, 2);
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

void WorldLevelScene::addWorldLevelLayer(WorldLevelLayer* worldLevelLayer) {
  m_worldLevelLayers.push_back(worldLevelLayer);
  addChild(worldLevelLayer, 1);
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
