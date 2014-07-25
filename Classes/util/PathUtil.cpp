#include "PathUtil.h"
#include <sstream>

std::string PathUtil::getScene(int act, int level) {
    std::stringstream sstm;
    sstm << "scene/" << act << "/" << level << "/scene.json";
    return sstm.str();
}
