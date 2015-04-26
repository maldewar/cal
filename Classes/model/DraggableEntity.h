#ifndef __DRAGGABLE_ENTITY_NODE_H__
#define __DRAGGABLE_ENTITY_NODE_H__

#include "cocos2d.h"
#include "Entity.h"
#include "../component/DraggableComponent.h"

class DraggableEntity : public Entity, public DraggableComponent
{
protected:
    int m_state;
    cocostudio::Armature* m_armature;

public:
    /**
     * Class constructor.
     */
    DraggableEntity(void);
    /**
     * Class destructor.
     */
    virtual ~DraggableEntity(void);
    /**
     * Get the identifier for this class.
     * @return Type identifier.
     */
    virtual int getType();
    virtual void setBody(b2Body* body);
    static DraggableEntity* create();
    /**
     * Returns an instance of this class.
     * @return DraggableEntity instance.
     */
    static DraggableEntity* create(bool active);
    /**
     * Initialization method.
     * @return True if the object is correctly initialized.
     */
    virtual bool init(bool active);
    virtual void update(float dt);
    virtual void select();
};

#endif // __DRAGGABLE_ENTITY_NODE_H__
