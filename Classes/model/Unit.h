#ifndef __UNIT_NODE_H__
#define __UNIT_NODE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Entity.h"
#include "../component/ContactComponent.h"
#include "../component/AIComponent.h"

const int UNIT_ANIM_STAND_FRONT = 0;
const int UNIT_ANIM_FALL        = 1;
const int UNIT_ANIM_FALL_STOP   = 2;
const int UNIT_ANIM_ROLL        = 3;
const int UNIT_ANIM_ROLL_STOP   = 4;
const int UNIT_ANIM_STAND_SIDE  = 5;

class Unit : public Entity, public ContactComponent, public AIComponent
{
protected:
  bool m_isLost;

public:
  /**
   * Class constructor.
   */
  Unit(void);
  /**
   * Class destructor.
   */
  virtual ~Unit(void);
  /**
   * Get the identifier for this class.
   * @return Type identifier.
   */
  virtual int getType();
  /**
   * Set the body for this instance and its components.
   * @param body Box2D body.
   */
  virtual void setBody(b2Body* body) override;
  /**
   * Returns an instance of this class.
   * @return Unit instance.
   */
  static Unit* create(bool managed = false, bool setBody = false);
  /**
   * Initialization method.
   * @return True if the object is correctly initialized.
   */
  bool isLost();
  void setIsLost(bool isLost);
  void remove(bool isLost);
  virtual bool init(void);
  /**
   * Update method.
   * @return Seconds passed since last update.
   */
  virtual void update(float dt);
  virtual void select();
  virtual void contactStart(b2Body* body, Entity* contactEntity = nullptr);
  virtual void contactEnd(b2Body* body, Entity* contactEntity = nullptr);

  virtual void onStateChange(int state, int substate);
  virtual void onSubstateChange(int substate);
  virtual void onDirectionChange(int direction);

  virtual void setAnimation(int animation);
  virtual void randomSkin();
};

#endif // __UNIT_NODE_H__
