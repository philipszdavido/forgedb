//
//  TokenType.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 21/04/2026.
//

#ifndef TokenType_hpp
#define TokenType_hpp

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

enum class TokenType {
    
    LEFT_BRACE, RIGHT_BRACE,
    LEFT_PAREN, RIGHT_PAREN,
    LEFT_BRACKET, RIGHT_BRACKET,
    BAD_STRING,
    
    COLON, SEMICOLON,
    COMMA,

    DOT, HASH, IDENT,
    DOUBLE_COLON,
    LEFT_SQUARE_BRACE,
    RIGHT_SQUARE_BRACE,
    GT, LT, PLUS, TILDE,
    PIPE, EQUALS,

    NUMBER,
    DIMENSION,
    PERCENTAGE,
    STRING,
    FUNCTION,
    URL,
    VARIABLE,
    FUNCTION_ARG,
    VALUE_END,
    VALUE_START,
    
    AND, STAR,
    
    KEYWORD,

    WHITESPACE,
    DELIM,
    END_OF_FILE
};

void printTokenType(TokenType type);

#endif /* TokenType_hpp */
