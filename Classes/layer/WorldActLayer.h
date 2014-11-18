#ifndef __WORLD_ACT_LAYER__
#define __WORLD_ACT_LAYER__

#include <vector>
#include "BasicRUBELayer.h"
#include "cocostudio/CocoStudio.h"
#include "../model/Entity.h"

class WorldActLayer : public BasicRUBELayer
{
protected:
  std::string m_filename;
  int m_act;

public:
  WorldActLayer();
  static WorldActLayer* create(int act, std::string filename);
  virtual bool init(int act, std::string filename);
  virtual std::string getFilename();
  virtual cocos2d::Point initialWorldOffset();
  virtual float initialWorldScale();
  virtual void afterLoadProcessing(b2dJson* json);
  void removeBodyFromWorld(b2Body* body);
  virtual void onBodyTouchBegan(b2Body* body, b2Fixture* fixture);
  virtual void onWorldTouchBegan(b2Vec2& position);

};

#endif /* __WORLD_ACT_LAYER__ */
