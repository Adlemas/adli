#include <nodes/binary.h>

using namespace ast::nodes;

// Binary node class

BinaryNode::BinaryNode(Node *left, Node *right)
        : Node(BINARY) {
    m_left = left;
    m_right = right;
    m_operator = NONE;
}

BinaryNode::BinaryNode(Node *left, Node *right, Operator op)
        : Node(BINARY) {
    m_left = left;
    m_right = right;
    m_operator = op;
}

BinaryNode::~BinaryNode() {
    delete m_left;
    delete m_right;
}

Node *BinaryNode::left() {
    return m_left;
}

Node *BinaryNode::right() {
    return m_right;
}

Operator BinaryNode::op() {
    return m_operator;
}

void BinaryNode::setLeft(Node *left) {
    m_left = left;
}

void BinaryNode::setRight(Node *right) {
    m_right = right;
}

void BinaryNode::setOp(Operator op) {
    m_operator = op;
}

// --- Binary node class
