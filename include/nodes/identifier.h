#ifndef IDENTIFIER_NODE_H
#define IDENTIFIER_NODE_H

#include <nodes/node.h>

namespace ast {
    namespace nodes {
        class IdentifierNode : public Node
        {
            std::string m_name;

        public:
            explicit IdentifierNode(std::string name);
            ~IdentifierNode() override;

            std::string name();
        };
    }
}

#endif