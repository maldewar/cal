#ifndef __ENTRY_NODE_H__
#define __ENTRY_NODE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include <Box2D/Box2D.h>
#include "Entity.h"

const int ENTRY_STATE_CLOSED  = 0;
const int ENTRY_STATE_OPEN    = 1;
const int ENTRY_STATE_CLOSING = 2;
const int ENTRY_STATE_OPENING = 3;

const int ENTRY_ANIM_OPENING = 0;
const int ENTRY_ANIM_CLOSING = 1;
const int ENTRY_ANIM_RELEASE = 2;

class Entry : public Entity
{
protected:
    int m_units;
    int m_capacity;
    bool m_open;
    int m_openTimer;
    int m_interval;
    float m_forceMinDistance;
    float m_forceMaxDistance;
    float m_forceMaxAngle;
    float m_forceMinAngularImpulse;
    float m_forceMaxAngularImpulse;
    int m_state;
    bool m_transition;
    cocostudio::Armature* m_armature;

public:
    /**
     * Class constructor.
     */
    Entry(void);
    /**
     * Class destructor.
     */
    virtual ~Entry(void);
    /**
     * Get the identifier for this class.
     * @return Type identifier.
     */
    virtual int getType();
    /**
     * Returns an instance of this class.
     * @return Entry instance.
     */
    static Entry* create();
    /**
     * Initialization method.
     * @return True if the object is correctly initialized.
     */
    virtual bool init(void);
    /**
     * Object description.
     * @return Print ready string for this object.
     */
    //virtual std::string getDescription() const override;
    /**
     * Sets the amount of Unit instances this Entry will generate.
     * @param capacity Amount of Unit instances to generate.
     */
    void setCapacity(int capacity);
    /**
     * Gets the amount of Unit instances this Entry will generate.
     * @returns Amount of Unit instances to generate.
     */
    int getCapacity();
    /**
     * Gets the amount of Unit instances that remain to be generated.
     * @returns Amount of Unit instances that remain to be generated.
     */
    int getUnits();
    /**
     * Opens the Entry so Unit instances can be generated.
     */
    void open(float dt);
    /**
     * Closes the Entry stoping the the generation of Unit instances.
     */
    void close(float dt);
    /**
     * Sets the state of the Entry as open or closed.
     * @param isOpen True if the Entry has to be open.
     */
    void setOpen(bool isOpen);
    /**
     * If an Entry is initialised closed this sets the number
     * of milliseconds to wait before it auto-opens.
     * @param openTimer Milliseconds for this Entry to open.
     */
    void setOpenTimer(int openTimer);
    /**
     * Sets the interval inbetween spawning Units.
     * @param interval Milliseconds between Units.
     */
    void setInterval(int interval);
    /**
     * Gets the interval inbetween spawning Units.
     * @return Milliseconds between Units.
     */
    int getInterval();
    void setForceMinDistance(float distance);
    float getForceMinDistance();
    void setForceMaxDistance(float distance);
    float getForceMaxDistance();
    void setForceMinAngularImpulse(float angularImpulse);
    float getForceMinAngularImpulse();
    void setForceMaxAngularImpulse(float angularImpulse);
    float getForceMaxAngularImpulse();
    /**
     * Sets the random Pi area used to eject Units.
     * @param angle Between 0 and 2 Pi.
     */
    void setForceMaxAngle(float angle);
    /**
     * Gets the random Pi area used to eject Units.
     * @returns Value between 0 and 2 Pi.
     */
    float getForceMaxAngle();
    /**
     * Gets the randomized vector used to eject Units.
     * @return Vector.
     */
    //b2Vec2 getRandomForce();
    /**
     * State for this entry.
     * @param state State the entry is on.
     */
    void setState(int state);
    virtual void update(float dt);
    virtual void spawnUnit(float dt);
    b2Vec2 getRandomForce();
    //virtual void onEnter();
};

#endif // __ENTRY_NODE_H__
