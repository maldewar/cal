#ifndef __WORLD_LEVEL_CTRL_LAYER_H__
#define __WORLD_LEVEL_CTRL_LAYER_H__

#include <string>
#include <stack>

#include "cocos2d.h"
#include "../scene/WorldLevelScene.h"
class WorldLevelScene;

class WorldLevelCtrlLayer : public cocos2d::Layer
{
private:
  enum State {
    Showing,
    Waiting
  };
  WorldLevelScene* m_scene;

public:
  CREATE_FUNC(WorldLevelCtrlLayer);
  virtual bool init();
  void pushState(State state);
  void popState();
  void settingsBtnCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
  void returnBtnCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
  void pauseBtnCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
  void finishStateAnimation();
  void setScene(WorldLevelScene* scene);

private:
  void setUILayer();
  void setTouchEnabled(bool enabled);
  void playAnimationIn(State state);
  void playAnimationOut(State state);
  void playStateAnimation(std::string name);
  void scaleWidget(cocos2d::ui::Widget* widget, const Align align);
};

#endif // __WORLD_LEVEL_CTRL_LAYER_H__
