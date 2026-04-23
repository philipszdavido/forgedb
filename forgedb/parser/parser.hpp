//
//  parser.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 14/04/2026.
//

#ifndef parser_hpp
#define parser_hpp

#include <stdio.h>
#include "../token/Token.hpp"

class Parser {
    
public:
    Parser(vector<Token>& tokens) : tokens(tokens) {}
    void parse();
    
private:
    const std::vector<Token>& tokens;
    size_t index = 0;

    Token current();
    Token next();
    void advance();
    bool eof();
    bool match(TokenType type);

};

#endif /* parser_hpp */
