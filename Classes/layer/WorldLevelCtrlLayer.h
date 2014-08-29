#ifndef __WORLD_LEVEL_CTRL_LAYER_H__
#define __WORLD_LEVEL_CTRL_LAYER_H__

#include <string>
#include "UILayer.h"
//#include "../model/Entity.h"
class Entity;

class WorldLevelCtrlLayer : public UILayer
{
public:
  enum State {
    Inactive,
    Showing,
    Waiting
  };

public:
  virtual bool init(WorldLevelScene* scene);
  virtual void update(float dt);
  void beginCtrlTouch(Entity* entity);
  void endCtrlTouch();
  void cancelCtrlTouch();
  Entity* getCtrlEntity();
  virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);

  virtual void onBeginCtrlTouch();
  virtual void onCancelCtrlTouch();
  virtual void onEndCtrlTouch();

protected:
  cocos2d::ui::Layout* m_opacityLayout;
  cocos2d::Vec2* m_center;
  Entity* m_entity;
  float m_touchTime;
  float m_showingTime;
};

#endif // __WORLD_LEVEL_CTRL_LAYER_H__
