//  Author: Chris Campbell - www.iforce2d.net
//  -----------------------------------------
//
//  BasicRUBELayer
//
//  This class extends Layer to load in a RUBE scene file on init.
//  It uses the debug draw display to show the scene, and  does not
//  load any images. The touch methods are used to zoom, pan, and to
//  create a mouse joint to drag dynamic bodies around.
//
//  This class is mostly here to keep the first example simple, and
//  concentrate on getting positions and scales correct before any
//  images are involved. In most cases you would subclass RUBELayer
//  to make a more useful layer.
//
//  The scene file to load, and the initial position and scale are
//  given by methods which should be overridden in subclasses.
//
//  The position of the layer is set with setPosition(Point)
//  and specifies the location on screen where 0,0 in the physics world
//  will be located, in pixels. Hence you can check anytime where the
//  (0,0) point of the physics world is with getPosition()
//
//  The scale of the layer is the number of pixels for one physics unit.
//  Eg. if the screen is 320 pixels high and you want it to be 10 units
//  high in the physics world, the scale would be 32. You can set this
//  with [self setScale:(float)] and check it with [self scale].
//
//  This class provides the screenToWorld and worldToScreen methods
//  which are invaluable when converting locations between screen and
//  physics world coordinates.
//

#include <vector>

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "../util/Box2DDebugDraw.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"

#ifndef BASIC_RUBE_LAYER
#define BASIC_RUBE_LAYER

class b2dJson;

class BasicRUBELayer : public cocos2d::Layer
{
protected:
    b2World* m_world;
    // Used to draw debug data.
	  Box2DDebugDraw* m_debugDraw;
    // Used when dragging bodies around.
    b2MouseJoint* m_mouseJoint;
    // The other body for the mouse joint (static, no fixtures).
    b2Body* m_mouseJointGroundBody;
    // Keep track of which touch started the mouse joint.
    cocos2d::Touch* m_mouseJointTouch;
    bool m_debugDrawEnabled;
    cocos2d::CustomCommand m_customCommand;
    std::vector<b2ParticleSystem*> m_particleSystems;
    b2ParticleSystem* _particleSystem;

protected:
  void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);
        
public:
    BasicRUBELayer();
    virtual ~BasicRUBELayer();
    static cocos2d::Scene* scene();
    virtual bool init();
    CREATE_FUNC(BasicRUBELayer);
    virtual b2World* getWorld();
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    // Override to specify which JSON file to load.
    virtual std::string getFilename();
    // Override to set the initial view position.
    virtual cocos2d::Point initialWorldOffset();
    // Override to set the initial view scale.
    virtual float initialWorldScale();
    virtual void loadWorld();
    // Override to do something after loading the world (before discarding JSON info)
    virtual void afterLoadProcessing(b2dJson* json);
    virtual void clear();
    // Converts a position in screen pixels to a location in the physics world.
    virtual b2Vec2 screenToWorld(cocos2d::Point screenPos);
    // Converts a location in the physics world to a position in screen pixels.
    virtual cocos2d::Point worldToScreen(b2Vec2 worldPos);
    virtual void update(float dt);
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
    
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    // Return the first fixture found under the touch location.
    b2Fixture* getTouchedFixture(cocos2d::Touch* touch);
    // Return false from this function to prevent punch zoom and pan.
    virtual bool allowPinchZoom();
    virtual bool enableDebugDraw(bool enable);
};

#endif /* BASIC_RUBE_LAYER */


