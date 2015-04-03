#ifndef _PATH_UTIL_H_
#define _PATH_UTIL_H_

#include <string>

class PathUtil
{
private:
  static bool m_use_png;

public:
  static std::string getScene(int act, int level);
  static std::string getAct(int act);
  static std::string getImageWithExtension(std::string path);
};

#endif
