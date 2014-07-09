#include "WorldLevelDebugLayer.h"
#include "ui/UILayout.h"
#include "ui/UILayoutParameter.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool WorldLevelDebugLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    m_scene = nullptr;

    auto size = Director::getInstance()->getWinSize();
    //ui::Layout* layout = ui::Layout::create();
    //layout->setSize(Size(500, 500));
    //layout->setPosition(Vec2(960, 540));
    //layout->setPosition(Vec2(0,540));
    //layout->setPosition(Vec2(0,0));
    //layout->setAnchorPoint(Vec2(0,0));
    //layout->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    //layout->setBackGroundColor(Color3B(128, 128, 128));
    //addChild(layout);

    m_box2dBtn = ui::Button::create("btn_normal.png", "btn_selected.png");
    //m_box2dBtn = ui::Button::create("ui/btn/btn_settings_default.pvr", "ui/btn/btn_settings_press.pvr");
    //m_box2dBtn->setSize(Size(100,100));
    m_box2dBtn->setAnchorPoint(Vec2(0.5f, 0.5f));
    m_box2dBtn->setPosition(Vec2(size.width/2, 50));
    m_box2dBtn->addTouchEventListener(CC_CALLBACK_2(WorldLevelDebugLayer::box2dBtnCallback, this));
    addChild(m_box2dBtn);
    return true;
}

void WorldLevelDebugLayer::box2dBtnCallback(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED && m_scene) {
    bool isDebugEnable = m_scene->isDebugEnable();
    m_scene->enableDebug(!isDebugEnable);
  }
}

void WorldLevelDebugLayer::setScene(WorldLevelScene* scene) {
  m_scene = scene;
}
