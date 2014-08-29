#ifndef __UI_LAYER_H__
#define __UI_LAYER_H__

#include <stack>

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CCActionObject.h"
class WorldLevelScene;

class UILayer : public cocos2d::Layer
{
protected:
  std::stack<int> m_states;
  int m_state;
  cocos2d::Size m_visibleSize;
  cocos2d::Size m_winSize;
  WorldLevelScene* m_scene;
  enum Align {
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
  };

public:
  //CREATE_FUNC(UILayer);
  /**
   * Initializes variables.
   */
  virtual bool init();
  /**
   * Add a state to the stack.
   */
  virtual void pushState(int state);
  /**
   * Removes the top most state in the stack.
   */
  virtual void popState(int howMany = 1);
  /**
   * Gets the top most stack in the stack.
   */
  virtual int getState();
  virtual void finishStateAnimation();
  virtual void setScene(WorldLevelScene* scene);

protected:
  /**
   * Animation to play when adding a new state.
   */
  virtual void playAnimationIn(int state);
  /**
   * Animation to play when removing a state.
   */
  virtual void playAnimationOut(int state);
  virtual void playStateAnimation(std::string name);
  virtual void scaleWidget(cocos2d::ui::Widget* widget, const Align align);
};

#endif // __UI_LAYER_H__
