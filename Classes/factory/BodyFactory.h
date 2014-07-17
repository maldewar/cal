#ifndef __BODY_FACTORY__
#define __BODY_FACTORY__

#include <string>
#include <unordered_map>
#include "Box2D/Box2D.h"

#include "cocos2d.h"
#include "../util/json/json.h"
#include "../util/b2dJson.h"

class BodyFactory : public cocos2d::Ref
{
public:
  static BodyFactory* getInstance();
  static void destroyInstance();

private:
  BodyFactory(void);
  ~BodyFactory(void);

public:
  virtual bool init();
  virtual bool hasBodyDef(std::string category);
  virtual bool addBodyDef(std::string category, b2Body* body);
  virtual bool addBodyDef(std::string category, Json::Value json);
  virtual b2Body* getBody(std::string category);
  virtual void randomizeUnitBody(b2Body* unitBody);
  void setWorld(b2World* world);

protected:
  std::unordered_map<std::string, Json::Value> m_bodyDefs;
  b2dJson* m_b2dJson;
  b2World* m_world;
};

#endif
