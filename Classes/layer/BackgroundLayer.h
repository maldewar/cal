#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"

class BackgroundLayer : public cocos2d::LayerGradient
{
private:
  cocos2d::Size m_visibleSize;
  cocos2d::Size m_winSize;

public:
  static BackgroundLayer* create(int bgType);
  virtual bool init(int bgType);

};

#endif // __BACKGROUND_LAYER_H__
