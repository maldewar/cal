#include <math.h>
#include "WorldLevelScene.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"
#include "../util/PathUtil.h"
#include "../factory/SceneFactory.h"

WorldLevelScene::WorldLevelScene() {
  m_worldLevelUILayer = nullptr;
  m_worldLevelDebugLayer = nullptr;
  m_paused = false;
  m_debug = true;
  m_gravityAngle = -M_PI_2;
  m_gravityAngleRotatesWorld = true;
  m_ctrl = CTRL_NONE;
  m_sceneDef = nullptr;

  m_unitsInScene = 0;
  m_unitsSaved = 0;
  m_unitsLost = 0;
  m_unitsRequired = 0;
}

WorldLevelScene* WorldLevelScene::create(std::string filename) {
  WorldLevelScene* worldLevelScene = new (std::nothrow) WorldLevelScene();
  if (worldLevelScene && worldLevelScene->init(filename)) {
    worldLevelScene->autorelease();
    return worldLevelScene;
  }
  CC_SAFE_DELETE(worldLevelScene);
  return nullptr;
}

WorldLevelScene* WorldLevelScene::create(int act, int level) {
  std::string scenePath = PathUtil::getScene(act, level);
  return WorldLevelScene::create(scenePath);
}

bool WorldLevelScene::init(std::string filename) {
  cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("sprite/entry/entry.pvr",
    "sprite/entry/entry.plist", "entry.ExportJson");
  cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("sprite/exit/exit.pvr",
          "sprite/exit/exit.plist", "exit.ExportJson");
  cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("sprite/unit/unit.pvr",
    "sprite/unit/unit.plist","unit.ExportJson");
  cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("sprite/gravitron/gravitron.pvr",
    "sprite/gravitron/gravitron.plist", "gravitron.ExportJson");
  cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("ui/ctrl/ctrl.pvr",
    "ui/ctrl/ctrl.plist", "wheelCtrl.ExportJson");

  std::string sceneFactoryError;
  m_sceneDef = SceneFactory::getInstance()->getSceneDef(filename.c_str(), sceneFactoryError);
  if (!sceneFactoryError.empty()) {
    CCLOG("SceneFactory error %s", sceneFactoryError.c_str());
    //TODO: kill scene.
  }
  int topIndex = -100;
  for (auto layerDef : m_sceneDef->getLayerDefs()) {
    CCLOG("LAYER DEF TYPE:%d INDEX:%d", layerDef->getType(), layerDef->getIndex());
    if (layerDef->isEnabled()) {
      if (layerDef->getType() == LAYER_TYPE_WORLD) {
        WorldLayerDef* worldLayerDef = static_cast<WorldLayerDef*>(layerDef);
        WorldLevelLayer* worldLayer = SceneFactory::getInstance()->buildWorldLevelLayer(worldLayerDef);
        addWorldLevelLayer(worldLayer, worldLayerDef->getIndex());
      } else if (layerDef->getType() == LAYER_TYPE_BG) {
        BgLayerDef* bgLayerDef = static_cast<BgLayerDef*>(layerDef);
        BackgroundLayer* bgLayer = SceneFactory::getInstance()->buildBackgroundLayer(bgLayerDef);
        addChild(bgLayer, bgLayerDef->getIndex());
      }
      if (layerDef->getIndex() > topIndex)
        topIndex = layerDef->getIndex();
    }
  }

  //Ctrl Layer
  m_worldLevelCtrlLayer = WorldLevelCtrlLayer::create(this);
  addChild(m_worldLevelCtrlLayer, topIndex + 1);

  //World UI Layer
  WorldLevelUILayer* uiLayer = WorldLevelUILayer::create();
  m_worldLevelUILayer = uiLayer;
  uiLayer->setScene(this);
  addChild(uiLayer, topIndex + 2);

  //World Debug Layer
  if (m_debug) {
    m_worldLevelDebugLayer = WorldLevelDebugLayer::create();
    m_worldLevelDebugLayer->setScene(this);
    addChild(m_worldLevelDebugLayer, topIndex + 3);
  }

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

void WorldLevelScene::addWorldLevelLayer(WorldLevelLayer* worldLevelLayer, int index) {
  //Set as main
  m_worldLevelLayer = worldLevelLayer;
  m_worldLevelLayer->setMain(true);
  m_unitsInScene = m_worldLevelLayer->getUnitCount();
  m_worldLevelLayers.push_back(worldLevelLayer);
  addChild(worldLevelLayer, index);
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
  if (m_gravityAngleRotatesWorld) {
    m_worldLevelLayer->rotate(-m_gravityAngle - M_PI_2, 0.5f);
  }
  for (auto worldLevelLayer : m_worldLevelLayers) {
    worldLevelLayer->getWorld()->SetGravity(b2Vec2(xGravity, yGravity));
    for (b2Body* b = worldLevelLayer->getWorld()->GetBodyList(); b; b = b->GetNext()) {
      b->SetAwake(true);
    }
  }
}

float WorldLevelScene::getGravityAngle() {
  return m_gravityAngle;
}

void WorldLevelScene::selectCtrl(int ctrl, Entity* entity) {
  m_ctrl = ctrl;
  if (m_ctrl == CTRL_GRAVITRON) {
    m_worldLevelCtrlLayer->beginCtrlTouch(ctrl, entity);
  }
}

bool WorldLevelScene::gravityAngleRotatesWorld() {
  return m_gravityAngleRotatesWorld;
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

void WorldLevelScene::onExit() {
  Scene::onExit();
  cocostudio::ActionManagerEx::destroyInstance();
}

void WorldLevelScene::addUnit(int count) {
  m_unitsInScene += count;
  CCLOG("New unit added to scene, total: %d", m_unitsInScene);
}

void WorldLevelScene::removeUnit(int count, bool isLost) {
  if (isLost) {
    m_unitsLost += count;
  } else {
    m_unitsSaved += count;
  }
  m_unitsInScene -= count;
  CCLOG("Unit removed from scene, total: %d", m_unitsInScene);
}
