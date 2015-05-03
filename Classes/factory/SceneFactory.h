#ifndef __SCENE_FACTORY__
#define __SCENE_FACTORY__

#include <string>
#include "Box2D/Box2D.h"

#include "cocos2d.h"
#include "../util/json/json.h"
#include "../model/ActSceneDef.h"
#include "../model/LevelSceneDef.h"
#include "../model/LayerDef.h"
#include "../model/BgLayerDef.h"
#include "../model/WorldLayerDef.h"
#include "../layer/BackgroundLayer.h"
#include "../layer/WorldLevelLayer.h"
#include "../layer/WorldActLayer.h"

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
  virtual SceneDef* getSceneDef(const char* filename);
  virtual ActSceneDef* getActSceneDef(const char* filename);
  virtual LevelSceneDef* getLevelSceneDef(const char* filename);
  virtual LayerDef* getLayerDef(Json::Value& jLayerDef);
  virtual WorldLayerDef * getWorldLayerDef(Json::Value& jLayerDef);
  virtual BgLayerDef* getBgLayerDef(Json::Value& jLayerDef);
  virtual WorldLevelLayer* getWorldLevelLayer(WorldLevelScene* parent,
                                              WorldLayerDef* worldLayerDef);
  virtual WorldActLayer* getWorldActLayer(int act,
                                          WorldLayerDef* worldLayerDef);
  virtual BackgroundLayer* getBackgroundLayer(BgLayerDef* bgLayerDef);

private:
  virtual bool buildSceneDef(SceneDef* sceneDef,
                             const char* filename);
  virtual bool buildActSceneDef(ActSceneDef* actSceneDef,
                                const char* filename);
  virtual bool buildLevelSceneDef(LevelSceneDef* levelSceneDef,
                                const char* filename);
  virtual bool buildLayerDef(LayerDef* layerDef,
                             Json::Value& jLayerDef);
  virtual bool buildWorldLayerDef(WorldLayerDef* worldLayerDef,
                                  Json::Value& jLayerDef);
  virtual bool buildBgLayerDef(BgLayerDef* bgLayerDef,
                               Json::Value& jLayerDef);
  bool readFile(const char* filename,
                std::string& errorMsg,
                Json::Value& root);

};

#endif
