#ifndef __SELECT_CTRL_LAYER_H__
#define __SELECT_CTRL_LAYER_H__

#include <string>
#include "WorldLevelCtrlLayer.h"
#include "../model/ctrl/WheelCtrl.h"
class WheelCtrl;

class SelectCtrlLayer : public WorldLevelCtrlLayer
{
public:
  static SelectCtrlLayer* create(WorldLevelScene* scene);
  virtual bool init(WorldLevelScene* scene);
  virtual void update(float dt);
  virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
  virtual void onBeginCtrlTouch();
  virtual void onEndCtrlTouch();
  virtual void onCancelCtrlTouch();

private:
  WheelCtrl* m_wheelCtrl;

private:
  void playAnimationIn(int state);
  void playAnimationOut(int state);
};

#endif // __SELECT_CTRL_LAYER_H__
