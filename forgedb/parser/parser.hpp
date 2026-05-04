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
#include "expressions/includes.h"
#include "expressions/Binary/Binary.hpp"

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
    
    unique_ptr<Expression> parsePrimary();
    unique_ptr<Expression> parseBinary();
    unique_ptr<Expression> parseExpression();
    
    unique_ptr<Expression> parseOr();
    unique_ptr<Expression> parseAnd();
    unique_ptr<Expression> parseComparison();
    
    bool checkValues(std::initializer_list<string> values);
    bool check(std::string value);
};

#endif /* parser_hpp */
