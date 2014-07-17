#ifndef __MAIN_MENU_SCENE__
#define __MAIN_MENU_SCENE__

#include <vector>
#include "cocos2d.h"
#include "../layer/MainMenuUILayer.h"
class MainMenuUILayer;

class MainMenuScene : public cocos2d::Scene
{
protected:
  MainMenuUILayer* m_mainMenuUILayer;

public:
  MainMenuScene(void);
  virtual ~MainMenuScene(void);
  static MainMenuScene* create();
  virtual bool init(void);
  virtual void onExit() override;
};

#endif /* __MAIN_MENU_SCENE__ */
