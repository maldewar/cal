#include <stdlib.h> 
#include "cmath"
#include "CMath.h"

float CMath::m_mToPx = 100;
float CMath::m_pxToM = 1/100;
float CMath::m_cameraTargetWidthM = 3.25;
float CMath::m_maxZoomFactor = 1.3;
int CMath::m_mToPxRatio = 1;

CMath::CMath() {
};

void CMath::setFactor(int screenWidth, int screenHeight) {
    m_mToPx = screenWidth / m_cameraTargetWidthM;
    m_pxToM = 1 / m_mToPx;
    m_mToPxRatio = round(m_mToPx * m_maxZoomFactor);
};

cocos2d::Vec2* CMath::getPointAt(float x, float y, float distance, float angle) {
    x += distance * cos(angle);
    y += distance * sin(angle);
    return new cocos2d::Vec2(x, y);
};

cocos2d::Vec2* CMath::getPointAt(cocos2d::Vec2* base, float distance, float angle) {
    return getPointAt(base->x, base->y, distance, angle);
};

b2Vec2* CMath::getWorldPointAt(float x, float y, float distance, float angle) {
  x += distance * cos(angle);
  y += distance * sin(angle);
  return new b2Vec2(x, y);
}

b2Vec2* CMath::getWorldPointAt(b2Vec2* base, float distance, float angle) {
  return getWorldPointAt(base->x, base->y, distance, angle);
}

float CMath::random(float a, float b) {
  float random = ((float) rand()) / (float) RAND_MAX;
  float diff = b - a;
  float r = random * diff;
  return (a + r);
};

float CMath::getTriangleAngle(float aX, float aY,
                              float bX, float bY,
                              float cX, float cY) {
  float dAB = getDistance(aX, aY, bX, bY);
  float dBC = getDistance(bX, bY, cX, cY);
  float dCA = getDistance(cX, cY, aX, aY);
  float pX, pY;
  if (dAB < dBC && dAB < dCA) {
    //dAB smaller edge, C pointing vertix.
    pX = cX;
    pY = cY;
  } else if (dBC < dAB && dBC < dCA) {
    //dBC smaller edge, A pointing vertix.
    pX = aX;
    pY = aY;
    aX = bX;
    aY = bY;
    bX = cX;
    bY = cY;
  } else {
    //dCA smaller edge, B pointing vertix.
    pX = bX;
    pY = bY;
    bX = aX;
    bY = aY;
    aX = cX;
    aY = cY;
  }
  float angleAP = CMath::getAngle(pX, pY, aX, aY);
  float angleBP = CMath::getAngle(pX, pY, bX, bY);
  return ((angleAP + angleBP) / 2) + M_PI;
}

float CMath::getAngleOffset(float base, float offset) {
  float angle = fmod(base + offset, M_PI * 2);
  if (angle > M_PI)
    angle -= 2 * M_PI;
  if (angle < -M_PI)
    angle += 2 * M_PI;
  return angle;
};

bool CMath::linesIntersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    return ((relativeCCW(x1, y1, x2, y2, x3, y3) *
        relativeCCW(x1, y1, x2, y2, x4, y4) <= 0)
        && (relativeCCW(x3, y3, x4, y4, x1, y1) *
        relativeCCW(x3, y3, x4, y4, x2, y2) <= 0));
};

int CMath::relativeCCW(float x1, float y1, float x2, float y2, float px, float py)
{
    x2 -= x1;
    y2 -= y1;
    px -= x1;
    py -= y1;
    double ccw = px * y2 - py * x2;
    if (ccw == 0.0f) {
        // The point is colinear, classify based on which side of
        // the segment the point falls on.  We can calculate a
        // relative value using the projection of px,py onto the
        // segment - a negative value indicates the point projects
        // outside of the segment in the direction of the particular
        // endpoint used as the origin for the projection.
        ccw = px * x2 + py * y2;
        if (ccw > 0.0f) {
            // Reverse the projection to be relative to the original x2,y2
            // x2 and y2 are simply negated.
            // px and py need to have (x2 - x1) or (y2 - y1) subtracted
            //    from them (based on the original values)
            // Since we really want to get a positive answer when the
            //    point is "beyond (x2,y2)", then we want to calculate
            //    the inverse anyway - thus we leave x2 & y2 negated.
            px -= x2;
            py -= y2;
            ccw = px * x2 + py * y2;
            if (ccw < 0.0f) {
                ccw = 0.0f;
            }
        }
    }
    return (ccw < 0.0f) ? -1 : ((ccw > 0.0f) ? 1 : 0);
}
