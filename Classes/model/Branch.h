#ifndef __BRANCH_NODE_H__
#define __BRANCH_NODE_H__

#include <vector>
#include "cocos2d.h"
#include "Entity.h"
#include "../component/ContactComponent.h"

const int BRANCH_STATE_INACTIVE = 0;
const int BRANCH_STATE_ACTIVE   = 1;
const int BRANCH_STATE_LOCKED   = 2;

const int BRANCH_ANIM_INACTIVE = 0;
const int BRANCH_ANIM_ACTIVE   = 1;

class Branch : public Entity, public ContactComponent
{
protected:
  int m_state;
  std::vector<b2RevoluteJoint*> m_joints;
  float m_topAngle;
  float m_bottomAngle;
  float m_angle;
  float m_motorSpeed;

public:
    /**
     * Class constructor.
     */
    Branch(void);
    /**
     * Class destructor.
     */
    virtual ~Branch(void);
    /**
     * Get the identifier for this class.
     * @return Type identifier.
     */
    virtual int getType();
    /**
     * Creates and entity of this type.
     * @return Branch instance.
     */
    static Branch* create();
    /**
     * Returns an instance of this class.
     * @return Branch instance.
     */
    static Branch* create(bool active);
    /**
     * Initialization method.
     * @return True if the object is correctly initialized.
     */
    virtual bool init(bool active);
    void activate(float dt);
    void deactivate(float dt);
    virtual void update(float dt);
    virtual void select(b2Body* body);
    void addJoint(b2RevoluteJoint* joint);

    void setAngle(float angle);
    float getAngle();
    void setTopAngle(float topAngle);
    float getTopAngle();
    void setBottomAngle(float bottomAngle);
    float getBottomAngle();
    void setMotorSpeed(float motorSpeed);
    float getMotorSpeed();
    void applyAngle(float angle);

    virtual void sensorReceive(b2Body* body, Entity* receivedEntity);
    /** Should Return true if deregisters from the listener. **/
    virtual bool onEndTouchEvent();
};

#endif // __BRANCH_NODE_H__
