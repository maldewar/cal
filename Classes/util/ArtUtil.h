#ifndef __ART_UTIL__
#define __ART_UTIL__

#include <string>

#include "cocos2d.h"

class ArtUtil
{
private:
  ArtUtil(void);

public:
  static cocos2d::Color4B getColor4B(std::string hexColor) {
    long int numColor = stol(hexColor, 0, 16);
    int red   = (numColor & 0xFF000000) >> 24;
    int green = (numColor & 0x00FF0000) >> 16;
    int blue  = (numColor & 0x0000FF00) >> 8;
    int alpha = numColor & 0x000000FF;
    cocos2d::log("%d:%d:%d:%d", red, green, blue, alpha);
    return cocos2d::Color4B(red, green, blue, alpha);
  }
};

#endif
