#include "StorageManager.h"

static StorageManager* s_sharedStorageManager = nullptr;

std::string StorageManager::s_selected_slot = "slot";
std::string StorageManager::s_slot_pct = "pct";
std::string StorageManager::s_slot_act = "act";
std::string StorageManager::s_slot_lvl = "lvl";
std::string StorageManager::s_slot_time = "time";

StorageManager* StorageManager::getInstance() {
  if (s_sharedStorageManager == nullptr) {
    s_sharedStorageManager = new StorageManager();
    if (!s_sharedStorageManager || !s_sharedStorageManager->init()) {
      CC_SAFE_DELETE(s_sharedStorageManager);
    }
  }
  return s_sharedStorageManager;
}

void StorageManager::destroyInstance() {
  CC_SAFE_RELEASE_NULL(s_sharedStorageManager);
}

StorageManager::StorageManager(void) {
}

StorageManager::~StorageManager(void) {
}

bool StorageManager::init() {
  m_slot_prefix = cocos2d::UserDefault::getInstance()->getStringForKey(s_selected_slot.c_str());
  if (m_slot_prefix.empty()) {
    m_slot_prefix = "s1_";
    cocos2d::UserDefault::getInstance()->setStringForKey(s_selected_slot.c_str(), m_slot_prefix);
    resetSlot();
  }
  return true;
}

float StorageManager::getPercentage() {
  return cocos2d::UserDefault::getInstance()->getFloatForKey((m_slot_prefix + s_slot_pct).c_str());
}

int StorageManager::getAct() {
  return cocos2d::UserDefault::getInstance()->getIntegerForKey((m_slot_prefix + s_slot_act).c_str());
}

int StorageManager::getLevel() {
  return cocos2d::UserDefault::getInstance()->getIntegerForKey((m_slot_prefix + s_slot_lvl).c_str());
}

int StorageManager::getTime() {
  return cocos2d::UserDefault::getInstance()->getIntegerForKey((m_slot_prefix + s_slot_time).c_str());
}

void StorageManager::setPercentage(float percentage) {
  cocos2d::UserDefault::getInstance()->setFloatForKey((m_slot_prefix + s_slot_pct).c_str(), percentage);
  cocos2d::UserDefault::getInstance()->flush();
}

void StorageManager::setAct(int act) {
  cocos2d::UserDefault::getInstance()->setIntegerForKey((m_slot_prefix + s_slot_act).c_str(), act);
  cocos2d::UserDefault::getInstance()->setIntegerForKey((m_slot_prefix + s_slot_lvl).c_str(), 0);
  cocos2d::UserDefault::getInstance()->flush();
}

void StorageManager::setLevel(int level) {
  cocos2d::UserDefault::getInstance()->setIntegerForKey((m_slot_prefix + s_slot_lvl).c_str(), level);
  cocos2d::UserDefault::getInstance()->flush();
}

void StorageManager::setTime(int time) {
  cocos2d::UserDefault::getInstance()->setIntegerForKey((m_slot_prefix + s_slot_time).c_str(), time);
  cocos2d::UserDefault::getInstance()->flush();
}

void StorageManager::resetSlot() {
  cocos2d::UserDefault::getInstance()->setFloatForKey((m_slot_prefix + s_slot_pct).c_str(), 0.0f);
  cocos2d::UserDefault::getInstance()->setIntegerForKey((m_slot_prefix + s_slot_act).c_str(), 1);
  cocos2d::UserDefault::getInstance()->setIntegerForKey((m_slot_prefix + s_slot_lvl).c_str(), 1);
  cocos2d::UserDefault::getInstance()->setIntegerForKey((m_slot_prefix + s_slot_time).c_str(), 0);
  cocos2d::UserDefault::getInstance()->flush();
}
