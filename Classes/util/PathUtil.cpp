#include "PathUtil.h"
#include <sstream>

bool PathUtil::m_use_png = false;

std::string PathUtil::getScene(int act, int level) {
  return "scene/" + std::to_string(act) + "/" + std::to_string(level) + "/scene.json";
}

std::string PathUtil::getAct(int act) {
  return "conf/act/" + std::to_string(act) + "/scene.json";
}

std::string PathUtil::getImageWithExtension(std::string path) {
  if (PathUtil::m_use_png) {
    return path + ".png";
  } else {
    return path + ".pvr";
  }
}
