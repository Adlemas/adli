#ifndef NODE_H
#define NODE_H

namespace ast {
    namespace nodes {
        enum NodeType
        {
            BINARY,
            UNARY,
            LITERAL,
            TERNARY,
            STATEMENTS,
            // TODO: Implement statement node type
            STATEMENT,
            VARIABLE_DECLARATION,
            VARIABLE_ASSIGNMENT,
            IDENTIFIER,
        };

        // Char string for each node type
        static const char *NODE_TYPE_STRINGS[] = {
                "BINARY",
                "UNARY",
                "LITERAL",
                "TERNARY",
                "STATEMENTS",
                "STATEMENT",
                "VARIABLE_DECLARATION",
                "VARIABLE_ASSIGNMENT",
                "IDENTIFIER",
        };

        class Node {
            NodeType m_type;

        public:
            explicit Node(NodeType type);

            virtual ~Node() = 0;

            NodeType type();
        };
    }
}

#endif