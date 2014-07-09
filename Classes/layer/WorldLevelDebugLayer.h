#ifndef __WORLD_LEVEL_DEBUG_LAYER_H__
#define __WORLD_LEVEL_DEBUG_LAYER_H__

#include <string>
#include <stack>

#include "cocos2d.h"
#include "ui/UIButton.h"
#include "ui/UICheckBox.h"
#include "../scene/WorldLevelScene.h"
class WorldLevelScene;

class WorldLevelDebugLayer : public cocos2d::Layer
{
private:
  cocos2d::ui::Button* m_box2dBtn;
  WorldLevelScene* m_scene;

public:
  CREATE_FUNC(WorldLevelDebugLayer);
  virtual bool init();
  void box2dBtnCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
  void setScene(WorldLevelScene* scene);
};

#endif // __WORLD_LEVEL_DEBUG_LAYER_H__
