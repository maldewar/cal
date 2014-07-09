#ifndef __WORLD_LEVEL_SCENE__
#define __WORLD_LEVEL_SCENE__

#include <vector>
#include <string>
#include "cocos2d.h"
#include "../layer/BackgroundLayer.h"
#include "../layer/WorldLevelLayer.h"
#include "../layer/WorldLevelUILayer.h"
#include "../layer/WorldLevelDebugLayer.h"
class WorldLevelLayer;
class WorldLevelUILayer;
class WorldLevelDebugLayer;

class WorldLevelScene : public cocos2d::Scene
{
protected:
  std::vector<WorldLevelLayer*> m_worldLevelLayers;
  WorldLevelUILayer* m_worldLevelUILayer;
  WorldLevelDebugLayer* m_worldLevelDebugLayer;
  bool m_paused;
  bool m_debug;
  float m_gravityAngle;

public:
  WorldLevelScene(void);
  virtual ~WorldLevelScene(void);
  static WorldLevelScene* create(std::string filename);
  virtual bool init(void);
  virtual void pause(bool pause);
  virtual void togglePause();
  virtual void toggleDebug();
  virtual void addWorldLevelLayer(WorldLevelLayer* worldLevelLayer);
  virtual void pauseChildrenRecursive(cocos2d::Node* node, bool pause);
  virtual void setGravityAngle(float angle);
  virtual bool isDebugEnable();
  virtual void enableDebug(bool debug);
};

#endif /* __WORLD_LEVEL_SCENE__ */
