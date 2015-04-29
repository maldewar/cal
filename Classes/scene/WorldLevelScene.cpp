#include <math.h>
#include "WorldLevelScene.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"
#include "../util/PathUtil.h"
#include "../util/CMath.h"
#include "../factory/SceneFactory.h"

float WorldLevelScene::m_gravityAngle = 0;
b2Vec2 WorldLevelScene::m_gravity     = b2Vec2(0, 0);
b2Vec2 WorldLevelScene::m_rightNormal = b2Vec2(0, 0);
b2Vec2 WorldLevelScene::m_leftNormal  = b2Vec2(0, 0);
float WorldLevelScene::m_gravityCos   = 1;
float WorldLevelScene::m_gravitySin   = 0;

WorldLevelScene::WorldLevelScene() : BaseScene() {
  m_worldLevelLayer = nullptr;
  m_worldLevelUILayer = nullptr;
  m_gravityCtrlLayer = nullptr;
  m_selectCtrlLayer = nullptr;
  m_worldLevelStatisticsLayer = nullptr;
  m_worldLevelDebugLayer = nullptr;
  m_paused = false;
  m_debug = true;
  m_gravityAngle = -M_PI_2;
  m_gravityAngleRotatesWorld = true;
  m_ctrl = CTRL_NONE;
  m_levelSceneDef = nullptr;

  m_unitsInScene  = 0;
  m_unitsSaved    = 0;
  m_unitsLost     = 0;
  m_unitsRequired = 0;

  m_startTouchLocation = new cocos2d::Vec2();
  m_endTouchLocation   = new cocos2d::Vec2();
  m_startTouch = nullptr;
  m_endTouch = nullptr;
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
  cocos2d::log("WorldLevelScene::init filename:%s", filename.c_str());
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

  m_levelSceneDef = SceneFactory::getInstance()->getLevelSceneDef(filename.c_str());
  if (m_levelSceneDef == nullptr) {
    //TODO: kill scene.
  }

  m_unitsRequired = m_levelSceneDef->getUnitsRequired();

  cocos2d::log("WorldLevelScene::init...");
  if (!BaseScene::init(filename)) {
    return false;
  }
  /*
  for (auto layerDef : m_levelSceneDef->getLayerDefs()) {
    if (layerDef->isEnabled()) {
      if (layerDef->getType() == LAYER_TYPE_WORLD) {
        WorldLayerDef* worldLayerDef = static_cast<WorldLayerDef*>(layerDef);
        WorldLevelLayer* worldLayer = SceneFactory::getInstance()->getWorldLevelLayer(worldLayerDef);

        addWorldLevelLayer(worldLayer, worldLayerDef->getIndex());
      } else if (layerDef->getType() == LAYER_TYPE_BG) {
        BgLayerDef* bgLayerDef = static_cast<BgLayerDef*>(layerDef);
        BackgroundLayer* bgLayer = SceneFactory::getInstance()->getBackgroundLayer(bgLayerDef);
        addChild(bgLayer, bgLayerDef->getIndex());
      }
      if (layerDef->getIndex() > topIndex)
        topIndex = layerDef->getIndex();
    }
  }
  */

  //Gravity Ctrl Layer
  m_gravityCtrlLayer = GravityCtrlLayer::create(this);
  addChild(m_gravityCtrlLayer, m_topIndex + 1);

  //Select Ctrl Layer
  m_selectCtrlLayer = SelectCtrlLayer::create(this);
  addChild(m_selectCtrlLayer, m_topIndex + 2);

  //World UI Layer
  m_worldLevelUILayer = WorldLevelUILayer::create();
  m_worldLevelUILayer->setScene(this);
  addChild(m_worldLevelUILayer, m_topIndex + 3);

  //Statistics Layer
  m_worldLevelStatisticsLayer = WorldLevelStatisticsLayer::create();
  m_worldLevelStatisticsLayer->setVisible(false);
  addChild(m_worldLevelStatisticsLayer, m_topIndex + 4);

  //World Debug Layer
  if (m_debug) {
    m_worldLevelDebugLayer = WorldLevelDebugLayer::create();
    m_worldLevelDebugLayer->setScene(this);
    addChild(m_worldLevelDebugLayer, m_topIndex + 5);
  }

  return true;
}

void WorldLevelScene::pause(bool pause) {
  m_paused = pause;
  for (auto layer : m_worldLevelLayers) {
    layer->pause(m_paused);
  }
}

void WorldLevelScene::togglePause() {
  pause(!m_paused);
}

void WorldLevelScene::toggleDebug() {
}

void WorldLevelScene::onLayerAdded(BaseLayer* layer, LayerDef* layerDef) {
  cocos2d::log("!!!!!!!!!!!!!!!!!!!!!!!!!!! ON LAYER ADDED: %f", m_gravityAngle);
  // TODO: Inspect, probably not respecting isMain
  if (layerDef->getType() == LAYER_TYPE_WORLD) {
    m_worldLevelLayer = static_cast<WorldLevelLayer*>(layer);
    m_unitsInScene = m_worldLevelLayer->getUnitCount();
    m_worldLevelLayers.push_back(m_worldLevelLayer);
    m_worldLevelLayer->enableDebugDraw(m_debug);
    float xGravity = cos(m_gravityAngle) * 6;
    float yGravity = sin(m_gravityAngle) * 6;
    m_worldLevelLayer->getWorld()->SetGravity(b2Vec2(xGravity, yGravity));
    updateGravityValues();

    m_worldLevelLayer->setWorldLevelScene(this);
  }
}

void WorldLevelScene::setGravityAngle(float angle) {
  cocos2d::log("!!!!!!!!!!!!!!!!!!!!!!!!!!! SET GRAVITY ANGLE: %f", angle);
  m_gravityAngle = CMath::wrapPosNegPI(angle);
  float xGravity = cos(m_gravityAngle) * 6;
  float yGravity = sin(m_gravityAngle) * 6;
  if (m_gravityAngleRotatesWorld) {
    m_worldLevelLayer->rotate(-m_gravityAngle - M_PI_2,
        0.5f,
        BaseLayer::TweenEq::Bounce,
        BaseLayer::TweenEasing::Out);
  }
  for (auto worldLevelLayer : m_worldLevelLayers) {
    worldLevelLayer->getAISystem()->setGravityAngle(angle);
    worldLevelLayer->getWorld()->SetGravity(b2Vec2(xGravity, yGravity));
    for (b2Body* b = worldLevelLayer->getWorld()->GetBodyList(); b; b = b->GetNext()) {
      b->SetAwake(true);
    }
  }
  updateGravityValues();
  m_gravity = m_worldLevelLayer->getWorld()->GetGravity();
  m_gravityCos = cos(m_gravityAngle);
  m_gravitySin = sin(m_gravityAngle);
}

float WorldLevelScene::getGravityAngle() {
  return m_gravityAngle;
}

b2Vec2 WorldLevelScene::getGravity() {
  return m_gravity;
}

float WorldLevelScene::getGravityCos() {
  return m_gravityCos;
}

float WorldLevelScene::getGravitySin() {
  return m_gravitySin;
}

b2Vec2 WorldLevelScene::getRightNormal() {
  return m_rightNormal;
}

b2Vec2 WorldLevelScene::getLeftNormal() {
  return m_leftNormal;
}

void WorldLevelScene::selectCtrl(int ctrl, Entity* entity) {
  m_ctrl = ctrl;
  if (m_ctrl == CTRL_GRAVITRON) {
    m_gravityCtrlLayer->beginCtrlTouch(entity);
  } else if (m_ctrl == CTRL_SELECT) {
    m_selectCtrlLayer->beginCtrlTouch(entity);
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

WorldLevelLayer* WorldLevelScene::getWorldLevelLayer() {
  return m_worldLevelLayer;
}

b2Vec2 WorldLevelScene::screenToWorld(cocos2d::Point screenPos) {
  if (m_worldLevelLayer) {
    return m_worldLevelLayer->screenToWorld(screenPos);
  }
  return b2Vec2(0, 0);
}

cocos2d::Point WorldLevelScene::worldToScreen(b2Vec2 worldPos) {
  if (m_worldLevelLayer) {
    return m_worldLevelLayer->worldToScreen(worldPos);
  }
  return cocos2d::Point(0, 0);
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
    if (m_unitsSaved >= m_unitsRequired) {
      m_worldLevelStatisticsLayer->setVisible(true);
      CCLOG("LEVEL COMPLETE!!!");
    }
  }
  m_unitsInScene -= count;
  CCLOG("Unit removed from scene, total: %d", m_unitsInScene);
}

cocos2d::Vec2* WorldLevelScene::getStartTouchLocation() {
  return m_startTouchLocation;
}

cocos2d::Touch* WorldLevelScene::getStartTouch() {
  return m_startTouch;
}

void WorldLevelScene::setStartTouch(cocos2d::Touch* touch) {
  m_startTouch = touch;
  m_startTouchLocation->x = touch->getLocation().x;
  m_startTouchLocation->y = touch->getLocation().y;
}

cocos2d::Vec2* WorldLevelScene::getEndTouchLocation() {
  return m_endTouchLocation;
}

cocos2d::Touch* WorldLevelScene::getEndTouch() {
  return m_endTouch;
}

void WorldLevelScene::setEndTouch(cocos2d::Touch* touch) {
  m_endTouch = touch;
  m_endTouchLocation->x = touch->getLocation().x;
  m_endTouchLocation->y = touch->getLocation().y;
}

void WorldLevelScene::onBeginCtrl(WorldLevelCtrlLayer* ctrlLayer) {
  if (ctrlLayer->isPausingCtrl()) {
    pause(true);
  }
  if (ctrlLayer->isLockingCtrl()) {
    m_worldLevelLayer->setTouchEnabled(false);
  }
  if (ctrlLayer->isFollowingCtrl()) {
    m_worldLevelLayer->follow(ctrlLayer->getEntity()->getBody(), 0.2f);
  }
}

void WorldLevelScene::onCancelCtrl(WorldLevelCtrlLayer* ctrlLayer) {
  if (ctrlLayer->isPausingCtrl()) {
    pause(false);
  }
  if (ctrlLayer->isLockingCtrl()) {
    m_worldLevelLayer->setTouchEnabled(true);
  }
  if (ctrlLayer->isFollowingCtrl()) {
    m_worldLevelLayer->cancelFollow();
  }
}

void WorldLevelScene::onEndCtrl(WorldLevelCtrlLayer* ctrlLayer) {
  if (ctrlLayer->isPausingCtrl()) {
    pause(false);
  }
  if (ctrlLayer->isLockingCtrl()) {
    m_worldLevelLayer->setTouchEnabled(true);
  }
  if (ctrlLayer->isFollowingCtrl()) {
    m_worldLevelLayer->cancelFollow();
  }
}

SceneDef* WorldLevelScene::getSceneDef(std::string filename) {
  if (m_levelSceneDef == nullptr) {
    m_levelSceneDef = SceneFactory::getInstance()->getLevelSceneDef(filename.c_str());
  }
  return m_levelSceneDef;
}

BaseLayer* WorldLevelScene::getWorldLayer(WorldLayerDef* worldLayerDef) {
  return SceneFactory::getInstance()->getWorldLevelLayer(this, worldLayerDef);
}

void WorldLevelScene::moveCameraTo(float worldX,
                                   float worldY,
                                   float duration,
                                   BaseLayer::TweenEq eq,
                                   BaseLayer::TweenEasing easing) {
  if (m_worldLevelLayer) {
    cocos2d::Point position = m_worldLevelLayer->worldToScreen(b2Vec2(worldX, worldY));
    m_worldLevelLayer->translate(position.x,
                                 position.y,
                                 duration,
                                 eq,
                                 easing);
  }
}

void WorldLevelScene::updateGravityValues() {
  m_gravity = m_worldLevelLayer->getWorld()->GetGravity();
  m_gravityCos = cos(m_gravityAngle);
  m_gravitySin = sin(m_gravityAngle);
  m_rightNormal.x = cos(m_gravityAngle + M_PI_2);
  m_rightNormal.y = sin(m_gravityAngle + M_PI_2);
  m_leftNormal.x = cos(m_gravityAngle - M_PI_2);
  m_leftNormal.y = sin(m_gravityAngle - M_PI_2);
}
