#ifndef WORLD_LEVEL_LAYER
#define WORLD_LEVEL_LAYER

#include "BasicRUBELayer.h"
#include "cocostudio/CocoStudio.h"

//
//  ImageInfo
//
//  Holds information about one image in the layer, most importantly
//  the body it is attached to and its position relative to that body.
//
//  When the body is moved by the physics engine, this information is
//  used to place the image in the correct position to match the physics.
//  If the body is NULL, the position is relative to 0,0 and angle zero.
//
struct ImageInfo {
    cocos2d::Sprite* sprite;
    std::string name;
    class b2Body* body;
    float scale;
    float aspectScale;
    float angle;
    cocos2d::Point center;
    float opacity;
    bool flip;
    int colorTint[4];
    
};

//-------------------------

class WorldLevelLayer : public BasicRUBELayer
{
protected:
    std::set<ImageInfo*> m_imageInfos;
    
public:
    static cocos2d::Scene* scene();
    CREATE_FUNC(WorldLevelLayer);
    virtual std::string getFilename();
    virtual cocos2d::Point initialWorldOffset();
    virtual float initialWorldScale();
    virtual void afterLoadProcessing(b2dJson* json);
    virtual void clear();
    void setImagePositionsFromPhysicsBodies();
    virtual void onEnter() override;
    virtual void update(float dt);
    void removeBodyFromWorld(b2Body* body);
    void removeImageFromWorld(ImageInfo* imgInfo);
    cocos2d::Sprite* getAnySpriteOnBody(b2Body* body);
    cocos2d::Sprite* getSpriteWithImageName(std::string name);

};

#endif /* WORLD_LEVEL_LAYER */
