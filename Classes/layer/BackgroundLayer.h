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

  bool translate(float x, float y, float transitionTime = 0);
  bool scale(float factor, float transitionTime = 0);
  bool rotate(float angle, float transitionTime = 0);

};

#endif // __BACKGROUND_LAYER_H__
