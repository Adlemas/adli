#ifndef AST_DEBUG_H
#define AST_DEBUG_H

#define TABULATION_SIZE 4

#define TOKEN_NAME_MAX_LENGTH 20

#include <iostream>
#include <astparser.h>

void parse_tokenizer(Tokenizer &tokenizer);

void print_tokens(Tokenizer &tokenizer);

void print_nodes(ast::nodes::StatementsNode *node);

void print_node(ast::nodes::Node *node, int tabulation);

#endif