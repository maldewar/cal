#include "ImageBody.h"

ImageBody::ImageBody() : Entity() {
  m_sprite = nullptr;
}

ImageBody::~ImageBody() {
}

int ImageBody::getType() {
  return ENTITY_TYPE_IMAGE_BODY;
}

ImageBody* ImageBody::create(std::string filename, b2Body* body) {
  ImageBody* imageBody = nullptr;
  imageBody = new (std::nothrow) ImageBody();
  if (imageBody && imageBody->init(filename))
  {
    imageBody->autorelease();
    imageBody->setBody(body);
    imageBody->update(0);
    return imageBody;
  }
  CC_SAFE_DELETE(imageBody);
  return nullptr;
}

bool ImageBody::init(std::string filename) {
  m_sprite = cocos2d::Sprite::create(filename.c_str());
  if (m_sprite) {
    setScale(PX_TO_M);
    addChild(m_sprite);
    scheduleUpdate();
    return true;
  }
  return false;
}
