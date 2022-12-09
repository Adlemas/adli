#ifndef LITERAL_NODE_H
#define LITERAL_NODE_H

#include <nodes/node.h>

namespace ast {
    namespace nodes {
        enum LiteralType {
            UNDEFINED,
            INT,
            FLOAT,
            STRING,
            BOOL,
        };

// Char string for each literal type
        static const char *LITERAL_TYPE_STRINGS[] = {
                "UNDEFINED",
                "INT",
                "FLOAT",
                "STRING",
                "BOOL",
        };

        class LiteralNode : public Node {
            LiteralType m_type;
            void *m_value;

        public:
            LiteralNode(LiteralType type, void *value);

            ~LiteralNode() override;

            LiteralType literal_type();

            void *value();
        };
    }
}

#endif