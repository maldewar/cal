#ifndef __BASE_SCENE__
#define __BASE_SCENE__

#include <string>
#include <vector>
#include "cocos2d.h"
#include "../layer/BaseLayer.h"
#include "../model/SceneDef.h"
#include "../model/WorldLayerDef.h"
class BaseLayer;

class BaseScene : public cocos2d::Scene
{
protected:
  SceneDef *m_sceneDef;
  BaseLayer* m_mainLayer;
  std::vector<BaseLayer*> m_layers;
  int m_topIndex;
  int m_bottomIndex;
  bool m_keysEnabled;
  bool m_translateKeysEnabled;
  bool m_scaleKeysEnabled;
  bool m_rotateKeysEnabled;
  bool m_translateTouchEnabled;
  bool m_scaleTouchEnabled;
  bool m_rotateTouchEnabled;
  bool m_rightKey;
  bool m_leftKey;
  bool m_upKey;
  bool m_downKey;
  bool m_zoomInKey;
  bool m_zoomOutKey;
  bool m_rotateCWKey;
  bool m_rotateCCWKey;
  float m_translationStep;
  float m_scalingStep;
  float m_rotationStep;
  float m_translationFactor;
  float m_scalingFactor;
  float m_rotatingFactor;

public:
  BaseScene(void);
  virtual bool init(std::string filename);
  virtual void update(float dt);
  void setCtrlEnabled(bool isCtrlEnabled);
  void translateCallback(float x, float y, BaseLayer* baseLayer);
  void rotationCallback(float angle, BaseLayer* baseLayer);
  void scaleCallback(float scale, BaseLayer* baseLayer);
  int getTopLayerIndex();
  int getBottomLayerIndex();
  virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode,
                            cocos2d::Event* event);
  virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode,
                             cocos2d::Event* event);

protected:
  virtual void onLayerAdded(BaseLayer* layer, LayerDef* layerDef);
  virtual SceneDef* getSceneDef(std::string filename) = 0;
  virtual BaseLayer* getWorldLayer(WorldLayerDef* worldLayerDef) = 0;
};

#endif /* __BASE_SCENE__ */
