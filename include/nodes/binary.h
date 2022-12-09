#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#include <nodes/node.h>
#include <nodes/operator.h>

namespace ast {
    namespace nodes {
        class BinaryNode : public Node {

            Node *m_left;
            Node *m_right;
            Operator m_operator;

        public:
            BinaryNode(Node *left, Node *right);

            BinaryNode(Node *left, Node *right, Operator op);

            ~BinaryNode() override;

            Node *left();

            Node *right();

            Operator op();

            void setLeft(Node *left);

            void setRight(Node *right);

            void setOp(Operator op);
        };
    }
}

#endif