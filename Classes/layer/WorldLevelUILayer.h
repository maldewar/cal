#ifndef __WORLD_LEVEL_UI_LAYER_H__
#define __WORLD_LEVEL_UI_LAYER_H__

#include <string>

#include "ui/UIButton.h"
#include "ui/UICheckBox.h"
#include "UILayer.h"

class WorldLevelUILayer : public UILayer
{
protected:
  static char* GAME_MENU_JSON;
  int m_animCount;
  int m_totalUnits;
  int m_totalRequiredUnits;
  int m_totalLostUnits;
  int m_totalSavedUnits;
  cocostudio::ActionObject* m_currentAction;
  cocos2d::ui::Button* m_settingsBtn;
  cocos2d::ui::Button* m_returnBtn;
  cocos2d::ui::CheckBox* m_pauseChk;

public:
  enum State {
    GameMenu,
    PauseMenu,
    ReturnMenu
  };

public:
  WorldLevelUILayer();
  CREATE_FUNC(WorldLevelUILayer);
  virtual bool init();
  virtual void onEnter();
  void settingsBtnCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
  void returnBtnCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
  void pauseBtnCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
  void finishStateAnimation();
  void setTotalUnits(int totalUnits);
  void setTotalRequiredUnits(int totalRequiredUnits);
  void setTotalSavedUnits(int totalSavedUnits);
  void setTotalLostUnits(int totalLostUnits);


private:
  void setUILayer();
  void playAnimationIn(int state);
  void playAnimationOut(int state);
  void playStateAnimation(std::string name);
};

#endif // __WORLD_LEVEL_UI_LAYER_H__
