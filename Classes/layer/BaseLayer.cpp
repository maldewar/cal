#include "BaseLayer.h"
#include "../util/CMath.h"

BaseLayer::BaseLayer() : cocos2d::Layer() {
  m_isMain = false;
  m_angle  = 0;
  m_scale  = 1;
  m_depth  = 0;
  m_alpha  = 1;
  m_xMax   = 0;
  m_xMin   = 0;
  m_yMax   = 0;
  m_yMin   = 0;
  m_scaleMax = 0;
  m_scaleMin = 0;
  m_touchEnabled          = true;
  m_translateTouchEnabled = true;
  m_rotateTouchEnabled    = true;
  m_scaleTouchEnabled     = true;
  m_translationEnabled = true;
  m_rotationEnabled    = false;
  m_scaleEnabled       = false;
  m_navigationEnabled  = true;
  m_onTranslation      = false;
  m_onRotation         = false;
  m_onScale            = false;
  m_locked             = false;
  m_translateTransitionLapse    = 0;
  m_rotateTransitionLapse       = 0;
  m_scaleTransitionLapse        = 0;
  m_translateDuration = 0;
  m_rotateDuration    = 0;
  m_scaleDuration     = 0;
  m_origin = cocos2d::Point(0, 0);
  m_angleOrigin = 0;
  m_scaleOrigin = 0;
  m_target = cocos2d::Point(0, 0);
  m_angleTarget = 0;
  m_scaleTarget = 0;
  m_winSize = cocos2d::Director::getInstance()->getWinSize();
  m_size = m_winSize;
  m_parent = nullptr;
  m_angleCos = 1;
  m_angleSin = 0;
}

BaseLayer::~BaseLayer() {
}

bool BaseLayer::init() {
  if ( !Layer::init() )
  {
    return false;
  }
  m_visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
  m_winCenter   = cocos2d::Point(m_winSize.width / 2, m_winSize.height/2);

  this->ignoreAnchorPointForPosition(false);
  this->setPosition(m_winCenter);
  this->setContentSize(cocos2d::Size(m_winSize.width,
                                     m_winSize.height));
  setCenter();

  return true;
}

bool BaseLayer::init(LayerDef* layerDef) {
  if (!this->init()) {
    return false;
  }
  m_size = cocos2d::Size(layerDef->getWidth(), layerDef->getHeight());
  m_depth  = layerDef->getDepth();
  m_alpha  = layerDef->getAlpha();
  m_translationEnabled = layerDef->isTranslationEnabled();
  m_rotationEnabled = layerDef->isRotationEnabled();
  m_scaleEnabled = layerDef->isScaleEnabled();
  m_isMain = layerDef->isMain();
  this->setContentSize (m_size);
  this->setOpacity(layerDef->getAlpha() * 255);
  this->setCascadeOpacityEnabled(true);
  setCenter();
  if (m_isMain) {
    auto listener = cocos2d::EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(BaseLayer::_onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(BaseLayer::_onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(BaseLayer::_onTouchesEnded, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(BaseLayer::_onTouchesCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
  }
  return true;
}

void BaseLayer::onEnter() {
  Layer::onEnter();
  scheduleUpdate();
}

void BaseLayer::onExit() {
  unscheduleUpdate();
  Layer::onExit();
}

void BaseLayer::update(float dt) {
  Layer::update(dt);
  if (m_onTranslation) {
    m_translateTransitionLapse += dt;
    if (m_translateTransitionLapse > m_translateDuration) {
      cancelTranslation();
      translate(m_target.x, m_target.y);
    } else {
      m_translateTweener.step(m_translateTransitionLapse * 1000);
      translate(m_positionTmp.x, m_positionTmp.y);
    }
  }
  if (m_onRotation) {
    m_rotateTransitionLapse += dt;
    if (m_rotateTransitionLapse > m_rotateDuration) {
      cancelRotation();
      rotate(m_angleTarget);
    } else {
      m_rotateTweener.step(m_rotateTransitionLapse * 1000);
      rotate(m_angleTmp);
    }
  }
  if (m_onScale) { 
    m_scaleTransitionLapse += dt;
    if (m_scaleTransitionLapse > m_scaleDuration) { 
      cancelScaling();
      scale(m_scaleTarget);
    } else {
      m_scaleTweener.step(m_scaleTransitionLapse * 1000);
      scale(m_scaleTmp);
    }
  }
}

bool BaseLayer::translate(float x, float y) {
  if (m_translationEnabled && m_navigationEnabled) {
    m_position.x = x;
    m_position.y = y;
    setCenter();
    if (m_isMain && m_parent) {
      m_parent->translateCallback(m_position.x, m_position.y, this);
    }
    return true;
  }
  return false;
}
  
bool BaseLayer::translate(float x,
                          float y,
                          float duration,
                          TweenEq eq,
                          TweenEasing easing) {
  if (m_translationEnabled && m_navigationEnabled) {
    m_onTranslation = true;
    m_translateDuration = duration;
    m_translateTransitionLapse = 0;
    m_origin = m_position;
    m_target = cocos2d::Point(x, y);
    m_positionTmp.x = m_origin.x;
    m_positionTmp.y = m_origin.y;
    tween::TweenerParam param(duration * 1000,
                              _getTweenEq(eq),
                              _getTweenEasing(easing));
    param.addProperty(&m_positionTmp.x, m_target.x);
    param.addProperty(&m_positionTmp.y, m_target.y);
    m_translateTweener = tween::Tweener(); //????
    m_translateTweener.addTween(param);
    return true;
  }
  return false;
}

bool BaseLayer::scale(float factor) {
  if (m_scaleEnabled && m_navigationEnabled) {
    m_scale = factor;
    setScale(m_scale);
    if (m_isMain && m_parent) {
      m_parent->scaleCallback(m_scale, this);
    }
    return true;
  }
  return false;
}

bool BaseLayer::scale(float factor,
                      float duration,
                      TweenEq eq,
                      TweenEasing easing) {
  if (m_scaleEnabled && m_navigationEnabled) {
    m_onScale = true;
    m_scaleDuration = duration;
    m_scaleTransitionLapse = 0;
    m_scaleOrigin = m_scale;
    m_scaleTarget = factor;
    m_scaleTmp = m_scaleOrigin;
    tween::TweenerParam param(duration * 1000,
                              _getTweenEq(eq),
                              _getTweenEasing(easing));
    param.addProperty(&m_scaleTmp, m_scaleTarget);
    m_scaleTweener = tween::Tweener();
    m_scaleTweener.addTween(param);
    return true;
  }
  return false;
}

bool BaseLayer::rotate(float angle) {
  if (m_rotationEnabled && m_navigationEnabled) {
    m_angle = CMath::wrapPosNegPI(angle);
    setRotation(CC_RADIANS_TO_DEGREES(-angle));
    m_angleSin = sin(-m_angle);
    m_angleCos = cos(-m_angle);
    if (m_isMain && m_parent) {
      m_parent->rotationCallback(m_angle, this);
    }
    return true;
  }
  return false;
}

bool BaseLayer::rotate(float angle,
                       float duration,
                       TweenEq eq,
                       TweenEasing easing) {
  if (m_rotationEnabled && m_navigationEnabled) {
    m_onRotation = true;
    m_rotateDuration = duration;
    m_rotateTransitionLapse = 0;
    m_angleOrigin = m_angle;
    m_angleTarget = angle;
    m_angleTmp = m_angleOrigin;
    tween::TweenerParam param(duration * 1000,
                              _getTweenEq(eq),
                              _getTweenEasing(easing));
    param.addProperty(&m_angleTmp, m_angleTarget);
    m_rotateTweener = tween::Tweener();
    m_rotateTweener.addTween(param);
    return true;
  }
  return false;
}

bool BaseLayer::translateStep(float dX, float dY) {
  return translate(m_position.x + (dX * m_angleCos - dY * m_angleSin),
                   m_position.y + (dX * m_angleSin + dY * m_angleCos));
}

bool BaseLayer::scaleStep(float dFactor) {
  return scale(getScaleFactor() + dFactor);
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
  return m_position.x;
}

float BaseLayer::getY() {
  return m_position.y;
}

float BaseLayer::getAngle() {
  return m_angle;
}

float BaseLayer::getScaleFactor() {
  return m_scale;
}

void BaseLayer::setParentScene(BaseScene* parent) {
  m_parent = parent;
}

BaseScene* BaseLayer::getParentScene() {
  return m_parent;
}

bool BaseLayer::isTranslationEnabled() {
  return m_translationEnabled;
}

void BaseLayer::setTranslationEnabled(bool translationEnabled) {
  m_translationEnabled = translationEnabled;
}

bool BaseLayer::isScaleEnabled() {
  return m_scaleEnabled;
}

void BaseLayer::setScaleEnabled(bool scaleEnabled) {
  m_scaleEnabled = scaleEnabled;
}

bool BaseLayer::isRotationEnabled() {
  return m_rotationEnabled;
}

void BaseLayer::setRotationEnabled(bool rotationEnabled) {
  m_rotationEnabled = rotationEnabled;
}

bool BaseLayer::isNavigationEnabled() {
  return m_navigationEnabled;
}

void BaseLayer::setNavigationEnabled(bool navigationEnabled) {
  m_navigationEnabled = navigationEnabled;
}

bool BaseLayer::isOnTranslation() {
  return m_onTranslation;
}

bool BaseLayer::isOnRotation() {
  return m_onRotation;
}

bool BaseLayer::isOnScaling() {
  return m_onScale;
}

bool BaseLayer::isOnTransition() {
  return (isOnTranslation() || isOnRotation() || isOnScaling());
}

void BaseLayer::cancelTranslation() {
  m_translateDuration = 0;
  m_onTranslation = false;
  m_translateTweener.removeTweens();
}

void BaseLayer::cancelRotation() {
  m_rotateDuration = 0;
  m_onRotation = false;
  m_rotateTweener.removeTweens();
}

void BaseLayer::cancelScaling() {
  m_scaleDuration = 0;
  m_onScale = false;
  m_scaleTweener.removeTweens();
}

void BaseLayer::translateCallback(float x, float y, BaseLayer* reference) {
  translate(x * m_depth, y * m_depth);
}

void BaseLayer::rotationCallback(float angle, BaseLayer* reference) {
  rotate(angle);
}

void BaseLayer::scaleCallback(float factor, BaseLayer* reference) {
  scale(factor); // TODO
}

void BaseLayer::setTouchEnabled(bool isTouchEnabled) {
  m_touchEnabled = isTouchEnabled;
}

void BaseLayer::setTranslateTouchEnabled(bool isTranslateTouchEnabled) {
  m_translateTouchEnabled = isTranslateTouchEnabled;
}

void BaseLayer::setRotateTouchEnabled(bool isRotateTouchEnabled) {
  m_rotateTouchEnabled = isRotateTouchEnabled;
}

void BaseLayer::setScaleTouchEnabled(bool isScaleTouchEnabled) {
  m_scaleTouchEnabled = isScaleTouchEnabled;
}

void BaseLayer::setCenter() {
  setAnchorPoint(cocos2d::Vec2(m_position.x/m_size.width + 0.5, m_position.y/m_size.height + 0.5));
}

void BaseLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches,
                               cocos2d::Event *unused_event) {
}

void BaseLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches,
                               cocos2d::Event *unused_event) {
}

void BaseLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches,
                               cocos2d::Event *unused_event) {
}

void BaseLayer::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches,
                                    cocos2d::Event *unused_event) {
}

void BaseLayer::_onTouchesBegan(const std::vector<cocos2d::Touch*>& touches,
                               cocos2d::Event *unused_event) {
  onTouchesBegan(touches, unused_event);
}

void BaseLayer::_onTouchesMoved(const std::vector<cocos2d::Touch*>& touches,
                               cocos2d::Event *unused_event) {
  if (m_isMain && !m_locked) {
    if (touches.size() > 1 &&
        ((m_scaleEnabled && m_touchEnabled && m_scaleTouchEnabled && !m_onScale) ||
         (m_rotationEnabled && m_touchEnabled && m_rotateTouchEnabled && !m_onRotation))) {
      cocos2d::Touch* touch0 = touches[0];
      cocos2d::Touch* touch1 = touches[1];
      cocos2d::Vec2 currentScreenPos0 = touch0->getLocation();
      cocos2d::Vec2 currentScreenPos1 = touch1->getLocation();
      cocos2d::Vec2 previousScreenPos0 = touch0->getPreviousLocation();
      cocos2d::Vec2 previousScreenPos1 = touch1->getPreviousLocation();
      if (m_scaleEnabled && m_scaleTouchEnabled && ! m_onScale) {
        float currentSeparation = currentScreenPos0.distance(currentScreenPos1);
        float previousSeparation = previousScreenPos0.distance(previousScreenPos1);
        if (previousSeparation > 10) {
          float scale = currentSeparation / previousSeparation;
          this->scale(m_scale * scale);
          if (m_translationEnabled && !m_onTranslation) {
            cocos2d::Vec2 currentMidpoint =
              ((currentScreenPos1 - currentScreenPos0) / 2) + currentScreenPos0;
            cocos2d::Vec2 previousMidpoint =
              ((previousScreenPos1 - previousScreenPos0) / 2) + previousScreenPos0;
            cocos2d::Vec2 moved = currentMidpoint - previousMidpoint;
            translate(m_position.x - (moved.x * m_angleCos - moved.y * m_angleSin) * scale,
                      m_position.y - (moved.x * m_angleSin + moved.y * m_angleCos) * scale);
          }
        }
      }
      if (m_rotationEnabled && m_touchEnabled && m_rotateTouchEnabled && !m_onRotation) {
        float currentAngle = CMath::getAngle(currentScreenPos0, currentScreenPos1);
        float previousAngle = CMath::getAngle(previousScreenPos0, previousScreenPos1);
        float angleDiff = currentAngle - previousAngle;
        rotate(m_angle + angleDiff);
      }
    } else if (m_translationEnabled && m_touchEnabled &&
               m_translateTouchEnabled && !m_onTranslation) {
      cocos2d::Touch* touch = touches[0];
      cocos2d::Vec2 currentScreenPos = touch->getLocation();
      cocos2d::Vec2 previousScreenPos = touch->getPreviousLocation();
      cocos2d::Vec2 moved = currentScreenPos - previousScreenPos;
      translate(m_position.x - (moved.x * m_angleCos - moved.y * m_angleSin),
                m_position.y - (moved.x * m_angleSin + moved.y * m_angleCos));
    }
  }
  onTouchesMoved(touches, unused_event);
}

void BaseLayer::_onTouchesEnded(const std::vector<cocos2d::Touch*>& touches,
                               cocos2d::Event *unused_event) {
  onTouchesEnded(touches, unused_event);
}

void BaseLayer::_onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches,
                                   cocos2d::Event *unused_event) {
  onTouchesCancelled(touches, unused_event);
}

short BaseLayer::_getTweenEq(TweenEq eq) {
  switch(eq) {
    case TweenEq::Linear:
      return tween::LINEAR;
    case TweenEq::Sine:
      return tween::SINE;
    case TweenEq::Quint:
      return tween::QUINT;
    case TweenEq::Quart:
      return tween::QUART;
    case TweenEq::Quad:
      return tween::QUAD;
    case TweenEq::Expo:
      return tween::EXPO;
    case TweenEq::Elastic:
      return tween::ELASTIC;
    case TweenEq::Cubic:
      return tween::CUBIC;
    case TweenEq::Circ:
      return tween::CIRC;
    case TweenEq::Bounce:
      return tween::BOUNCE;
    case TweenEq::Back:
      return tween::BACK;
    default:
      return tween::LINEAR;
  }
  return tween::LINEAR;
}

short BaseLayer::_getTweenEasing(TweenEasing easing) {
  switch(easing) {
    case TweenEasing::In:
      return tween::EASE_IN;
    case TweenEasing::Out:
      return tween::EASE_OUT;
    case TweenEasing::InOut:
      return tween::EASE_IN_OUT;
  }
  return tween::EASE_IN;
}
