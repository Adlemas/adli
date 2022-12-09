#include <nodes/statements.h>

using namespace ast::nodes;

// Statements node class

StatementsNode::StatementsNode()
        : Node(STATEMENTS) {
    m_statements = new std::vector<Node *>();
}

StatementsNode::~StatementsNode() {
    for (auto &m_statement: *m_statements) {
        delete m_statement;
    }
}

void StatementsNode::addStatement(Node *statement) {
    m_statements->push_back(statement);
}

std::vector<Node *> *StatementsNode::statements() {
    return m_statements;
}

void StatementsNode::next() {
    m_index++;
}

void StatementsNode::reset() {
    m_index = 0;
    next();
}

Node *StatementsNode::current() {
    if (m_index >= m_statements->size()) {
        return nullptr;
    }

    return m_statements->at(m_index);
}

unsigned long int StatementsNode::size() {
    return m_statements->size();
}

// --- Statements node class
