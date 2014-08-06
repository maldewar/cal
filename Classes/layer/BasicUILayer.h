#ifndef __BASIC_UI_LAYER_H__
#define __BASIC_UI_LAYER_H__

#include <string>

#include "ui/UIButton.h"
#include "ui/UICheckBox.h"
#include "UILayer.h"

class BasicUILayer : public UILayer
{
protected:
  static char* BASIC_UI_JSON;
  int m_sceneType;
  int m_animCount;
  cocostudio::ActionObject* m_currentAction;
  cocos2d::ui::Button* m_settingsBtn;
  cocos2d::ui::Button* m_returnBtn;
  cocos2d::ui::CheckBox* m_pauseChk;

public:
  enum SceneType {
    Act,
    Level,
    Cinematic
  };

public:
  static BasicUILayer* create(int sceneType = 0);
  virtual bool init(int sceneType);
  virtual void onEnter();
  virtual void onExit();
  void returnBtnCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);


private:
  void setUILayer();
  void playAnimationIn(int state);
  void playAnimationOut(int state);
  void playStateAnimation(std::string name);
};

#endif // __BASIC_UI_LAYER_H__
