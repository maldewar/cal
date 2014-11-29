#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"
#include "BaseLayer.h"

class BackgroundLayer : public BaseLayer
{
private:
  cocos2d::Size m_visibleSize;
  cocos2d::Size m_winSize;

public:
  BackgroundLayer();
  static BackgroundLayer* create(int bgType);
  virtual bool init(int bgType);

  bool translate(float x, float y);
  bool scale(float factor);
  bool rotate(float angle);

};

#endif // __BACKGROUND_LAYER_H__
