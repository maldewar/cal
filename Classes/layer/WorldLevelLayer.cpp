#include "WorldLevelLayer.h"
#include "WorldLevelUILayer.h"
#include "../util/b2dJson.h"
#include "../util/b2dJsonImage.h"
#include "../util/QueryCallbacks.h"
#include "../model/ImageNode.h"
#include "../model/ImageBody.h"
#include "../model/Entry.h"
#include "../model/Unit.h"
#include "../factory/BodyFactory.h"
#include "../factory/EntityFactory.h"
#include "../system/ContactSystem.h"

using namespace std;
using namespace cocos2d;

WorldLevelLayer::WorldLevelLayer() : BasicRUBELayer() {
  m_isMain = false;
  m_unitCount = 0;
  m_worldScene = nullptr;
  m_controlGrabbed = false;
  m_rayCastTool = new RayCastTool(10.0f);
  m_rayCastTool->SetFilter(ENTITY_TYPE_AREA);
  m_unitLayer = Layer::create();
  m_areaLayer = Layer::create();
  m_assetLayer = Layer::create();
  BasicRUBELayer::addChild(m_areaLayer, 3);
  BasicRUBELayer::addChild(m_unitLayer, 2);
  BasicRUBELayer::addChild(m_assetLayer, 1);
}

WorldLevelLayer* WorldLevelLayer::create(std::string filename) {
  WorldLevelLayer* worldLevelLayer = new (std::nothrow) WorldLevelLayer();
  if (worldLevelLayer && worldLevelLayer->init(filename)) {
    worldLevelLayer->autorelease();
    return worldLevelLayer;
  }
  CC_SAFE_DELETE(worldLevelLayer);
  return nullptr;
}

bool WorldLevelLayer::init(std::string filename) {
  m_filename = filename;
  if (BasicRUBELayer::init()) {
    setTouchEnabled(false);
    return true;
  }
  return false;
}

string WorldLevelLayer::getFilename() {
    return m_filename;
}

void WorldLevelLayer::setMain(bool isMain) {
  m_isMain = isMain;
  setTouchEnabled(m_isMain);
}

int WorldLevelLayer::getUnitCount() {
  return m_unitCount;
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
    //Size s = Director::getInstance()->getWinSize();
    //return cocos2d::Vec2(0,0);
    //return CCPointMake( s.width * (475 / 1024.0), s.height * (397 / 768.0) );
    // TODO: use cameras
    return getCenteredPosition(0, 0);
}


// Override superclass to set different starting scale
float WorldLevelLayer::initialWorldScale()
{
    Size s = Director::getInstance()->getWinSize();
    //return s.height / 35; //screen will be 35 physics units high
    return s.height/6;
}


// This is called after the Box2D world has been loaded, and while the b2dJson information
// is still available to do extra loading. Here is where we load the images.
void WorldLevelLayer::afterLoadProcessing(b2dJson* json)
{
    BodyFactory::getInstance()->setWorld(m_world);
    ContactSystem* contactSystem = new ContactSystem();
    m_world->SetContactListener(contactSystem);
    // Process bodies
    std::vector<b2Body*> b2Bodies;
    json->getAllBodies(b2Bodies);
    for (int i = 0; i < b2Bodies.size(); i++) {
      if (json->hasCustomString(b2Bodies[i], "category")) {
        std::string category = json->getCustomString(b2Bodies[i], "category");
        if (category.compare("entry") == 0) {
          Entry* entry = EntityFactory::getInstance()->getEntry(json, b2Bodies[i]);
          addChild(entry);
        } else if (category.compare("exit") == 0) {
          Exit* exit = EntityFactory::getInstance()->getExit(json, b2Bodies[i]);
          addChild(exit);
        }else if (category.compare("unit") == 0) {
          Unit* unit = EntityFactory::getInstance()->getUnit(json, b2Bodies[i]);
          addChild(unit);
        } else if (category.compare("area") == 0) {
          Area* area = EntityFactory::getInstance()->getArea(json, b2Bodies[i]);
          addChild(area);
        } else if (category.compare("gravitron") == 0) {
          Gravitron* gravitron = EntityFactory::getInstance()->getGravitron(json, b2Bodies[i]);
          addChild(gravitron);
        }
        BodyFactory::getInstance()->addBodyDef(category, b2Bodies[i]);
      }
    }

    // Process images
    std::vector<b2dJsonImage*> b2dImages;
    json->getAllImages(b2dImages);
    for (int i = 0; i < b2dImages.size(); i++) {
      b2dJsonImage* image = b2dImages[i];
      if (image->body) {
        ImageBody* imageBody = ImageBody::create(image->file, image->body);
        if (!imageBody) {
          continue;
        }
        addChild(imageBody);
      } else {
        ImageNode* imageNode = ImageNode::create(image->file);
        if (!imageNode) {
          continue;
        }
        imageNode->getSprite()->setFlipX(image->flip);
        imageNode->getSprite()->setColor(ccc3(image->colorTint[0], image->colorTint[1], image->colorTint[2]));
        imageNode->getSprite()->setOpacity(image->colorTint[3]);
        Size size = imageNode->getSprite()->getContentSize();
        float sizeRatio = size.height / 840.0f;
        float spriteScale = image->scale / sizeRatio;
        imageNode->getSprite()->setScale(spriteScale);
        Point pos = Point(image->center.x, image->center.y);
        b2Vec2 localPos( pos.x, pos.y );
        pos.x = localPos.x;
        pos.y = localPos.y;
        imageNode->setRotation( CC_RADIANS_TO_DEGREES(-image->angle) );
        imageNode->setPosition( pos );
        addChild(imageNode);
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

void WorldLevelLayer::addChild(Node* node) {
  Entity* entity = dynamic_cast<Entity*>(node);
  if (entity) {
    entity->setWorldLevelLayer(this);
    if (entity->getType() == ENTITY_TYPE_UNIT) {
      m_unitLayer->addChild(node);
      m_unitCount++;
      if (m_isMain) {
        m_worldScene->addUnit(1);
      }
      return;
    } else if (entity->getType() == ENTITY_TYPE_AREA) {
      m_areaLayer->addChild(node);
      return;
    }
  }
  m_assetLayer->addChild(node);
}

void WorldLevelLayer::removeChild(Node* node, bool cleanup) {
  Entity* entity = dynamic_cast<Entity*>(node);
  if (entity) {
    m_deletedEntities.push_back(entity);
    Unit* unit = dynamic_cast<Unit*>(entity);
    if (unit) {
      m_unitCount--;
    }
  } else {
    m_assetLayer->removeChild(node, cleanup);
  }
}

void WorldLevelLayer::setWorldLevelScene(WorldLevelScene* worldLevelScene) {
  m_worldScene = worldLevelScene;
}

WorldLevelScene* WorldLevelLayer::getWorldLevelScene() {
  return m_worldScene;
}

// This method should undo anything that was done by afterLoadProcessing, and make sure
// to call the superclass method so it can do the same
void WorldLevelLayer::clear()
{
  /*
    for (set<ImageInfo*>::iterator it = m_imageInfos.begin(); it != m_imageInfos.end(); ++it) {
        ImageInfo* imgInfo = *it;
        removeChild(imgInfo->sprite, true);
    }
    m_imageInfos.clear();
    
    BasicRUBELayer::clear();
  */
}

// Standard Cocos2d method. Call the super class to step the physics world, and then
// move the images to match the physics body positions
void WorldLevelLayer::update(float dt)
{
  if (m_deletedEntities.size() > 0) {
    vector<Entity*>::iterator entityIt = m_deletedEntities.begin();
    while (entityIt != m_deletedEntities.end()) {
      removeBodyFromWorld((*entityIt)->getBody());
      if ((*entityIt)->getType() == ENTITY_TYPE_UNIT) {
        if (m_isMain) {
          Unit* unit = dynamic_cast<Unit*>((*entityIt));
          m_worldScene->removeUnit(1, unit->isLost());
        }
        m_unitLayer->removeChild((*entityIt), true);
      } else if ((*entityIt)->getType() == ENTITY_TYPE_AREA) {
        m_areaLayer->removeChild((*entityIt), true);
      } else {
        m_assetLayer->removeChild((*entityIt), true);
      }
      entityIt = m_deletedEntities.erase(entityIt);
    }
  }
  BasicRUBELayer::update(dt);
}

// Remove one body and any images is had attached to it from the layer
void WorldLevelLayer::removeBodyFromWorld(b2Body* body)
{
  m_world->DestroyBody(body);
  /*
    
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
  */
}

void WorldLevelLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event) {
  BasicRUBELayer::onTouchesBegan(touches, event);
  if (touches.size() == 1) {
    Touch * touch = touches[0];
    m_worldScene->setTouch(touch);
  }
}

void WorldLevelLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) {
  if (!m_controlGrabbed) {
    BasicRUBELayer::onTouchesMoved(touches, unused_event);
    Touch* touch = touches[0];
    m_worldScene->setTouch(touch);
    Point screenPos = touch->getLocation();
    b2Vec2 worldPos = screenToWorld(screenPos);
    m_rayCastTool->RayCast(m_world, worldPos.x, worldPos.y, getWorldLevelScene()->getGravityAngle());
  }
}

void WorldLevelLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event) {
  m_worldScene->setTouch(nullptr);
  if (!m_navigationEnabled) {
    BasicRUBELayer::onTouchesEnded(touches, unused_event);
    return;
  }
}

void WorldLevelLayer::onBodyTouchBegan(b2Body* body, b2Fixture* fixture) {
  switch(body->GetType()) {
    case b2_staticBody:
      void* bodyUserData;
      bodyUserData  = body->GetUserData();
      if (bodyUserData) {
        Entity* entity = (Entity*)bodyUserData;
        switch(entity->getType()) {
          case ENTITY_TYPE_AREA:
            CCLOG("Area touched.");
            break;
          case ENTITY_TYPE_GRAVITRON:
            entity->select();
            break;
        }
      } else {
        CCLOG("Static body touched.");
      }
      break;
      break;
    case b2_kinematicBody:
      CCLOG("Kinematic body touched.");
      break;
    case b2_dynamicBody:
      void* dynamicBodyUserData;
      dynamicBodyUserData = body->GetUserData();
      if (dynamicBodyUserData) {
        Entity* entity = (Entity*)dynamicBodyUserData;
        switch(entity->getType()) {
          case ENTITY_TYPE_UNIT:
            entity->select();
            break;
          case ENTITY_TYPE_GRAVITRON:
            entity->select();
            break;
        }
      } else {
        CCLOG("Dynamic body touched.");
      }
      break;
  }
}

void WorldLevelLayer::onWorldTouchBegan(b2Vec2& position) {
}

void WorldLevelLayer::onDraw(const cocos2d::Mat4 &transform, uint32_t flags) {
  Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
  Director::getInstance()->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
  DrawPrimitives::setDrawColor4F(255, 255, 255, 1);
  DrawPrimitives::drawLine(*m_rayCastTool->GetStart(), *m_rayCastTool->GetEnd());
  Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

  BasicRUBELayer::onDraw(transform, flags);
}
