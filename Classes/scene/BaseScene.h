#ifndef __BASE_SCENE__
#define __BASE_SCENE__

#include <string>
#include <vector>
#include "cocos2d.h"
#include "../layer/BasicUILayer.h"
#include "../model/SceneDef.h"

class BaseScene : public cocos2d::Scene
{
protected:
  SceneDef *m_sceneDef;
  vector<cocos2d::Layer*> m_layers;

public:
  BaseScene(void);
  virtual ~BaseScene(void);
  virtual bool init(std::string filename);

protected:
  virtual SceneDef* getSceneDef() = 0;
};

#endif /* __BASE_SCENE__ */
