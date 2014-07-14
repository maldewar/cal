//  Author: Chris Campbell - www.iforce2d.net
//  -----------------------------------------
//
//  BasicRUBELayer
//
//  See header file for description.
//

#include "BasicRUBELayer.h"
#include "../util/b2dJson.h"
#include "../util/QueryCallbacks.h"

using namespace std;
using namespace cocos2d;

BasicRUBELayer::BasicRUBELayer()
{
    m_world = NULL;
    m_debugDraw = NULL;
    m_mouseJoint = NULL;
    m_mouseJointGroundBody = NULL;
    m_mouseJointTouch = NULL;
    m_debugDrawEnabled = false;

    m_worldCenter = b2Vec2(0,0);

    m_rotating = false;
    m_rotation = 0.0f;
    m_transitioning = false;
    m_transitionTemp = Vec2(0,0);
    m_transitionOrigin = Vec2(0,0);
    m_transitionTarget = Vec2(0,0);
    m_following = false;
    m_followingBody = nullptr;
}

BasicRUBELayer::~BasicRUBELayer()
{
    unscheduleUpdate();
    clear();
}

Scene* BasicRUBELayer::scene()
{
    auto scene = Scene::create();
    BasicRUBELayer* layer = BasicRUBELayer::create();
    scene->addChild(layer);
    return scene;
}

bool BasicRUBELayer::init()
{
    Layer::init();
    
    setTouchEnabled( true );
    setAccelerometerEnabled( true );    
    setAnchorPoint( Vec2(0,0) );
    
    // set the starting scale and offset values from the subclass
    setPosition( initialWorldOffset() );
    setScale( initialWorldScale() );
    
    // load the world from RUBE .json file (this will also call afterLoadProcessing)
    loadWorld();
    
    scheduleUpdate();
    setKeypadEnabled(true);
    
    return true;
}

b2World* BasicRUBELayer::getWorld() {
  return m_world;
}

void BasicRUBELayer::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    /*
    if ( keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE )
        goBack();
    */
}

// Override this in subclasses to specify which .json file to load
string BasicRUBELayer::getFilename()
{
    return "calaverasTemplate.json";
}


// Override this in subclasses to set the inital view position
Point BasicRUBELayer::initialWorldOffset()
{
    // This function should return the location in pixels to place
    // the (0,0) point of the physics world. The screen position
    // will be relative to the bottom left corner of the screen.
    
    //place (0,0) of physics world at center of bottom edge of screen
    Size s = Director::sharedDirector()->getWinSize();
    return CCPointMake( s.width/2, 0 );
}


// Override this in subclasses to set the inital view scale
float BasicRUBELayer::initialWorldScale()
{
    // This method should return the number of pixels for one physics unit.
    // When creating the scene in RUBE I can see that the jointTypes scene
    // is about 8 units high, so I want the height of the view to be about
    // 10 units, which for iPhone in landscape (480x320) we would return 32.
    // But for an iPad in landscape (1024x768) we would return 76.8, so to
    // handle the general case, we can make the return value depend on the
    // current screen height.
    
    Size s = Director::sharedDirector()->getWinSize();
    return s.height / 10; //screen will be 10 physics units high
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
    string fullpath = FileUtils::sharedFileUtils()->fullPathForFilename(filename.c_str());
    
    // This will print out the actual location on disk that the file is read from.
    // When using the simulator, exporting your RUBE scene to this folder means
    // you can edit the scene and reload it without needing to restart the app.
    log("Full path is: %s", fullpath.c_str());
    
    // Create the world from the contents of the RUBE .json file. If something
    // goes wrong, m_world will remain NULL and errMsg will contain some info
    // about what happened.
    b2dJson json;
    std::string errMsg;
    ssize_t fileSize = 0;
    unsigned char* fileData = FileUtils::sharedFileUtils()->getFileData(fullpath.c_str(), "r", &fileSize);
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
        m_debugDraw->SetFlags( b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_particleBit);
        m_world->SetDebugDraw(m_debugDraw);

        // This body is needed if we want to use a mouse joint to drag things around.
        b2BodyDef bd;
        m_mouseJointGroundBody = m_world->CreateBody( &bd );
        
        afterLoadProcessing(&json);
    }
    else
        log("%s",errMsg.c_str());
}


// Override this in subclasses to do some extra processing (eg. acquire references
// to named bodies, joints etc) after the world has been loaded, and while the b2dJson
// information is still available.
void BasicRUBELayer::afterLoadProcessing(b2dJson* json)
{
}

// This method should undo anything that was done by the loadWorld and afterLoadProcessing
// methods, and return to a state where loadWorld can safely be called again.
void BasicRUBELayer::clear()
{
    if ( m_world ) {
        log("Deleting Box2D world");
        delete m_world;
    }
    
    if ( m_debugDraw )
        delete m_debugDraw;
    
    m_world = NULL;
    m_mouseJoint = NULL;
    m_mouseJointGroundBody = NULL;
}


// Standard Cocos2d method, just step the physics world with fixed time step length
void BasicRUBELayer::update(float dt)
{
  if ( m_world )
    m_world->Step(1/60.0, 8, 3);
  CCLayer::update(dt);

  if (m_rotating) {
    m_transitionLapse += dt;
    if (m_transitionLapse > m_transitionDuration) {
      m_rotation = m_rotationTarget;
      m_rotating = false;
      //setRotation(CC_RADIANS_TO_DEGREES(-m_rotation));
      setCenteredRotation(m_rotation);
    } else {
      m_rotation = ((m_rotationTarget - m_rotationOrigin) * (m_transitionLapse / m_transitionDuration)) + m_rotationOrigin;
      //setRotation(CC_RADIANS_TO_DEGREES(-m_rotation));
      setCenteredRotation(m_rotation);
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
  }


  // Standard Cocos2d method
  void BasicRUBELayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
  {
    Layer::draw(renderer, transform, flags);
    m_customCommand.init(_globalZOrder + 1);
  m_customCommand.func = CC_CALLBACK_0(BasicRUBELayer::onDraw, this, transform, flags);
  renderer->addCommand(&m_customCommand);
}

void BasicRUBELayer::onDraw(const cocos2d::Mat4 &transform, uint32_t flags) {
    if ( !m_world )
        return;
    // debug draw display will be on top of anything else
    //Layer::draw(renderer, transform, flags);

    if (m_debugDrawEnabled) {   
      //ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
      //kmGLPushMatrix();
      Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
      Director::getInstance()->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
      
      
      m_world->DrawDebugData();
      
      // Draw mouse joint line
      if ( m_mouseJoint ) {
          b2Vec2 p1 = m_mouseJoint->GetAnchorB();
          b2Vec2 p2 = m_mouseJoint->GetTarget();
          
          b2Color c;
          c.Set(0.0f, 1.0f, 0.0f);
          m_debugDraw->DrawPoint(p1, 4.0f, c);
          m_debugDraw->DrawPoint(p2, 4.0f, c);
          
          c.Set(0.8f, 0.8f, 0.8f);
          m_debugDraw->DrawSegment(p1, p2, c);
      }
      
      //kmGLPopMatrix();
      Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    }
}


// Converts a position in screen pixels to a location in the physics world
b2Vec2 BasicRUBELayer::screenToWorld(cocos2d::Point screenPos)
{
    screenPos.y = Director::sharedDirector()->getWinSize().height - screenPos.y;
    
    Point layerOffset = getPosition();
    screenPos.x -= layerOffset.x;
    screenPos.y -= layerOffset.y;
    
    float scale = getScale();
    float angleSin = sin(m_rotation);
    float angleCos = cos(m_rotation);
    
    b2Vec2 worldPoint = b2Vec2((screenPos.x * angleCos + screenPos.y * angleSin) / scale,
                               (screenPos.y * angleCos - screenPos.x * angleSin) / scale);
    return worldPoint;
}


// Converts a location in the physics world to a position in screen pixels
cocos2d::Point BasicRUBELayer::worldToScreen(b2Vec2 worldPos)
{
    // TODO
    worldPos *= getScale();
    Point layerOffset = getPosition();
    Point p = CCPointMake(worldPos.x + layerOffset.x, worldPos.y + layerOffset.y);
    p.y = Director::sharedDirector()->getWinSize().height - p.y;
    return p;
}


// Standard Cocos2d method. Here we make a mouse joint to drag dynamic bodies around.
void BasicRUBELayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
    // Only make one mouse joint at a time!
    if ( m_mouseJoint )
        return;
    
    Touch *touch = touches[0];
    Point screenPos = touch->getLocationInView();
    b2Vec2 worldPos = screenToWorld(screenPos);
    //CCLOG("Touches began at wx:%f wy:%f sx:%f sy:%f", worldPos.x, worldPos.y, screenPos.x, screenPos.y);
    
    // Make a small box around the touched point to query for overlapping fixtures
    b2AABB aabb;
    b2Vec2 d(0.001f, 0.001f);
    aabb.lowerBound = worldPos - d;
    aabb.upperBound = worldPos + d;
    
    // Query the world for overlapping fixtures (the TouchDownQueryCallback simply
    // looks for any fixture that contains the touched point)
    TouchDownQueryCallback callback(worldPos);
    m_world->QueryAABB(&callback, aabb);
    
    // Check if we found something, and it was a dynamic body (can't drag static bodies)
    if (callback.m_fixture && callback.m_fixture->GetBody()->GetType() == b2_dynamicBody)
    {
        // The touched point was over a dynamic body, so make a mouse joint
        b2Body* body = callback.m_fixture->GetBody();
        b2MouseJointDef md;
        md.bodyA = m_mouseJointGroundBody;
        md.bodyB = body;
        md.target = worldPos;
        md.maxForce = 2500.0f * body->GetMass();
        m_mouseJoint = (b2MouseJoint*)m_world->CreateJoint(&md);
        body->SetAwake(true);
        m_mouseJointTouch = touch;
    }
}


// Standard Cocos2d method
void BasicRUBELayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
    if ( touches.size() > 1 ) {
        // At least two touches are moving at the same time
        if ( ! allowPinchZoom() )
            return;
        
        // Take the first two touches and use their movement to pan and zoom the scene.
        Touch *touch0 = touches[0];
        Touch *touch1 = touches[1];
        Point screenPos0 = touch0->getLocationInView();
        Point screenPos1 = touch1->getLocationInView();
        Point previousScreenPos0 = touch0->getPreviousLocationInView();
        Point previousScreenPos1 = touch1->getPreviousLocationInView();
        
        Point layerOffset = getPosition();
        float layerScale = getScale();
        
        // Panning
        // The midpoint is the point exactly between the two touches. The scene
        // should move by the same distance that the midpoint just moved.
        Point previousMidpoint = ccpMidpoint(previousScreenPos0, previousScreenPos1);
        Point currentMidpoint = ccpMidpoint(screenPos0, screenPos1);
        Point moved = ccpSub(currentMidpoint, previousMidpoint);
        moved.y *= -1;
        layerOffset = ccpAdd(layerOffset, moved);

        // Zooming
        // The scale should change by the same ratio as the previous and current
        // distance between the two touches. Unfortunately simply setting the scale
        // has the side-effect of moving the view center. We want to keep the midpoint
        // of the touches unchanged by scaling, so we need to look at what it was
        // before we scale...
        b2Vec2 worldCenterBeforeScaling = screenToWorld(currentMidpoint);
        
        // ... then perform the scale change...
        float previousSeparation = ccpDistance(previousScreenPos0, previousScreenPos1);
        float currentSeparation = ccpDistance(screenPos0, screenPos1);
        if ( previousSeparation > 10 ) { //just in case, prevent divide by zero
            layerScale *= currentSeparation / previousSeparation;
            setScale(layerScale);
        }

        // ... now check how that affected the midpoint, and cancel out the change:
        Point screenCenterAfterScaling = worldToScreen(worldCenterBeforeScaling);
        Point movedCausedByScaling = ccpSub(screenCenterAfterScaling, currentMidpoint);
        movedCausedByScaling.y *= -1;
        layerOffset = ccpSub(layerOffset, movedCausedByScaling);       
        
        setPosition(layerOffset);
    }
    else if ( m_mouseJoint ) {
        // Only one touch is moving. If it is the touch that started the mouse joint
        // move the target position of the mouse joint to the new touch position
        Touch *touch = touches[0];
        if ( touch == m_mouseJointTouch ) {
            Point screenPos = touch->getLocationInView();
            b2Vec2 worldPos = screenToWorld(screenPos);
            m_mouseJoint->SetTarget(worldPos);
        }
    }
}


// Standard Cocos2d method
void BasicRUBELayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
    Touch *touch = touches[0];
    Point screenPos = touch->getLocationInView();
    b2Vec2 worldPos = screenToWorld(screenPos);
    CCLOG("Touches ended at wx:%f wy:%f sx:%f sy:%f", worldPos.x, worldPos.y, screenPos.x, screenPos.y);
    // Check if one of the touches is the one that started the mouse joint.
    // If so we need to destroy the mouse joint and reset some variables.
    if ( m_mouseJoint ) {
        for (int i = 0; i < touches.size(); i++) {
            Touch* touch = touches[i];
            if ( touch != m_mouseJointTouch )
                continue;
            m_world->DestroyJoint(m_mouseJoint);
            m_mouseJoint = NULL;
            m_mouseJointTouch = NULL;
            break;
        }
    } else {
      //Try LiquidFun
      /*
      const b2ParticleSystemDef particleSystemDef;
      m_particleSystems[0] = m_world->CreateParticleSystem(&particleSystemDef);
      b2ParticleGroupDef pd;
      b2PolygonShape shape;
      shape.SetAsBox(10, 5);
      pd.shape = &shape;
      pd.flags = b2_elasticParticle;
      pd.angle = -0.5f;
      pd.angularVelocity = 2.0f;
      pd.position.Set(10 + 20 * 2, 40);
      pd.color.Set(2 * 255 / 5, 255 - 2 * 255 / 5, 128, 255);
      m_particleSystems[0]->CreateParticleGroup(pd);
      */

      /*
      b2ParticleSystemDef particleSystemDef;
      particleSystemDef.dampingStrength = 0.2f;
      particleSystemDef.radius = 0.3f;
      _particleSystem = m_world->CreateParticleSystem(&particleSystemDef);
      _particleSystem->SetGravityScale(0.4f);
      _particleSystem->SetDensity(1.2f);
      _particleSystem->SetRadius(0.15f);

      b2ParticleGroupDef pd;
      //pd.flags = b2_waterParticle | b2_colorMixingParticle;
      //pd.flags = b2_solidParticleGroup;
      pd.flags = b2_solidParticleGroup | b2_elasticParticle;
      pd.color.Set(30, 64, 194, 255);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.5f, 0.5f, b2Vec2(0.0f, 0.0f), 0.0);

      pd.shape = &shape2;
      _particleSystem->CreateParticleGroup(pd);
      */

    }
}


// Standard Cocos2d method
void BasicRUBELayer::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
    onTouchesEnded(touches, event);
}

b2Fixture* BasicRUBELayer::getTouchedFixture(Touch* touch)
{
    Point screenPos = touch->getLocationInView();
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

bool BasicRUBELayer::allowPinchZoom()
{
    return true;
}

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

void BasicRUBELayer::follow(b2Body* body, float transitionTime) {
  m_worldCenter.x = body->GetPosition().x;
  m_worldCenter.y = body->GetPosition().y;
  m_following = true;
  m_followingBody = body;
  m_transitionDuration = transitionTime;
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
  //CCLOG("World x:%F y=%f Offset x=%f y=%f angle=%f sin=%f cos=%f scale:%f", m_worldCenter.x, m_worldCenter.y, center.x, center.y, m_rotation, angleSin, angleCos, scale);
  return center;
}

void BasicRUBELayer::rotate(float angle, float transitionTime) {
  if (transitionTime > 0) {
    m_rotating = true;
    m_rotationOrigin = CC_DEGREES_TO_RADIANS(-getRotation());
    m_rotationTarget = angle;
    CCLOG("ORIGIN:%f TARGET:%f", m_rotationOrigin, m_rotationTarget);
    m_transitionLapse = 0;
    m_transitionDuration = transitionTime;
  } else {
    m_rotation = angle;
    setRotation(CC_RADIANS_TO_DEGREES(-m_rotation));
  }
}

void BasicRUBELayer::setCenteredRotation(float rotation) {
  setRotation(CC_RADIANS_TO_DEGREES(-rotation));
  Vec2 position = getCenteredPosition(m_worldCenter.x, m_worldCenter.y);
  setPosition(position);
}
