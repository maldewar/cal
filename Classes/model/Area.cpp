#include "Area.h"
#include "../util/IdUtil.h"

Area::Area() : Entity() {
  m_shapeDrawEnabled = false;
  m_color = cocos2d::Color4F(0.2, 0.1, 0.1, 1);
  setAutoId();
}

Area::~Area() {
}

int Area::getType() {
  return ENTITY_TYPE_AREA;
}

Area* Area::create() {
  Area* area = new (std::nothrow) Area();
  if (area && area->init())
  {
    area->autorelease();
    return area;
  }
  CC_SAFE_DELETE(area);
  return nullptr;
}

bool Area::init(void) {
  scheduleUpdate();
  return true;
}
