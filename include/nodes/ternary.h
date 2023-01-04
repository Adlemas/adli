#ifndef TERNARY_NODE_H
#define TERNARY_NODE_H

#include <nodes/node.h>

namespace ast {
    namespace nodes {
        // Ternary node
        // Example: (a > b) ? a : b
        class TernaryNode : public Node
        {
            Node *m_condition;
            Node *m_left;
            Node *m_right;

        public:
            TernaryNode(Node *condition, Node *left, Node *right);
            ~TernaryNode() override;

            Node *condition();
            Node *left();
            Node *right();

            void setCondition(Node *condition);
            void setLeft(Node *left);
            void setRight(Node *right);
        };
    }
}

#endif