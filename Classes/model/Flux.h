#ifndef __FLUX_NODE_H__
#define __FLUX_NODE_H__

#include <unordered_map>

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "Entity.h"
#include "../component/ContactComponent.h"
#include "../engine/Timer.h"

const int FLUX_STATE_INACTIVE = 0;
const int FLUX_STATE_ACTIVE   = 1;
const int FLUX_STATE_AUTO     = 2;

class Flux : public Entity, public ContactComponent
{
protected:
  int m_state;
  float m_arrowAngle;
  bool m_isSelected;
  Timer* m_timer;
  b2Vec2* m_target;
  bool m_waitingForAuto;
  bool m_isAuto;
  std::unordered_map<std::string, Unit*> m_units;

public:
  /**
   * Class constructor.
   */
  Flux(void);
  /**
   * Class destructor.
   */
  virtual ~Flux(void);
  /**
   * Get the identifier for this class.
   * @return Type identifier.
   */
  virtual int getType() override;
  static Flux* create();
  /**
   * Returns an instance of this class.
   * @return Flux instance.
   */
  static Flux* create(bool active);
  /**
   * Initialization method.
   * @return True if the object is correctly initialized.
   */
  virtual bool init(bool active);
  void activate(float dt);
  void deactivate(float dt);
  void setArrowAngle(float angle);
  float getArrowAngle();
  void setTarget(float x, float y);
  b2Vec2* getTarget();
  virtual void update(float dt);
  virtual void select();
  virtual void deselect();

  virtual void sensorReceive(b2Body* body, Entity* receivedEntity);
  virtual void sensorLose(b2Body* body, Entity* lostEntity);

protected:
  bool dispatchUnit();
  void setAuto(bool isAuto);
};

#endif // __FLUX_NODE_H__
