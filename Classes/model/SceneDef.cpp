#include "SceneDef.h"

SceneDef::SceneDef() {
  m_id = "";
  m_title = "";
  m_translateEnabled = true;
  m_rotateEnabled    = true;
  m_scaleEnabled     = true;
  m_cameraX          = 0;
  m_cameraY          = 0;
  m_cameraZoom       = 1;
}

SceneDef::~SceneDef() {
  for (auto layerDef : m_layerDefs) {
    delete layerDef;
  }
}

std::string SceneDef::getId() {
  return m_id;
}

void SceneDef::setId(std::string id) {
  m_id = id;
}

std::string SceneDef::getTitle() {
  return m_title;
}

void SceneDef::setTitle(std::string title) {
  m_title = title;
}

std::vector<LayerDef*> SceneDef::getLayerDefs() {
  return m_layerDefs;
}

void SceneDef::addLayerDef(LayerDef* layerDef) {
  m_layerDefs.push_back(layerDef);
}

bool SceneDef::isTranslateEnabled() {
  return m_translateEnabled;
}

void SceneDef::setTranslateEnabled(bool isTranslateEnabled) {
  m_translateEnabled = isTranslateEnabled;
}

bool SceneDef::isRotateEnabled() {
  return m_rotateEnabled;
}
 
void SceneDef::setRotateEnabled(bool isRotateEnabled) {
  m_rotateEnabled = isRotateEnabled;
}

bool SceneDef::isScaleEnabled() {
  return m_scaleEnabled;
}
 
void SceneDef::setScaleEnabled(bool isScaleEnabled) {
  m_scaleEnabled = isScaleEnabled;
}

float SceneDef::getCameraX() {
  return m_cameraX;
}

void SceneDef::setCameraX(float cameraX) {
  m_cameraX = cameraX;
}

float SceneDef::getCameraY() {
  return m_cameraY;
}

void SceneDef::setCameraY(float cameraY) {
  m_cameraY = cameraY;
}

float SceneDef::getCameraZoom() {
  return m_cameraZoom;
}

void SceneDef::setCameraZoom(float cameraZoom) {
  m_cameraZoom = cameraZoom;
}
