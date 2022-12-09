#ifndef TERNARY_NODE_H
#define TERNARY_NODE_H

#include <nodes/node.h>

namespace ast {
    namespace nodes {
        // Ternary node
        // Example: (a > b) ? a : b
        class TernaryNode : public Node
        {
            Node *m_left;
            Node *m_middle;
            Node *m_right;

        public:
            TernaryNode(Node *left, Node *middle, Node *right);
            ~TernaryNode() override;

            Node *left();
            Node *middle();
            Node *right();

            void setLeft(Node *left);
            void setMiddle(Node *middle);
            void setRight(Node *right);
        };
    }
}

#endif