#ifndef PARSER_H
#define PARSER_H

#include <tokenizer.h>

namespace ast
{

    namespace nodes
    {
        enum LiteralType
        {
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

        enum Operator
        {
            NONE,
            PLUS,
            MINUS,
            MULTIPLY,
            DIVIDE,
            MODULO,
            NOT,
        };

        // Char string for each operator
        static const char *OPERATOR_STRINGS[] = {
                "NONE",
                "PLUS",
                "MINUS",
                "MULTIPLY",
                "DIVIDE",
                "MODULO",
                "NOT",
        };

        class Node
        {
            NodeType m_type;

        public:
            explicit Node(NodeType type);

            virtual ~Node() = 0;

            NodeType type();
        };

        class LiteralNode : public Node
        {
            LiteralType m_type;
            void *m_value;

        public:
            LiteralNode(LiteralType type, void *value);
            ~LiteralNode() override;

            LiteralType literal_type();
            void *value();
        };

        class IdentifierNode : public Node
        {
            std::string m_name;

        public:
            explicit IdentifierNode(std::string name);
            ~IdentifierNode() override;

            std::string name();
        };

        class BinaryNode : public Node
        {

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

    class Parser
    {
        Tokenizer *m_tokenizer;
        Token *m_current_token;

        void init();

        static void error(const char *msg);

        void eat(Token::Type type);

        Token::Type peek();

        nodes::Node *factor(); // UnaryNode | LiteralNode | ParenthesisNode

        nodes::Node *term(); // factor ((MUL | DIV | MODULO) factor)*

        nodes::Node *expr(); // term ((PLUS | MINUS) term)*

        nodes::StatementsNode *prog(); // expr*

    public:
        explicit Parser(Tokenizer *tokenizer);
        ~Parser();

        nodes::StatementsNode *parse();
    };

} // namespace ast

#endif // PARSER_H