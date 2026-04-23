//
//  parser.cpp
//  forgedb
//
//  Created by Chidume Nnamdi on 14/04/2026.
//

#include "parser.hpp"

void Parser::parse() {
    
}

Token Parser::current() { return tokens[index]; }
Token Parser::next() { return tokens[index + 1]; }

void Parser::advance() { index++; }

bool Parser::eof() {
    return index >= tokens.size() || tokens[index].type == TokenType::END_OF_FILE;
}

bool Parser::match(TokenType type) {
    if (current().type != type) return false;

    advance();
    return true;

}
