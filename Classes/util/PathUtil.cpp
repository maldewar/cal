#include "PathUtil.h"
#include <sstream>

std::string PathUtil::getScene(int act, int level) {
  std::stringstream sstm;
  sstm << "scene/" << act << "/" << level << "/scene.json";
  return sstm.str();
}

std::string PathUtil::getAct(int act) {
  std::stringstream sstm;
  sstm << "conf/act/act" << act << ".json";
  return sstm.str();
}
