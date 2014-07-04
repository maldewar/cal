#ifndef __UNIT_NODE_H__
#define __UNIT_NODE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include <Box2D/Box2D.h>
#include "Entity.h"
#include "../component/ContactComponent.h"
#include "../component/AIComponent.h"

const int UNIT_ANIM_STAND_FRONT = 0;
const int UNIT_ANIM_FALL        = 1;
const int UNIT_ANIM_FALL_STOP   = 2;
const int UNIT_ANIM_ROLL        = 3;
const int UNIT_ANIM_ROLL_STOP   = 4;
const int UNIT_ANIM_STAND_SIDE  = 5;

class Unit : public Entity, public ContactComponent, public AIComponent
{
protected:
    cocostudio::Armature* m_armature;
    cocos2d::Sprite* m_sprite;
    int m_animation;

public:
    /**
     * Class constructor.
     */
    Unit(void);
    /**
     * Class destructor.
     */
    virtual ~Unit(void);
    /**
     * Get the identifier for this class.
     * @return Type identifier.
     */
    virtual int getType();
    /**
     * Set the body for this instance and its components.
     * @param body Box2D body.
     */
    virtual void setBody(b2Body* body) override;
    /**
     * Returns an instance of this class.
     * @return Unit instance.
     */
    static Unit* create(bool managed = false, bool setBody = false);
    /**
     * Initialization method.
     * @return True if the object is correctly initialized.
     */
    virtual bool init(void);
    /**
     * Update method.
     * @return Seconds passed since last update.
     */
    virtual void update(float dt);
    virtual void contactStart();
    virtual void contactEnd();
    virtual void onStateChange(int state, int substate);
    virtual void onSubstateChange(int substate);
    virtual void onDirectionChange(bool isRight);
    virtual void setAnimation(int animation);
};

#endif // __UNIT_NODE_H__
