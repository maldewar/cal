#include "BaseLayer.h"

BaseLayer::BaseLayer() {
  m_x     = 0;
  m_y     = 0;
  m_angle = 0;
  m_xMax  = 0;
  m_xMin  = 0;
  m_yMax  = 0;
  m_yMin  = 0;
  m_scaleMax = 0;
  m_scaleMin = 0;
  m_translationEnabled = false;
  m_rotationEnabled    = false;
  m_scaleEnabled       = false;
  m_onTransition       = false;
}

BaseLayer::~BaseLayer() {
}

bool BaseLayer::init() {
  if ( !Layer::init() )
  {
    return false;
  }
  m_visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
  m_winSize     = cocos2d::Director::getInstance()->getWinSize();
  CCLOG("Layer Visible size, width: %f height: %f ",
        m_visibleSize.width, m_visibleSize.height);
  CCLOG("Layer Window size, width: %f height: %f", m_winSize.width, m_winSize.height);
  return true;
}

bool BaseLayer::translate(float x, float y, float transitionTime) {
  // pure virtual
}

bool BaseLayer::scale(float factor, float transitionTime) {
  // pure virtual
}

bool BaseLayer::rotate(float angle, float transitionTime) {
  // pure virtual
}

float BaseLayer::getX() {
  return m_x;
}

float BaseLayer::getY() {
  return m_y;
}

float BaseLayer::getAngle() {
  return m_angle;
}

float BaseLayer::getScale() {
  return Layer::getScale();
}

bool BaseLayer::isTranslationEnabled() {
  return m_translationEnabled;
}

void BaseLayer::setTranslationEnabled(bool isTranslationEnabled) {
  m_translationEnabled = isTranslationEnabled;
}

bool BaseLayer::isScaleEnabled() {
  return m_scaleEnabled;
}

void BaseLayer::setScaleEnabled(bool isScaleEnabled) {
  m_scaleEnabled = isScaleEnabled;
}

bool BaseLayer::isRotationEnabled() {
  return m_rotationEnabled;
}

void BaseLayer::setRotationEnabled(bool rotationEnabled) {
  m_rotationEnabled = rotationEnabled;
}

bool BaseLayer::onTransition() {
  return m_onTransition;
}
