//  Author: Chris Campbell - heavily modified by Maldewar
//  -----------------------------------------
//
//  BasicRUBELayer
//
//  See header file for description.
//

#include "BasicRUBELayer.h"
#include "../util/b2dJson.h"
#include "../util/b2dJsonImage.h"
#include "../util/MultiQueryCallbacks.h"
#include "../util/CMath.h"
#include "../model/ImageNode.h"
#include "../model/ImageBody.h"
#include "../model/Entity.h"

using namespace std;
using namespace cocos2d;

BasicRUBELayer::BasicRUBELayer() : BaseLayer() {
  m_world     = NULL;
  m_filename  = "";
  m_debugDraw = NULL;
  m_debugDrawEnabled  = false;

  m_worldCenter = b2Vec2(0,0);

  m_rotating = false;
  m_rotation = 0.0f;
  m_cosRotation = 1;
  m_sinRotation = 0;
  m_transitioning    = false;
  m_transitionTemp   = Vec2(0,0);
  m_transitionOrigin = Vec2(0,0);
  m_transitionTarget = Vec2(0,0);
  m_following = false;
  m_followingBody = nullptr;
  m_paused = false;

  m_bodyTouchBegan = false;
  m_worldTouchBegan = false;

  m_wToPx = m_winSize.height / 2;
  m_pxToW = 1/m_wToPx;
}

BasicRUBELayer::~BasicRUBELayer() {
}

bool BasicRUBELayer::init(BaseScene* parent, WorldLayerDef* worldLayerDef) {
  if (! BaseLayer::init(worldLayerDef)) {
    return false;
  }
  setParentScene(parent);
  m_filename = worldLayerDef->getPath();
  scale(1);
  loadWorld();
  return true;
}

void BasicRUBELayer::onEnter() {
  Layer::onEnter();
  scheduleUpdate();
}

void BasicRUBELayer::onExit() {
  unscheduleUpdate();
  clear();
  Layer::onExit();
}

void BasicRUBELayer::setRotation(float degrees) {
  m_rotation = CMath::wrapPosNegPI(CC_DEGREES_TO_RADIANS(-degrees));
  Layer::setRotation(CC_RADIANS_TO_DEGREES(-m_rotation));
  m_cosRotation = cos(m_rotation);
  m_sinRotation = sin(m_rotation);
}

b2World* BasicRUBELayer::getWorld() {
  return m_world;
}

// Override this in subclasses to specify which .json file to load
string BasicRUBELayer::getFilename()
{
    return m_filename;
}

// Attempts to load the world from the .json file given by getFilename.
// If successful, the method afterLoadProcessing will also be called,
// to allow subclasses to do something extra while the b2dJson information
// is still available.
void BasicRUBELayer::loadWorld()
{
  // The clear method should undo anything that is done in this method,
  // and also whatever is done in the afterLoadProcessing method.
  clear();
  
  // Get the name of the .json file to load, eg. "jointTypes.json"
  string filename = getFilename();
  
  // Find out the absolute path for the file
  string fullpath = FileUtils::getInstance()->fullPathForFilename(filename.c_str());
  
  // Create the world from the contents of the RUBE .json file. If something
  // goes wrong, m_world will remain NULL and errMsg will contain some info
  // about what happened.
  b2dJson json;
  std::string errMsg;
  ssize_t fileSize = 0;
  unsigned char* fileData = FileUtils::getInstance()->getFileData(fullpath.c_str(), "r", &fileSize);
  std::string jsonContent;
  jsonContent.assign(reinterpret_cast<const char*>(fileData), fileSize);
  m_world = json.readFromString(jsonContent, errMsg);
  
  if ( m_world ) {
    // Set up a debug draw so we can see what's going on in the physics engine.
    // The scale for rendering will be handled by the layer scale, which will affect
    // the entire layer, so we keep the PTM ratio here to 1 (ie. one physics unit
    // will be one pixel)
    m_debugDraw = new Box2DDebugDraw(1);
      
    // set the debug draw to show fixtures, and let the world know about it
    //m_debugDraw->SetFlags( b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_particleBit);
    m_debugDraw->SetFlags( b2Draw::e_shapeBit | b2Draw::e_jointBit);
    m_world->SetDebugDraw(m_debugDraw);
      
    afterLoadProcessing(&json);
  }
  else
    log("%s",errMsg.c_str());
}


// Override this in subclasses to do some extra processing (eg. acquire references
// to named bodies, joints etc) after the world has been loaded, and while the b2dJson
// information is still available.
void BasicRUBELayer::afterLoadProcessing(b2dJson* json) {
  // Process images
  std::vector<b2dJsonImage*> b2dImages;
  json->getAllImages(b2dImages);
  for (int i = b2dImages.size() - 1; i >= 0; i--) {
    b2dJsonImage* image = b2dImages[i]; 
    if (image->body) {
      ImageBody* imageBody = ImageBody::create(image->file, 
                                               image->body);
      if (!imageBody) {
        continue;
      }
      imageBody->setPositionZ(image->renderOrder);
      addChild(imageBody);
    } else {
      ImageNode* imageNode = ImageNode::create(image->file);
      if (!imageNode) {
        continue;
      }
      imageNode->getSprite()->setFlipX(image->flip);
      imageNode->getSprite()->setColor(ccc3(image->colorTint[0],
                                            image->colorTint[1],
                                            image->colorTint[2]));
      imageNode->getSprite()->setOpacity(image->colorTint[3]);
      Size size = imageNode->getSprite()->getContentSize();
      float sizeRatio = size.height / 540.0f; // 840
      float spriteScale = image->scale / sizeRatio;
      imageNode->getSprite()->setScale(spriteScale);
      Point pos = cocos2d::Vec2(image->center.x,
                                image->center.y);
      b2Vec2 localPos( pos.x, pos.y );
      pos.x = localPos.x;
      pos.y = localPos.y;
      imageNode->setRotation( CC_RADIANS_TO_DEGREES(-image->angle) );
      imageNode->setPosition( pos );
      imageNode->setPositionZ(image->renderOrder);
      addChild(imageNode, image->renderOrder);
    }
  }
}

// This method should undo anything that was done by the loadWorld and afterLoadProcessing
// methods, and return to a state where loadWorld can safely be called again.
void BasicRUBELayer::clear() {
    if ( m_world ) {
        log("Deleting Box2D world");
        delete m_world;
    }
    
    if ( m_debugDraw )
        delete m_debugDraw;
    
    m_world = NULL;
}


// Standard Cocos2d method, just step the physics world with fixed time step length
void BasicRUBELayer::update(float dt)
{
  BaseLayer::update(dt);
  if (!m_paused) {
    if ( m_world ) {
      m_world->Step(1/60.0f, 8, 3);
    }
  }
  /*
  if (!m_paused) {
    if ( m_world )
      m_world->Step(1/60.0, 8, 3);
    CCLayer::update(dt);
  }

  if (m_rotating) {
    m_transitionLapse += dt;
    if (m_transitionLapse > m_transitionDuration) {
      m_rotating = false;
      setCenteredRotation(m_rotationTarget);
    } else {
      setCenteredRotation(((m_rotationTarget - m_rotationOrigin) * (m_transitionLapse / m_transitionDuration)) + m_rotationOrigin);
    }
  } else {
    if (m_following) {
      if (m_transitionLapse > m_transitionDuration) {
        setPosition(this->getCenteredPosition(m_followingBody->GetPosition().x, m_followingBody->GetPosition().y));
      } else {
        m_transitionLapse += dt;
        m_transitionTarget = this->getCenteredPosition(m_followingBody->GetPosition().x, m_followingBody->GetPosition().y);
        m_transitionTemp.x = ((m_transitionTarget.x - m_transitionOrigin.x) * (m_transitionLapse/m_transitionDuration)) + m_transitionOrigin.x;
        m_transitionTemp.y = ((m_transitionTarget.y - m_transitionOrigin.y) * (m_transitionLapse/m_transitionDuration)) + m_transitionOrigin.y;
        setPosition(m_transitionTemp);
      }
    } else {
      if (m_transitioning) {
        m_transitionLapse += dt;
        if (m_transitionLapse > m_transitionDuration) {
          m_transitioning = false;
          setPosition(m_transitionTarget);
        } else {
          m_transitionTemp.x = ((m_transitionTarget.x - m_transitionOrigin.x) * (m_transitionLapse/m_transitionDuration)) +   m_transitionOrigin.x;
          m_transitionTemp.y = ((m_transitionTarget.y - m_transitionOrigin.y) * (m_transitionLapse/m_transitionDuration)) +   m_transitionOrigin.y;
          setPosition(m_transitionTemp);
        }
      }
    }
  }
  */
}


// Standard Cocos2d method
void BasicRUBELayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) {
  Layer::draw(renderer, transform, flags);
  m_customCommand.init(_globalZOrder + 1);
  m_customCommand.func = CC_CALLBACK_0(BasicRUBELayer::onDraw, this, transform, flags);
  renderer->addCommand(&m_customCommand);
}

void BasicRUBELayer::onDraw(const cocos2d::Mat4 &transform, uint32_t flags) {
    if ( !m_world )
        return;
    // debug draw display will be on top of anything else
    if (m_debugDrawEnabled) {   
      Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
      Director::getInstance()->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
      m_world->DrawDebugData();
      Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    }
}


// Converts a position in screen pixels to a location in the physics world
b2Vec2 BasicRUBELayer::screenToWorld(cocos2d::Point screenPos)
{
  Point nodeSpace = convertToNodeSpace(screenPos);
  return b2Vec2(nodeSpace.x, nodeSpace.y);
}


// Converts a location in the physics world to a position in screen pixels
cocos2d::Point BasicRUBELayer::worldToScreen(b2Vec2 worldPos)
{
  cocos2d::Point position = convertToWorldSpaceAR(cocos2d::Point(worldPos.x, worldPos.y));
  position.x -= 960;
  position.y -= 540;
  cocos2d::Point newPos = cocos2d::Point((position.x * m_cosRotation + position.y * m_sinRotation),
                                         (position.y * m_cosRotation - position.x * m_sinRotation));
  return newPos;
  /*
    Point layerOffset = getPosition();
    worldPos *= getScale();
    //
    // Rotation Matrix for counterclockwise angles, transposed to inverse
    // | cosA -sinA | |x|
    // | sinA  cosA | |y|
    ///
    Point p = Point((worldPos.x * m_cosRotation - worldPos.y * m_sinRotation) + layerOffset.x,
                    (worldPos.y * m_cosRotation + worldPos.x * m_sinRotation) + layerOffset.y);

    return p;
    */
}


// Standard Cocos2d method. Here we make a mouse joint to drag dynamic bodies around.
void BasicRUBELayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event) {
  if (touches.size() == 1) {
    Touch *touch = touches[0];
    Point screenPos = touch->getLocation();
    b2Vec2 worldPos = screenToWorld(screenPos);

    // Make a small box around the touched point to query for overlapping fixtures
    b2AABB aabb;
    b2Vec2 d(0.001f, 0.001f);
    aabb.lowerBound = worldPos - d;
    aabb.upperBound = worldPos + d;

    // Query the world for overlapping fixtures (the TouchDownQueryCallback simply
    // looks for any fixture that contains the touched point)
    TouchDownMultiQueryCallback callback(worldPos);
    m_world->QueryAABB(&callback, aabb);

    // Check if we found something, and it was a dynamic body (can't drag static bodies)
    if (callback.hasTouch()) {
      m_bodyTouchBegan = true;
      onBodyTouchBegan(callback.getBodies(), callback.getFixtures());
    } else {
      m_worldTouchBegan = true;
      onWorldTouchBegan(worldPos);
    }
  }
}

// Standard Cocos2d method
void BasicRUBELayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
  Touch *touch = touches[0];
  Point screenPos = touch->getLocation();
  b2Vec2 worldPos = screenToWorld(screenPos);
  if (m_bodyTouchBegan) {
    m_bodyTouchBegan = false;
    onBodyTouchEnded();
  }
  if (m_worldTouchBegan) {
    m_worldTouchBegan = false;
    onWorldTouchEnded();
  }
}

// Standard Cocos2d method
void BasicRUBELayer::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
  onTouchesEnded(touches, event);
}

void BasicRUBELayer::onBodyTouchBegan(std::vector<b2Body*> bodies, std::vector<b2Fixture*> fixtures) {
}

void BasicRUBELayer::onWorldTouchBegan(b2Vec2& position) {
}

void BasicRUBELayer::onBodyTouchEnded() {
}

void BasicRUBELayer::onWorldTouchEnded() {
}

/*
b2Fixture* BasicRUBELayer::getTouchedFixture(Touch* touch)
{
    Point screenPos = touch->getLocation();
    b2Vec2 worldPos = screenToWorld(screenPos);
    
    // Make a small box around the touched point to query for overlapping fixtures
    b2AABB aabb;
    b2Vec2 d(0.001f, 0.001f);
    aabb.lowerBound = worldPos - d;
    aabb.upperBound = worldPos + d;
    TouchDownQueryCallback callback(worldPos);
    m_world->QueryAABB(&callback, aabb);
    return callback.m_fixture;
}
*/

bool BasicRUBELayer::enableDebugDraw(bool enable) {
  m_debugDrawEnabled = enable;
  return m_debugDrawEnabled;
}

void BasicRUBELayer::centerPoint(float x, float y, float time) {
  Vec2 centerPosition = getCenteredPosition(x, y);
  if (time > 0) {
    transition(getPosition(), centerPosition, time);
  } else {
    setPosition(centerPosition);
  }
}

void BasicRUBELayer::centerBody(b2Body* body, float time) {
  centerPoint(body->GetPosition().x, body->GetPosition().y, time);
}

void BasicRUBELayer::transition(Vec2 origin, Vec2 target, float time) {
  m_transitioning = true;
  m_transitionDuration = time;
  m_transitionLapse = 0.0f;
  m_transitionOrigin = origin;
  m_transitionTarget = target;
}

void BasicRUBELayer::cancelTransition() {
  m_transitioning = false;
}

void BasicRUBELayer::follow(b2Body* body, float time) {
  m_worldCenter.x = body->GetPosition().x;
  m_worldCenter.y = body->GetPosition().y;
  m_following = true;
  m_followingBody = body;
  m_transitionDuration = time;
  m_transitionLapse = 0;
  m_transitionOrigin = getPosition();
}

void BasicRUBELayer::cancelFollow() {
  m_following = false;
}

cocos2d::Vec2 BasicRUBELayer::getCenteredPosition(float worldX, float worldY) {
  float angleSin = sin(m_rotation);
  float angleCos = cos(m_rotation);
  float scale = getScale();
  Vec2 center = Vec2(960 - (worldX * angleCos - worldY * angleSin) * scale,
                     540 - (worldY * angleCos + worldX * angleSin) * scale);
  return center;
}

void BasicRUBELayer::setCenteredRotation(float rotation) {
  setRotation(CC_RADIANS_TO_DEGREES(-rotation));
  Vec2 position = getCenteredPosition(m_worldCenter.x, m_worldCenter.y);
  setPosition(position);
}

void BasicRUBELayer::pause(bool pause) {
  m_paused = pause;
  for (auto child : getChildren()) {
    pauseChildrenRecursive(child, m_paused);
  }
}

bool BasicRUBELayer::isPaused() {
  return m_paused;
}

void BasicRUBELayer::pauseChildrenRecursive(cocos2d::Node* node, bool pause) {
  if (pause) {
    node->pauseSchedulerAndActions();
  } else {
    node->resumeSchedulerAndActions();
  }
  for (auto child : node->getChildren()) {
    pauseChildrenRecursive(child, pause);
  }
}

void BasicRUBELayer::setCenter() {
  setAnchorPoint(cocos2d::Vec2(m_position.x/(m_size.width * getScale()), m_position.y/(m_size.height*getScale())));
}

bool BasicRUBELayer::scale(float factor) {
  if (m_scaleEnabled) {
    m_scale = factor;
    setScale(m_scale * m_wToPx);
    if (m_isMain && m_parent) {
      m_parent->scaleCallback(m_scale, this);
    }
    return true;
  }
  return false;
}

//bool BasicRUBELayer::rotate(float angle) {
  /*
  if (transitionTime > 0) {
    m_rotating = true;
    m_rotationOrigin = CMath::wrapPosNegPI(CC_DEGREES_TO_RADIANS(-getRotation()));
    m_rotationTarget = CMath::wrapPosNegPI(angle);
    if (m_rotationOrigin > 0 && m_rotationTarget < 0) {
      if (m_rotationOrigin + -m_rotationTarget > M_PI) {
        m_rotationTarget += M_PI * 2;
      }
    } else if (m_rotationTarget > 0 && m_rotationOrigin < 0) {
      if (m_rotationTarget + -m_rotationOrigin > M_PI) {
        m_rotationOrigin += M_PI * 2;
      }
    }
    m_transitionLapse = 0;
    m_transitionDuration = transitionTime;
  } else {
    setRotation(CC_RADIANS_TO_DEGREES(-angle));
  }
  */
  /*
  if (BaseLayer::rotate(angle)) {
    setRotation(CC_RADIANS_TO_DEGREES(-angle));
    return true;
  }*/
  //if (BaseLayer::rotate(angle)) {
    //return true;
  //}
  //return false;
//}
