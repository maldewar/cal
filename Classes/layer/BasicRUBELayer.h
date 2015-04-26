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
#include <string>

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "BaseLayer.h"
#include "../model/WorldLayerDef.h"
#include "../util/Box2DDebugDraw.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"

#ifndef BASIC_RUBE_LAYER
#define BASIC_RUBE_LAYER

class b2dJson;

class BasicRUBELayer : public BaseLayer
{
protected:
  b2World* m_world;
  std::string m_filename;
  // Used to draw debug data.
  Box2DDebugDraw* m_debugDraw;
  // Used when dragging bodies around.
  b2MouseJoint* m_mouseJoint;
  // The other body for the mouse joint (static, no fixtures).
  b2Body* m_mouseJointGroundBody;
  // Keep track of which touch started the mouse joint.
  cocos2d::Touch* m_mouseJointTouch;

  b2Vec2 m_worldCenter;

  bool m_rotating;
  float m_rotation;
  float m_rotationOrigin;
  float m_rotationTarget;
  float m_cosRotation;
  float m_sinRotation;
  bool m_bodyTouchBegan;
  bool m_worldTouchBegan;

  bool m_transitioning;
  float m_transitionDuration;
  float m_transitionLapse;
  cocos2d::Vec2 m_transitionTemp;
  cocos2d::Vec2 m_transitionOrigin;
  cocos2d::Vec2 m_transitionTarget;

  bool m_following;
  b2Body* m_followingBody;
  bool m_paused;

  bool m_debugDrawEnabled;
  cocos2d::CustomCommand m_customCommand;
  //std::vector<b2ParticleSystem*> m_particleSystems;
  //b2ParticleSystem* _particleSystem;

  float m_wToPx;
  float m_pxToW;

protected:
  virtual void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);
  /**
   * Gets the offset point to set the layer position centered around a
   * world coordinate.
   * @param worldX X world coordinate.
   * @param worldY Y world coordinate.
   * @return Offset point in screen units.
   */
  virtual cocos2d::Vec2 getCenteredPosition(float worldX, float worldY);
  virtual void setCenteredRotation(float rotation);
  virtual void pauseChildrenRecursive(cocos2d::Node* node, bool pause);
  virtual void setCenter();
        
public:
  BasicRUBELayer();
  virtual ~BasicRUBELayer();
  static cocos2d::Scene* scene();
  virtual bool init(BaseScene* parent, WorldLayerDef* worldLayerDef);
  virtual void onEnter();
  virtual void onExit();
  virtual void setRotation(float degrees) override;
  virtual b2World* getWorld();
  // Override to specify which JSON file to load.
  virtual std::string getFilename();
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
  virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches,
                              cocos2d::Event *unused_event);
  virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches,
                              cocos2d::Event *unused_event);
  virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches,
                                  cocos2d::Event *unused_event);
  virtual void onBodyTouchBegan(b2Body* body, b2Fixture* fixture);
  virtual void onWorldTouchBegan(b2Vec2& position);
  virtual void onBodyTouchEnded();
  virtual void onWorldTouchEnded();
  // Return the first fixture found under the touch location.
  b2Fixture* getTouchedFixture(cocos2d::Touch* touch);
  virtual bool enableDebugDraw(bool enable);
  /**
   * Center the view of the layer to this point.
   * @param x X world coordinate.
   * @param y Y world coordinate.
   * @param time Seconds to transition to the target.
   */
  virtual void centerPoint(float x, float y, float time = 0.0f);
  /**
   * Centers the view to the center of a body.
   * @param body Box2D body.
   * @param time Seconds to transition to the target.
   */
  virtual void centerBody(b2Body* body, float time = 0.0f);
  /**
   * Transition of the view from an origin to a target point.
   * @param origin Initial point in world coordinates.
   * @param target Target point in world coordinates.
   * @param time Seconds to transition to the target.
   */
  virtual void transition(cocos2d::Vec2 origin, cocos2d::Vec2 target, float time);
  /**
   * Cancel any ongoing transition.
   */
  virtual void cancelTransition();
  /**
   * Maintains the view centered around a body.
   * @param body Box2D body to follow.
   * @param time Seconds to transition to the target.
   */
  virtual void follow(b2Body* body, float time = 0);
  /**
   * Cancel any ongoing follow up to a body.
   */
  virtual void cancelFollow();
  virtual void pause(bool pause);
  virtual bool isPaused();
  virtual bool scale(float factor);
  //virtual bool rotate(float angle);

};

#endif /* BASIC_RUBE_LAYER */


