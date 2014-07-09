#include "UILayer.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"
#include "ui/UILayout.h"
#include "ui/UILayoutParameter.h"
#include "platform/CCDevice.h"

USING_NS_CC;

bool UILayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    m_visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    m_winSize = Director::getInstance()->getWinSize();

    m_scene = nullptr;

    return true;
}

void UILayer::pushState(int state) {
  if (!m_states.empty()) {
    playAnimationOut(m_states.top());
  }
  if ( m_states.empty() || state != m_states.top()) {
    m_states.push(state);
    playAnimationIn(state);
  }
}

void UILayer::popState() {
  if (!m_states.empty()) {
    playAnimationOut(m_states.top());
    m_states.pop();
    if (!m_states.empty()) {
      playAnimationIn(m_states.top());
    }
  }
}

void UILayer::playAnimationIn(int state) {
}

void UILayer::playAnimationOut(int state) {
}

void UILayer::playStateAnimation(std::string name) {
}

void UILayer::finishStateAnimation() {
}

void UILayer::scaleWidget(ui::Widget* widget, const Align align) {
  int dpi = Device::getDPI();
  int minDPI = 96;
  int maxDPI = 240;
  if (dpi < minDPI || dpi > maxDPI)
    return;
  float minScale = 0.4;
  float maxScale = 0.75;
  float scale = (dpi - minDPI) * (maxScale - minScale) / (float)(maxDPI - minDPI) + minScale;
  Size contentSize = widget->getContentSize();
  CCLOG("SCALE %f SIZEX:%f SIZEY:%f", scale, contentSize.width, contentSize.height);
  float positionX = contentSize.width - (scale * contentSize.width);
  float positionY = contentSize.height - (scale * contentSize.height);
  widget->setScale(scale);
  // margin (left, top, right, bottom)
  switch(align) {
    case Align::TopLeft:
      widget->getLayoutParameter()->setMargin(ui::Margin(0,-positionY,0,0));
      break;
    case Align::TopRight:
      widget->getLayoutParameter()->setMargin(ui::Margin(0,-positionY,-positionX,0));
      break;
    case Align::BottomLeft:
      break;
    case Align::BottomRight:
      widget->getLayoutParameter()->setMargin(ui::Margin(0,0,-positionX,0));
      break;
  }
}

void UILayer::setScene(WorldLevelScene* scene) {
  m_scene = scene;
}