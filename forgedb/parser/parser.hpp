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
    
    void parseFunctionCall();
    
    unique_ptr<Expression> parsePrimary();
    unique_ptr<Expression> parseBinary();
    unique_ptr<Expression> parseExpression();
    
    unique_ptr<Expression> parseOr();
    unique_ptr<Expression> parseAnd();
    unique_ptr<Expression> parseComparison();
    
    bool checkValues(std::initializer_list<string> values);
    bool check(std::string value);
    
    unique_ptr<Statement> parseStatement();
    void consumeKeyword(string keyword);
    
    void parseSelectList(Select& select);
    
    void parseFrom(Select& select);
    
    void parseJoins(Select& select);
    
    void parseWhere(Select& select);
    
    void parseGroupBy(Select& select);
    
    void parseHaving(Select& select);
    
    void parseOrderBy(Select& select);
    
    void parseLimit(Select& select);
    
    void parseOffset(Select& select);
    
    bool checkKeyword(string keyword);
    bool matchKeyword(string keyword);
    
    unique_ptr<Expression> parseTerm();
    
    unique_ptr<Expression> parseFactor();
    
    unique_ptr<Expression> parseUnary();
    unique_ptr<Expression> parseEquality();
};

#endif /* parser_hpp */
