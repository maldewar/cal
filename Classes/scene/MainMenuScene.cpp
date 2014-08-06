#include <math.h>
#include "MainMenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"

MainMenuScene::MainMenuScene() {
  m_mainMenuUILayer = nullptr;
}

MainMenuScene::~MainMenuScene() {
}

MainMenuScene* MainMenuScene::create() {
  MainMenuScene* mainMenuScene = new (std::nothrow) MainMenuScene();
  if (mainMenuScene && mainMenuScene->init()) {
    mainMenuScene->autorelease();
    return mainMenuScene;
  }
  CC_SAFE_DELETE(mainMenuScene);
  return nullptr;
}

bool MainMenuScene::init(void) {
  CCLOG("CALLING MAIN MENU SCENE INIT.");
  MainMenuUILayer* mainMenuUILayer = MainMenuUILayer::create();
  addChild(mainMenuUILayer, 0);
  return true;
}

void MainMenuScene::onEnter() {
  CCLOG("MainMenuScene::onEnter");
  Scene::onEnter();
}

void MainMenuScene::onExit() {
  CCLOG("MainMenuScene::onExit");
  //Scene::onExit();
  //Node::onExit();
  //stopAllActions();
  //unscheduleAllSelectors();
  //removeFromParentAndCleanup(true);
  Scene::onExit();
}
