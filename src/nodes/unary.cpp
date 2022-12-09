#include <nodes/unary.h>

using namespace ast::nodes;

// Unary node class

UnaryNode::UnaryNode(Node *node)
        : Node(UNARY) {
    m_node = node;
    m_operator = NONE;
}

UnaryNode::UnaryNode(Node *node, Operator op)
        : Node(UNARY) {
    m_node = node;
    m_operator = op;
}

UnaryNode::~UnaryNode() {
    delete m_node;
}

Node *UnaryNode::node() {
    return m_node;
}

Operator UnaryNode::op() {
    return m_operator;
}

void UnaryNode::setNode(Node *node) {
    m_node = node;
}

void UnaryNode::setOp(Operator op) {
    m_operator = op;
}

// --- Unary node class
