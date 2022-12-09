#include <nodes/identifier.h>

using namespace ast::nodes;

// Identifier node class

IdentifierNode::IdentifierNode(std::string name) : Node(IDENTIFIER) {
    m_name = *new std::string(std::move(name));
}

IdentifierNode::~IdentifierNode() {
    m_name.clear();
}

std::string IdentifierNode::name() {
    return m_name;
}

// --- Identifier node class