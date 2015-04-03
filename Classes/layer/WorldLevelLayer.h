#ifndef __WORLD_LEVEL_LAYER__
#define __WORLD_LEVEL_LAYER__

#include <vector>
#include "BasicRUBELayer.h"
#include "cocostudio/CocoStudio.h"
#include "../scene/WorldLevelScene.h"
#include "../model/Entity.h"
#include "../model/WorldLayerDef.h"
#include "../engine/RayCastTool.h"
#include "../system/ContactSystem.h"
#include "../system/AISystem.h"

class WorldLevelScene;
class RayCastTool;

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
  WorldLevelScene* m_parent;
  ContactSystem* m_contactSystem;
  AISystem* m_AISystem;

public:
  WorldLevelLayer ();
  static WorldLevelLayer* create (WorldLevelScene* parent,
                                  WorldLayerDef* worldLayerDef);
  virtual bool init (WorldLevelScene* parent,
                     WorldLayerDef* worldLayerDef);
  virtual int getUnitCount ();
  virtual void afterLoadProcessing (b2dJson* json);
  virtual void addChild (cocos2d::Node* node) override;
  virtual void removeChild (cocos2d::Node* node, bool cleanup = true) override;
  virtual void setWorldLevelScene (WorldLevelScene* worldScene);
  virtual WorldLevelScene* getWorldLevelScene ();
  virtual void setParentScene(BaseScene* parent);
  virtual void clear ();
  virtual void update (float dt);
  void removeBodyFromWorld (b2Body* body);
  virtual void onBodyTouchBegan (b2Body* body, b2Fixture* fixture);
  virtual void onWorldTouchBegan(b2Vec2& position);
  virtual AISystem* getAISystem();

protected:
  virtual void onDraw(const cocos2d::Mat4 &transform, uint32_t flags) override;

};

#endif /* __WORLD_LEVEL_LAYER__ */
