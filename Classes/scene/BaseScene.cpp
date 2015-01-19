#include <math.h>
#include "BaseScene.h"
#include "../factory/SceneFactory.h"

BaseScene::BaseScene() : cocos2d::Scene() {
  m_sceneDef    = nullptr;
  m_mainLayer   = nullptr;
  m_topIndex    = 0;
  m_bottomIndex = 0;
  m_translationKeysEnabled = true;
  m_rotationKeysEnabled    = true;
  m_scalingKeysEnabled     = true;
  m_rightKey    = false;
  m_leftKey     = false;
  m_upKey       = false;
  m_downKey     = false;
  m_zoomInKey   = false;
  m_zoomOutKey  = false;
  m_rotateCWKey    = false;
  m_rotateCCWKey   = false;
  m_translationStep = 10.0f;
  m_scalingStep     = 0.01f;
  m_rotationStep    = 0.01f;
  m_translationFactor = 0;
  m_scalingFactor     = 0;
  m_rotatingFactor    = 0;
}

bool BaseScene::init(std::string filename) {
  // Binding Keys
  auto keyboardListener = cocos2d::EventListenerKeyboard::create();
  keyboardListener->onKeyPressed = CC_CALLBACK_2(BaseScene::onKeyPressed, this);
  keyboardListener->onKeyReleased = CC_CALLBACK_2(BaseScene::onKeyReleased, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

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
      if (layerDef->isMain()) {
        baseLayer->setIsMain(true);
        m_mainLayer = baseLayer;
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
  scheduleUpdate();
  return true;
}

void BaseScene::update(float dt) {
  cocos2d::Scene::update(dt);
  if (m_leftKey || m_rightKey || m_upKey || m_downKey) {
    if (m_mainLayer) {
      float dX = 0;
      float dY = 0;
      if (m_leftKey)
        dX -= m_translationStep;
      if (m_rightKey)
        dX += m_translationStep;
      if (m_upKey)
        dY += m_translationStep;
      if (m_downKey)
        dY -= m_translationStep;
      if (m_translationFactor < 1) {
        m_translationFactor += 0.01f;
        m_mainLayer->translateStep(dX * m_translationFactor,
                                   dY * m_translationFactor);
      } else {
        m_mainLayer->translateStep(dX, dY);
      }
    }
  }
  if (m_zoomInKey || m_zoomOutKey) {
    if (m_mainLayer) {
      float m_scaleDelta = 0;
      if (m_zoomInKey)
        m_scaleDelta += m_scalingStep;
      if (m_zoomOutKey)
        m_scaleDelta -= m_scalingStep;
      if (m_scalingFactor < 1) {
        m_scalingFactor += 0.01f;
        m_mainLayer->scaleStep(m_scaleDelta * m_scalingFactor);
      } else {
        m_mainLayer->scaleStep(m_scaleDelta);
      }
    }
  }
  if (m_rotateCWKey || m_rotateCCWKey) {
    if (m_mainLayer) {
      float m_angleDelta = 0;
      if (m_rotateCWKey)
        m_angleDelta += m_rotationStep;
      if (m_rotateCCWKey)
        m_angleDelta -= m_rotationStep;
      if (m_rotatingFactor < 1) {
        m_rotatingFactor += 0.01f;
        m_mainLayer->rotateStep(m_angleDelta * m_rotatingFactor);
      } else {
        m_mainLayer->rotateStep(m_angleDelta);
      }
    }
  }
}

int BaseScene::getTopLayerIndex() {
  return m_topIndex;
}

int BaseScene::getBottomLayerIndex() {
  return m_bottomIndex;
}

void BaseScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
  CCLOG("Key with keycode %d pressed", keyCode);
  if (m_translationKeysEnabled) {
    switch(keyCode) {
      case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
      case cocos2d::EventKeyboard::KeyCode::KEY_KP_RIGHT:
        m_rightKey = true; return;
        break;
      case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
      case cocos2d::EventKeyboard::KeyCode::KEY_KP_LEFT:
        m_leftKey = true; return;
        break;
      case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
      case cocos2d::EventKeyboard::KeyCode::KEY_KP_UP:
        m_upKey = true; return;
        break;
      case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
      case cocos2d::EventKeyboard::KeyCode::KEY_KP_DOWN:
        m_downKey = true; return;
        break;
    }
  }
  if (m_scalingKeysEnabled) {
    switch(keyCode) {
      case cocos2d::EventKeyboard::KeyCode::KEY_PLUS:
      case cocos2d::EventKeyboard::KeyCode::KEY_KP_PLUS:
        m_zoomInKey = true; return;
        break;
      case cocos2d::EventKeyboard::KeyCode::KEY_MINUS:
      case cocos2d::EventKeyboard::KeyCode::KEY_KP_MINUS:
        m_zoomOutKey = true; return;
        break;
    }
  }
  if (m_rotationKeysEnabled) {
    switch(keyCode) {
      case cocos2d::EventKeyboard::KeyCode::KEY_1:
        m_rotateCCWKey = true; return;
        break;
      case cocos2d::EventKeyboard::KeyCode::KEY_2:
        m_rotateCWKey = true; return;
        break;
    }
  }
}

void BaseScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
  CCLOG("Key with keycode %d released", keyCode);
  if (m_translationKeysEnabled) {
    switch(keyCode) {
      case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
      case cocos2d::EventKeyboard::KeyCode::KEY_KP_RIGHT:
        if (!m_upKey && !m_downKey)
          m_translationFactor = 0;
        m_rightKey = false; return;
        break;
      case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
      case cocos2d::EventKeyboard::KeyCode::KEY_KP_LEFT:
        if (!m_upKey && !m_downKey)
          m_translationFactor = 0;
        m_leftKey = false; return;
        break;
      case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
      case cocos2d::EventKeyboard::KeyCode::KEY_KP_UP:
        if (!m_rightKey && !m_leftKey)
          m_translationFactor = 0;
        m_upKey = false; return;
        break;
      case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
      case cocos2d::EventKeyboard::KeyCode::KEY_KP_DOWN:
        if (!m_rightKey && !m_leftKey)
          m_translationFactor = 0;
        m_downKey = false; return;
        break;
    }
  }
  if (m_scalingKeysEnabled) {
    switch(keyCode) {
      case cocos2d::EventKeyboard::KeyCode::KEY_PLUS:
      case cocos2d::EventKeyboard::KeyCode::KEY_KP_PLUS:
        m_scalingFactor = 0;
        m_zoomInKey = false; return;
        break;
      case cocos2d::EventKeyboard::KeyCode::KEY_MINUS:
      case cocos2d::EventKeyboard::KeyCode::KEY_KP_MINUS:
        m_scalingFactor = 0;
        m_zoomOutKey = false; return;
        break;
    }
  }
  if (m_rotationKeysEnabled) {
    switch(keyCode) {
      case cocos2d::EventKeyboard::KeyCode::KEY_1:
        m_rotatingFactor = 0;
        m_rotateCCWKey = false; return;
        break;
      case cocos2d::EventKeyboard::KeyCode::KEY_2:
        m_rotatingFactor = 0;
        m_rotateCWKey = false; return;
        break;
    }
  }
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
