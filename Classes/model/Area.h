#ifndef __AREA_NODE_H__
#define __AREA_NODE_H__

#include "cocos2d.h"
#include "Entity.h"

class Area : public Entity
{

public:
    /**
     * Class constructor.
     */
    Area(void);
    /**
     * Class destructor.
     */
    virtual ~Area(void);
    /**
     * Get the identifier for this class.
     * @return Type identifier.
     */
    virtual int getType();
    /**
     * Returns an instance of this class.
     * @return Area instance.
     */
    static Area* create();
    /**
     * Initialization method.
     * @return True if the object is correctly initialized.
     */
    virtual bool init(void);
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
};

#endif // __AREA_NODE_H__
