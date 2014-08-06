#ifndef __LEVEL_MENU_SCENE__
#define __LEVEL_MENU_SCENE__

#include <string>
#include "cocos2d.h"
#include "../layer/LevelMenuLayer.h"
#include "../layer/BasicUILayer.h"
class LevelMenuLayer;

class LevelMenuScene : public cocos2d::Scene
{
protected:
  int m_act;
  LevelMenuLayer* m_levelMenuLayer;
  BasicUILayer* m_basicUILayer;

public:
  LevelMenuScene(void);
  virtual ~LevelMenuScene(void);
  static LevelMenuScene* create(int act, std::string filename);
  virtual bool init(int act, std::string filename);
};

#endif /* __LEVEL_MENU_SCENE__ */
