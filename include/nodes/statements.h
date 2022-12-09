#ifndef STATEMENTS_NODE_H
#define STATEMENTS_NODE_H

#include <vector>
#include <nodes/node.h>

namespace ast {
    namespace nodes {
        class StatementsNode : public Node
        {
            std::vector<Node *> *m_statements;
            int m_index = 0;

        public:
            StatementsNode();
            ~StatementsNode() override;

            void addStatement(Node *statement);
            std::vector<Node *> *statements();

            void reset();
            void next();
            Node *current();

            unsigned long int size();
        };
    }
}

#endif