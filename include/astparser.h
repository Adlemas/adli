#ifndef PARSER_H
#define PARSER_H

#include <tokenizer.h>

namespace ast
{

    namespace nodes
    {
        enum _LiteralType
        {
            UNDEFINED,
            INT,
            FLOAT,
            STRING,
            BOOL,
        };
        typedef enum _LiteralType LiteralType;

        // Char string for each literal type
        static const char *LITERAL_TYPE_STRINGS[] = {
            "UNDEFINED",
            "INT",
            "FLOAT",
            "STRING",
            "BOOL",
        };

        enum _NodeType
        {
            BINARY,
            UNARY,
            LITERAL,
            VARIABLE_DECLARATION,
            VARIABLE_ASSIGNMENT,
            VARIABLE,
            TERNARY,
            STATEMENTS,
            // TODO: Implement statement node type
            STATEMENT,
        };
        typedef enum _NodeType NodeType;

        // Char string for each node type
        static const char *NODE_TYPE_STRINGS[] = {
            "BINARY",
            "UNARY",
            "LITERAL",
            "VARIABLE_DECLARATION",
            "VARIABLE_ASSIGNMENT",
            "VARIABLE",
            "TERNARY",
            "STATEMENTS",
            "STATEMENT",
        };

        class Node
        {
            NodeType m_type;

        public:
            Node(NodeType type);

            virtual ~Node() = 0;

            NodeType type();
        };

        class LiteralNode : public Node
        {
            LiteralType m_type;
            void *m_value;

        public:
            LiteralNode(LiteralType type, void *value);
            ~LiteralNode();

            LiteralType literal_type();
            void *value();
        };

        enum _Operator
        {
            NONE,
            PLUS,
            MINUS,
            MULTIPLY,
            DIVIDE,
            MODULO,
        };
        typedef enum _Operator Operator;

        // Char string for each operator
        static const char *OPERATOR_STRINGS[] = {
            "NONE",
            "PLUS",
            "MINUS",
            "MULTIPLY",
            "DIVIDE",
            "MODULO",
        };

        class BinaryNode : public Node
        {

            Node *m_left;
            Node *m_right;
            Operator m_operator;

        public:
            BinaryNode(Node *left, Node *right);
            BinaryNode(Node *left, Node *right, Operator op);
            ~BinaryNode();

            Node *left();
            Node *right();
            Operator op();

            void setLeft(Node *left);
            void setRight(Node *right);
            void setOp(Operator op);
        };

        class UnaryNode : public Node
        {
            Node *m_node;
            Operator m_operator;

        public:
            UnaryNode(Node *node);
            UnaryNode(Node *node, Operator op);
            ~UnaryNode();

            Node *node();
            Operator op();

            void setNode(Node *node);
            void setOp(Operator op);
        };

        // Ternalary node
        class TernaryNode : public Node
        {
            Node *m_left;
            Node *m_middle;
            Node *m_right;

        public:
            TernaryNode(Node *left, Node *middle, Node *right);
            ~TernaryNode();

            Node *left();
            Node *middle();
            Node *right();

            void setLeft(Node *left);
            void setMiddle(Node *middle);
            void setRight(Node *right);
        };

        class StatementsNode : public Node
        {
            std::vector<Node *> *m_statements;
            int m_index = 0;

        public:
            StatementsNode();
            ~StatementsNode();

            void addStatement(Node *statement);
            std::vector<Node *> *statements();

            void reset();
            void next();
            Node *current();

            unsigned long int size();
        };

    }

    class Parser
    {
        Tokenizer *m_tokenizer;
        Token *m_current_token;

        void init();

        static void error(const char *msg);

        void eat(Token::Type type);

        Token::Type peek();

        nodes::Node *factor();

        nodes::Node *term();

        nodes::Node *expr();

        nodes::StatementsNode *prog();

    public:
        Parser(Tokenizer *tokenizer);
        ~Parser();

        nodes::StatementsNode *parse();
    };

} // namespace ast

#endif // PARSER_H