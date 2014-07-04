#include "Area.h"

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
  return true;
}

void Area::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags) {
  CCLOG("drawing Area");
  float mRatio = 1;
  int maxVertices = 64;
  cocos2d::CCPoint mVertices[maxVertices];
  cocos2d::ccGLEnableVertexAttribs( cocos2d::kCCVertexAttribFlag_Position );
  cocos2d::kmGLPushMatrix();
  const b2Transform& xf = m_body->GetTransform();
  for (b2Fixture* f = m_body->GetFixtureList(); f; f = f->GetNext()) {
    CCLOG("Entering draw fixture");
    //b2Fixture* fixture, const b2Transform& xf, const b2Color& color
    //DrawShape(f, xf, b2Color(0.5f, 0.9f, 0.5f));
    const b2Color& color = b2Color(0.5f, 0.9f, 0.5f);
    b2PolygonShape* poly = (b2PolygonShape*)f->GetShape();
    int32 vertexCount = poly->m_count;
    b2Assert(vertexCount <= b2_maxPolygonVertices);
    b2Vec2 vertices[b2_maxPolygonVertices];
    for (int32 i = 0; i < vertexCount; ++i)
    {
      vertices[i] = b2Mul(xf, poly->m_vertices[i]);
    }
    //const b2Vec2* aVertices, int32 aVertexCount, const b2Color& aColor
    //m_debugDraw->DrawSolidPolygon(vertices, vertexCount, color);
    for (int i = 0; i < maxVertices && i < vertexCount; i++ )
        mVertices[i].setPoint( mRatio * vertices[i].x, mRatio * vertices[i].y );

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    cocos2d::ccDrawSolidPoly(mVertices, vertexCount, cocos2d::ccc4f(color.r, color.g, color.b, 1));

    cocos2d::ccDrawColor4F(color.r, color.g, color.b, 1);
    
    cocos2d::ccDrawPoly(mVertices, vertexCount, true);
  }
  /*
    for (int i = 0; i < DEBUG_DRAW_MAX_VERTICES && i < aVertexCount; i++ )
        mVertices[i].setPoint( mRatio * aVertices[i].x, mRatio * aVertices[i].y );

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    ccDrawSolidPoly(mVertices, aVertexCount, ccc4f(aColor.r, aColor.g, aColor.b, 0.5));

    ccDrawColor4F(aColor.r, aColor.g, aColor.b, 1);
    ccDrawPoly(mVertices, aVertexCount, true);
  */
  cocos2d::kmGLPopMatrix();
}
