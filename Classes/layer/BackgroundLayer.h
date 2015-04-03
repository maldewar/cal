#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"
#include "BaseLayer.h"
#include "2d/CCLayer.h"
#include "../model/BgLayerDef.h"

class BackgroundLayer : public BaseLayer
{
protected:
  cocos2d::Color4B m_color; // TODO: look for existing parsers.
  bool m_imgStretch;
  float m_imgAlpha;

private:
  cocos2d::LayerColor* m_layerColor;
  cocos2d::Sprite* m_imgLayer;

public:
  BackgroundLayer();
  static BackgroundLayer* create(BgLayerDef *bgLayerDef);
  virtual bool init(BgLayerDef *bgLayerDef);

};

#endif // __BACKGROUND_LAYER_H__
