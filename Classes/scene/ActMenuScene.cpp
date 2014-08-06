#include <math.h>
#include "ActMenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"

ActMenuScene::ActMenuScene() {
  m_actMenuLayer = nullptr;
  m_basicUILayer = nullptr;
}

ActMenuScene::~ActMenuScene() {
}

ActMenuScene* ActMenuScene::create() {
  ActMenuScene* mainMenuScene = new (std::nothrow) ActMenuScene();
  if (mainMenuScene && mainMenuScene->init()) {
    mainMenuScene->autorelease();
    return mainMenuScene;
  }
  CC_SAFE_DELETE(mainMenuScene);
  return nullptr;
}

bool ActMenuScene::init(void) {
  m_actMenuLayer = ActMenuLayer::create();
  addChild(m_actMenuLayer, 0);
  m_basicUILayer = BasicUILayer::create(BasicUILayer::SceneType::Act);
  addChild(m_basicUILayer);
  return true;
}

void ActMenuScene::onEnter() {
  CCLOG("ActMenuScene::onEnter");
  Scene::onEnter();
}

void ActMenuScene::onExit() {
  CCLOG("ActMenuScene::onExit");
  /*
  stopAllActions();
  removeFromParentAndCleanup(true);
  cocostudio::ActionManagerEx::destroyInstance();
  */
  Scene::onExit();
}
