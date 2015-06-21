#ifndef __ENTITY_ELEM_NODE_H__
#define __ENTITY_ELEM_NODE_H__

#include <unordered_map>
#include <string>
#include "cocos2d.h"
#include <spine/spine-cocos2dx.h>
#include "Box2D/Box2D.h"
#include "2d/CCNode.h"
#include "../manager/ConfigurationManager.h"
#include "../model/Entity.h"
class Entity;

const int ENTITY_ELEM_TYPE_DEFAULT  = 1;

class EntityElem : public cocos2d::Node
{
protected:
  std::string m_id;
  Entity* m_entity;
  b2Fixture* m_fixture;
  spine::SkeletonAnimation* m_skeletonNode;
  static std::unordered_map<int, int> m_ids;
  bool m_touchEnabled;

public:
  /**
   * Class constructor.
   */
  EntityElem(void);
  /**
   * Class destructor.
   */
  virtual ~EntityElem(void);
  virtual void setId(std::string id);
  virtual std::string getId();
  /**
   * Get the identifier for the subclass.
   * @return Type identifier for the object.
   */
  virtual int getType();
  /**
   * Set the Box2d fixture for this entity.
   * @param fixture Box2D fixture object.
   */
  virtual void setFixture(b2Fixture* fixture);
  /**
   * Get the Box2D fixture for this entity.
   * @return Box2D fixture object.
   */
  virtual b2Fixture* getFixture();
  /**
   * Set the entity for this entity element.
   * @param entity Parent entity.
   */
  virtual void setEntity(Entity* entity);
  /**
   * Get the entity for this entity.
   * @return Parent entity.
   */
  virtual Entity* getEntity();
  /**
   * Sets this fixture to trigger touch events.
   * @param touchEnabled True to trigger touch events.
   */
  virtual void setTouchEnabled(bool touchEnabled);
  /**
   * Tells if the element should trigger touch events.
   * @return True if the element should trigger touch events.
   */ 
  virtual bool isTouchEnabled();
  /**
   * Override Node update method.
   * @param dt Time passed from the last update call.
   */
  virtual void update(float dt);
  /**
   * EntityElem is selected.
   */
  virtual void select();
  virtual void select(b2Fixture* fixture);
  virtual void select(cocos2d::Touch* touch);

protected:
  void setAutoId();
};

#endif // __ENTITY_ELEM_NODE_H__
