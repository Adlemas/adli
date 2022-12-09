#ifndef UNARY_NODE_H
#define UNARY_NODE_H

#include <nodes/node.h>
#include <nodes/operator.h>

namespace ast {
    namespace nodes {
        // UnaryNode
        // Example: -1 , !true
        class UnaryNode : public Node
        {
            Node *m_node;
            Operator m_operator;

        public:
            explicit UnaryNode(Node *node);
            UnaryNode(Node *node, Operator op);
            ~UnaryNode() override;

            Node *node();
            Operator op();

            void setNode(Node *node);
            void setOp(Operator op);
        };
    }
}

#endif