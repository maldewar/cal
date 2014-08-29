#include "IdUtil.h"
#include <sstream>

static IdUtil* s_sharedIdUtil = nullptr;

IdUtil* IdUtil::getInstance() {
  if (s_sharedIdUtil == nullptr) {
    s_sharedIdUtil = new IdUtil();
    if (!s_sharedIdUtil || !s_sharedIdUtil->init()) {
      CC_SAFE_DELETE(s_sharedIdUtil);
    }
  }
  return s_sharedIdUtil;
}

void IdUtil::destroyInstance() {
  CC_SAFE_RELEASE_NULL(s_sharedIdUtil);
}

IdUtil::IdUtil(void) {
}

IdUtil::~IdUtil(void) {
  m_idCount.clear();
}

bool IdUtil::init() {
  m_idCount.clear();
  return true;
}

std::string IdUtil::getId(std::string type) {
  int id;
  if (m_idCount.count(type) > 0) {
    id = m_idCount[type];
    id++;
  } else {
    id = 1;
  }
  m_idCount[type] = id;
  std::ostringstream stream;
  stream << type << "_" << id;
  return stream.str();
}
