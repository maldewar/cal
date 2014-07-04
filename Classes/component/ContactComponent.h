#ifndef __CONTACT_COMPONENT_H__
#define __CONTACT_COMPONENT_H__

class ContactComponent
{
protected:
    int m_contacts;

public:
    /**
     * Class constructor.
     */
    ContactComponent(void);
    /**
     * Class destructor.
     */
    virtual ~ContactComponent(void);
    virtual void addContact();
    virtual void removeContact();
    virtual bool hasContact();
    virtual void contactStart();
    virtual void contactEnd();
};

#endif // __CONTACT_COMPONENT_H__
