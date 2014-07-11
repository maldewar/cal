#ifndef __WHEEL_CTRL_NODE_H__
#define __WHEEL_CTRL_NODE_H__

#include "cocos2d.h"
#include "2d/CCNode.h"
#include "cocostudio/CocoStudio.h"
#include "../../scene/WorldLevelScene.h"

const int WHEEL_CTRL_STATE_HIDDEN  = 0;
const int WHEEL_CTRL_STATE_SHOWING = 1;
const int WHEEL_CTRL_STATE_HIDING = 2;

const int WHEEL_CTRL_ANIM_SHOWING= 0;
const int WHEEL_CTRL_ANIM_HIDING = 1;
const int WHEEL_CTRL_ANIM_CANCEL = 2;

class WheelCtrl : public cocos2d::Node
{
protected:
  int m_state;
  cocostudio::Armature* m_armature;
  bool m_pauseScene;
  WorldLevelScene* m_scene;
  float m_targetAngle;

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
    static WheelCtrl* create(WorldLevelScene* scene);
    /**
     * Initialization method.
     * @return True if the object is correctly initialized.
     */
    virtual bool init(WorldLevelScene* scene);
    virtual void show();
    virtual void hide();
    virtual void update(float dt);
    virtual void setWorldLevelScene(WorldLevelScene* scene);
    virtual void setTargetAngle(float angle);
    virtual void applyTargetAngle();
};

#endif // __WHEEL_CTRL_NODE_H__
