#include <math.h>
#include "LevelMenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"

LevelMenuScene::LevelMenuScene() {
  m_act = 0;
  m_levelMenuLayer = nullptr;
  m_basicUILayer = nullptr;
}

LevelMenuScene::~LevelMenuScene() {
}

LevelMenuScene* LevelMenuScene::create(int act, std::string filename) {
  LevelMenuScene* mainMenuScene = new (std::nothrow) LevelMenuScene();
  if (mainMenuScene && mainMenuScene->init(act, filename)) {
    mainMenuScene->autorelease();
    return mainMenuScene;
  }
  CC_SAFE_DELETE(mainMenuScene);
  return nullptr;
}

bool LevelMenuScene::init(int act, std::string filename) {
  m_act = act;
  m_levelMenuLayer = LevelMenuLayer::create(m_act, filename);
  m_basicUILayer = BasicUILayer::create(BasicUILayer::SceneType::Level);
  addChild(m_levelMenuLayer, 0);
  addChild(m_basicUILayer, 1);
  return true;
}
