#ifndef __ACT_MENU_SCENE__
#define __ACT_MENU_SCENE__

#include <vector>
#include "cocos2d.h"
#include "../layer/ActMenuLayer.h"
#include "../layer/BasicUILayer.h"
class ActMenuLayer;

class ActMenuScene : public cocos2d::Scene
{
protected:
  ActMenuLayer* m_actMenuLayer;
  BasicUILayer* m_basicUILayer;

public:
  ActMenuScene(void);
  virtual ~ActMenuScene(void);
  static ActMenuScene* create();
  virtual bool init(void);
  virtual void onEnter() override;
  virtual void onExit() override;
};

#endif /* __ACT_MENU_SCENE__ */
