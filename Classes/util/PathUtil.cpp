#include "PathUtil.h"
#include <sstream>

std::string PathUtil::getScene(int act, int level) {
  return "scene/" + std::to_string(act) + "/" + std::to_string(level) + "/scene.json";
}

std::string PathUtil::getAct(int act) {
  return "conf/act/" + std::to_string(act) + "/scene.json";
}
