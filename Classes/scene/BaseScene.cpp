#include <math.h>
#include "BaseScene.h"
#include "../factory/SceneFactory.h"

BaseScene::BaseScene() {
}

BaseScene::~BaseScene() {
}

bool BaseScene::init(std::string filename) {
  // Get the scene definition.
  std::string sceneFactoryError;
  m_sceneDef = getSceneDef();
  SceneFactory::getInstance()->buildSceneDef(m_sceneDef, filename.c_str(), sceneFactoryError);
  if (!sceneFactoryError.empty()) {
    CCLOG("SceneFactory error %s", sceneFactoryError.c_str());
    // TODO: clean
    return false;
  }

  // Add layers
  for (auto layerDef : m_sceneDef->getLayerDefs()) {
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
  return true;
}

SceneDef* BaseScene::getSceneDef() {
  // Pure virtual
  return nullptr;
}
