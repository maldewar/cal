#include "WorldLevelStatisticsLayer.h"
#include "../manager/StorageManager.h"
#include "../scene/LevelMenuScene.h"
#include "../scene/WorldLevelScene.h"
#include "../util/PathUtil.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"
#include "ui/UILayout.h"
#include "ui/UILayoutParameter.h"

USING_NS_CC;

int WorldLevelStatisticsLayer::s_actPageWidth = 1920;

WorldLevelStatisticsLayer::WorldLevelStatisticsLayer() {
  m_rootLayout = nullptr;
}

WorldLevelStatisticsLayer::~WorldLevelStatisticsLayer() {
}

WorldLevelStatisticsLayer* WorldLevelStatisticsLayer::create() {
  WorldLevelStatisticsLayer* worldLevelStatisticsLayer = new (std::nothrow) WorldLevelStatisticsLayer();
  if (worldLevelStatisticsLayer && worldLevelStatisticsLayer->init()) {
    worldLevelStatisticsLayer->autorelease();
    return worldLevelStatisticsLayer;
  }
  CC_SAFE_DELETE(worldLevelStatisticsLayer);
  return nullptr;
}

// on "init" you need to initialize your instance
bool WorldLevelStatisticsLayer::init()
{
  if ( !Layer::init() )
  {
    return false;
  }
  m_rootLayout = ui::Layout::create();
  m_rootLayout->setContentSize(Size(1920, 1080));
  m_rootLayout->setAnchorPoint(Vec2(0, 0));
  m_rootLayout->setPosition(Vec2(0, 0));
  m_rootLayout->setSize(Size(1920, 1080));
  addChild(m_rootLayout);

  ui::Layout* bgLayout = ui::Layout::create();
  bgLayout->setContentSize(Size(1920, 1080));
  bgLayout->setAnchorPoint(Vec2(0, 0));
  bgLayout->setPosition(Vec2(0, 0));
  bgLayout->setSize(Size(1920, 1080));
  bgLayout->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
  bgLayout->setBackGroundColor(Color3B(0, 0, 0));
  bgLayout->setOpacity(128);
  bgLayout->setTouchEnabled(false);
  m_rootLayout->addChild(bgLayout);

  int buttonXPosition = 960;
  int buttonYPosition = 540;

  ui::Button* continueBtn = ui::Button::create("btn_normal.png");
  continueBtn->setPosition(Vec2(buttonXPosition, buttonYPosition));
  continueBtn->addTouchEventListener(CC_CALLBACK_2(WorldLevelStatisticsLayer::continueBtnCallback, this));
  m_rootLayout->addChild(continueBtn);

  return true;
}

void WorldLevelStatisticsLayer::onEnter() {
  Layer::onEnter();
}

void WorldLevelStatisticsLayer::onExit() {
  Layer::onExit();
}

void WorldLevelStatisticsLayer::continueBtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    Director::getInstance()->replaceScene(LevelMenuScene::create(1, PathUtil::getAct(1)));
  }
}
