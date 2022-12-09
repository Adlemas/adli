#include <nodes/ternary.h>

using namespace ast::nodes;

// Ternary node class

TernaryNode::TernaryNode(Node *left, Node *middle, Node *right)
        : Node(TERNARY) {
    m_left = left;
    m_middle = middle;
    m_right = right;
}

TernaryNode::~TernaryNode() {
    delete m_left;
    delete m_middle;
    delete m_right;
}

Node *TernaryNode::left() {
    return m_left;
}

Node *TernaryNode::middle() {
    return m_middle;
}

Node *TernaryNode::right() {
    return m_right;
}

void TernaryNode::setLeft(Node *left) {
    m_left = left;
}

void TernaryNode::setMiddle(Node *middle) {
    m_middle = middle;
}

void TernaryNode::setRight(Node *right) {
    m_right = right;
}

// --- Ternary node class
