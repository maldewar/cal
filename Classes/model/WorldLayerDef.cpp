#include "WorldLayerDef.h"

WorldLayerDef::WorldLayerDef() : LayerDef() {
  m_isMain = false;
}

WorldLayerDef::~WorldLayerDef() {
}

WorldLayerDef* WorldLayerDef::create()
{
  WorldLayerDef *worldLayerDef = new (std::nothrow) WorldLayerDef();
  if (worldLayerDef && worldLayerDef->init())
  {
    return worldLayerDef;
  }
  return nullptr;
}

bool WorldLayerDef::init()
{
  return true;
}

int WorldLayerDef::getType() {
  return LAYER_TYPE_WORLD;
}

std::string WorldLayerDef::getPath() {
  return m_path;
}

void WorldLayerDef::setPath(std::string path) {
  m_path = path;
}
