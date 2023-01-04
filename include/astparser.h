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

        /**
         * Literal: INT
         * Identifier
         * Parenthesis: '(' expr ')'
         * Unary: '-' factor
         *      | '+' factor
         *      | '!' factor
         */
        nodes::Node *factor();

        /**
         * Factor: factor ('*' | '/' | '%') factor
         */
        nodes::Node *term();

        /**
         * Expr: term ('+' | '-') term
         *     | ternary ('?' expr ':' expr)
         */
        nodes::Node *expr();

        /**
         * Program: statement ';' (statement)*
         */
        nodes::StatementsNode *prog(); // expr*

    public:
        explicit Parser(Tokenizer *tokenizer);
        ~Parser();

        nodes::StatementsNode *parse();
    };

} // namespace ast

#endif // PARSER_H