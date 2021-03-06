#include "ChoiceGraph.h"
#include <sstream>
#include <algorithm>
#include "../util/CMath.h"
#include "../scene/WorldLevelScene.h"
//#include "../Engine/RayCastTool.h"
//#include "../Util/Log.h"
//#include "Scene.h"
//#include "AreaNode.h"

/*
template <class CGraph> struct ChoiceGraph::exercise_vertex {
    exercise_vertex(CGraph& g_) : m_graph(g_) {}
    CGraph& m_graph;
    typedef typename boost::graph_traits<CGraph>::vertex_descriptor Vertex;
    void operator()(const Vertex& v) const
    {
        typedef boost::graph_traits<CGraph> GraphTraits;
        typename boost::property_map<CGraph, boost::vertex_index_t>::type index = boost::get(boost::vertex_index, m_graph);
        std::stringstream s1;
        s1 << "out-edges: ";
        typename GraphTraits::out_edge_iterator out_i, out_end;
        typename GraphTraits::edge_descriptor e;
        for (boost::tie(out_i, out_end) = boost::out_edges(v, m_graph);
            out_i != out_end; ++out_i) {
            e = *out_i;
            Vertex src = boost::source(e, m_graph), targ = boost::target(e, m_graph);
            s1 << "(" << index[src] << "," << index[targ] << ") ";
        }
        s1 << std::endl;
        Log::L(s1.str());
    }
}
*/

/*
ChoiceGraph::ChoiceGraph(WorldLayer* worldLayer) {
    m_worldLayer = worldLayer;
    m_graph = new CGraph();
    m_nodeIndex = 0;
    //AccessEdgeSet();
    //std::for_each(boost::vertices(*m_graph).first, boost::vertices(*m_graph).second,
    //              exercise_vertex<Graph>(*m_graph));
}
*/

ChoiceGraph::ChoiceGraph() {
  m_graph = new CGraph();
  m_nodeIndex = 0;
  m_debugDrawEnabled = false;
  m_drawNode = cocos2d::DrawNode::create();
  //AccessEdgeSet();
  //std::for_each(boost::vertices(*m_graph).first, boost::vertices(*m_graph).second,
  //              exercise_vertex<Graph>(*m_graph));
}

CGraph* ChoiceGraph::getGraph() {
  return m_graph;
}

cocos2d::DrawNode* ChoiceGraph::getDrawNode() {
  return m_drawNode;
}

bool ChoiceGraph::addEntity(Entity* entity) {
  if (m_entities.count(entity->getId()) == 0) {
    m_entities[entity->getId()] = entity;
    addWalkableBody(entity->getBody());
    updateNodeDraw();
    return true;
  }
  return false;
}

bool ChoiceGraph::removeEntity(std::string id) {
  if (m_entities.count(id) >= 1) {
    m_entities.erase(id);
    // TODO: remove nodes from graph.
    return true;
  }
  return false;
}

/*
GraphNode* ChoiceGraph::GetGraphNode(int areaNodeId) {
    GraphNode* graphNode;
    graphNode = &(*m_graph)[areaNodeId];
    return graphNode;
}
*/

void ChoiceGraph::setDebugDrawEnabled(bool debugDrawEnabled) {
  m_debugDrawEnabled = debugDrawEnabled;
}

bool ChoiceGraph::isDebugDrawEnabled() {
  return m_debugDrawEnabled;
}

void ChoiceGraph::updateNodeDraw() {
  if (!m_debugDrawEnabled)
    return;
  
  CIndexMap index = boost::get(boost::vertex_index, *m_graph);
  vertex_t v, _v;
  GraphNode* node;
  GraphNode* neighbourNode;
  std::pair<CVertexIter, CVertexIter> vp;
  CGraph::adjacency_iterator neighbourIt, neighbourEnd;
  const cocos2d::Color4F nodeColor = cocos2d::Color4F::WHITE;
  const cocos2d::Color4F terminalNodeColor = cocos2d::Color4F::YELLOW;
  const cocos2d::Color4F actionNodeColor = cocos2d::Color4F::ORANGE;
  
  // Clear previous points and lines.
  m_drawNode->clear();
  
  // Iteration through the graph pairs of edges.
  for (vp = boost::vertices(*m_graph); vp.first != vp.second; ++vp.first) {
  
    v = index[*vp.first];
    node = &(*m_graph)[v];

    // Draw node with color according to nature.
    if (node->terminal) {
      if (node->action == ACTION_DESCEND) {
        m_drawNode->drawDot(cocos2d::Vec2(node->x, node->y), 0.02, actionNodeColor);
      } else {
        m_drawNode->drawDot(cocos2d::Vec2(node->x, node->y), 0.02, terminalNodeColor);
      }
    } else {
      m_drawNode->drawDot(cocos2d::Vec2(node->x, node->y), 0.02, nodeColor);
    }

    /*
    SDL_RenderFillRect(m_renderer, m_pointRect);
    if (node->anchor) {
      RendererUtil::SetColor(m_renderer, RendererUtil::Color::GREEN, 92);
      SDL_RenderDrawLine(m_renderer,
        CMath::MToPxInt(node->x),
        CMath::MToPxInt(CMath::ToCanvas(node->y, m_scene_height)),
        CMath::MToPxInt(node->anchor->x),
        CMath::MToPxInt(CMath::ToCanvas(node->anchor->y, m_scene_height)));
      m_pointRect->x = CMath::MToPxInt(node->anchor->x) - m_pointRect->w/2;
      m_pointRect->y = CMath::MToPxInt(CMath::ToCanvas(node->anchor->y, m_scene_height)) - m_pointRect->h/2;
      SDL_RenderFillRect(m_renderer, m_pointRect);
    }
    */
    //RendererUtil::SetColor(m_renderer, RendererUtil::Color::WHITE);
    boost::tie(neighbourIt, neighbourEnd) = boost::adjacent_vertices(v, *m_graph);
    for (; neighbourIt != neighbourEnd; ++neighbourIt){
      _v = index[*neighbourIt];
      neighbourNode = &(*m_graph)[_v];
      if (node->IsIntern()) {
        m_drawNode->drawSegment(cocos2d::Vec2(node->x, node->y), 
            cocos2d::Vec2(neighbourNode->x, neighbourNode->y),
            0.005, cocos2d::Color4F::WHITE);
      } else {
        m_drawNode->drawSegment(cocos2d::Vec2(node->x, node->y), 
            cocos2d::Vec2(neighbourNode->x, neighbourNode->y),
            0.005, cocos2d::Color4F::YELLOW);
      }
    }
   }

    //RendererUtil::ResetColor(m_renderer);
}

GraphNode* ChoiceGraph::addGraphNode(float x, float y, bool offsetAgainstGravity, b2Vec2* anchor) {
    GraphNode* graphNode;
    vertex_t vGraphNode;
    vGraphNode = boost::add_vertex(m_nodeIndex, *m_graph);
    graphNode = &(*m_graph)[vGraphNode];
    graphNode->id = m_nodeIndex;
    if (offsetAgainstGravity) {
        double gravityAgainstAngle = CMath::getAngleOffset(WorldLevelScene::getGravityAngle(), M_PI);
        cocos2d::Vec2* graphNodeLocation = CMath::getPointAt(x, y, VERTEX_GROUND_OFFSET, gravityAgainstAngle);
        graphNode->x = graphNodeLocation->x;
        graphNode->y = graphNodeLocation->y;
    } else {
        graphNode->x = x;
        graphNode->y = y;
    }
    m_nodeIndex++;
    graphNode->SetAnchor(anchor);
    return graphNode;
}

/*
GraphNode* ChoiceGraph::AddGraphNode(AreaNode* areaNode) {
    GraphNode* graphNode;
    vertex_t vGraphNode;
    Vector2* graphNodeLocation;
    double gravityAgainstAngle = CMath::GetAngleOffset(Scene::GetGravity()->Angle(), M_PI);
    if (areaNode->graphNodeId > -1) {
        Log::L("Warning: the AreaGraph already had an GraphNode");
    }
    graphNodeLocation = CMath::GetPointAt(areaNode, VERTEX_GROUND_OFFSET, gravityAgainstAngle);
    vGraphNode = boost::add_vertex(m_nodeIndex, *m_graph);
    graphNode = &(*m_graph)[vGraphNode];
    graphNode->id = m_nodeIndex;
    graphNode->x = graphNodeLocation->x;
    graphNode->y = graphNodeLocation->y;
    graphNode->anchor = areaNode;
    areaNode->graphNodeId = m_nodeIndex;
    m_nodeIndex++;
    return graphNode;
};
*/

void ChoiceGraph::addWalkableBody(b2Body* body) {
  b2Fixture* fixture = body->GetFixtureList();

  if (fixture) {
    // Trail of shape points.
    b2Vec2* point = nullptr;
    b2Vec2* _point  = nullptr;
    b2Vec2* __point = nullptr;
    b2Vec2* firstPoint = nullptr;

    // Point to save.
    cocos2d::Vec2* graphPoint = nullptr;

    // Trail of edges.
    vertex_t v = 0;
    vertex_t _v = 0;
    vertex_t __v = 0;
    vertex_t firstV = -1;

    // Trail of graph node.
    GraphNode* node = nullptr;
    GraphNode* _node = nullptr;
    GraphNode* firstNode = nullptr;

    float angle, _angle, absangle, linesAngle, distance = 0.0f;
    double gravityAngle = WorldLevelScene::getGravityAngle();
    double gravityOffsetAngle = CMath::getAngleOffset(gravityAngle, M_PI_2);
    typedef boost::graph_traits<CGraph>::vertex_descriptor vertex_t;
    int line = 0;
    bool newWalkLine = true;
    bool isIntern = false;
    bool convexChange = false;

    b2Shape::Type shapeType = fixture->GetShape()->GetType();
    if ( shapeType == b2Shape::e_chain ) {
      b2ChainShape* shape = (b2ChainShape*)fixture->GetShape();
      // shape->m_count repeats its last node.
      if (shape->m_count < 3)
        return;
      for (int i = 0; i < shape->m_count - 1; i++) {
        cocos2d::log("x:%f, y:%f", shape->m_vertices[i].x, shape->m_vertices[i].y);


        point = new b2Vec2(body->GetWorldPoint(shape->m_vertices[i]));
        //point->graphNodeId = -1;
        if (_point) { // Wait until we have a previous point.
          // Get angle of edge.
          angle = CMath::getAngleOffset(CMath::getAngle(_point->x, _point->y, point->x, point->y), -gravityOffsetAngle);
          // Get absolute angle of edge (to test walkability).
          absangle = CMath::getAbsoluteAngle(angle);
          if (__point) { //Checks for change in line convexion
            convexChange = isConvexChange(_point->x, _point->y, 
                                          point->x, point->y, 
                                          __point->x, __point->y, gravityAngle);
            if (convexChange) {
              isIntern = !isIntern;
              // If there's a change to convex, we set the last line terminal node.
              if (_node) {
                _node->terminal = true;
                m_terminalNodes.push_back(_node);
              }
            }
          }
          if (absangle < SLOPE_ANGLE_THRESHOLD) {
            // If the angle edge is walkable process the points involved (these are definetly
            // going to get added, but their connections to other edges remain to be seen).
            if (newWalkLine || convexChange) {
                //If there's a newline we set the terminal node on the old one.
                if (_node) {
                    _node->terminal = true;
                    m_terminalNodes.push_back(_node);
                }
                // If a new walking line need to be created we add its first node.
                _node = addGraphNode(_point->x, _point->y, true);
                _v = boost::vertex(_node->id, *m_graph);
                // Set the terminal node for the new line.
                _node->terminal = true;
                m_terminalNodes.push_back(_node);
                //if (area->IsClosed() && firstV == -1) {
                if (firstV == -1) {
                    // Save reference to the first node ever created in case we have a closes area.
                    // This is used to check the final connection.
                    firstV = _v;
                    firstPoint = _point;
                    firstNode = _node;
                }
                newWalkLine = false;
            }
            // If no new line is needed, we already have a previous node to connect to, so we
            // create the second node.
            node = addGraphNode(point->x, point->y, true);
            v = boost::vertex(node->id, *m_graph);
            //if (area->IsClosed()) {// If the area is closed mark node as intern or extern.
                node->intern = isIntern;
                _node->intern = isIntern;
            //}
            if (node->IsIntern() == _node->IsIntern()) {
                //distance = _point->Dist(point);
                distance = CMath::getDistance2(node->x, node->y, _node->x, _node->y);
                boost::add_edge(v, _v, CEdge(distance), *m_graph);
                boost::add_edge(_v, v, CEdge(distance), *m_graph);
            }
            _v = v;
            _node = node;
          } else {
              //If the angle edge is not walkable next one should make a new walking line.
              newWalkLine = true;
          }
          convexChange = false;
        }
        __point = _point;
        _point = point;
        line++;
      }
    }

    // Make last connection for closed areas.
    //if (area->IsClosed() && firstV != -1 && v != firstV && !newWalkLine) {
    if (firstV != -1 && v != firstV && !newWalkLine) {
      angle = CMath::getAngleOffset(CMath::getAngle(_point->x, _point->y, firstPoint->x, firstPoint->y  ),
                                    -gravityOffsetAngle);
      absangle = CMath::getAbsoluteAngle(angle);
      if (absangle < SLOPE_ANGLE_THRESHOLD) {
          distance = CMath::getDistance(_point->x, _point->y,
                                        firstPoint->x, firstPoint->y);
          boost::add_edge(_v, firstV, CEdge(distance), *m_graph);
          boost::add_edge(firstV, _v, CEdge(distance), *m_graph);
      }
    } else if (_node) {
      _node->terminal = true;
      m_terminalNodes.push_back(_node);
    }
  }
}

/*

void ChoiceGraph::AddExit(Exit* exit) {
};
*/

/*
void ChoiceGraph::Build() {
    m_graph->clear();
    m_nodeIndex = 0;
    for (auto &area : m_worldLayer->GetAreas()) {
        AddArea(area);
    }
    //GraphNode* node;
    //for (int i = 0; i < m_nodeIndex; i++) {
    //    node = &(*m_graph)[i];
    //    Log::L("Action for node %d: %d", node->id, node->action);
    //}
    CollectVertexInfo();
    ProcessAreaSegments();
    for (auto &exit : m_worldLayer->GetExits()) {
        AddExit(exit);
    }
    //typedef std::pair<int, int> Edge;
    //Edge edge_array[] = {Edge(A,B), Edge(A,D), Edge(C,A), Edge(D,C),
    //    Edge(C,E), Edge(B,D), Edge(D,E)};
    //const int num_edges = sizeof(edge_array)/sizeof(edge_array[0]);
    //m_graph = new Graph(NUM_VERTICES);
    //for(int i = 0; i < num_edges; ++i) {
    //    Log::L("Adding edge connecting %i to %i", edge_array[i].first, edge_array[i].second);
    //    boost::add_edge(edge_array[i].first, edge_array[i].second, *m_graph);
    //}
};
*/
void ChoiceGraph::commit() {
  for (auto &node : m_terminalNodes) {
    if (node->HasAnchor()) {
      expandNode(node->GetAnchor());
    }
  }
}

bool ChoiceGraph::expandNode(GraphNode* originNode, int direction) {
  //if (node->graphNodeId > -1)
  //  Log::L("Expanding node with id: %d", node->graphNodeId);
  if (BreaksGravity(originNode, node->neighborA) || BreaksGravity(node, node->neighborB)) {
    /*
    Log::L("Raycasting to ground.");
    RayCastTool* rcTool = new RayCastTool(0.9f);
    rcTool->SetFilter(AREA_BODY);
    rcTool->RayCast(m_worldLayer, node->x, node->y, Scene::GetGravity()->Angle());
    if (!rcTool->HasContact())
      return false;
    if (rcTool->GetAreaNodeA()->graphNodeId > -1 && rcTool->GetAreaNodeB()->graphNodeId > -1) {
      ConnectTriad(node, rcTool->GetEnd()->x, rcTool->GetEnd()->y, rcTool->GetAreaNodeA(), rcTool->GetAreaNodeB());
      return true;
    }
    AreaNode* downNode = SelectDownNode(rcTool->GetAreaNodeA(), rcTool->GetAreaNodeB());
    if (downNode) {
      if (downNode == rcTool->GetAreaNodeA() && downNode->graphNodeId > -1) {
        ConnectDuo(node, rcTool->GetEnd()->x, rcTool->GetEnd()->y, rcTool->GetAreaNodeA());
      } else if (downNode->graphNodeId > -1) {
          ConnectDuo(node, rcTool->GetEnd()->x, rcTool->GetEnd()->y, rcTool->GetAreaNodeB());
      } else {
        bool getsExpanded = ExpandNode(downNode);
        if (getsExpanded)
          ConnectDuo(node, rcTool->GetEnd()->x, rcTool->GetEnd()->y, downNode);
        else
          return false;
      }
      return true;
    }
    return false;
    */
  } else {
    /*
      Log::L("Expanding node downwards.");
      AreaNode* downNode = SelectDownNode(node->neighborA, node->neighborB);
      if (AreConnected(node, downNode))
          return false;
      if (downNode->graphNodeId >= 0) {
          Log::L("Connecting nodes %d and %d", node->graphNodeId, downNode->graphNodeId);
          ConnectNodes(node, downNode);
          return true;
      } else {
          int newDirection = 1;
          if (downNode == node->neighborA)
              newDirection = -1;
          //Log::L("Direction %d newDirection:%d downNode:%d node->neighborA:%d", direction, newDirection, downNode, node->neighborA);
          if (direction != 0 && newDirection != direction)
              return false;
          bool getsExpand = ExpandNode(downNode, newDirection);
          if (getsExpand) {
              ConnectNodes(node, downNode);
              return true;
          }
      }
      */
  }
  return false;
}
 /*
bool ChoiceGraph::BreaksGravity(AreaNode* nodeA, AreaNode* nodeB) {
    // TODO: check for gravity breakage.
    if (!nodeA || !nodeB) {
        Log::L("Breaks gravity.");
        if (!nodeA)
            Log::L("not node A");
        if (!nodeB)
            Log::L("not node B");
        return true;
    }
    return false;
};

AreaNode* ChoiceGraph::SelectDownNode(AreaNode* nodeA, AreaNode* nodeB) {
    // TODO: Rotate points around origin before comparision.
    if (!nodeA)
        return nodeB;
    if (!nodeB)
        return nodeA;
    if (nodeA->y < nodeB->y)
        return nodeA;
    else
        return nodeB;
};

bool ChoiceGraph::AreConnected(AreaNode* nodeA, AreaNode* nodeB) {
    if (nodeA->graphNodeId > -1 && nodeB->graphNodeId > -1) {
        vertex_t vA = boost::vertex(nodeA->graphNodeId, *m_graph);
        vertex_t vB = boost::vertex(nodeB->graphNodeId, *m_graph);
        std::pair<edge_t, bool> connectionAB = boost::edge(vA, vB, *m_graph);
        if (connectionAB.second)
            return true;
        else {
            std::pair<edge_t, bool> connectionBA = boost::edge(vB, vA, *m_graph);
            return connectionBA.second;
        }
    }
    return false;
};

bool ChoiceGraph::ConnectNodes(AreaNode* nodeA, AreaNode* nodeB, bool bothDirections) {
    vertex_t vA = 0;
    vertex_t vB = 0;
    GraphNode* graphNodeA;
    GraphNode* graphNodeB;
    if (nodeA->graphNodeId == -1) {
        graphNodeA = AddGraphNode(nodeA);
    } else {
        graphNodeA = GetGraphNode(nodeA->graphNodeId);
    }
    vA = boost::vertex(graphNodeA->id, *m_graph);
    if (nodeB->graphNodeId == -1) {
        graphNodeB = AddGraphNode(nodeB);
    } else {
        graphNodeB = GetGraphNode(nodeB->graphNodeId);
    }
    vB = boost::vertex(graphNodeB->id, *m_graph);
    float distance = nodeA->Dist(nodeB);
    boost::add_edge(vA, vB, CEdge(distance), *m_graph);
    if (bothDirections)
        boost::add_edge(vB, vA, CEdge(distance), *m_graph);
    graphNodeA->terminal = false;
    graphNodeB->terminal = false;
    return true;
};

bool ChoiceGraph::ConnectDuo(AreaNode* node, float x, float y, AreaNode* nodeT) {
    vertex_t vT = 0;
    vertex_t vN = 0;
    vertex_t vM = 0;
    GraphNode* graphNodeT;
    GraphNode* graphNodeN;
    GraphNode* graphNodeM;
    if (node->graphNodeId == -1) {
        graphNodeN = AddGraphNode(node);
    } else {
        graphNodeN = GetGraphNode(node->graphNodeId);
    }
    vN = boost::vertex(graphNodeN->id, *m_graph);
    if (nodeT->graphNodeId == -1) {
        graphNodeT = AddGraphNode(nodeT);
    } else {
        graphNodeT = GetGraphNode(nodeT->graphNodeId);
    }
    vT = boost::vertex(graphNodeT->id, *m_graph);
    graphNodeM = AddGraphNode(x, y, true);
    vM = boost::vertex(graphNodeM->id, *m_graph);
    // Make connections.
    float distance = node->Dist(graphNodeM);
    boost::add_edge(vN, vM, CEdge(distance), *m_graph);
    distance = nodeT->Dist(graphNodeM);
    boost::add_edge(vM, vT, CEdge(distance), *m_graph);
    graphNodeN->terminal = false;
    return true;
};

bool ChoiceGraph::ConnectTriad(AreaNode* node, float x, float y, AreaNode* nodeA, AreaNode* nodeB) {
    vertex_t vA = 0;
    vertex_t vB = 0;
    vertex_t vN = 0;
    vertex_t vM = 0;
    GraphNode* graphNodeA;
    GraphNode* graphNodeB;
    GraphNode* graphNodeN;
    GraphNode* graphNodeM;
    bool connectedAB = AreConnected(nodeA, nodeB);
    bool connectedBA = AreConnected(nodeB, nodeA);
    if (nodeA->graphNodeId == -1) {
        graphNodeA = AddGraphNode(nodeA);
    } else {
        graphNodeA = GetGraphNode(nodeA->graphNodeId);
    }
    vA = boost::vertex(graphNodeA->id, *m_graph);
    if (nodeB->graphNodeId == -1) {
        graphNodeB = AddGraphNode(nodeB);
    } else {
        graphNodeB = GetGraphNode(nodeB->graphNodeId);
    }
    vB = boost::vertex(graphNodeB->id, *m_graph);
    if (node->graphNodeId == -1) {
        graphNodeN = AddGraphNode(node);
    } else {
        graphNodeN = GetGraphNode(node->graphNodeId);
    }
    vN = boost::vertex(graphNodeN->id, *m_graph);
    graphNodeM = AddGraphNode(x, y, true);
    vM = boost::vertex(graphNodeM->id, *m_graph);
    if (connectedAB)
        boost::remove_edge(vA, vB, *m_graph);
    if (connectedBA)
        boost::remove_edge(vB, vA, *m_graph);
    // Make connections.
    float distance = node->Dist(graphNodeM);
    boost::add_edge(vN, vM, CEdge(distance), *m_graph);
    if (connectedAB) {
        distance = nodeA->Dist(graphNodeM);
        boost::add_edge(vA, vM, CEdge(distance), *m_graph);
        distance = nodeB->Dist(graphNodeM);
        boost::add_edge(vM, vB, CEdge(distance), *m_graph);
    }
    if (connectedBA) {
        distance = nodeB->Dist(graphNodeM);
        boost::add_edge(vB, vM, CEdge(distance), *m_graph);
        distance = nodeA->Dist(graphNodeM);
        boost::add_edge(vM, vA, CEdge(distance), *m_graph);
    }
    graphNodeN->terminal = false;
    return true;
};
*/

bool ChoiceGraph::isConvexChange(float xV, float yV, float xA, float yA, float xB, float yB, float angle) {
    float xVA = (xV + xA) / 2;
    float yVA = (yV + yA) / 2;
    float xVB = (xV + xB) / 2;
    float yVB = (yV + yB) / 2;
    cocos2d::Vec2* pVA1 = CMath::getPointAt(xVA, yVA, 300, angle);
    cocos2d::Vec2* pVA2 = CMath::getPointAt(xVA, yVA, -300, angle);
    cocos2d::Vec2* pVB1 = CMath::getPointAt(xVB, yVB, 300, angle);
    cocos2d::Vec2* pVB2 = CMath::getPointAt(xVB, yVB, -300, angle);
    bool aIntersect = CMath::linesIntersect(xV, yV, xA, yA, pVB1->x, pVB1->y, pVB2->x, pVB2->y);
    bool bIntersect = CMath::linesIntersect(xV, yV, xB, yB, pVA1->x, pVA1->y, pVA2->x, pVA2->y);
    return (aIntersect || bIntersect);
}

/*

void ChoiceGraph::AccessEdgeSet() {
    std::stringstream s;
    s << "edges(s) = ";
    typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;
    IndexMap index = boost::get(boost::vertex_index, *m_graph);
    boost::graph_traits<Graph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = boost::edges(*m_graph); ei != ei_end; ++ei) {
        s << "(" << index[boost::source(*ei, *m_graph)] << ","
            << index[boost::target(*ei, *m_graph)] << ") ";
    }
    s << std::endl;
    Log::L(s.str());
};
*/
