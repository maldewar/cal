#ifndef __ENTITY_NODE_H__
#define __ENTITY_NODE_H__

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "2d/CCNode.h"
#include "../manager/ConfigurationManager.h"
#include "../layer/WorldLevelLayer.h"

const int ENTITY_TYPE_UNIT  = 1;
const int ENTITY_TYPE_ENTRY = 2;
const int ENTITY_TYPE_AREA  = 3;
const int ENTITY_TYPE_EXIT  = 4;
const int ENTITY_TYPE_GRAVITRON = 5;
const int ENTITY_TYPE_IMAGE = 6;
const int ENTITY_TYPE_IMAGE_BODY = 7;

class Entity : public cocos2d::Node
{
protected:
    WorldLevelLayer* m_worldLayer;
    b2Body* m_body;
    float m_width;
    float m_height;

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
     * Get the identifier for the subclass.
     * @return Type identifier for the object.
     */
    virtual int getType();
    /**
     * Set the Box2d body for this entity.
     * @param body Box2D body object.
     */
    virtual void setBody(b2Body* body);
    /**
     * Get the Box2D body for this entity.
     * @return Box2D body object.
     */
    virtual b2Body* getBody();
    /**
     * Set the world layer for this entity.
     * @param worldLevelLayer World layer.
     */
    virtual void setWorldLevelLayer(WorldLevelLayer* worldLevelLayer);
    /**
     * Get the world layer for this entity.
     * @return World layer.
     */
    virtual WorldLevelLayer* getWorldLevelLayer();
    /**
     * Override Node update method.
     * @param dt Time passed from the last update call.
     */
    virtual void update(float dt);
};

#endif // __ENTITY_NODE_H__
