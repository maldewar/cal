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
    virtual bool isSensor();
    virtual void setIsSensor(bool isSensor);
    virtual void sensorStart(b2Body* body, Entity* sensorEntity = nullptr);
    virtual void sensorEnd(b2Body* body, Entity* sensorEntity = nullptr);
    virtual void sensorReceive(b2Body* body, Entity* receivedEntity = nullptr);
    virtual void sensorLose(b2Body* body, Entity* lostEntity = nullptr);
};

#endif // __CONTACT_COMPONENT_H__
