#ifndef __WORLD_LEVEL_CTRL_LAYER_H__
#define __WORLD_LEVEL_CTRL_LAYER_H__

#include <string>
#include "UILayer.h"
class Entity;

class WorldLevelCtrlLayer : public UILayer
{
public:
  enum State {
    Inactive,
    Showing,
    Waiting
  };

public:
  virtual bool init(WorldLevelScene* scene);
  virtual void update(float dt);
  /**
   * Called from the Scene when a control gets selected.
   * @param entity Entity bound to the control, if any.
   */
  void beginCtrlTouch(Entity* entity);
  /**
   * Called from within the layer when the user has finished input.
   */
  void endCtrlTouch();
  /**
   * Called from within the layer when the user cancels the control.
   */
  void cancelCtrlTouch();
  /**
   * Touches ended event, used to end or cancel the control input.
   */
  virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
  /**
   * The control layer fades to black when input starts.
   * @return True if the layer fades to black.
   */
  bool isFadeToBlackCtrl();
  /**
   * Set to true to fade the layer to black when input starts.
   * @param isFadeToBlackCtrl True to fade to black when input starts.
   */
  void setFadeToBlackCtrl(bool isFadeToBlackCtrl);
  bool isLockingCtrl();
  void setLockingCtrl(bool isLockingCtrl);
  bool isFollowingCtrl();
  void setFollowingCtrl(bool isFollowingCtrl);
  bool isPausingCtrl();
  void setPausingCtrl(bool isPausingCtrl);
  /**
   * Gets the entity bound to the control if present.
   * @return Entity if present, if not null.
   */
  Entity* getEntity();

  /**
   * Callback for when the input starts.
   */
  virtual void onBeginCtrlTouch();
  /**
   * Callback for when the input gets cancelled.
   */
  virtual void onCancelCtrlTouch();
  /**
   * Callback for when the input finishes.
   */
  virtual void onEndCtrlTouch();

protected:
  cocos2d::ui::Layout* m_opacityLayout;
  cocos2d::Vec2* m_center;
  Entity* m_entity;
  float m_touchTime;
  float m_showingTime;
  bool m_isFadeToBlackCtrl;
  bool m_isLockingCtrl;
  bool m_isFollowingCtrl;
  bool m_isPausingCtrl;
 
};

#endif // __WORLD_LEVEL_CTRL_LAYER_H__
