#ifndef __MAIN_MENU_UI_LAYER_H__
#define __MAIN_MENU_UI_LAYER_H__

#include <string>
#include <stack>

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "ui/UICheckBox.h"
#include "cocostudio/CCActionObject.h"

class MainMenuUILayer : public cocos2d::Layer
{
private:
  static char* MAIN_MENU_JSON;
  enum State {
    MainMenu,
    SettingsMenu,
    ContinueMenu
  };
  int m_animCount;
  std::stack<State> m_states;
  cocostudio::ActionObject* m_currentAction;
  cocos2d::Size m_visibleSize;
  cocos2d::Size m_winSize;
  cocos2d::ui::Button* m_startBtn;
  cocos2d::ui::Button* m_continueBtn;
  cocos2d::ui::Button* m_settingsBtn;
  cocos2d::ui::Button* m_settingsApplyBtn;
  cocos2d::ui::Button* m_returnBtn;
  cocos2d::ui::CheckBox* m_musicChk;
  cocos2d::ui::CheckBox* m_soundChk;

public:
  CREATE_FUNC(MainMenuUILayer);
  virtual bool init();
  virtual void onEnter();
  void pushState(State state);
  void popState();
  void startBtnCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
  void continueBtnCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
  void settingsBtnCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
  void returnBtnCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
  void finishStateAnimation();

private:
  void setUILayer();
  void setTouchEnabled(bool enabled);
  void playAnimationIn(State state);
  void playAnimationOut(State state);
  void playStateAnimation(std::string name);
};

#endif // __MAIN_MENU_UI_LAYER_H__
