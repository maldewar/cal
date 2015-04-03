#include "BackgroundLayer.h"
#include "../util/ArtUtil.h"
#include "../util/PathUtil.h"

#include <spine/spine-cocos2dx.h>

USING_NS_CC;

BackgroundLayer::BackgroundLayer() : BaseLayer() {
  m_color      = Color4B::BLACK;
  m_color.a    = 0;
  m_imgStretch = true;
  m_imgAlpha   = 1;
  m_layerColor = nullptr;
  m_imgLayer   = nullptr;
}

BackgroundLayer* BackgroundLayer::create(BgLayerDef* bgLayerDef) {
  BackgroundLayer* backgroundLayer = new (std::nothrow) BackgroundLayer();
  if (backgroundLayer && backgroundLayer->init(bgLayerDef)) {
    backgroundLayer->autorelease();
    return backgroundLayer;
  }
  CC_SAFE_DELETE(backgroundLayer);
  return nullptr;
}

bool BackgroundLayer::init(BgLayerDef* bgLayerDef)
{
  if (! BaseLayer::init(bgLayerDef)) {
    return false;
  }
  m_color = ArtUtil::getColor4B(bgLayerDef->getColor());
  m_imgStretch = bgLayerDef->isImgStretch();
  m_imgAlpha = bgLayerDef->getImgAlpha();

  // Create image layer
  if (bgLayerDef->getImgPath().compare("") != 0) {
    cocos2d::Sprite* m_imgLayer = cocos2d::Sprite::create(
        PathUtil::getImageWithExtension(bgLayerDef->getImgPath()));
    m_imgLayer->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
    m_imgLayer->setPosition(m_size.width/2, m_size.height/2);
    if (bgLayerDef->isImgStretch()) {
      m_imgLayer->setScale(m_size.width/m_imgLayer->getContentSize().width,
                           m_size.height/m_imgLayer->getContentSize().height);
    }
    m_imgLayer->setOpacity(bgLayerDef->getImgAlpha() * 255);
    this->addChild(m_imgLayer);
  }

  // Create color layer
  m_layerColor = cocos2d::LayerColor::create(m_color, m_size.width, m_size.height);
  m_layerColor->ignoreAnchorPointForPosition(false);
  m_layerColor->setAnchorPoint(cocos2d::Vec2(0, 0));
  m_layerColor->setPosition(cocos2d::Vec2(0, 0));
  this->addChild(m_layerColor);

  spine::SkeletonAnimation* skeletonNode = spine::SkeletonAnimation::createWithFile("skeletons/unit/skeleton.json", "unit/skeleton.atlas");
  skeletonNode->setAnimation(0, "still", true);
  skeletonNode->setSkin("calavera_a");
  addChild(skeletonNode);


  return true;
}
