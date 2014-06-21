#ifndef __ENTITY_NODE_H__
#define __ENTITY_NODE_H__

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "2d/CCNode.h"

class Entity : public cocos2d::Node
{
protected:
    b2Body* m_body;

public:
    /**
     * Class constructor.
     */
    Entity(void);
    /**
     * Class destructor.
     */
    virtual ~Entity(void);
    /**
     * Sets the Box2d body for this entity.
     * @param body Box2D body object.
     */
    void setBody(b2Body* body);
    /**
     * Override Node update method.
     * @param dt Time passed from the last update call.
     */
    virtual void update(float dt);
};

#endif // __ENTITY_NODE_H__
