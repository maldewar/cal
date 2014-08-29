#ifndef _RAYCAST_TOOL_H_
    #define _RAYCAST_TOOL_H_
#include <Box2D/Box2D.h>
#include "cocos2d.h"
#include "../model/Entity.h"

class RayCastTool : public b2RayCastCallback {
    private:
        float m_rayLength;
        b2Vec2*        m_start;
        cocos2d::Vec2* m_startTemp;
        b2Vec2*        m_end;
        cocos2d::Vec2* m_endTemp;
        int            m_objectType;
        int            m_objectTypeFilter;
        bool           m_hasContact;
        Entity*        m_entity;

    public:
        /**
         * Class constructor.
         * @param rayLength Distance in meters to limit raycasting.
         */
        RayCastTool(float rayLength);
        /**
         * Cast a ray to the next object encounter in the world
         * given a reference point and an angle.
         * @param worldLayer World containing the objects to detect.
         * @param x X coordinate for the reference point.
         * @param y Y coordinate for the reference point.
         * @param gravityAngle Angle in radians for casting the ray.
         */
        void RayCast(b2World* world, float x, float y, float gravityAngle);
        /**
         * Cast a ray to the next object encounter in the world
         * given a reference point, an angle and the distance of the ray.
         * @param worldLayer World containing the objects to detect.
         * @param x X coordinate for the reference point.
         * @param y Y coordinate for the reference point.
         * @param gravityAngle Angle in radians for casting the ray.
         * @param distance Distance in meters to cast the ray.
         */
        void RayCast(b2World* world, float x, float y, float gravityAngle, float distance);
        /**
         * Callback function, called when a collition is detected.
         * @param fixture Fixture the dectection was detected against.
         * @param point Point in world coordinates where the collision ocurred.
         * @param fraction Fraction from the original raycast distance.
         * @param index In case of a chain shape, the index of the edge where the collition occurred.
         * @return Fraction of the ray distance where the collition was detected.
         */
        float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
        /**
         * Returns true when there was a ray cast contact.
         * @return True if there was a ray cast contact.
         */
        bool HasContact();
        /**
         * Sets the fixture to ignore all objects except the ones matching this type.
         * param objectType Type of the object to detect.
         */
        void SetFilter(int type);
        /**
         * Clears any previously set filter.
         */
        void ClearFilter();
        /**
         * Gets the starting point of the ray.
         * @return Ray starting point.
         */
        cocos2d::Vec2* GetStart();
        /**
         * Gets the ending point of the ray.
         * @return Ray ending point.
         */
        cocos2d::Vec2* GetEnd();
        /**
         * Gets the type of the colliding object.
         * @return Colliding object type.
         */
        int GetObjectType();
};

#endif
