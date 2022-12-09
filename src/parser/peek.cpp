#include <astparser.h>

using namespace ast;

// Peek token
// Get next token's type from tokenizer
// without changing current token
Token::Type Parser::peek() {
    return m_tokenizer->peek_token()->type;
}
