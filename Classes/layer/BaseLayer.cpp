#include "BaseLayer.h"

BaseLayer::BaseLayer() : cocos2d::Layer() {
  m_isMain = false;
  m_x      = 0;
  m_y      = 0;
  m_angle  = 0;
  m_depth  = 0;
  m_xMax   = 0;
  m_xMin   = 0;
  m_yMax   = 0;
  m_yMin   = 0;
  m_scaleMax = 0;
  m_scaleMin = 0;
  m_translationEnabled = true;
  m_rotationEnabled    = false;
  m_scaleEnabled       = false;
  m_translateTransitionLapse    = 0;
  m_rotateTransitionLapse       = 0;
  m_scaleTransitionLapse        = 0;
  m_translateTransitionDuration = 0;
  m_rotateTransitionDuration    = 0;
  m_scaleTransitionDuration     = 0;
  m_xOrigin = 0;
  m_yOrigin = 0;
  m_angleOrigin = 0;
  m_scaleOrigin = 0;
  m_xTarget = 0;
  m_yTarget = 0;
  m_angleTarget = 0;
  m_scaleTarget = 0;
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
  m_winCenter   = cocos2d::Point(m_winSize.width / 2, m_winSize.height/2);

  // Set the layer at the center of the screen
  setPosition(m_winCenter.x, m_winCenter.y);

  // Set the anchor point at the center of the layer
  setAnchorPoint(cocos2d::Vec2(0,0));

  this->setContentSize(cocos2d::Size(m_winSize.height,
                                     m_winSize.height));

  return true;
}

bool BaseLayer::translate(float x, float y) {
  if (m_translationEnabled) {
    m_x = x;
    m_y = y;
    setAnchorPoint(cocos2d::Vec2(x, y));
    return true;
  }
  return false;
}

bool BaseLayer::translate(float x, float y, float transitionDuration) {
  if (m_translationEnabled) {
    return true;
  }
  return false;
}

bool BaseLayer::scale(float factor) {
  if (m_scaleEnabled) {
    setCenter();
    return true;
  }
  return false;
}

bool BaseLayer::scale(float factor, float transitionDuration) {
  return true;
}

bool BaseLayer::rotate(float angle) {
  if (m_rotationEnabled) {
    m_angle = angle;
    setRotation(CC_RADIANS_TO_DEGREES(-angle));
    return true;
  }
  return false;
}

bool BaseLayer::rotate(float angle, float transitionDuration) {
  return true;
}

bool BaseLayer::translateStep(float dX, float dY) {
  float transX = dX / m_visibleSize.height / getScale();
  float transY = dY / m_visibleSize.height / getScale();
  float angleSin = sin(-m_angle);
  float angleCos = cos(-m_angle);
  return translate(getX() + (transX * angleCos - transY * angleSin),
                   getY() + (transX * angleSin + transY * angleCos));
}

bool BaseLayer::scaleStep(float dFactor) {
  return scale(getScale() + dFactor);
}

bool BaseLayer::rotateStep(float dAngle) {
  return rotate(getAngle() + dAngle);
}

bool BaseLayer::isMain() {
  return m_isMain;
}

void BaseLayer::setIsMain(bool isMain) {
  m_isMain = isMain;
  m_depth = 1;
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

bool BaseLayer::isOnTranslation() {
  return (m_translateTransitionDuration > 0);
}

bool BaseLayer::isOnRotation() {
  return (m_rotateTransitionDuration > 0);
}

bool BaseLayer::isOnScaling() {
  return (m_scaleTransitionDuration > 0);
}

bool BaseLayer::isOnTransition() {
  return (isOnTranslation() || isOnRotation() || isOnScaling());
}

void BaseLayer::setAnchorPoint (const cocos2d::Point &anchorPoint) {
  Layer::setAnchorPoint (anchorPoint);
}

void BaseLayer::setCenter() {
  float angleSin = sin(m_angle);
  float angleCos = cos(m_angle);
  m_winCenter.x = 960 - (m_x * angleCos - m_x * angleSin) * 1;
  m_winCenter.y = 540 - (m_y * angleCos + m_x * angleSin) * 1;
  CCLOG("m_x:%f m_y:%f angle:%f scale:%f", m_x, m_y, m_angle, getScale());
  CCLOG("center_x:%f center_y:%f", m_winCenter.x, m_winCenter.y);
}
