#ifndef _GRAPHNODE_H_
    #define _GRAPHNODE_H_

#include "cocos2d.h"      
#include "Box2D/Box2D.h"

class GraphNode : public b2Vec2 {
public:
  int id;
  bool intern;
  bool terminal;
  int action;

private:
  b2Vec2* m_anchor;

public:
  GraphNode();
  GraphNode(int id);
  GraphNode(int id, float x, float y);
  int GetId();
  bool IsIntern();
  b2Vec2* GetAnchor();

};

#endif
