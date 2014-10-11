#include "Area.h"
#include "../util/IdUtil.h"

Area::Area() : Entity() {
}

Area::~Area() {
}

int Area::getType() {
  return ENTITY_TYPE_AREA;
}

Area* Area::create() {
  Area* area = new (std::nothrow) Area();
  if (area && area->init())
  {
    area->autorelease();
    return area;
  }
  CC_SAFE_DELETE(area);
  return nullptr;
}

bool Area::init(void) {
  scheduleUpdate();
  setId(IdUtil::getInstance()->getId("area"));
  return true;
}

void Area::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags) {
  m_customCommand.init(_globalZOrder);
  m_customCommand.func = CC_CALLBACK_0(Area::onDraw, this, transform, flags);
  renderer->addCommand(&m_customCommand);
}

void Area::onDraw(const cocos2d::Mat4 &transform, uint32_t flags) {
  cocos2d::Director::getInstance()->pushMatrix(cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
  cocos2d::Director::getInstance()->loadMatrix(cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

  //CHECK_GL_ERROR_DEBUG();
  //glEnable( GL_LINE_SMOOTH );
  //glEnable( GL_POLYGON_SMOOTH );

  float mRatio = 1.0f;
  int maxVertices = 64;
  cocos2d::Point *mVertices = new cocos2d::Point[maxVertices];
  const b2Transform& xf = m_body->GetTransform();
  for (b2Fixture* f = m_body->GetFixtureList(); f; f = f->GetNext()) {
    const b2Color& color = b2Color(0.1f, 0.1f, 0.1f);
    b2PolygonShape* poly = (b2PolygonShape*)f->GetShape();
    int32 vertexCount = poly->m_count;
    b2Assert(vertexCount <= b2_maxPolygonVertices);
    b2Vec2 vertices[b2_maxPolygonVertices];
    for (int32 i = 0; i < vertexCount; ++i)
    {
      //vertices[i] = b2Mul(xf, poly->m_vertices[i]);
      vertices[i] = poly->m_vertices[i];
    }
    for (int i = 0; i < maxVertices && i < vertexCount; i++ ) {
        mVertices[i].setPoint( mRatio * vertices[i].x, mRatio * vertices[i].y );
    }

    cocos2d::DrawPrimitives::drawSolidPoly(mVertices, vertexCount, cocos2d::Color4F(color.r, color.g, color.b, 1));

    cocos2d::DrawPrimitives::setDrawColor4F(color.r, color.g, color.b, 1);
    
    cocos2d::DrawPrimitives::drawPoly(mVertices, vertexCount, true);
  }
  CHECK_GL_ERROR_DEBUG();
  cocos2d::Director::getInstance()->popMatrix(cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
