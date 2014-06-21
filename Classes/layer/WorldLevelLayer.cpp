#include "WorldLevelLayer.h"
#include "../util/b2dJson.h"
#include "../util/b2dJsonImage.h"
#include "../model/Entry.h"
#include "../model/Unit.h"

using namespace std;
using namespace cocos2d;


// Standard Cocos2d method, simply returns a scene with an instance of this class as a child
Scene* WorldLevelLayer::scene()
{
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("sprite/entry/entry.pvr", "sprite/entry/entry.plist", "entry.ExportJson");
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("sprite/unit/unit.pvr","sprite/unit/unit.plist","unit.ExportJson");
    auto scene = Scene::create();
    WorldLevelLayer* layer = WorldLevelLayer::create();
    scene->addChild(layer);
    return scene;
}

string WorldLevelLayer::getFilename()
{
    return "scene/calaverasTemplate.json";
}


// Override superclass to set different starting offset
Point WorldLevelLayer::initialWorldOffset()
{
    // If you are not sure what to set the starting position as, you can
    // pan and zoom the scene until you get the right fit, and then set
    // a breakpoint in the draw or update methods to see what the values
    // of [self scale] and [self position] are.
    //
    // For the images.json scene, I did this on my iPad in landscape (1024x768)
    // and came up with a value of 475,397 for the position. Since the
    // offset is measured in pixels, we need to set this as a percentage of
    // the current screen height instead of a fixed value, to get the same
    // result on different devices.
    // 
    Size s = Director::sharedDirector()->getWinSize();
    return CCPointMake( s.width * (475 / 1024.0), s.height * (397 / 768.0) );
}


// Override superclass to set different starting scale
float WorldLevelLayer::initialWorldScale()
{
    Size s = Director::sharedDirector()->getWinSize();
    //return s.height / 35; //screen will be 35 physics units high
    return s.height/4;
}


// This is called after the Box2D world has been loaded, and while the b2dJson information
// is still available to do extra loading. Here is where we load the images.
void WorldLevelLayer::afterLoadProcessing(b2dJson* json)
{
    std::vector<b2Body*> b2Bodies;
    json->getAllBodies(b2Bodies);
    for (int i = 0; i < b2Bodies.size(); i++) {
      if (json->hasCustomString(b2Bodies[i], "category")) {
        std::string category = json->getCustomString(b2Bodies[i], "category");
        if (category.compare("entry") == 0) {
          Entry* entry = Entry::create();
          entry->setScale(1/(float)840);
          entry->setBody(b2Bodies[i]);
          entry->update(0);
          addChild(entry);
        } else if (category.compare("unit") == 0) {
          Unit* unit = Unit::create();
          unit->setScale(1/(float)840);
          unit->setBody(b2Bodies[i]);
          unit->scheduleUpdate();
          unit->update(0);
          addChild(unit);
        }
      }
    }
    /*
    // fill a vector with all images in the RUBE scene
    std::vector<b2dJsonImage*> b2dImages;
    json->getAllImages(b2dImages);
        
    // loop through the vector, create Sprites for each image and store them in m_imageInfos
    for (int i = 0; i < b2dImages.size(); i++) {
        b2dJsonImage* img = b2dImages[i];
        
        log("Loading image: %s", img->file.c_str());
        
        // try to load the sprite image, and ignore if it fails
        Sprite* sprite = Sprite::create(img->file.c_str());
        if ( ! sprite )
            continue;
        
        // add the sprite to this layer and set the render order
        addChild(sprite);
        reorderChild(sprite, img->renderOrder); //watch out - RUBE render order is float but cocos2d uses integer (why not float?)
        
        // these will not change during simulation so we can set them now
        sprite->setFlipX(img->flip);
        sprite->setColor(ccc3(img->colorTint[0], img->colorTint[1], img->colorTint[2]));
        sprite->setOpacity(img->colorTint[3]);
        sprite->setScale(img->scale / sprite->getContentSize().height);
        
        // create an info structure to hold the info for this image (body and position etc)
        ImageInfo* imgInfo = new ImageInfo;
        imgInfo->sprite = sprite;
        imgInfo->name = img->name;
        imgInfo->body = img->body;
        imgInfo->scale = img->scale;
        imgInfo->aspectScale = img->aspectScale;
        imgInfo->angle = img->angle;
        imgInfo->center = CCPointMake(img->center.x, img->center.y);
        imgInfo->opacity = img->opacity;
        imgInfo->flip = img->flip;
        for (int n = 0; n < 4; n++)
            imgInfo->colorTint[n] = img->colorTint[n];
        
        // add the info for this image to the list
        m_imageInfos.insert(imgInfo);
    }
    
    // start the images at their current positions on the physics bodies
    setImagePositionsFromPhysicsBodies();
    */
}


// This method should undo anything that was done by afterLoadProcessing, and make sure
// to call the superclass method so it can do the same
void WorldLevelLayer::clear()
{
    for (set<ImageInfo*>::iterator it = m_imageInfos.begin(); it != m_imageInfos.end(); ++it) {
        ImageInfo* imgInfo = *it;
        removeChild(imgInfo->sprite, true);
    }
    m_imageInfos.clear();
    
    BasicRUBELayer::clear();
}

void WorldLevelLayer::onEnter()
{
  cocos2d::Layer::onEnter();
  //cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("sprite/entry/entry.pvr", "sprite/entry/entry.plist", "entry.ExportJson");
}


// Standard Cocos2d method. Call the super class to step the physics world, and then
// move the images to match the physics body positions
void WorldLevelLayer::update(float dt)
{
    //superclass will Step the physics world
    BasicRUBELayer::update(dt);
    //setImagePositionsFromPhysicsBodies();
}

// Move all the images to where the physics engine says they should be
void WorldLevelLayer::setImagePositionsFromPhysicsBodies()
{
    for (set<ImageInfo*>::iterator it = m_imageInfos.begin(); it != m_imageInfos.end(); ++it) {
        ImageInfo* imgInfo = *it;
        Point pos = imgInfo->center;
        float angle = -imgInfo->angle;
        if ( imgInfo->body ) {            
            //need to rotate image local center by body angle
            b2Vec2 localPos( pos.x, pos.y );
            b2Rot rot( imgInfo->body->GetAngle() );
            localPos = b2Mul(rot, localPos) + imgInfo->body->GetPosition();
            pos.x = localPos.x;
            pos.y = localPos.y;
            angle += -imgInfo->body->GetAngle();
        }
        imgInfo->sprite->setRotation( CC_RADIANS_TO_DEGREES(angle) );
        imgInfo->sprite->setPosition( pos );
    }
}


// Remove one body and any images is had attached to it from the layer
void WorldLevelLayer::removeBodyFromWorld(b2Body* body)
{
    //destroy the body in the physics world
    m_world->DestroyBody( body );
    
    //go through the image info array and remove all sprites that were attached to the body we just deleted
    vector<ImageInfo*> imagesToRemove;
    for (set<ImageInfo*>::iterator it = m_imageInfos.begin(); it != m_imageInfos.end(); ++it) {
        ImageInfo* imgInfo = *it;
        if ( imgInfo->body == body ) {
            removeChild(imgInfo->sprite, true);
            imagesToRemove.push_back(imgInfo);
        }
    }
    
    //also remove the infos for those images from the image info array
    for (int i = 0; i < imagesToRemove.size(); i++)
        m_imageInfos.erase( imagesToRemove[i] );
}


// Remove one image from the layer
void WorldLevelLayer::removeImageFromWorld(ImageInfo* imgInfo)
{
    removeChild(imgInfo->sprite, true);
    m_imageInfos.erase(imgInfo);
}

Sprite* WorldLevelLayer::getAnySpriteOnBody(b2Body* body)
{
    for (set<ImageInfo*>::iterator it = m_imageInfos.begin(); it != m_imageInfos.end(); ++it) {
        ImageInfo* imgInfo = *it;
        if ( imgInfo->body == body )
            return imgInfo->sprite;
    }
    return NULL;
}

Sprite* WorldLevelLayer::getSpriteWithImageName(std::string name)
{
    for (set<ImageInfo*>::iterator it = m_imageInfos.begin(); it != m_imageInfos.end(); ++it) {
        ImageInfo* imgInfo = *it;
        if ( imgInfo->name == name )
            return imgInfo->sprite;
    }
    return NULL;
}
