#ifndef AST_DEBUG_H
#define AST_DEBUG_H

#define TABULATION_SIZE 4

#include <iostream>
#include <astparser.h>

void print_nodes(ast::nodes::StatementsNode *node);

void print_node(ast::nodes::Node *node, int tabulation);

#endif