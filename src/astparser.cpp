
#include <astparser.h>

using namespace ast;

// Parser class implementation

// Initialize parser
// Get first token from tokenizer
void Parser::init() {
    m_current_token = m_tokenizer->next_token();
}

// Constructor
// Initialize tokenizer
// Call init function
Parser::Parser(Tokenizer *tokenizer) {
    m_tokenizer = tokenizer;
    m_current_token = nullptr;
    init();
}

// Destructor
Parser::~Parser() = default;

// Main parse function
// Call prog function
nodes::StatementsNode *Parser::parse() {
    return prog();
}