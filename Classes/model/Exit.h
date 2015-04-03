#ifndef __EXIT_NODE_H__
#define __EXIT_NODE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "Box2D/Box2D.h"
#include "Entity.h"
#include "../component/ContactComponent.h"

const int EXIT_STATE_CLOSED  = 0;
const int EXIT_STATE_OPEN    = 1;
const int EXIT_STATE_CLOSING = 2;
const int EXIT_STATE_OPENING = 3;

const int EXIT_ANIM_OPENING  = 0;
const int EXIT_ANIM_CLOSING  = 1;
const int EXIT_ANIM_INCOMING = 2;

class Exit : public Entity, public ContactComponent
{
protected:
    int m_units;
    int m_capacity;
    bool m_open;
    int m_openTimer;
    int m_interval;
    int m_state;
    bool m_transition;
    cocostudio::Armature* m_armature;

public:
    /**
     * Class constructor.
     */
    Exit(void);
    /**
     * Class destructor.
     */
    virtual ~Exit(void);
    /**
     * Get the identifier for this class.
     * @return Type identifier.
     */
    virtual int getType();
    /**
     * Returns an instance of this class.
     * @return Exit instance.
     */
    static Exit* create();
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
     * Sets the amount of Unit instances this Exit will generate.
     * @param capacity Amount of Unit instances to generate.
     */
    void setCapacity(int capacity);
    /**
     * Gets the amount of Unit instances this Exit will generate.
     * @returns Amount of Unit instances to generate.
     */
    int getCapacity();
    /**
     * Gets the amount of Unit instances that remain to be generated.
     * @returns Amount of Unit instances that remain to be generated.
     */
    int getUnits();
    /**
     * Opens the Exit so Unit instances can be generated.
     */
    void open(float dt);
    /**
     * Closes the Exit stoping the the generation of Unit instances.
     */
    void close(float dt);
    /**
     * Sets the state of the Exit as open or closed.
     * @param isOpen True if the Exit has to be open.
     */
    void setOpen(bool isOpen);
    /**
     * If an Exit is initialised closed this sets the number
     * of milliseconds to wait before it auto-opens.
     * @param openTimer Milliseconds for this Exit to open.
     */
    void setOpenTimer(int openTimer);
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
    virtual void sensorReceive(b2Body* body, Entity* entity);
};

#endif // __EXIT_NODE_H__
