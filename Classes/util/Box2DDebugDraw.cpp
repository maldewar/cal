
#include "Box2DDebugDraw.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#ifndef WIN32
#include <alloca.h>
#endif

using namespace cocos2d;

Box2DDebugDraw::Box2DDebugDraw(float aRatio) : mRatio(aRatio)
    , mPointSizeLocation(-1)
    , mColorLocation(-1)
{
  initShader();
}


void Box2DDebugDraw::initShader( void )
{
    mShaderProgram = ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_U_COLOR);
    mPointSizeLocation = mShaderProgram->getUniformLocation("u_pointSize");
    mColorLocation = mShaderProgram->getUniformLocation("u_color");
}


void Box2DDebugDraw::DrawPolygon(const b2Vec2* aVertices, int32 aVertexCount, const b2Color& aColor)
{
    for (int i = 0; i < DEBUG_DRAW_MAX_VERTICES && i < aVertexCount; i++ )
        mVertices[i].setPoint( mRatio * aVertices[i].x, mRatio * aVertices[i].y );
    
    DrawPrimitives::setDrawColor4F(aColor.r, aColor.g, aColor.b, 1);
    DrawPrimitives::drawPoly((Point*)aVertices, aVertexCount, true);
}


void Box2DDebugDraw::DrawSolidPolygon(const b2Vec2* aVertices, int32 aVertexCount, const b2Color& aColor)
{
    for (int i = 0; i < DEBUG_DRAW_MAX_VERTICES && i < aVertexCount; i++ )
        mVertices[i].setPoint( mRatio * aVertices[i].x, mRatio * aVertices[i].y );
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    DrawPrimitives::drawSolidPoly(mVertices, aVertexCount, Color4F(aColor.r, aColor.g, aColor.b, 0.25));
    
    DrawPrimitives::setDrawColor4F(aColor.r, aColor.g, aColor.b, 1);
    DrawPrimitives::drawPoly(mVertices, aVertexCount, true);
}


void Box2DDebugDraw::DrawCircle(const b2Vec2& aCenter, float32 aRadius, const b2Color& aColor)
{
    DrawPrimitives::setDrawColor4F(aColor.r, aColor.g, aColor.b, 1);
    DrawPrimitives::drawCircle(Point(mRatio * aCenter.x, mRatio * aCenter.y), aRadius, 0, DEBUG_DRAW_CIRCLE_SEGMENTS, false, 1, 1);
}


void Box2DDebugDraw::DrawSolidCircle(const b2Vec2& aCenter, float32 aRadius, const b2Vec2& aAxis,
		const b2Color& aColor)
{
    const float coef = 2.0f * (float)M_PI / DEBUG_DRAW_CIRCLE_SEGMENTS;
    
    mVertices[0].setPoint( mRatio * aCenter.x, mRatio * aCenter.y );
    for(unsigned int i = 0; i <= DEBUG_DRAW_CIRCLE_SEGMENTS; i++) {
        float rads = i*coef;
        GLfloat j = aRadius * cosf(rads) + mRatio * aCenter.x;
        GLfloat k = aRadius * sinf(rads) + mRatio * aCenter.y;
        
        mVertices[i].setPoint( j, k );
    }
    DrawPrimitives::drawSolidPoly(mVertices, DEBUG_DRAW_CIRCLE_SEGMENTS, Color4F(aColor.r, aColor.g, aColor.b, 0.25));
    
    DrawPrimitives::setDrawColor4F(aColor.r, aColor.g, aColor.b, 1);
    DrawPrimitives::drawCircle(Point(mRatio * aCenter.x, mRatio * aCenter.y), aRadius, 0, DEBUG_DRAW_CIRCLE_SEGMENTS, false);
    
    b2Vec2 p = aCenter + aRadius * aAxis;
    DrawPrimitives::drawLine(Point(aCenter.x, aCenter.y), Point(p.x, p.y));
}


void Box2DDebugDraw::DrawParticles(const b2Vec2 *centers_old, float32 radius, const b2ParticleColor *colors, int32 count) {
/*
  // normally this is how we'd enable them on desktop OpenGL,
  // but for some reason this is not applying textures, so we use alpha instead
  glEnable(GL_POINT_SPRITE);
  glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
  */
  const float particle_size_multiplier = 8;  // no falloff
  const float global_alpha = 0.35f;  // instead of texture

  mShaderProgram->setUniformLocationWith1f(mPointSizeLocation, radius * mRatio * particle_size_multiplier);

  GL::blendFunc(GL_SRC_ALPHA, GL_ONE);

  b2Vec2* centers = (b2Vec2 *) alloca(sizeof(b2Vec2) * count);
  for(int i=0; i<count; i++) {
    centers[i].x = centers_old[i].x *mRatio;
    centers[i].y = centers_old[i].y *mRatio;
  }

  glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, centers);
  glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 0, 0, 1, 1);

  if (0 /*colors*/)
  {
    // hack to render with proper alpha on desktop for Testbed
    b2ParticleColor * mcolors = const_cast<b2ParticleColor *>(colors);
    for (int i = 0; i < count; i++)
    {
      mcolors[i].a = static_cast<uint8>(global_alpha * 255);
    }
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, &colors[0].r);
  }
  else
  {
    glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_COLOR, 1, 1, 1, global_alpha);
    mShaderProgram->setUniformLocationWith4f(mColorLocation, 1, 1, 1, global_alpha);
  }

  glDrawArrays(GL_POINTS, 0, count);
  CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,count);
}


void Box2DDebugDraw::DrawSegment(const b2Vec2& aP1, const b2Vec2& aP2, const b2Color& aColor)
{
  DrawPrimitives::setDrawColor4F(aColor.r, aColor.g, aColor.b, 1);
  DrawPrimitives::drawLine(ccp(aP1.x, aP1.y), ccp(aP2.x, aP2.y));
}


void Box2DDebugDraw::DrawTransform(const b2Transform& aXf)
{
	b2Vec2 p1 = aXf.p, p2;
	const float32 k_axisScale = 0.4f;

	p2 = p1 + k_axisScale * aXf.q.GetXAxis();
	DrawSegment(p1, p2, b2Color(1, 0, 0));

	p2 = p1 + k_axisScale * aXf.q.GetYAxis();
	DrawSegment(p1, p2, b2Color(0, 1, 0));
}


void Box2DDebugDraw::DrawPoint(const b2Vec2& aP, float32 aSize, const b2Color& aColor)
{
  DrawPrimitives::setDrawColor4F(aColor.r, aColor.g, aColor.b, 1);
  DrawPrimitives::drawPoint( Point(mRatio * aP.x, mRatio * aP.y) );
}


void Box2DDebugDraw::DrawString(int aX, int aY, const char* aString, ...)
{
}


void Box2DDebugDraw::DrawAABB(b2AABB* aAabb, const b2Color& aColor)
{
	mVertices[0].setPoint( aAabb->lowerBound.x * mRatio, aAabb->lowerBound.y * mRatio );
	mVertices[1].setPoint( aAabb->upperBound.x * mRatio, aAabb->lowerBound.y * mRatio );
	mVertices[2].setPoint( aAabb->upperBound.x * mRatio, aAabb->upperBound.y * mRatio );
	mVertices[3].setPoint( aAabb->lowerBound.x * mRatio, aAabb->upperBound.y * mRatio );
  DrawPrimitives::drawPoly((Point*)mVertices, 8, true);
}

