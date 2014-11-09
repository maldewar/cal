#include "ActMenuLayer.h"
#include "../manager/StorageManager.h"
#include "../scene/LevelMenuScene.h"
#include "../scene/WorldLevelScene.h"
#include "../util/PathUtil.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"
#include "ui/UILayout.h"
#include "ui/UILayoutParameter.h"

USING_NS_CC;

int ActMenuLayer::s_actPageWidth = 1920;

ActMenuLayer::ActMenuLayer() {
  m_rootLayout = nullptr;
}

ActMenuLayer::~ActMenuLayer() {
}

ActMenuLayer* ActMenuLayer::create() {
  ActMenuLayer* actMenuLayer = new (std::nothrow) ActMenuLayer();
  if (actMenuLayer && actMenuLayer->init()) {
    actMenuLayer->autorelease();
    return actMenuLayer;
  }
  CC_SAFE_DELETE(actMenuLayer);
  return nullptr;
}

// on "init" you need to initialize your instance
bool ActMenuLayer::init()
{
  if ( !Layer::init() )
  {
    return false;
  }
  m_rootLayout = ui::Layout::create();
  m_rootLayout->setContentSize(Size(1920, 1080));
  m_rootLayout->setAnchorPoint(Vec2(0, 0));
  m_rootLayout->setPosition(Vec2(0, 0));
  addChild(m_rootLayout);

  m_pageView = ui::PageView::create();
  m_pageView->setContentSize(Size(1920, 1080));
  m_pageView->setAnchorPoint(Vec2(0, 0));
  m_pageView->setPosition(Vec2(0, 0));
  m_rootLayout->addChild(m_pageView);


  int buttonXPosition = 960;
  int buttonYPosition = 540;
  int currentAct = StorageManager::getInstance()->getAct();

  ui::Layout* layout0 = ui::Layout::create();
  layout0->setContentSize(Size(s_actPageWidth, 1080));
  ui::Button* button0 = ui::Button::create();
  button0->setPosition(Vec2(s_actPageWidth / 2, buttonYPosition));
  layout0->addChild(button0);
  m_pageView->insertPage(layout0, 1);
  bool showAct0 = currentAct >= 2;
  showAct0 = true;
  if (showAct0) {
    button0->loadTextureNormal("act/act0.pvr");
    button0->addTouchEventListener(CC_CALLBACK_2(ActMenuLayer::act0BtnCallback, this));
  } else {
    button0->loadTextureNormal("act/act_back.pvr");
    button0->setEnabled(false);
  }

  ui::Layout* layout1 = ui::Layout::create();
  layout1->setContentSize(Size(s_actPageWidth, 1080));
  ui::Button* button1 = ui::Button::create();
  button1->setPosition(Vec2(s_actPageWidth / 2, buttonYPosition));
  layout1->addChild(button1);
  m_pageView->insertPage(layout1, 1);
  bool showAct1 = currentAct >= 2;
  showAct1 = true;
  if (showAct1) {
    button1->loadTextureNormal("act/act1.pvr");
    button1->addTouchEventListener(CC_CALLBACK_2(ActMenuLayer::act1BtnCallback, this));
  } else {
    button1->loadTextureNormal("act/act_back.pvr");
    button1->setEnabled(false);
  }

  ui::Layout* layout2 = ui::Layout::create();
  layout2->setContentSize(Size(s_actPageWidth, 1080));
  ui::Button* button2 = ui::Button::create();
  button2->setPosition(Vec2(s_actPageWidth / 2, buttonYPosition));
  layout2->addChild(button2);
  m_pageView->insertPage(layout2, 1);
  bool showAct2 = currentAct >= 2;
  showAct2 = true;
  if (showAct2) {
    button2->loadTextureNormal("act/act2.pvr");
    button2->addTouchEventListener(CC_CALLBACK_2(ActMenuLayer::act2BtnCallback, this));
  } else {
    button2->loadTextureNormal("act/act_back.pvr");
    button2->setEnabled(false);
  }

  ui::Layout* layout3 = ui::Layout::create();
  layout3->setContentSize(Size(s_actPageWidth, 1080));
  ui::Button* button3 = ui::Button::create();
  button3->setPosition(Vec2(s_actPageWidth / 2, buttonYPosition));
  layout3->addChild(button3);
  m_pageView->insertPage(layout3, 1);
  bool showAct3 = currentAct >= 3;
  showAct3 = true;
  if (showAct3) {
    button3->loadTextureNormal("act/act3.pvr");
    button3->addTouchEventListener(CC_CALLBACK_2(ActMenuLayer::act3BtnCallback, this));
  } else {
    button3->loadTextureNormal("act/act_back.pvr");
    button3->setEnabled(false);
  }

  ui::Layout* layout4 = ui::Layout::create();
  layout4->setContentSize(Size(s_actPageWidth, 1080));
  ui::Button* button4 = ui::Button::create();
  button4->setPosition(Vec2(s_actPageWidth / 2, buttonYPosition));
  layout4->addChild(button4);
  m_pageView->insertPage(layout4, 1);
  bool showAct4 = currentAct >= 4;
  showAct4 = true;
  if (showAct4) {
    button4->loadTextureNormal("act/act4.pvr");
    button4->addTouchEventListener(CC_CALLBACK_2(ActMenuLayer::act4BtnCallback, this));
  } else {
    button4->loadTextureNormal("act/act_back.pvr");
    button4->setEnabled(false);
  }

  ui::Layout* layout5 = ui::Layout::create();
  layout5->setContentSize(Size(s_actPageWidth, 1080));
  ui::Button* button5 = ui::Button::create();
  button5->setPosition(Vec2(s_actPageWidth / 2, buttonYPosition));
  layout5->addChild(button5);
  m_pageView->insertPage(layout5, 1);
  bool showAct5 = currentAct >= 5;
  showAct5 = true;
  if (showAct5) {
    button5->loadTextureNormal("act/act5.pvr");
    button5->addTouchEventListener(CC_CALLBACK_2(ActMenuLayer::act5BtnCallback, this));
  } else {
    button5->loadTextureNormal("act/act_back.pvr");
    button5->setEnabled(false);
  }

  return true;
}

void ActMenuLayer::onEnter() {
  CCLOG("ActMenuLayer::onEnter");
  Layer::onEnter();
}

void ActMenuLayer::onExit() {
  //unscheduleUpdate();
  CCLOG("ActMenuLayer::onExit");
  Layer::onExit();
}

void ActMenuLayer::act0BtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    Director::getInstance()->replaceScene(LevelMenuScene::create(0, PathUtil::getAct(0)));
  }
}

void ActMenuLayer::act1BtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    Director::getInstance()->replaceScene(LevelMenuScene::create(1, PathUtil::getAct(1)));
  }
}

void ActMenuLayer::act2BtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    CCLOG("LOADING WORLD LEVEL SCENE.");
    //Director::getInstance()->replaceScene(LevelMenuScene::create(PathUtil::getAct(2)));
    Director::getInstance()->replaceScene(WorldLevelScene::create(0,1));
  }
}

void ActMenuLayer::act3BtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    //Director::getInstance()->replaceScene(LevelMenuScene::create(PathUtil::getAct(3)));
  }
}

void ActMenuLayer::act4BtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    //Director::getInstance()->replaceScene(LevelMenuScene::create(PathUtil::getAct(4)));
  }
}

void ActMenuLayer::act5BtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    //Director::getInstance()->replaceScene(LevelMenuScene::create(PathUtil::getAct(5)));
  }
}
