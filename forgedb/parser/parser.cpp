//
//  parser.cpp
//  forgedb
//
//  Created by Chidume Nnamdi on 14/04/2026.
//

#include "parser.hpp"
#include "statements/select/Select.hpp"

void Parser::parse() {
    while (!eof()) {
        Token token = current();
        
        if (token.type == TokenType::KEYWORD) {
            if (token.value == "SELECT") {
                parseSelect();
            }
        }
        
        advance();
    }
}

void Parser::parseSelect() {
    auto select = make_unique<Select>();
    
    consumeToken(current(), "Expected SELECT");
    
    // next is columns
    
    if (current().type == TokenType::STAR) {
        
    } else {
        // consume all comma till keyword FROM
    }
}

void Parser::consumeToken(Token token, string msgError) {
    if (current().type == token.type && current().value == token.value && !eof()) {
        return advance();
    }
    throw runtime_error(msgError);
}

void Parser::consumeTokenType(TokenType type, string msgError) {
    if (current().type == type && !eof()) {
        return advance();
    }
    throw runtime_error(msgError);
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
