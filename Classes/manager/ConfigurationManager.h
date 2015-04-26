#ifndef __CONFIGURATION_MANAGER__
#define __CONFIGURATION_MANAGER__

#include <vector>
#include <string>

#include "cocos2d.h"

const float M_TO_PX = 540.0f;
const float PX_TO_M = 1/540.0f;
const float DESIGN_HEIGHT = 1080.0f;

class ConfigurationManager : public cocos2d::Ref
{
public:
  static ConfigurationManager* getInstance();
  static void destroyInstance();

private:
  ConfigurationManager(void);
  ~ConfigurationManager(void);

public:
  virtual bool init();

};

#endif
