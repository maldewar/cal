#ifndef __WORLD_LEVEL_STATISTICS_LAYER_H__
#define __WORLD_LEVEL_STATISTICS_LAYER_H__

#include <string>
#include <stack>

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "ui/UICheckBox.h"
#include "cocostudio/CCActionObject.h"

class WorldLevelStatisticsLayer : public cocos2d::Layer
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

public:
  WorldLevelStatisticsLayer();
  virtual ~WorldLevelStatisticsLayer();
  static WorldLevelStatisticsLayer* create();
  virtual bool init();
  virtual void onEnter();
  virtual void onExit();
  void continueBtnCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

};

#endif // __WORLD_LEVEL_STATISTICS_LAYER_H__
