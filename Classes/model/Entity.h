#ifndef __ENTITY_NODE_H__
#define __ENTITY_NODE_H__

#include <unordered_map>
#include <string>
#include "cocos2d.h"
#include <spine/spine-cocos2dx.h>
#include "Box2D/Box2D.h"
#include "2d/CCNode.h"
#include "../manager/ConfigurationManager.h"
#include "../layer/WorldLevelLayer.h"
class WorldLevelLayer;

const int ENTITY_TYPE_UNIT  = 1;
const int ENTITY_TYPE_ENTRY = 2;
const int ENTITY_TYPE_AREA  = 3;
const int ENTITY_TYPE_EXIT  = 4;
const int ENTITY_TYPE_GRAVITRON = 5;
const int ENTITY_TYPE_IMAGE = 6;
const int ENTITY_TYPE_IMAGE_BODY = 7;
const int ENTITY_TYPE_LEVEL = 8;
const int ENTITY_TYPE_BRANCH = 9;
const int ENTITY_TYPE_DRAGGABLE = 10;

const int ENTITY_ANIM_STAND = 0;
const int ENTITY_ANIM_WALK  = 1;
const int ENTITY_ANIM_FALL  = 2;

class Entity : public cocos2d::Node
{
protected:
  std::string m_id;
  WorldLevelLayer* m_worldLayer;
  b2Body* m_body;
  spine::SkeletonAnimation* m_skeletonNode;
  float m_width;
  float m_height;
  static std::unordered_map<int, int> m_ids;
  int m_animation;
  int m_skin;
  bool m_shapeDrawEnabled;
  cocos2d::Color4F m_color;
  int m_zOrderDraw;
  int m_zOrderTouch;

public:
  /**
   * Class constructor.
   */
  Entity(void);
  /**
   * Class destructor.
   */
  virtual ~Entity(void);
  virtual void setId(std::string id);
  virtual std::string getId();
  /**
   * Get the identifier for the subclass.
   * @return Type identifier for the object.
   */
  virtual int getType();
  /**
   * Set the Box2d body for this entity.
   * @param body Box2D body object.
   */
  virtual void setBody(b2Body* body);
  /**
   * Get the Box2D body for this entity.
   * @return Box2D body object.
   */
  virtual b2Body* getBody();
  /**
   * Set the world layer for this entity.
   * @param worldLevelLayer World layer.
   */
  virtual void setWorldLevelLayer(WorldLevelLayer* worldLevelLayer);
  /**
   * Get the world layer for this entity.
   * @return World layer.
   */
  virtual WorldLevelLayer* getWorldLevelLayer();
  /**
   * Override Node update method.
   * @param dt Time passed from the last update call.
   */
  virtual void update(float dt);
  /**
   * Entity is selected.
   */
  virtual void select();
  virtual void select(b2Body* body);
  virtual void select(cocos2d::Touch* touch);
  virtual float getSkeletonScale();
  virtual float getGroundOffset();
  virtual void enableShapeDraw(bool isShapeDrawEnabled);
  virtual void setZOrderDraw(int zOrderDraw);
  virtual int getZOrderDraw();
  virtual void setZOrderTouch(int zOrderTouch);
  virtual int getZOrderTouch();

  virtual void onDirectionChange(int direction);
  virtual void setAnimation(int animation);
  virtual void setSkin(int skin);
  virtual int getSkin();
  virtual void randomSkin();

  virtual bool onStartTouchEvent(cocos2d::Touch* touch);
  virtual bool onMoveTouchEvent(cocos2d::Touch* touch);
  virtual bool onEndTouchEvent(cocos2d::Touch* touch);

  virtual void draw(cocos2d::Renderer* renderer,
                    const cocos2d::Mat4 &transform,
                    uint32_t flags) override;

protected:
  void setAutoId();
  void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);
  cocos2d::CustomCommand m_customCommand;
};

#endif // __ENTITY_NODE_H__
