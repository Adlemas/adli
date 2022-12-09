#include <astparser.h>

#include <iostream>

using namespace ast;

// Error handling
// Print error message and exit
void Parser::error(const char *msg) {
    std::cout << "ParseError: " << msg << std::endl;
    exit(-1);
}
