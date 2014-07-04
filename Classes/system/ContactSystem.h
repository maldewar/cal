#ifndef _CONTACT_SYSTEM_H_
    #define _CONTACT_SYSTEM_H_
#include <Box2D/Box2D.h>

class ContactSystem : public b2ContactListener {
    public:
        ContactSystem();

    public:
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);

};

#endif
