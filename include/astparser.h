#ifndef PARSER_H
#define PARSER_H

#include <tokenizer.h>

#include <nodes/node.h>
#include <nodes/statements.h>
#include <nodes/unary.h>
#include <nodes/literal.h>
#include <nodes/binary.h>
#include <nodes/ternary.h>
#include <nodes/identifier.h>
#include <nodes/statements.h>
#include <nodes/operator.h>

namespace ast
{
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