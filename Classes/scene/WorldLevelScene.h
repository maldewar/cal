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
  static float m_gravityAngle;
  static b2Vec2 m_gravity;
  static b2Vec2 m_rightNormal;
  static b2Vec2 m_leftNormal;
  static float m_gravityCos;
  static float m_gravitySin;
  bool m_gravityAngleRotatesWorld;
  int m_ctrl;

  int m_totalUnits;
  int m_totalSavedUnits;
  int m_totalLostUnits;
  int m_totalRequiredUnits;
  cocos2d::Touch* m_startTouch;
  cocos2d::Touch* m_endTouch;
  cocos2d::Vec2* m_startTouchLocation;
  cocos2d::Vec2* m_endTouchLocation;

public:
  WorldLevelScene(void);
  static WorldLevelScene* create(int act, int level);
  static WorldLevelScene* create(std::string filename);
  virtual bool init(std::string filename);
  virtual void pause(bool pause);
  virtual void togglePause();
  virtual void toggleDebug();
  virtual void onLayerAdded(BaseLayer* layer, LayerDef* layerDef);
  virtual void setGravityAngle(float angle);
  static float getGravityAngle();
  static b2Vec2 getGravity();
  static b2Vec2 getRightNormal();
  static b2Vec2 getLeftNormal();
  static float getGravityCos();
  static float getGravitySin();
  virtual bool gravityAngleRotatesWorld();
  virtual void selectCtrl(int ctrl, Entity* entity);
  virtual bool isDebugEnable();
  virtual void enableDebug(bool debug);
  virtual void onExit() override;
  virtual WorldLevelLayer* getWorldLevelLayer();
  /**
   * Converts a position in screen pixels
   * to a location in the physics world.
   * @param screenPos Position on the screen.
   * @return Position on the world.
   */
  virtual b2Vec2 screenToWorld(cocos2d::Point screenPos);
  /**
   * Converts a location in the physics world
   * to a position in screen pixelsa
   * @param worldPos Position on the world.
   * @return Position on the screen.
   */
  virtual cocos2d::Point worldToScreen(b2Vec2 worldPos);

  virtual void onBeginCtrl(WorldLevelCtrlLayer* ctrlLayer);
  virtual void onCancelCtrl(WorldLevelCtrlLayer* ctrlLayer);
  virtual void onEndCtrl(WorldLevelCtrlLayer* ctrlLayer);

  void addUnit(int count);
  void removeUnit(int count, bool isLost = true);

  cocos2d::Touch* getStartTouch();
  cocos2d::Vec2* getStartTouchLocation();
  void setStartTouch(cocos2d::Touch* touch);
  cocos2d::Touch* getEndTouch();
  cocos2d::Vec2* getEndTouchLocation();
  void setEndTouch(cocos2d::Touch* touch);

  SceneDef* getSceneDef(std::string filename);
  BaseLayer* getWorldLayer(WorldLayerDef* worldLayerDef);

  void moveCameraTo(float worldX,
    float worldY,
    float duration = 0,
    BaseLayer::TweenEq eq = BaseLayer::TweenEq::Linear,
    BaseLayer::TweenEasing easing = BaseLayer::TweenEasing::In);

private:
  void updateGravityValues();

};

#endif /* __WORLD_LEVEL_SCENE__ */
