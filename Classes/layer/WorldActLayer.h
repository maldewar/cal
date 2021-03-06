#ifndef __WORLD_ACT_LAYER__
#define __WORLD_ACT_LAYER__

#include "BasicRUBELayer.h"
#include "cocostudio/CocoStudio.h"
#include "../model/Entity.h"
#include "../model/WorldLayerDef.h"

class WorldActLayer : public BasicRUBELayer
{
protected:
  int m_act;

public:
  WorldActLayer();
  static WorldActLayer* create (int act, WorldLayerDef* worldLayerDef);
  virtual bool init (int act, WorldLayerDef* worldLayerDef);
  virtual void afterLoadProcessing (b2dJson* json);
  void removeBodyFromWorld (b2Body* body);
  virtual void onBodyTouchBegan (std::vector<b2Body*> bodies, std::vector<b2Fixture*> fixtures);
  virtual void onWorldTouchBegan (b2Vec2& position);

};

#endif /* __WORLD_ACT_LAYER__ */
