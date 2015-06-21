#ifndef __WORLD_LEVEL_LAYER__
#define __WORLD_LEVEL_LAYER__

#include <vector>
#include <map>
#include "BasicRUBELayer.h"
#include "cocostudio/CocoStudio.h"
#include "../scene/WorldLevelScene.h"
#include "../model/Entity.h"
#include "../model/WorldLayerDef.h"
#include "../engine/RayCastTool.h"
#include "../system/ContactSystem.h"
#include "../system/AISystem.h"

class Branch;
class WorldLevelScene;
class RayCastTool;
class AISystem;

class WorldLevelLayer : public BasicRUBELayer
{
protected:
  std::vector<Entity*> m_deletedEntities;
  int m_unitCount;
  WorldLevelScene* m_worldScene;
  cocos2d::Layer* m_unitLayer;
  cocos2d::Layer* m_areaLayer;
  cocos2d::Layer* m_assetLayer;
  RayCastTool* m_rayCastTool;
  bool m_controlGrabbed;
  Entity* m_touchedEntity;
  WorldLevelScene* m_parent;
  ContactSystem* m_contactSystem;
  AISystem* m_AISystem;
  std::map<std::string, Branch*> m_branches;
  std::map<std::string, Entity*> m_touchListeners;

public:
  WorldLevelLayer ();
  static WorldLevelLayer* create (WorldLevelScene* parent,
                                  WorldLayerDef* worldLayerDef);
  virtual bool init (WorldLevelScene* parent,
                     WorldLayerDef* worldLayerDef);
  virtual int getUnitCount ();
  virtual void removeUnit(int count, bool isLost);
  virtual void addUnit(int count);
  virtual void afterLoadProcessing (b2dJson* json);
  virtual void addChild (cocos2d::Node* node) override;
  virtual void removeChild (cocos2d::Node* node, bool cleanup = true) override;
  virtual void setWorldLevelScene (WorldLevelScene* worldScene);
  virtual WorldLevelScene* getWorldLevelScene ();
  virtual void setParentScene(BaseScene* parent);
  virtual void clear();
  virtual void update(float dt);
  void removeBodyFromWorld(b2Body* body);
  virtual void onBodyTouchBegan(std::vector<b2Body*> bodies, std::vector<b2Fixture*> fixtures);
  virtual void onBodyTouchEnded();
  virtual void onWorldTouchBegan(b2Vec2& position);
  virtual AISystem* getAISystem();

  virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches,
                              cocos2d::Event *unused_event);
  virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches,
                                      cocos2d::Event *unused_event);
  virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches,
                              cocos2d::Event *unused_event);

  virtual bool addTouchListener(Entity* entity);
  virtual bool removeTouchListener(Entity* entity);
  /**
   * Gets the index of the body touched based on the
   * z touch index of a list of bodies.
   * @param bodies List of bodies.
   * @return int Index of the touched body.
   */
  int getTouchedBody(std::vector<b2Body*> bodies);

protected:
  virtual void onDraw(const cocos2d::Mat4 &transform, uint32_t flags) override;
  virtual void setDataOnFixtures(b2dJson* json, b2Body* body, Entity* parent);

};

#endif /* __WORLD_LEVEL_LAYER__ */
