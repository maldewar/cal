#include "BgLayerDef.h"

BgLayerDef::BgLayerDef() : LayerDef() {
  m_bgType     = 0;
  m_imgStretch = false;
  m_imgAlpha   = 1;
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

std::string BgLayerDef::getColor() {
  return m_color;
}

void BgLayerDef::setColor(std::string color) {
  m_color = color;
}

std::string BgLayerDef::getImgPath() {
  return m_imgPath;
}

void BgLayerDef::setImgPath(std::string path) {
  m_imgPath = path;
}

bool BgLayerDef::isImgStretch() {
  return m_imgStretch;
}

void BgLayerDef::setIsImgStretch(bool isImgStretch) {
  m_imgStretch = isImgStretch;
}

float BgLayerDef::getImgAlpha() {
  return m_imgAlpha;
}

void BgLayerDef::setImgAlpha(float imgAlpha) {
  m_imgAlpha = imgAlpha;
}
