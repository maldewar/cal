#ifndef __BASE_SCENE__
#define __BASE_SCENE__

#include <string>
#include <vector>
#include "cocos2d.h"
#include "../layer/BaseLayer.h"
#include "../model/SceneDef.h"
#include "../model/WorldLayerDef.h"

class BaseScene : public cocos2d::Scene
{
protected:
  SceneDef *m_sceneDef;
  std::vector<BaseLayer*> m_layers;
  int m_topIndex;
  int m_bottomIndex;

public:
  BaseScene(void);
  virtual bool init(std::string filename);
  int getTopLayerIndex();
  int getBottomLayerIndex();

protected:
  virtual void onLayerAdded(BaseLayer* layer, LayerDef* layerDef);
  virtual SceneDef* getSceneDef(std::string filename) = 0;
  virtual BaseLayer* getWorldLayer(WorldLayerDef* worldLayerDef) = 0;
};

#endif /* __BASE_SCENE__ */
