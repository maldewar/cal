#include "ConfigurationManager.h"

static ConfigurationManager* s_sharedConfigurationManager = nullptr;

ConfigurationManager* ConfigurationManager::getInstance() {
  if (s_sharedConfigurationManager == nullptr) {
    s_sharedConfigurationManager = new ConfigurationManager();
    if (!s_sharedConfigurationManager || !s_sharedConfigurationManager->init()) {
      CC_SAFE_DELETE(s_sharedConfigurationManager);
    }
  }
  return s_sharedConfigurationManager;
}

void ConfigurationManager::destroyInstance() {
  CC_SAFE_RELEASE_NULL(s_sharedConfigurationManager);
}

ConfigurationManager::ConfigurationManager(void) {
}

ConfigurationManager::~ConfigurationManager(void) {
}

bool ConfigurationManager::init() {
  return true;
}
