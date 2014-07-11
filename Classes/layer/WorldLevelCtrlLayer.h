#ifndef __WORLD_LEVEL_CTRL_LAYER_H__
#define __WORLD_LEVEL_CTRL_LAYER_H__

#include <string>
#include "UILayer.h"
#include "../model/Entity.h"
#include "../model/ctrl/WheelCtrl.h"
class Entity;
class WheelCtrl;

class WorldLevelCtrlLayer : public UILayer
{
public:
  enum State {
    Inactive,
    Showing,
    Waiting
  };

public:
  static WorldLevelCtrlLayer* create(WorldLevelScene* scene);
  virtual bool init(WorldLevelScene* scene);
  virtual void update(float dt);
  virtual void beginCtrlTouch(int ctrl, Entity* entity);
  virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
  virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);

private:
  cocos2d::ui::Layout* m_opacityLayout;
  WheelCtrl* m_wheelCtrl;
  cocos2d::Vec2* m_center;
  float m_touchTime;
  float m_showingTime;
  int m_ctrl;

private:
  void playAnimationIn(int state);
  void playAnimationOut(int state);
  void playStateAnimation(std::string name);
};

#endif // __WORLD_LEVEL_CTRL_LAYER_H__
