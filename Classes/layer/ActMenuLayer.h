#ifndef __ACT_MENU_LAYER_H__
#define __ACT_MENU_LAYER_H__

#include <string>
#include <stack>

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "ui/UICheckBox.h"
#include "cocostudio/CCActionObject.h"

class ActMenuLayer : public cocos2d::Layer
{
private:
  static int s_actPageWidth;
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

  cocos2d::ui::Layout* m_rootLayout;
  cocos2d::ui::PageView* m_pageView;

public:
  ActMenuLayer();
  virtual ~ActMenuLayer();
  static ActMenuLayer* create();
  virtual bool init();
  virtual void onEnter();
  virtual void onExit();
  void act0BtnCallback(cocos2d::Ref* sender,
                       cocos2d::ui::Widget::TouchEventType type);
  void act1BtnCallback(cocos2d::Ref* sender,
                       cocos2d::ui::Widget::TouchEventType type);
  void act2BtnCallback(cocos2d::Ref* sender,
                       cocos2d::ui::Widget::TouchEventType type);
  void act3BtnCallback(cocos2d::Ref* sender,
                       cocos2d::ui::Widget::TouchEventType type);
  void act4BtnCallback(cocos2d::Ref* sender,
                       cocos2d::ui::Widget::TouchEventType type);
  void act5BtnCallback(cocos2d::Ref* sender,
                       cocos2d::ui::Widget::TouchEventType type);
};

#endif // __ACT_MENU_LAYER_H__
