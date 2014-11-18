#include "BackgroundLayer.h"

USING_NS_CC;

BackgroundLayer::BackgroundLayer() : BaseLayer() {
}

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
  /*
  initWithColor(Color4B(255,29,0,255), Color4B(250,255,5,255));
  changeWidthAndHeight(1920, 1080);
  */
  return true;
}

bool BackgroundLayer::translate(float x, float y, float transitionTime) {
  return true;
}

bool BackgroundLayer::scale(float factor, float transitionTime) {
  return true;
}

bool BackgroundLayer::rotate(float angle, float transitionTime) {
  return true;
}
