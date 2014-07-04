#include "BackgroundLayer.h"

USING_NS_CC;

bool BackgroundLayer::init()
{
  CCLOG("CALLING BACKGROUNDLAYER::INIT");
  initWithColor(Color4B(255,29,0,255), Color4B(250,255,5,255));
  changeWidthAndHeight(1920, 1080);
  return true;
}
