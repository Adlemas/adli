#include <nodes/literal.h>

using namespace ast::nodes;

// Literal node class

LiteralNode::LiteralNode(LiteralType type, void *value) : Node(LITERAL) {
    m_type = type;
    m_value = value;
}

LiteralType LiteralNode::literal_type() {
    return m_type;
}

LiteralNode::~LiteralNode() = default;

void *LiteralNode::value() {
    return m_value;
}

// --- Literal node class
