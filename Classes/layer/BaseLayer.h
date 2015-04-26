#ifndef __BASE_LAYER_H__
#define __BASE_LAYER_H__

#include "cocos2d.h"
#include "../scene/BaseScene.h"
#include "../model/LayerDef.h"
#include "../util/CppTweener.h"
class BaseScene;

class BaseLayer : public cocos2d::Layer
{
public:
  enum TweenEq {
    Linear,
    Sine,
    Quint,
    Quart,
    Quad,
    Expo,
    Elastic,
    Cubic,
    Circ,
    Bounce,
    Back
  };
  enum TweenEasing {
    In,
    Out,
    InOut
  };

protected:
  bool m_isMain;
  cocos2d::Size m_size;
  cocos2d::Point m_position;
  float m_angle;
  float m_scale;
  float m_depth;
  float m_alpha;
  bool m_touchEnabled;
  bool m_translateTouchEnabled;
  bool m_rotateTouchEnabled;
  bool m_scaleTouchEnabled;
  bool m_translationEnabled;
  bool m_rotationEnabled;
  bool m_scaleEnabled;
  bool m_navigationEnabled;
  bool m_onTranslation;
  bool m_onRotation;
  bool m_onScale;
  bool m_locked;
  float m_scaleMax;
  float m_scaleMin;
  float m_xMax;
  float m_xMin;
  float m_yMax;
  float m_yMin;
  tween::Tweener m_translateTweener;
  tween::Tweener m_rotateTweener;
  tween::Tweener m_scaleTweener;
  float m_translateTransitionLapse;
  float m_rotateTransitionLapse;
  float m_scaleTransitionLapse;
  float m_translateDuration;
  float m_rotateDuration;
  float m_scaleDuration;
  cocos2d::Point m_origin;
  float m_angleOrigin;
  float m_scaleOrigin;
  cocos2d::Point m_target;
  float m_angleTarget;
  float m_scaleTarget;
  cocos2d::Point m_positionTmp;
  float m_angleTmp;
  float m_scaleTmp;
  cocos2d::Size m_visibleSize;
  cocos2d::Size m_winSize;
  cocos2d::Point m_winCenter;
  BaseScene* m_parent;
  float m_angleCos;
  float m_angleSin;

public:
  BaseLayer ();
  virtual ~BaseLayer ();
  virtual bool init ();
  virtual bool init (LayerDef* layerDef);
  virtual void onEnter();
  virtual void onExit();
  virtual void update(float dt);
  virtual bool translate (float x, float y);
  virtual bool translate (float x,
                          float y,
                          float duration,
                          TweenEq eq = TweenEq::Linear,
                          TweenEasing easing = TweenEasing::In);
  virtual bool scale (float factor);
  virtual bool scale (float factor,
                      float duration,
                      TweenEq eq = TweenEq::Linear,
                      TweenEasing easing = TweenEasing::In);
  virtual bool rotate (float angle);
  virtual bool rotate (float angle,
                       float duration,
                       TweenEq eq = TweenEq::Linear,
                       TweenEasing easing = TweenEasing::In);
  virtual bool translateStep (float dX, float dY);
  virtual bool scaleStep (float dFactor);
  virtual bool rotateStep (float dAngle);
  virtual bool isMain ();
  virtual void setIsMain (bool isMain);
  virtual float getX ();
  virtual float getY ();
  virtual float getAngle ();
  virtual float getScaleFactor ();
  virtual void setParentScene (BaseScene* parent);
  virtual BaseScene* getParentScene ();
  virtual bool isTranslationEnabled ();
  virtual void setTranslationEnabled (bool translationEnabled);
  virtual bool isScaleEnabled ();
  virtual void setScaleEnabled (bool scaleEnabled);
  virtual bool isRotationEnabled ();
  virtual void setRotationEnabled (bool rotationEnabled);
  virtual bool isNavigationEnabled();
  virtual void setNavigationEnabled(bool navigationEnabled);
  bool isOnTranslation ();
  bool isOnRotation ();
  bool isOnScaling ();
  bool isOnTransition ();
  void cancelTranslation ();
  void cancelRotation ();
  void cancelScaling ();
  void translateCallback (float x, float y, BaseLayer* reference);
  void rotationCallback (float angle, BaseLayer* reference);
  void scaleCallback (float factor, BaseLayer* reference);
  void setTouchEnabled(bool isTouchEnabled);
  void setTranslateTouchEnabled(bool isTranslateTouchEnabled);
  void setRotateTouchEnabled(bool isRotateTouchEnabled);
  void setScaleTouchEnabled(bool isScaleTouchEnabled);

protected:
  virtual void setCenter();
  virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches,
                              cocos2d::Event *unused_event);
  virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches,
                              cocos2d::Event *unused_event);
  virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches,
                              cocos2d::Event *unused_event);
  virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches,
                                  cocos2d::Event *unused_event);

private:
  void _onTouchesBegan(const std::vector<cocos2d::Touch*>& touches,
                       cocos2d::Event *unused_event);
  void _onTouchesMoved(const std::vector<cocos2d::Touch*>& touches,
                       cocos2d::Event *unused_event);
  void _onTouchesEnded(const std::vector<cocos2d::Touch*>& touches,
                       cocos2d::Event *unused_event);
  void _onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches,
                           cocos2d::Event *unused_event);
  short _getTweenEq(TweenEq eq);
  short _getTweenEasing(TweenEasing easing);

};

#endif // __BASE_LAYER_H__
