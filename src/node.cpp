#include <nodes/node.h>

using namespace ast::nodes;

// Common node class

Node::Node(NodeType type) {
    m_type = type;
}

Node::~Node() = default;

NodeType Node::type() {
    return m_type;
}
