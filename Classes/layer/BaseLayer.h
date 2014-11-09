#ifndef __BASE_LAYER_H__
#define __BASE_LAYER_H__

#include "cocos2d.h"

class BaseLayer : public cocos2d::Layer
{
protected:
  float m_x;
  float m_y;
  float m_angle;
  bool m_translationEnabled;
  bool m_rotationEnabled;
  bool m_scaleEnabled;
  float m_scaleMax;
  float m_scaleMin;
  float m_xMax;
  float m_xMin;
  float m_yMax;
  float m_yMin;
  bool m_onTransition;
  cocos2d::Size m_visibleSize;
  cocos2d::Size m_winSize;

public:
  BaseLayer();
  virtual ~BaseLayer();
  virtual bool init();
  virtual bool translate(float x, float y, float transitionTime = 0) = 0;
  virtual bool scale(float factor, float transitionTime = 0) = 0;
  virtual bool rotate(float angle, float transitionTime = 0) = 0;
  virtual float getX();
  virtual float getY();
  virtual float getAngle();
  virtual float getScale();
  virtual bool isTranslationEnabled();
  virtual void setTranslationEnabled(bool isTranslationEnabled);
  virtual bool isScaleEnabled();
  virtual void setScaleEnabled(bool isScaleEnabled);
  virtual bool isRotationEnabled();
  virtual void setRotationEnabled(bool isRotationEnabled);

protected:
  virtual bool onTransition();

};

#endif // __BASE_LAYER_H__
