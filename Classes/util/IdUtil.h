#ifndef __ID_UTIL__
#define __ID_UTIL__

#include <string>
#include <unordered_map>

#include "cocos2d.h"

class IdUtil : public cocos2d::Ref
{
public:
  static IdUtil* getInstance();
  static void destroyInstance();

private:
  IdUtil(void);
  ~IdUtil(void);

public:
  virtual bool init();
  virtual std::string getId(std::string type);

protected:
  std::unordered_map<std::string, int> m_idCount;
};

#endif
