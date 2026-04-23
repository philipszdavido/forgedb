//
//  lexer.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 14/04/2026.
//

#ifndef lexer_hpp
#define lexer_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "../token/Token.hpp"

using namespace std;

class Lexer {
public:
    Lexer(const string& sql);
    vector<Token> lex();
    vector<Token> tokens;
    
private:
    const string& sql;
    int index = 0;
    void add(TokenType type, string value);
    void add(TokenType type, const char value);
    
    void collectIdentifier();
    void collectDigit();
    
    bool isWhitespace(char c);
    bool isDigit(char c);
    bool isAlpha(char c);
    
    char current();
    char next(int offset = 1);
    void advance();
    bool eof();


};

#endif /* lexer_hpp */
