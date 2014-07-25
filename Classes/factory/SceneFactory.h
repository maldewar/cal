#ifndef __SCENE_FACTORY__
#define __SCENE_FACTORY__

#include <string>
#include "Box2D/Box2D.h"

#include "cocos2d.h"
#include "../util/json/json.h"
#include "../model/SceneDef.h"
#include "../model/LayerDef.h"
#include "../model/BgLayerDef.h"
#include "../model/WorldLayerDef.h"
#include "../layer/BackgroundLayer.h"
#include "../layer/WorldLevelLayer.h"

class SceneFactory : public cocos2d::Ref
{
public:
  static SceneFactory* getInstance();
  static void destroyInstance();

private:
  SceneFactory(void);
  ~SceneFactory(void);

public:
  virtual bool init();
  virtual SceneDef* getSceneDef(const char* filename, std::string& errorMsg);
  virtual LayerDef* buildLayerDef(Json::Value jValue);
  virtual WorldLevelLayer* buildWorldLevelLayer(WorldLayerDef* worldLayerDef);
  virtual BackgroundLayer* buildBackgroundLayer(BgLayerDef* bgLayerDef);

private:
  virtual void buildBaseLayerDef(LayerDef* layerDef, Json::Value jValue);

};

#endif
