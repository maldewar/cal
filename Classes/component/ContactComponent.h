#ifndef __CONTACT_COMPONENT_H__
#define __CONTACT_COMPONENT_H__

#include <Box2D/Box2D.h>
#include "../model/Entity.h"

class ContactComponent
{
protected:
    bool m_isSensor;
    int m_contacts;
    int m_sensors;

public:
    /**
     * Class constructor.
     */
    ContactComponent(void);
    /**
     * Class destructor.
     */
    virtual ~ContactComponent(void);

    virtual void addContact(b2Body* body, Entity* contactEntity = nullptr);
    virtual void removeContact(b2Body* body, Entity* contactEntity = nullptr);
    virtual bool hasContact();
    virtual void contactStart(b2Body* body, Entity* contactEntity = nullptr);
    virtual void contactEnd(b2Body* body, Entity* contactEntity = nullptr);

    virtual void enterSensor(b2Body* body, Entity* sensorEntity = nullptr);
    virtual void exitSensor(b2Body* body, Entity* sensorEntity = nullptr);
    virtual bool inSensor();
    /**
     * Get if this entity has a sensor fixture.
     * @return True if the entity has a sensor fixture.
     */
    virtual bool isSensor();
    /**
     * Set this entity as having a sensor fixture.
     * @param isSensor True if the entity has a sensor fixture.
     */
    virtual void setIsSensor(bool isSensor);
    /**
     * Called on an entity when it enters a sensor.
     * @param body Box2D body.
     * @param sensorEntity sensor Entity.
     */
    virtual void sensorStart(b2Body* body, Entity* sensorEntity = nullptr);
    /**
     * Called on an entity when it exits a sensor.
     * @param body Box2D body.
     * @param sensorEntity sensor Entity.
     */
    virtual void sensorEnd(b2Body* body, Entity* sensorEntity = nullptr);
    /**
     * Called on a sensor entity when it receives a body or an entity.
     * @param body Box2D body received by the sensor.
     * @param receivedEntity If the body belongs to an entity is send as parameter.
     */
    virtual void sensorReceive(b2Body* body, Entity* receivedEntity = nullptr);
    /**
     * Called on a sensor entity when it loses a body or an entity.
     * @param body Box2D body losed by the sensor.
     * @param lostEntity If the body belongs to an entity is send as parameter.
     */
    virtual void sensorLose(b2Body* body, Entity* lostEntity = nullptr);
};

#endif // __CONTACT_COMPONENT_H__
