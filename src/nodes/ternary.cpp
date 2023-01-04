#include <nodes/ternary.h>

using namespace ast::nodes;

// Ternary node class

TernaryNode::TernaryNode(Node *left, Node *middle, Node *right)
        : Node(TERNARY) {
    m_condition = left;
    m_left = middle;
    m_right = right;
}

TernaryNode::~TernaryNode() {
    delete m_condition;
    delete m_left;
    delete m_right;
}

Node *TernaryNode::condition() {
    return m_condition;
}

Node *TernaryNode::left() {
    return m_left;
}

Node *TernaryNode::right() {
    return m_right;
}

void TernaryNode::setCondition(Node *condition) {
    m_condition = condition;
}

void TernaryNode::setLeft(Node *left) {
    m_left = left;
}

void TernaryNode::setRight(Node *right) {
    m_right = right;
}

// --- Ternary node class
