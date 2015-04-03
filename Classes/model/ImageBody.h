#ifndef __IMAGE_BODY_NODE_H__
#define __IMAGE_BODY_NODE_H__

#include <string>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Entity.h"

class ImageBody : public Entity
{
protected:
    cocos2d::Sprite* m_sprite;

public:
    /**
     * Class constructor.
     */
    ImageBody(void);
    /**
     * Class destructor.
     */
    virtual ~ImageBody(void);
    /**
     * Get the identifier for this class.
     * @return Type identifier.
     */
    virtual int getType();
    /**
     * Returns an instance of this class.
     * @return ImageBody instance.
     */
    static ImageBody* create(std::string filename, b2Body* body);
    /**
     * Initialization method.
     * @return True if the object is correctly initialized.
     */
    virtual bool init(std::string filename);
};

#endif // __IMAGE_BODY_NODE_H__
