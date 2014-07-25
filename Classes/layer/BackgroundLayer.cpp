#include "BackgroundLayer.h"

USING_NS_CC;

BackgroundLayer* BackgroundLayer::create(int bgLayer) {
  BackgroundLayer* backgroundLayer = new (std::nothrow) BackgroundLayer();
  if (backgroundLayer && backgroundLayer->init(bgLayer)) {
    backgroundLayer->autorelease();
    return backgroundLayer;
  }
  CC_SAFE_DELETE(backgroundLayer);
  return nullptr;
}

bool BackgroundLayer::init(int bgType)
{
  initWithColor(Color4B(255,29,0,255), Color4B(250,255,5,255));
  changeWidthAndHeight(1920, 1080);
  return true;
}
