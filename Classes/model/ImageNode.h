#ifndef __IMAGE_NODE_H__
#define __IMAGE_NODE_H__

#include <string>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Entity.h"

class ImageNode : public cocos2d::Node
{
protected:
    cocos2d::Sprite* m_sprite;

public:
    /**
     * Class constructor.
     */
    ImageNode(void);
    /**
     * Class destructor.
     */
    virtual ~ImageNode(void);
    /**
     * Get the identifier for this class.
     * @return Type identifier.
     */
    virtual int getType();
    /**
     * Returns an instance of this class.
     * @return ImageNode instance.
     */
    static ImageNode* create(std::string filename);
    /**
     * Initialization method.
     * @return True if the object is correctly initialized.
     */
    virtual bool init(std::string filename);
    /**
     * Get the sprite used by this image.
     * @return Sprite instance.
     */
    virtual cocos2d::Sprite* getSprite();
};

#endif // __IMAGE_NODE_H__
