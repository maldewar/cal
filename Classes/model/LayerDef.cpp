#include "LayerDef.h"

LayerDef::LayerDef() {
  m_id      = "";
  m_isMain  = false;
  m_index   = 0;
  m_width   = 0;
  m_height  = 0;
  m_depth   = 1;
  m_alpha   = 1;
  m_enabled = true;
  m_translationEnabled = true;
  m_rotationEnabled    = false;
  m_scaleEnabled       = false;
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

float LayerDef::getDepth() {
  return m_depth;
}

void LayerDef::setDepth(float depth) {
  m_depth = depth;
}

float LayerDef::getAlpha() {
  return m_alpha;
}

void LayerDef::setAlpha(float alpha) {
  m_alpha = alpha;
}

bool LayerDef::isEnabled() {
  return m_enabled;
}

void LayerDef::setIsEnabled(bool enabled) {
  m_enabled = enabled;
}

bool LayerDef::isTranslationEnabled() {
  return m_translationEnabled;
}

void LayerDef::setIsTranslationEnabled(bool isTranslationEnabled) {
  m_translationEnabled = isTranslationEnabled;
}

bool LayerDef::isRotationEnabled() { 
  return m_rotationEnabled;
}

void LayerDef::setIsRotationEnabled(bool isRotationEnabled) { 
  m_rotationEnabled = isRotationEnabled;
}

bool LayerDef::isScaleEnabled() { 
  return m_scaleEnabled;
}

void LayerDef::setIsScaleEnabled(bool isScaleEnabled) { 
  m_scaleEnabled = isScaleEnabled;
}
