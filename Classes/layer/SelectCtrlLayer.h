#ifndef __SELECT_CTRL_LAYER_H__
#define __SELECT_CTRL_LAYER_H__

#include <string>
#include "WorldLevelCtrlLayer.h"
#include "../model/ctrl/WheelCtrl.h"
#include "../engine/RayCastTool.h"
class WheelCtrl;
class RayCastTool;

class SelectCtrlLayer : public WorldLevelCtrlLayer
{
public:
  static SelectCtrlLayer* create(WorldLevelScene* scene);
  virtual bool init(WorldLevelScene* scene);
  virtual void update(float dt);
  virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
  virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
  virtual void onBeginCtrlTouch();
  virtual void onEndCtrlTouch();
  virtual void onCancelCtrlTouch();
  virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

protected:
  virtual void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);

private:
  WheelCtrl* m_selectCtrl;
  WheelCtrl* m_cursorCtrl;
  RayCastTool* m_rayCastTool;
  cocos2d::CustomCommand m_customCommand; // for raycast line rendering.

private:
  void playAnimationIn(int state);
  void playAnimationOut(int state);
};

#endif // __SELECT_CTRL_LAYER_H__
