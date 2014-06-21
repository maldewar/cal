#ifndef __UNIT_NODE_H__
#define __UNIT_NODE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include <Box2D/Box2D.h>
#include "Entity.h"

class Unit : public Entity
{
protected:
    cocostudio::Armature* m_armature;
    cocos2d::Sprite* m_sprite;

public:
    /**
     * Class constructor.
     */
    Unit(void);
    /**
     * Class destructor.
     */
    virtual ~Unit(void);
    /**
     * Returns an instance of this class.
     * @return Unit instance.
     */
    static Unit* create();
    /**
     * Initialization method.
     * @return True if the object is correctly initialized.
     */
    virtual bool init(void);
};

#endif // __UNIT_NODE_H__
