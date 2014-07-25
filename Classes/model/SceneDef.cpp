#include "SceneDef.h"

SceneDef::SceneDef() {
  m_id = "";
  m_title = "";
}

SceneDef::~SceneDef() {
}

SceneDef* SceneDef::create()
{
  SceneDef *sceneDef = new (std::nothrow) SceneDef();
  if (sceneDef && sceneDef->init())
  {
    return sceneDef;
  }
  return nullptr;
}

bool SceneDef::init()
{
  /**
  m_armature = cocostudio::Armature::create("sceneDef");
  if (m_armature) {
    addChild(m_armature);
    setScale(PX_TO_M);
    setIsSensor(true);
    scheduleUpdate();
    return true;
  }
  */
  return false;
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
