#include "BgLayerDef.h"

BgLayerDef::BgLayerDef() : LayerDef() {
  m_bgType = 0;
}

BgLayerDef::~BgLayerDef() {
}

BgLayerDef* BgLayerDef::create()
{
  BgLayerDef *worldLayerDef = new (std::nothrow) BgLayerDef();
  if (worldLayerDef && worldLayerDef->init())
  {
    return worldLayerDef;
  }
  return nullptr;
}

bool BgLayerDef::init()
{
  return true;
}

int BgLayerDef::getType() {
  return LAYER_TYPE_BG;
}

int BgLayerDef::getBgType() {
  return m_bgType;
}

void BgLayerDef::setBgType(int bgType) {
  m_bgType = bgType;
}
