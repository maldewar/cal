#include "SelectCtrlLayer.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "editor-support/cocostudio/CCActionManagerEx.h"
#include "../scene/WorldLevelScene.h"
#include "../util/CMath.h"
#include "../model/Unit.h"
#include "../component/AIComponentSeekCmd.h"

USING_NS_CC;

SelectCtrlLayer* SelectCtrlLayer::create(WorldLevelScene* scene) {
  SelectCtrlLayer* selectCtrlLayer = new (std::nothrow) SelectCtrlLayer();
  if (selectCtrlLayer && selectCtrlLayer->init(scene)) {
    selectCtrlLayer->autorelease();
    return selectCtrlLayer;
  }
  CC_SAFE_DELETE(selectCtrlLayer);
  return nullptr;
}

bool SelectCtrlLayer::init(WorldLevelScene* scene) {
  if ( !WorldLevelCtrlLayer::init(scene) ) {
    return false;
  }
  m_selectCtrl = WheelCtrl::create(m_scene, WHEEL_CTRL_TYPE_SELECT);
  m_cursorCtrl = WheelCtrl::create(m_scene, WHEEL_CTRL_TYPE_CURSOR);
  m_rayCastTool = new RayCastTool(10.0f);
  m_rayCastTool->SetFilter(ENTITY_TYPE_AREA);
  addChild(m_selectCtrl);
  addChild(m_cursorCtrl);
  m_showingTime = 0.34f;
  m_cooldownTime = 0.5f;
  m_isFollowingCtrl = false;
  m_isPausingCtrl = true;
  m_isFadeToBlackCtrl = false;
  m_worldTargetPoint = new b2Vec2(0, 0);
  m_units.clear();
  return true;
}

void SelectCtrlLayer::update(float dt) {
  WorldLevelCtrlLayer::update(dt);
  if (m_state == State::Active) {
    m_selectCtrl->setRotation(m_selectCtrl->getRotation() + 0.7f);
    m_cursorCtrl->setRotation(m_cursorCtrl->getRotation() + 2.0f);
  }
}

void SelectCtrlLayer::playAnimationIn(int state) {
}

void SelectCtrlLayer::playAnimationOut(int state) {
  switch (state) {
    case State::Showing:
      m_selectCtrl->setRotation(0);
      m_cursorCtrl->setRotation(0);
      m_selectCtrl->hide();
      m_cursorCtrl->hide();
      break;
  }
}

void SelectCtrlLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event){
  Touch* touch = touches[0];
  Point screenPos = touch->getLocation();
  m_cursorCtrl->setPosition(screenPos);
  b2Vec2 worldPos = m_scene->screenToWorld(screenPos);
  m_rayCastTool->RayCast(m_scene->getWorldLevelLayer()->getWorld(),
                         worldPos.x, worldPos.y,
                         m_scene->getGravityAngle());
}

void SelectCtrlLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event){
  Touch* touch = touches[0];
  Point screenPos = touch->getLocation();
  m_cursorCtrl->setPosition(screenPos);
  b2Vec2 worldPos = m_scene->screenToWorld(screenPos);
  m_rayCastTool->RayCast(m_scene->getWorldLevelLayer()->getWorld(),
                         worldPos.x, worldPos.y,
                         m_scene->getGravityAngle());
}

void SelectCtrlLayer::onBeginCtrlTouch(Entity* entity) {
  m_units.clear();
  if (entity->getType() == ENTITY_TYPE_UNIT) {
    m_units.push_back((Unit*)entity);
  }
  m_selectCtrl->show();
  m_cursorCtrl->show();
  Point p = m_scene->worldToScreen(m_entity->getBody()->GetPosition());
  m_selectCtrl->setPosition(p);
}

void SelectCtrlLayer::onEndCtrlTouch() {
  m_selectCtrl->hide();
  m_cursorCtrl->hide();
  m_worldTargetPoint->Set(m_rayCastTool->GetEnd()->x, m_rayCastTool->GetEnd()->y);
  for (auto unit : m_units) {
    unit->command(new AIComponentSeekCmd(m_rayCastTool->GetWorldEnd()));
  }
}

void SelectCtrlLayer::onCancelCtrlTouch() {
  m_selectCtrl->hide();
  m_cursorCtrl->hide();
}

void SelectCtrlLayer::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags) {
  m_customCommand.func = CC_CALLBACK_0(SelectCtrlLayer::onDraw, this, transform, flags);
  renderer->addCommand(&m_customCommand);
  WorldLevelCtrlLayer::draw(renderer, transform, flags);
}

void SelectCtrlLayer::onDraw( const cocos2d::Mat4 &transform, uint32_t flags) {
  DrawPrimitives::setDrawColor4F(255, 255, 255, 1);
  DrawPrimitives::drawLine(m_scene->worldToScreen(*m_rayCastTool->GetWorldStart()),
                           m_scene->worldToScreen(*m_rayCastTool->GetWorldEnd()));
}
