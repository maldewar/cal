#include "Unit.h"

Unit::Unit() : Entity() {
  m_sprite = nullptr;
}

Unit::~Unit(){
}

Unit* Unit::create()
{
  Unit *entry = new (std::nothrow) Unit();
  if (entry && entry->init())
  {
    entry->autorelease();
    return entry;
  }
  CC_SAFE_DELETE(entry);
  return nullptr;
}

bool Unit::init(void)
{
  /*
  m_sprite = cocos2d::Sprite::create("sprite/unit/frame0000.pvr");
  if (m_sprite) {
    m_sprite->setScale(m_sprite->getContentSize().width/(0.15 * 840));
    addChild(m_sprite);
    return true;
  }
  return false;
  */
  m_armature = cocostudio::Armature::create("unit");
  CCLOG("..Unit::init created armature");
  //m_armature->getAnimation()->playWithIndex(0);
  if (m_armature) {
    m_armature->setScale(m_armature->getContentSize().width/(0.15 * 840));
    addChild(m_armature);
    return true;
  }
  return false;
}
