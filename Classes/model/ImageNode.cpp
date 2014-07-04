#include "ImageNode.h"

ImageNode::ImageNode() : Node() {
  m_sprite = nullptr;
}

ImageNode::~ImageNode() {
}

int ImageNode::getType() {
  return ENTITY_TYPE_IMAGE;
}

ImageNode* ImageNode::create(std::string filename) {
  ImageNode* imageNode = nullptr;
  imageNode = new (std::nothrow) ImageNode();
  if (imageNode && imageNode->init(filename))
  {
    imageNode->autorelease();
    return imageNode;
  }
  CC_SAFE_DELETE(imageNode);
  return nullptr;
}

bool ImageNode::init(std::string filename) {
  m_sprite = cocos2d::Sprite::create(filename.c_str());
  if (m_sprite) {
    addChild(m_sprite);
    setScale(PX_TO_M);
    return true;
  }
  return false;
}

cocos2d::Sprite* ImageNode::getSprite() {
  return m_sprite;
}
