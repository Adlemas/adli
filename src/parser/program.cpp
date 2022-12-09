#include <astparser.h>

using namespace ast;

// Program
// expr* EOF
nodes::StatementsNode *Parser::prog() {
    auto *statements = new nodes::StatementsNode();

    while (m_current_token->type != Token::EOF_) {
        // Comment
        if (m_current_token->type == Token::COMMENT) {
            eat(Token::COMMENT);
            continue;
        }
        statements->addStatement(expr());
        eat(Token::SEMICOLON);
    }

    return statements;
}
