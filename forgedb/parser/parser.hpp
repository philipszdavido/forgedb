//
//  parser.hpp
//  forgedb
//
//  Created by Chidume Nnamdi on 14/04/2026.
//

#ifndef parser_hpp
#define parser_hpp

#include <stdio.h>
#include <vector>

#include "../token/Token.hpp"
#include "statements/statement/Statement.hpp"
#include "statements/select/Select.hpp"

class Parser {
    
public:
    Parser(vector<Token>& tokens) : tokens(tokens) {}
    void parse();
    std::vector<unique_ptr<Statement>> stmts;
    
private:
    const std::vector<Token>& tokens;
    size_t index = 0;

    void consumeToken(Token token, string msgError);
    void consumeTokenType(TokenType type, string msgError);
    unique_ptr<Select> parseSelect();
    Token current();
    Token next();
    void advance();
    bool eof();
    bool match(TokenType type);

};

#endif /* parser_hpp */
