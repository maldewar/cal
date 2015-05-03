//  Author: Chris Campbell - www.iforce2d.net
//  -----------------------------------------
//
//  QueryCallbacks
//
//  Some callbacks used with QueryAABB to quickly find fixtures
//  in a rectangular region of the world.
//

#ifndef MULTIQUERYCALLBACKS_H
#define MULTIQUERYCALLBACKS_H

#include "Box2D/Box2D.h"
#include "cocos2d.h"

//
// TouchDownMultiQueryCallback
//
// This is about the simplest type of query callback, for when
// we merely want to get one fixture - any fixture at all - that
// contains the touch point. There may actually be multiple fixtures
// that contain the touch point, and if so it's undetermined which
// one we will get.
//
#include <vector>

class TouchDownMultiQueryCallback : public b2QueryCallback
{
public:
    b2Vec2 m_point;             // this will be initialized with the touch point before calling QueryAABB
    std::vector<b2Fixture*> m_fixtures;
    std::vector<b2Body*> m_bodies;

    // Constructor just records the touch point and initializes the fixture to NULL
    TouchDownMultiQueryCallback(const b2Vec2& point)
    {
        m_point    = point;
    }
    
    // This function will be called by Box2D for every fixture with an AABB that
    // overlaps the query region. We can check each of these to see if the touch
    // point is actually inside them or not. If it is, we record that fixture as
    // the result, and return false to tell Box2D this QueryAABB is finished.
    bool ReportFixture(b2Fixture* fixture)
    {
        // at this point we know the fixture ovelaps the AABB, but we also
        // check if it contains the touch point or not
        if ( fixture->TestPoint(m_point) ) {
          m_bodies.push_back(fixture->GetBody());
          m_fixtures.push_back(fixture);
        }
        // returning true keeps QueryAABB going to check other fixtures in the query region
        return true;
    }

    std::vector<b2Body*> getBodies() {
      return m_bodies;
    }

    std::vector<b2Fixture*> getFixtures() {
      return m_fixtures;
    }

    bool hasTouch() {
      return (m_bodies.size() > 0);
    }
    
};

#endif
