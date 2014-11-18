#ifndef __WORLD_LEVEL_SCENE__
#define __WORLD_LEVEL_SCENE__

#include <vector>
#include <string>
#include "cocos2d.h"
#include "BaseScene.h"
#include "../layer/BackgroundLayer.h"
#include "../layer/WorldLevelLayer.h"
#include "../layer/GravityCtrlLayer.h"
#include "../layer/SelectCtrlLayer.h"
#include "../layer/WorldLevelUILayer.h"
#include "../layer/WorldLevelDebugLayer.h"
#include "../layer/WorldLevelStatisticsLayer.h"
#include "../model/Entity.h"
#include "../model/LevelSceneDef.h"
class WorldLevelLayer;
class WorldLevelUILayer;
class GravityCtrlLayer;
class SelectCtrlLayer;
class WorldLevelStatisticsLayer;
class WorldLevelDebugLayer;
class Entity;
class SceneDef;

const int CTRL_NONE      = 0;
const int CTRL_GRAVITRON = 1;
const int CTRL_SELECT    = 2;

class WorldLevelScene : public BaseScene
{
protected:
  std::vector<WorldLevelLayer*> m_worldLevelLayers;
  WorldLevelLayer* m_worldLevelLayer;
  WorldLevelUILayer* m_worldLevelUILayer;
  GravityCtrlLayer* m_gravityCtrlLayer;
  SelectCtrlLayer* m_selectCtrlLayer;
  WorldLevelStatisticsLayer* m_worldLevelStatisticsLayer;
  WorldLevelDebugLayer* m_worldLevelDebugLayer;
  LevelSceneDef* m_levelSceneDef;
  bool m_paused;
  bool m_debug;
  float m_gravityAngle;
  static b2Vec2 m_gravity;
  bool m_gravityAngleRotatesWorld;
  int m_ctrl;

  int m_unitsInScene;
  int m_unitsSaved;
  int m_unitsLost;
  int m_unitsRequired;
  cocos2d::Touch* m_touch;

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
  static b2Vec2 getGravity();
  virtual bool gravityAngleRotatesWorld();
  virtual void selectCtrl(int ctrl, Entity* entity);
  virtual bool isDebugEnable();
  virtual void enableDebug(bool debug);
  virtual void onExit() override;
  virtual WorldLevelLayer* getWorldLevelLayer();
  // Converts a position in screen pixels to a location in the physics world.
  virtual b2Vec2 screenToWorld(cocos2d::Point screenPos);
  // Converts a location in the physics world to a position in screen pixels.
  virtual cocos2d::Point worldToScreen(b2Vec2 worldPos);

  virtual void onBeginCtrl(WorldLevelCtrlLayer* ctrlLayer);
  virtual void onCancelCtrl(WorldLevelCtrlLayer* ctrlLayer);
  virtual void onEndCtrl(WorldLevelCtrlLayer* ctrlLayer);

  void addUnit(int count);
  void removeUnit(int count, bool isLost = true);

  cocos2d::Touch* getTouch();
  void setTouch(cocos2d::Touch* touch);

  SceneDef* getSceneDef(std::string filename);
  BaseLayer* getWorldLayer(WorldLayerDef* worldLayerDef);

};

#endif /* __WORLD_LEVEL_SCENE__ */
