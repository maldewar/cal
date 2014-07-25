#include "LayerDef.h"

LayerDef::LayerDef() {
  m_id = "";
  m_index = 0;
  m_distance = 0;
  m_enabled = true;
}

LayerDef::~LayerDef() {
}

LayerDef* LayerDef::create() {
  LayerDef *layerDef = new (std::nothrow) LayerDef();
  if (layerDef && layerDef->init())
  {
    return layerDef;
  }
  return nullptr;
}

bool LayerDef::init()
{
  return true;
}

std::string LayerDef::getId() {
  return m_id;
}

void LayerDef::setId(std::string id) {
  m_id = id;
}

int LayerDef::getType() {
  return 0;
}

int LayerDef::getIndex() {
  return m_index;
}

void LayerDef::setIndex(int index) {
  m_index = index;
}

float LayerDef::getDistance() {
  return m_distance;
}

void LayerDef::setDistance(float distance) {
  m_distance = distance;
}

bool LayerDef::isEnabled() {
  return m_enabled;
}

void LayerDef::setIsEnabled(bool enabled) {
  m_enabled = enabled;
}
