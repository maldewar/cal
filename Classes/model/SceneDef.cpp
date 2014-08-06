#include "SceneDef.h"

SceneDef::SceneDef() {
  m_id = "";
  m_title = "";
  m_unitsRequired = 0;
}

SceneDef::~SceneDef() {
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

int SceneDef::getUnitsRequired() {
  return m_unitsRequired;
}

void SceneDef::setUnitsRequired(int unitsRequired) {
  m_unitsRequired = unitsRequired;
}

std::vector<LayerDef*> SceneDef::getLayerDefs() {
  return m_layerDefs;
}

void SceneDef::addLayerDef(LayerDef* layerDef) {
  m_layerDefs.push_back(layerDef);
}
