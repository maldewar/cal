#ifndef _CMATH_H_
    #define _CMATH_H_

#include <string>
#include "cocos2d.h"
#include "Box2D/Box2D.h"

/**
 * Constant for degrees to radians convertion.
 */
const int DEGTORAD = 0.0174532925199432957f;
/**
 * Constant for radians to degrees convertion.
 */
const int RADTODEG = 57.295779513082320876f;

class CMath {
private:
  CMath();
  static int relativeCCW(float x1, float y1, float x2, float y2, float px, float py);

private:
  static float m_mToPx;
  static float m_pxToM;
  static float m_cameraTargetWidthM;
  static float m_maxZoomFactor;
  static int m_mToPxRatio;

public:
  static void setFactor(int screenWidth, int screenHeight);
  static inline float pxToM(float value) {
      return value * m_pxToM;
  };
  static inline float mToPx(float value) {
      return value * m_mToPx;
  };
  static inline  int pxToMInt(float value) {
      return round(pxToM(value));
  };
  static inline int pxToMInt(float value, float scale) {
      return round(pxToM(value * scale));
  };
  static inline int mToPxInt(float value) {
      return round(mToPx(value));
  };
  static inline int mToPxInt(float value, float scale) {
      return round(mToPx(value * scale));
  };
  static inline float getMToPxFactor() {
      return m_mToPx;
  };
  static inline float getPxToMFactor() {
      return m_pxToM;
  };
  static inline int getMToPxRatio() {
      return m_mToPxRatio;
  };
  /**
   * Gets bottom to top Y coordinates.
   */
  static inline float toCartesian(float y, float height) {
      return height - y;
  };
  /**
   * Gets top to bottom Y coordinates.
   */
  static inline float toCanvas(float y, float height) {
      return (y - height) * -1;
  };
  static inline float toDeg(float rad) {
      return rad * RADTODEG;
  };
  static inline float toRad(float deg) {
      return deg * DEGTORAD;
  };
  static inline float getDistance2(float x1, float y1, float x2, float y2) {
      return (pow(x1 - x2, 2) + pow(y1 - y2, 2));
  };
  static inline float getDistance(float x1, float y1, float x2, float y2) {
      return sqrt(getDistance2(x1, y1, x2, y2));
  };
  static cocos2d::Vec2* getPointAt(float x, float y, float distance, float angle);
  static cocos2d::Vec2* getPointAt(cocos2d::Vec2* base, float distance, float angle);
  static b2Vec2* getWorldPointAt(float x, float y, float distance, float angle);
  static b2Vec2* getWorldPointAt(b2Vec2* base, float distance, float angle);
  static float random(float a, float b);
  /**
   * Normalizes an angle in radian between 0 and PI and 0 and -  PI.
   * @angle Angle to normalize in radians.
   * @return Normalized angle.
   */
  static inline float getAbsoluteAngle(float angle) {
    if (angle >= 0 && angle <= M_PI_2)
      return angle;
    else if (angle > 0)
      return fabs(angle - M_PI);
    else if (angle < 0 && angle >= -M_PI_2)
      return fabs(angle);
    else
      return angle + M_PI;
  };
  static inline float getAngle(float x1, float y1, float x2, float y2) {
    return atan2(y2 - y1, x2 - x1);
  };
  static inline float getAngle(cocos2d::Vec2 pointA, cocos2d::Vec2 pointB) {
    return getAngle(pointA.x, pointA.y, pointB.x, pointB.y);
  };
  static inline float getAngle(float xV, float yV, float xA, float yA, float xB, float yB) {
    float dVA = getDistance(xV, yV, xA, yA);
    float dVB = getDistance(xV, yV, xB, yB);
    float dAB = getDistance(xA, yA, xB, yB);
    return acos((pow(dVA, 2) + pow(dVB, 2) - pow(dAB, 2))/(2 * dVA * dVB));
  };
  /**
   * Returns the results of a sum of angles normalized between -PI and PI radians.
   * @param base Base angle.
   * @param offset Offset angle.
   * @return Resulting angle.
   */
  static float getAngleOffset(float base, float offset);
  static inline float getAngleDistance(float angleA, float angleB) {
      return fabs(angleA - angleB);
  };
  static inline float getAbsoluteDiff(float val1, float val2) {
      return fabs(val2 - val1);
  };
  static inline float getAbsolute(float val) {
      return fabs(val);
  };
  static inline float getComplementAngle(float angle) {
      if (angle < 0)
          return -M_PI - angle;
      else
          return M_PI - angle;
  };
  static bool linesIntersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

  template<typename T>
  static inline T mod(T x, T y)
  {
    static_assert(!std::numeric_limits<T>::is_exact , "Mod: floating-point type expected");
    if (0. == y)
      return x;
    double m= x - y * floor(x/y);
    // handle boundary cases resulted from floating-point cut off:
    if (y > 0)              // modulo range: [0..y)
    {
      if (m>=y)           // Mod(-1e-16             , 360.    ): m= 360.
        return 0;
      if (m<0 ) {
        if (y+m == y)
          return 0  ; // just in case...
        else
          return y+m; // Mod(106.81415022205296 , _TWO_PI ): m= -1.421e-14 
      }
    } else {                    // modulo range: (y..0]
      if (m<=y)           // Mod(1e-16              , -360.   ): m= -360.
        return 0;
      if (m>0 ) {
        if (y+m == y)
         return 0  ; // just in case...
        else
         return y+m; // Mod(-106.81415022205296, -_TWO_PI): m= 1.421e-14 
      }
    }
    return m;
  }

  // wrap [rad] angle to [-PI..PI)
  static inline double wrapPosNegPI(double fAng)
  {
    return mod(fAng + M_PI, M_PI * 2) - M_PI;
  }

  // wrap [rad] angle to [0..TWO_PI)
  static inline double wrapTwoPI(double fAng)
  {
    return mod(fAng, M_PI * 2);
  }

  // wrap [deg] angle to [-180..180)
  static inline double wrapPosNeg180(double fAng)
  {
    return mod(fAng + 180., 360.) - 180.;
  }

  // wrap [deg] angle to [0..360)
  static inline double wrap360(double fAng)
  {
    return mod(fAng ,360.);
  }

  static inline double boundBetween(double val, double lowerBound, double upperBound){
    if(lowerBound > upperBound){std::swap(lowerBound, upperBound);}
    val-=lowerBound; //adjust to 0
    double rangeSize = upperBound - lowerBound;
    if(rangeSize == 0){return upperBound;} //avoid dividing by 0
    return val - (rangeSize * std::floor(val/rangeSize)) + lowerBound;
  }
        
};
#endif
