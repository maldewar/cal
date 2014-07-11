#ifndef __GRAVITRON_NODE_H__
#define __GRAVITRON_NODE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "Entity.h"
#include "../component/ContactComponent.h"

const int GRAVITRON_STATE_INACTIVE = 0;
const int GRAVITRON_STATE_ACTIVE   = 1;
const int GRAVITRON_STATE_LOCKED   = 2;

const int GRAVITRON_ANIM_INACTIVE = 0;
const int GRAVITRON_ANIM_ACTIVE   = 1;

class Gravitron : public Entity, public ContactComponent
{
protected:
    int m_state;
    cocostudio::Armature* m_armature;

public:
    /**
     * Class constructor.
     */
    Gravitron(void);
    /**
     * Class destructor.
     */
    virtual ~Gravitron(void);
    /**
     * Get the identifier for this class.
     * @return Type identifier.
     */
    virtual int getType();
    static Gravitron* create();
    /**
     * Returns an instance of this class.
     * @return Gravitron instance.
     */
    static Gravitron* create(bool active);
    /**
     * Initialization method.
     * @return True if the object is correctly initialized.
     */
    virtual bool init(bool active);
    void activate(float dt);
    void deactivate(float dt);
    virtual void update(float dt);
    virtual void select();

    virtual void sensorReceive(b2Body* body, Entity* receivedEntity);
};

#endif // __GRAVITRON_NODE_H__
