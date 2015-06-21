#include "GraphNode.h"

GraphNode::GraphNode() : GraphNode(0, 0, 0) {};

GraphNode::GraphNode(int id) : GraphNode(id, 0, 0) {};

GraphNode::GraphNode(int id, float x, float y) : b2Vec2(x, y) {
    this->id = id;
    intern   = false;
    terminal = false;
    action   = 0;
    m_anchor   = nullptr;
}

int GraphNode::GetId() {
    return id;
}

bool GraphNode::IsIntern() {
    return intern;
}

b2Vec2* GraphNode::GetAnchor() {
  return m_anchor;
}
