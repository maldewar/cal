#ifndef __WORLD_LEVEL_SCENE__
#define __WORLD_LEVEL_SCENE__

#include <vector>
#include <string>
#include "cocos2d.h"
#include "../layer/BackgroundLayer.h"
#include "../layer/WorldLevelLayer.h"
#include "../layer/GravityCtrlLayer.h"
#include "../layer/WorldLevelUILayer.h"
#include "../layer/WorldLevelDebugLayer.h"
#include "../layer/WorldLevelStatisticsLayer.h"
#include "../model/Entity.h"
#include "../model/SceneDef.h"
class WorldLevelLayer;
class WorldLevelUILayer;
class GravityCtrlLayer;
class WorldLevelStatisticsLayer;
class WorldLevelDebugLayer;
class Entity;
class SceneDef;

const int CTRL_NONE      = 0;
const int CTRL_GRAVITRON = 1;
const int CTRL_SELECT    = 2;

class WorldLevelScene : public cocos2d::Scene
{
protected:
  std::vector<WorldLevelLayer*> m_worldLevelLayers;
  WorldLevelLayer* m_worldLevelLayer;
  WorldLevelUILayer* m_worldLevelUILayer;
  GravityCtrlLayer* m_gravityCtrlLayer;
  WorldLevelStatisticsLayer* m_worldLevelStatisticsLayer;
  WorldLevelDebugLayer* m_worldLevelDebugLayer;
  SceneDef* m_sceneDef;
  bool m_paused;
  bool m_debug;
  float m_gravityAngle;
  bool m_gravityAngleRotatesWorld;
  int m_ctrl;

  int m_unitsInScene;
  int m_unitsSaved;
  int m_unitsLost;
  int m_unitsRequired;

public:
  WorldLevelScene(void);
  static WorldLevelScene* create(int act, int level);
  static WorldLevelScene* create(std::string filename);
  virtual bool init(std::string filename);
  virtual void pause(bool pause);
  virtual void togglePause();
  virtual void toggleDebug();
  virtual void addWorldLevelLayer(WorldLevelLayer* worldLevelLayer, int index);
  virtual void setGravityAngle(float angle);
  virtual float getGravityAngle();
  virtual bool gravityAngleRotatesWorld();
  virtual void selectCtrl(int ctrl, Entity* entity);
  virtual bool isDebugEnable();
  virtual void enableDebug(bool debug);
  virtual void onExit() override;
  virtual WorldLevelLayer* getWorldLevelLayer();

  virtual void onBeginCtrl(WorldLevelCtrlLayer* ctrlLayer);
  virtual void onCancelCtrl(WorldLevelCtrlLayer* ctrlLayer);
  virtual void onEndCtrl(WorldLevelCtrlLayer* ctrlLayer);

  void addUnit(int count);
  void removeUnit(int count, bool isLost = true);
};

#endif /* __WORLD_LEVEL_SCENE__ */
