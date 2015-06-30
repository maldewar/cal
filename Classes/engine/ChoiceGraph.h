#ifndef _CHOICEGRAPH_H_
  #define _CHOICEGRAPH_H_
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <string>
#include <vector>
#include "GraphNode.h"
#include "../model/Entity.h"
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/topology.hpp"
#include "boost/graph/simple_point.hpp"
#include "boost/graph/dijkstra_shortest_paths.hpp"

const int ACTION_DESCEND = 1;

typedef boost::square_topology<>::point_type CPoint;

struct CEdge {
    CEdge(const std::size_t &w):weight(w) {}
    CEdge():weight(0) {}
    float weight;
};
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS,
                            GraphNode, CEdge> CGraph;
typedef boost::property_map<CGraph, boost::vertex_index_t>::type CIndexMap;
typedef boost::graph_traits<CGraph>::vertex_iterator CVertexIter;
typedef boost::graph_traits<CGraph>::vertex_descriptor vertex_t;
typedef boost::graph_traits<CGraph>::edge_descriptor edge_t;

const float VERTEX_GROUND_OFFSET  = 0.15f;
const float SLOPE_ANGLE_THRESHOLD = M_PI_4;

/**
 * Models a graph according to a Scene.
 */
class ChoiceGraph {
private:
  bool m_debugDrawEnabled;
  CGraph* m_graph;
  std::vector<GraphNode*> m_terminalNodes;
  int m_nodeIndex;
  std::unordered_map<std::string, Entity*> m_entities;
  cocos2d::DrawNode* m_drawNode;

public:
  ChoiceGraph();
  CGraph* getGraph();
  cocos2d::DrawNode* getDrawNode();
  bool addEntity(Entity* entity);
  bool removeEntity(std::string id);
  /*
  void Build();
  void AddArea(Area* area);
  void AddExit(Exit* exit);
  */
  void setDebugDrawEnabled(bool debugDrawEnabled);
  bool isDebugDrawEnabled();
  void updateNodeDraw();

private:
  GraphNode* addGraphNode(float x, float y,
                          bool offsetAgainstGravity = false,
                          b2Vec2* anchor = nullptr);
  void addWalkableBody(b2Body* body);

/*
private:
  GraphNode* GetGraphNode(int areaNodeId);
  GraphNode* AddGraphNode(float x, float y, bool offsetAgainstGravity = false);
  GraphNode* AddGraphNode(AreaNode* areaNode);
  */
  bool isConvexChange(float xV, float yV,
                      float xA, float yA, 
                      float xB, float yB, float angle);
  void commit();
  bool expandNode(GraphNode* originNode, int direction = 0);
  /*
  bool BreaksGravity(AreaNode* nodeA, AreaNode* nodeB);
  AreaNode* SelectDownNode(AreaNode* nodeA, AreaNode* nodeB);
  bool AreConnected(AreaNode* nodeA, AreaNode* nodeB);
  bool ConnectNodes(AreaNode* nodeA, AreaNode* nodeB, bool bothDirections = false);
  bool ConnectDuo(AreaNode* node, float x, float y, AreaNode* nodeT);
  bool ConnectTriad(AreaNode* node, float x, float y, AreaNode* nodeA, AreaNode* nodeB);
  void AccessEdgeSet();
  */
};

#endif
