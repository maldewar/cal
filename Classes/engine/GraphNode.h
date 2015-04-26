#ifndef _GRAPHNODE_H_
    #define _GRAPHNODE_H_

#include "Box2D/Box2D.h"

class GraphNode : public b2Vec2 {
  public:
    int id;
    bool intern;
    bool terminal;
    int action;
    b2Vec2* anchor;

  public:
    GraphNode();
    GraphNode(int id);
    GraphNode(int id, float x, float y);
    int GetId();
    bool IsIntern();

};

#endif
