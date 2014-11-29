#include "LayerDef.h"

LayerDef::LayerDef() {
  m_id      = "";
  m_isMain  = false;
  m_index   = 0;
  m_width   = 0;
  m_height  = 0;
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

bool LayerDef::isMain() {
    return m_isMain;
}

void LayerDef::setIsMain(bool isMain) {
    m_isMain = isMain;
}

int LayerDef::getIndex() {
  return m_index;
}

void LayerDef::setIndex(int index) {
  m_index = index;
}

float LayerDef::getWidth() {
  return m_width;
}

void LayerDef::setWidth(float width) {
  m_width = width;
}

float LayerDef::getHeight() {
  return m_height;
}

void LayerDef::setHeight(float height) {
  m_height = height;
}

bool LayerDef::isEnabled() {
  return m_enabled;
}

void LayerDef::setIsEnabled(bool enabled) {
  m_enabled = enabled;
}
