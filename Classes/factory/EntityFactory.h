#ifndef __ENTITY_FACTORY__
#define __ENTITY_FACTORY__

#include "cocos2d.h"
#include "../util/json/json.h"
#include "../util/b2dJson.h"
#include "../model/Unit.h"
#include "../model/Entry.h"
#include "../model/Area.h"

class EntityFactory : public cocos2d::Ref
{
public:
  static EntityFactory* getInstance();
  static void destroyInstance();

private:
  EntityFactory(void);
  ~EntityFactory(void);

public:
  virtual bool init();
  virtual Unit* getUnit(b2dJson* json, b2Body* body);
  virtual Entry* getEntry(b2dJson* json, b2Body* body);
  virtual Area* getArea(b2dJson* json, b2Body* body);

};

#endif
