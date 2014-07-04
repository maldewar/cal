#ifndef __WORLD_LEVEL_UI_LAYER_H__
#define __WORLD_LEVEL_UI_LAYER_H__

#include <string>
#include <stack>

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "ui/UICheckBox.h"
#include "cocostudio/CCActionObject.h"
#include "../scene/WorldLevelScene.h"
class WorldLevelScene;

class WorldLevelUILayer : public cocos2d::Layer
{
private:
  static char* GAME_MENU_JSON;
  enum State {
    GameMenu,
    PauseMenu,
    ReturnMenu
  };
  enum Align {
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
  };
  int m_animCount;
  std::stack<State> m_states;
  cocostudio::ActionObject* m_currentAction;
  cocos2d::Size m_visibleSize;
  cocos2d::Size m_winSize;
  cocos2d::ui::Button* m_settingsBtn;
  cocos2d::ui::Button* m_returnBtn;
  cocos2d::ui::CheckBox* m_pauseChk;
  WorldLevelScene* m_scene;

public:
  CREATE_FUNC(WorldLevelUILayer);
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

#endif // __WORLD_LEVEL_UI_LAYER_H__
