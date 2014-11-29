#include <math.h>
#include "ActScene.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"
#include "../factory/SceneFactory.h"

ActScene::ActScene() : BaseScene() {
  m_actSceneDef = nullptr;
  m_act = 0;
  m_worldActLayer = nullptr;
  m_basicUILayer   = nullptr;
  m_rotationStep = 0.05f;
}

ActScene* ActScene::create(int act, std::string filename) {
  ActScene* actScene = new (std::nothrow) ActScene();
  if (actScene && actScene->init(act, filename)) {
    actScene->autorelease();
    return actScene;
  }
  CC_SAFE_DELETE(actScene);
  return nullptr;
}

bool ActScene::init(int act, std::string filename) {
  BaseScene::init(filename);
  m_act = act;
  //m_worldActLayer = WorldActLayer::create(m_act, filename);
  //m_basicUILayer = BasicUILayer::create(BasicUILayer::SceneType::Level);
  //addChild(m_worldActLayer, 0);
  //addChild(m_basicUILayer, 1);
  return true;
}

SceneDef* ActScene::getSceneDef(std::string filename) {
  if (m_actSceneDef == nullptr) {
    m_actSceneDef = SceneFactory::getInstance()->getActSceneDef(filename.c_str());
  }
  return m_actSceneDef;
}

BaseLayer* ActScene::getWorldLayer(WorldLayerDef* worldLayerDef) {
  return SceneFactory::getInstance()->getWorldActLayer(m_act, worldLayerDef);
}
