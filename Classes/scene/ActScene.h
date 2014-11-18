#ifndef __ACT_SCENE__
#define __ACT_SCENE__

#include <string>
#include "../scene/BaseScene.h"
#include "../layer/WorldActLayer.h"
#include "../layer/BasicUILayer.h"
#include "../model/ActSceneDef.h"
class WorldActLayer;

class ActScene : public BaseScene
{
protected:
  ActSceneDef* m_actSceneDef;
  int m_act;
  WorldActLayer* m_worldActLayer;
  BasicUILayer* m_basicUILayer;
  
  SceneDef *getSceneDef(const std::string filename);
  BaseLayer* getWorldLayer(WorldLayerDef* worldLayerDef);

public:
  ActScene(void);
  static ActScene* create(int act, std::string filename);
  virtual bool init(int act, std::string filename);
};

#endif /* __ACT_SCENE__ */
