#include <math.h>
#include "BaseScene.h"
#include "../factory/SceneFactory.h"

BaseScene::BaseScene() : cocos2d::Scene() {
  m_sceneDef    = nullptr;
  m_topIndex    = 0;
  m_bottomIndex = 0;
}

bool BaseScene::init(std::string filename) {
  // Get the scene definition.
  m_sceneDef = getSceneDef(filename);
  if (m_sceneDef == nullptr)
    return false;

  // Add layers
  bool layerAdded = false;
  int layerIndex = 0;
  BaseLayer* baseLayer = nullptr;
  for (auto layerDef : m_sceneDef->getLayerDefs()) {
    layerAdded = false;
    if (layerDef->isEnabled()) {
      switch(layerDef->getType()) {
        case LAYER_TYPE_WORLD: {
          WorldLayerDef* worldLayerDef = static_cast<WorldLayerDef*>(layerDef);
          baseLayer = getWorldLayer(worldLayerDef);
          layerAdded = true;
          break;
        }
        case LAYER_TYPE_BG: {
          BgLayerDef* bgLayerDef = static_cast<BgLayerDef*>(layerDef);
          baseLayer = SceneFactory::getInstance()->getBackgroundLayer(bgLayerDef);
          layerAdded = true;
          break;
        }
      }
    }
    if (layerAdded) {
      addChild(baseLayer, layerDef->getIndex());
      layerIndex = layerDef->getIndex();
      onLayerAdded(baseLayer, layerDef);
      if (layerIndex < m_bottomIndex)
        m_bottomIndex = layerIndex;
      if (layerIndex > m_topIndex)
        m_topIndex = layerIndex;
    }
  }
  return true;
}

int BaseScene::getTopLayerIndex() {
  return m_topIndex;
}

int BaseScene::getBottomLayerIndex() {
  return m_bottomIndex;
}

void BaseScene::onLayerAdded(BaseLayer* layer, LayerDef* layerDef) {
}

SceneDef* BaseScene::getSceneDef(std::string filename) {
  // Pure virtual
  return nullptr;
}

BaseLayer* BaseScene::getWorldLayer(WorldLayerDef* worldLayerDef) {
  // Pure virtual
  return nullptr;
}
