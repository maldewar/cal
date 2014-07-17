#include "BodyFactory.h"

static BodyFactory* s_sharedBodyFactory = nullptr;

BodyFactory* BodyFactory::getInstance() {
  if (s_sharedBodyFactory == nullptr) {
    s_sharedBodyFactory = new BodyFactory();
    if (!s_sharedBodyFactory || !s_sharedBodyFactory->init()) {
      CC_SAFE_DELETE(s_sharedBodyFactory);
    }
  }
  return s_sharedBodyFactory;
}

void BodyFactory::destroyInstance() {
  CC_SAFE_RELEASE_NULL(s_sharedBodyFactory);
}

BodyFactory::BodyFactory(void) {
  m_bodyDefs.clear();
  m_b2dJson = nullptr;
  m_world = nullptr;
}

BodyFactory::~BodyFactory(void) {
  m_bodyDefs.clear();
  CC_SAFE_DELETE(m_b2dJson);
}

bool BodyFactory::init() {
  m_bodyDefs.clear();
  m_b2dJson = new (std::nothrow) b2dJson(false);
  if (m_b2dJson) {
    return true;
  }
  return false;
}

bool BodyFactory::hasBodyDef(std::string category) {
  if (m_bodyDefs.count(category) > 0)
    return true;
  return false;
}

bool BodyFactory::addBodyDef(std::string category, b2Body* body) {
  if (!hasBodyDef(category)) {
    return addBodyDef(category, m_b2dJson->b2j(body));
  }
  return false;
}

bool BodyFactory::addBodyDef(std::string category, Json::Value json) {
  if (!hasBodyDef(category)) {
    m_bodyDefs[category] = json;
    return true;
  }
  return false;
}

b2Body* BodyFactory::getBody(std::string category) {
  b2Body* body = nullptr;
  if (hasBodyDef(category) && m_world != nullptr) {
    body = m_b2dJson->j2b2Body(m_world, m_bodyDefs[category]);
  }
  return body;
}

void BodyFactory::randomizeUnitBody(b2Body* unitBody) {
  b2Fixture* fixture = unitBody->GetFixtureList();
  fixture->SetDensity(CCRANDOM_0_1() * 0.4f + 0.8f);
}

void BodyFactory::setWorld(b2World* world) {
  m_world = world;
}
