#ifndef __BASE_LAYER_H__
#define __BASE_LAYER_H__

#include "cocos2d.h"

class BaseLayer : public cocos2d::Layer
{
protected:
  float m_x;
  float m_y;
  float m_angle;
  float m_depth;
  bool m_translationEnabled;
  bool m_rotationEnabled;
  bool m_scaleEnabled;
  float m_scaleMax;
  float m_scaleMin;
  float m_xMax;
  float m_xMin;
  float m_yMax;
  float m_yMin;
  float m_translateTransitionLapse;
  float m_rotateTransitionLapse;
  float m_scaleTransitionLapse;
  float m_translateTransitionDuration;
  float m_rotateTransitionDuration;
  float m_scaleTransitionDuration;
  float m_xOrigin;
  float m_yOrigin;
  float m_angleOrigin;
  float m_scaleOrigin;
  float m_xTarget;
  float m_yTarget;
  float m_angleTarget;
  float m_scaleTarget;
  cocos2d::Size m_visibleSize;
  cocos2d::Size m_winSize;
  cocos2d::Point m_winCenter;;
  bool m_isMain;

public:
  BaseLayer();
  virtual ~BaseLayer();
  virtual bool init();
  virtual bool translate(float x, float y);
  virtual bool translate(float x, float y, float transitionDuration);
  virtual bool scale(float factor);
  virtual bool scale(float factor, float transitionDuration);
  virtual bool rotate(float angle);
  virtual bool rotate(float angle, float transitionDuration);
  virtual bool translateStep(float dX, float dY);
  virtual bool scaleStep(float dFactor);
  virtual bool rotateStep(float dAngle);
  virtual bool isMain();
  virtual void setIsMain(bool isMain);
  virtual float getX();
  virtual float getY ();
  virtual float getAngle ();
  virtual float getScale ();
  virtual bool isTranslationEnabled ();
  virtual void setTranslationEnabled (bool isTranslationEnabled);
  virtual bool isScaleEnabled ();
  virtual void setScaleEnabled (bool isScaleEnabled);
  virtual bool isRotationEnabled ();
  virtual void setRotationEnabled (bool isRotationEnabled);
  virtual void setAnchorPoint (const cocos2d::Point &anchorPoint);
  bool isOnTranslation();
  bool isOnRotation();
  bool isOnScaling();
  bool isOnTransition();

protected:
  virtual void setCenter();
};

#endif // __BASE_LAYER_H__
