#ifndef __LEVEL_MENU_LAYER__
#define __LEVEL_MENU_LAYER__

#include <vector>
#include "BasicRUBELayer.h"
#include "cocostudio/CocoStudio.h"
#include "../model/Entity.h"

class LevelMenuLayer : public BasicRUBELayer
{
protected:
  std::string m_filename;
  int m_act;

public:
  LevelMenuLayer();
  static LevelMenuLayer* create(int act, std::string filename);
  virtual bool init(int act, std::string filename);
  virtual std::string getFilename();
  virtual cocos2d::Point initialWorldOffset();
  virtual float initialWorldScale();
  virtual void afterLoadProcessing(b2dJson* json);
  void removeBodyFromWorld(b2Body* body);
  virtual void onBodyTouched(b2Body* body, b2Fixture* fixture);

};

#endif /* __LEVEL_MENU_LAYER__ */
