#ifndef __WHEEL_CTRL_NODE_H__
#define __WHEEL_CTRL_NODE_H__

#include "cocos2d.h"
#include "2d/CCNode.h"
#include "cocostudio/CocoStudio.h"
#include "../../scene/WorldLevelScene.h"

const int WHEEL_CTRL_STATE_HIDDEN  = 0;
const int WHEEL_CTRL_STATE_SHOWING = 1;
const int WHEEL_CTRL_STATE_HIDING = 2;

const int WHEEL_CTRL_ANIM_POINTER_SHOWING = 0;
const int WHEEL_CTRL_ANIM_POINTER_HIDING  = 1;
const int WHEEL_CTRL_ANIM_SELECT_SHOWING  = 2;
const int WHEEL_CTRL_ANIM_SELECT_HIDING   = 3;
const int WHEEL_CTRL_ANIM_CURSOR_SHOWING  = 4;
const int WHEEL_CTRL_ANIM_CURSOR_HIDING   = 5;
const int WHEEL_CTRL_ANIM_CIRCLE_SHOWING  = 6;
const int WHEEL_CTRL_ANIM_CIRCLE_HIDING   = 7;
const int WHEEL_CTRL_ANIM_POINTER = 8;
const int WHEEL_CTRL_ANIM_SELECT  = 9;
const int WHEEL_CTRL_ANIM_CURSOR  = 10;
const int WHEEL_CTRL_ANIM_CIRCLE  = 11;

const int WHEEL_CTRL_TYPE_POINTER = 0;
const int WHEEL_CTRL_TYPE_SELECT  = 1;
const int WHEEL_CTRL_TYPE_CURSOR  = 2;
const int WHEEL_CTRL_TYPE_CIRCLE  = 3;

class WheelCtrl : public cocos2d::Node
{
protected:
  int m_state;
  int m_type;
  cocostudio::Armature* m_armature;
  bool m_pauseScene;
  WorldLevelScene* m_scene;
  float m_targetAngle;
  bool m_isCancelled;

public:
    /**
     * Class constructor.
     */
    WheelCtrl(void);
    /**
     * Class destructor.
     */
    virtual ~WheelCtrl(void);
    /**
     * Returns an instance of this class.
     * @return WheelCtrl instance.
     */
    static WheelCtrl* create(WorldLevelScene* scene, int type = 0);
    /**
     * Initialization method.
     * @return True if the object is correctly initialized.
     */
    virtual bool init(WorldLevelScene* scene, int type);
    virtual void show(bool ease = true);
    virtual void hide(bool ease = true);
    virtual void update(float dt);
    virtual void setWorldLevelScene(WorldLevelScene* scene);
    virtual void setTargetAngle(float angle);
    virtual void applyTargetAngle();
    virtual void cancel();
    virtual bool isCancelled();
};

#endif // __WHEEL_CTRL_NODE_H__
